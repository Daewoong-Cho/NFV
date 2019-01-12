#include	"common.h"
#include	"cfginfo.h"
#include	"shm.h"

FILE    *ReadFd;
char    ReadBuff[256];
struct  ST_INFO *ptr;

int _ReadLine(void);
void _GarbageDel(int start_idx);

int main(int argc, char *argv[])
{

	int		shm_id, icnt=0, i;
	char	sfname[256];
	short	read_size, proc_no, destproc_no, port_no;

	/* Shared Memory Attach */
	ptr = (struct ST_INFO *)SetSharedMemory ();

	printf("ptr address=[%p]\n", ptr);

	sprintf(sfname, "%s/%s", getenv("HOME"), CFG_PATH);
	if ((ReadFd = fopen(sfname, "rb")) == NULL)
	{
		printf("Config file find error. [%s] \n", CFG_PATH);
		return 0;
	}

	/** Initialize Process Infomation **/
	ptr->ProcCount = 0;
	for(i=0; i<MAX_PROC_COUNT; i++)
	{
		    memset(&PROC(i), 0x00, sizeof(PROC(i)));
	}

  while (1)
  {
      read_size = _ReadLine();
      if (read_size == -1)
          break;
      else if (read_size == 0)
          continue;
  
      if (!strncmp(ReadBuff, "ProcNo", strlen("ProcNo")))
      {
          icnt++;
		  ptr->ProcCount++;

          _GarbageDel(strlen("ProcNo"));
          proc_no = (short) atoi(ReadBuff);
          memset(&PROC(icnt-1), 0x00, sizeof(PROC(icnt-1)));
  
          PROC(icnt-1).ProcNo = proc_no;
          printf("proc=%d [%d]\n", proc_no, PROC(icnt-1).ProcNo);
      }

      else if (!strncmp(ReadBuff, "DescProcNo", strlen("DescProcNo")))
      {
          _GarbageDel(strlen("DescProcNo"));
          destproc_no = (short) atoi(ReadBuff);
  
          PROC(icnt-1).DestProcNo = destproc_no;
          printf("proc=%d [%d]\n", destproc_no, PROC(icnt-1).DestProcNo);
      }
      else if (!strncmp(ReadBuff, "ProcType", strlen("ProcType")))
      {
          _GarbageDel(strlen("ProcType"));
          strcpy(PROC(icnt-1).ProcType, ReadBuff);
          printf("proc_type=%s[%s]\n", ReadBuff, PROC(icnt-1).ProcType);
      }
      
      else if (!strncmp(ReadBuff, "ProcName", strlen("ProcName")))
      {
          _GarbageDel(strlen("ProcName"));
          strcpy(PROC(icnt-1).ProcName, ReadBuff);
          printf("name=%s[%s]\n", ReadBuff, PROC(icnt-1).ProcName);
      }

      else if (!strncmp(ReadBuff, "Command", strlen("Command")))
      {
          _GarbageDel(strlen("Command"));
          strcpy(PROC(icnt-1).Command, ReadBuff);
          printf("command=%s[%s]\n", ReadBuff, PROC(icnt-1).Command);
      }

      else if (!strncmp(ReadBuff, "IpAddr", strlen("IpAddr")))
      {
          _GarbageDel(strlen("IpAddr"));
          strcpy(PROC(icnt-1).IpAddr, ReadBuff);
          printf("IpAddr=%s[%s]\n", ReadBuff, PROC(icnt-1).IpAddr);
      }

      else if (!strncmp(ReadBuff, "PortNo", strlen("PortNo")))
      {
          _GarbageDel(strlen("PortNo"));

		  port_no = atoi(ReadBuff);
          PROC(icnt-1).PortNo = (short) port_no;
          printf("PortNo=%d[%d]\n", port_no, PROC(icnt-1).PortNo);
      }

      else if (!strncmp(ReadBuff, "LogFile", strlen("LogFile")))
      {
          _GarbageDel(strlen("LogFile"));
          strcpy(PROC(icnt-1).LogFile, ReadBuff);
          printf("LogFile=%s[%s]\n", ReadBuff, PROC(icnt-1).LogFile);
      }

      else if (!strncmp(ReadBuff, "StartUpFlag", strlen("StartUpFlag")))
      {
          _GarbageDel(strlen("StartUpFlag"));
          PROC(icnt-1).StartUpFlag = atoi(ReadBuff);
          printf("StartUpFlag=%d[%d]\n", atoi(ReadBuff), PROC(icnt-1).StartUpFlag);
  	  }
      else if (!strncmp(ReadBuff, "MaxRevokeCnt", strlen("MaxRevokeCnt")))
      {
          _GarbageDel(strlen("MaxRevokeCnt"));
          PROC(icnt-1).MaxRevokeCnt = atoi(ReadBuff);
          printf("MaxRevokeCnt=%d[%d]\n", atoi(ReadBuff), PROC(icnt-1).MaxRevokeCnt);
  	  }
      
  }

  fclose(ReadFd);

  printf("cfg_load icnt=%d\n", icnt);

}

int _ReadLine(void)
{
    int read_ptr;
    char    one_ch;

    read_ptr = 0;
    memset(ReadBuff, 0x00, sizeof(ReadBuff));

    do
    {
        one_ch = fgetc(ReadFd);

        if (feof(ReadFd))
        {
            return(-1);
        }

        if (one_ch == '#')
        {
            while ((one_ch = fgetc(ReadFd)) != '\n');
            break;
        }
        else
        {
            ReadBuff[read_ptr] = one_ch;
            read_ptr ++;
        }
    } while (one_ch != '\n');

    return(read_ptr);
}


void _GarbageDel(start_idx)
int     start_idx;
{
    int idx, str_size;
    char    TempBuff[256];

    str_size = strlen(ReadBuff);
    memset(TempBuff, 0x00, sizeof(TempBuff));
    memcpy(&TempBuff[0], &ReadBuff[0], str_size);

    for (idx = start_idx; idx < str_size; idx++)
    {
        if (TempBuff[idx] != '\t' && TempBuff[idx] != ' ')
            break;
    }
    memset(ReadBuff, 0x00, sizeof(ReadBuff));
    memcpy(&ReadBuff[0], &TempBuff[idx], str_size - idx - 1);
    /* -1 : '\n' delete */
}
