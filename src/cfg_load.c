#include	"common.h"
#include	"cfginfo.h"
#include	"shm.h"

FILE    *ReadFd;
char    ReadBuff[256];
struct  ST_INFO *ptr;
struct	VM_INFO	*pvm;

int _ReadLine(void);
void _GarbageDel(int start_idx);

int main(int argc, char *argv[])
{

	int		shm_id, icnt=0, i, icnt_vm=0, icnt_nf=0;
	char	sfname[256], sfname1[256], sfname2[256];
	short	read_size, proc_no, destproc_no, port_no;

	/* Shared Memory Attach */
	ptr = (struct ST_INFO *)SetST_INFO ();
	pvm = (struct VM_INFO *)SetVM_INFO ();
	pnf = (struct NF_INFO *)SetNF_INFO ();

	printf("ptr address=[%p]\n", ptr);
	printf("pvm address=[%p]\n", pvm);
	printf("pnf address=[%p]\n", pnf);

	sprintf(sfname, "%s/%s", getenv("HOME"), CFG_PATH);
	sprintf(sfname1, "%s/%s", getenv("HOME"), CONFIG_PATH);
	sprintf(sfname2, "%s/%s", getenv("HOME"), NF_PATH);

	if ((ReadFd = fopen(sfname, "rb")) == NULL)
	{
		printf("Config file find error. [%s] \n", CFG_PATH);
		return 0;
	}

	/** Initialize Process Infomation **/
	ptr->ProcCount = 0;
	ptr->VMCount = 0;
	ptr->vNICCount = 0;
	ptr->pNICCount = 0;
	ptr->vSwitchCount = 0;
	ptr->pSwitchCount = 0;

	pnf->nf_count = 0;

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

	  if (memcmp(PROC(icnt-1).ProcType, "VM", sizeof("VM")) == 0)
		ptr->VMCount++;
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

      else if (!strncmp(ReadBuff, "CPU_Limit", strlen("CPU_Limit")))
      {
          _GarbageDel(strlen("CPU_Limit"));

          VM(icnt-1).cpu_limit = atoi(ReadBuff);
          printf("CPU_Limit=%d[%d]\n", atoi(ReadBuff), VM(icnt-1).cpu_limit);
      }

      else if (!strncmp(ReadBuff, "Band_Limit", strlen("Band_Limit")))
      {
          _GarbageDel(strlen("Band_Limit"));

          VM(icnt-1).bandwidth_limit = atoi(ReadBuff);
          printf("Band_Limit=%d[%d]\n", atoi(ReadBuff), VM(icnt-1).bandwidth_limit);
      }

      else if (!strncmp(ReadBuff, "LogFile", strlen("LogFile")))
      {
          _GarbageDel(strlen("LogFile"));
          strcpy(PROC(icnt-1).LogFile, ReadBuff);
          printf("LogFile=%s[%s]\n", ReadBuff, PROC(icnt-1).LogFile);
	  if (memcmp(PROC(icnt-1).ProcType, "VM", sizeof("VM")) == 0)
	{
		memset(&EVM(icnt_vm), 0x00, sizeof(EVM(icnt_vm)));
		EVM(icnt_vm++) = VM(icnt-1);
	}
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
      else if (!strncmp(ReadBuff, "VMNo", strlen("VMNo")))
      {
          _GarbageDel(strlen("VMNo"));
	  VM(icnt-1).vm_no = atoi(ReadBuff);
	  printf("VMNo=%d[%d]\n", atoi(ReadBuff), VM(icnt-1).vm_no);
      }
      else if (!strncmp(ReadBuff, "vNICNo", strlen("vNICNo")))
      {
          _GarbageDel(strlen("vNICNo"));
	
	  if (memcmp(PROC(icnt-1).ProcType, "VM", sizeof("VM")) == 0)
	{
		  VM(icnt-1).vNIC_no = atoi(ReadBuff);
		  printf("vNICNo=%d[%d]\n", atoi(ReadBuff), VM(icnt-1).vNIC_no);
	}
	  else if (memcmp(PROC(icnt-1).ProcType, "vNIC", sizeof("vNIC")) == 0)
	{
		  ptr->vNICCount++;
		  VNIC(icnt-1).vNIC_no = atoi(ReadBuff);
		  printf("vNICNo=%d[%d]\n", atoi(ReadBuff), VNIC(icnt-1).vNIC_no);
	}
      }
      else if (!strncmp(ReadBuff, "vSwitchNo", strlen("vSwitchNo")))
      {
          _GarbageDel(strlen("vSwitchNo"));
	  if (memcmp(PROC(icnt-1).ProcType, "VM", sizeof("VM")) == 0)
	{
		  VM(icnt-1).vSwitch_no = atoi(ReadBuff);
		  printf("vSwitchNo=%d[%d]\n", atoi(ReadBuff), VM(icnt-1).vSwitch_no);
	}
	  else if (memcmp(PROC(icnt-1).ProcType, "vSwitch", sizeof("vSwitch")) == 0)
	{
		  ptr->vSwitchCount++;
		  VSWITCH(icnt-1).vSwitch_no = atoi(ReadBuff);
		  printf("vSwitchNo=%d[%d]\n", atoi(ReadBuff), VSWITCH(icnt-1).vSwitch_no);
	}
      }

      else if (!strncmp(ReadBuff, "pNICNo", strlen("pNICNo")))
      {
          _GarbageDel(strlen("pNICNo"));
	  if (memcmp(PROC(icnt-1).ProcType, "VM", sizeof("VM")) == 0)
	{
		  VM(icnt-1).pNIC_no = atoi(ReadBuff);
		  printf("pNICNo=%d[%d]\n", atoi(ReadBuff), VM(icnt-1).pNIC_no);
	}
	  else if (memcmp(PROC(icnt-1).ProcType, "pNIC", sizeof("pNIC")) == 0)
	{
		  ptr->pNICCount++;
		  PNIC(icnt-1).pNIC_no = atoi(ReadBuff);
		  printf("vNICNo=%d[%d]\n", atoi(ReadBuff), PNIC(icnt-1).pNIC_no);
	}
      }

      else if (!strncmp(ReadBuff, "pSwitchNo", strlen("pSwitchNo")))
      {
          _GarbageDel(strlen("pSwitchNo"));
	  if (memcmp(PROC(icnt-1).ProcType, "VM", sizeof("VM")) == 0)
	{
		  VM(icnt-1).pSwitch_no = atoi(ReadBuff);
		  printf("pSwitchNo=%d[%d]\n", atoi(ReadBuff), VM(icnt-1).pSwitch_no);
	}
	  else if (memcmp(PROC(icnt-1).ProcType, "pSwitch", sizeof("pSwitch")) == 0)
	{
		  ptr->pSwitchCount++;
		  PSWITCH(icnt-1).pSwitch_no = atoi(ReadBuff);
		  printf("pSwitchNo=%d[%d]\n", atoi(ReadBuff), PSWITCH(icnt-1).pSwitch_no);
	}
      }
      
      
  }

  fclose(ReadFd);

  printf("cfg_load icnt=%d\n", icnt);


        sprintf(sfname1, "%s/%s", getenv("HOME"), CONFIG_PATH);
        if ((ReadFd = fopen(sfname1, "rb")) == NULL)
        {
                printf("Config file find error. [%s] \n", CONFIG_PATH);
                return 0;
        }

  while (1)
  {
      read_size = _ReadLine();
      if (read_size == -1)
          break;
      else if (read_size == 0)
          continue;

      if (!strncmp(ReadBuff, "vNIC_Latency", strlen("vNIC_Latency")))
      {
          _GarbageDel(strlen("vNIC_Latency"));

          ptr->vNIC_Latency = (short) atoi(ReadBuff);
          printf("vNIC_Latency=%d\n", ptr->vNIC_Latency);
      }
      else if (!strncmp(ReadBuff, "vSwitch_Latency", strlen("vSwitch_Latency")))
      {
          _GarbageDel(strlen("vSwitch_Latency"));

          ptr->vSwitch_Latency = (short) atoi(ReadBuff);
          printf("vSwitch_Latency=%d\n", ptr->vSwitch_Latency);
      }
      if (!strncmp(ReadBuff, "pNIC_Latency", strlen("pNIC_Latency")))
      {
          _GarbageDel(strlen("pNIC_Latency"));

          ptr->pNIC_Latency = (short) atoi(ReadBuff);
          printf("pNIC_Latency=%d\n", ptr->pNIC_Latency);
      }
      else if (!strncmp(ReadBuff, "pSwitch_Latency", strlen("pSwitch_Latency")))
      {
          _GarbageDel(strlen("pSwitch_Latency"));

          ptr->pSwitch_Latency = (short) atoi(ReadBuff);
          printf("pSwitch_Latency=%d\n", ptr->pSwitch_Latency);
      }
  }

  fclose(ReadFd);

  printf("config_load\n");

        if ((ReadFd = fopen(sfname2, "rb")) == NULL)
        {
                printf("Config file find error. [%s] \n", NF_PATH);
                return 0;
        }

        while(1)
        {
                read_size = _ReadLine();
                if (read_size == -1)
                  break;
                else if (read_size == 0)
                  continue;

		if (!strncmp(ReadBuff, "NF_NO", strlen("NF_NO")))
		{
		  icnt_nf++;
		  memset(&NF(icnt_nf-1), 0x00, sizeof(NF(icnt_nf-1)));
		  pnf->nf_count++;

		  _GarbageDel(strlen("NF_NO"));

		  NF(icnt_nf-1).nf_no = atoi(ReadBuff);
		  printf("NF_NO=%d [%d]\n", atoi(ReadBuff), NF(icnt_nf-1).nf_no);
		}

		else if (!strncmp(ReadBuff, "NF_NAME", strlen("NF_NAME")))
		{
		  _GarbageDel(strlen("NF_NAME"));
		  strcpy(NF(icnt_nf-1).nf_name, ReadBuff);
		  printf("NF_NAME=%s[%s]\n", ReadBuff, NF(icnt_nf-1).nf_name);
		}

		else if (!strncmp(ReadBuff, "CPU_REQ", strlen("CPU_REQ")))
		{
		  _GarbageDel(strlen("CPU_REQ"));

		  NF(icnt_nf-1).cpu_req = atoi(ReadBuff);
		  printf("CPU_REQ=%d [%d]\n", atoi(ReadBuff), NF(icnt_nf-1).cpu_req);
		}
		else if (!strncmp(ReadBuff, "BANDWIDTH_REQ", strlen("BANDWIDTH_REQ")))
		{
		  _GarbageDel(strlen("BANDWIDTH_REQ"));

		  NF(icnt_nf-1).bandwidth_req = atoi(ReadBuff);
		  printf("BANDWIDTH_REQ=%d [%d]\n", atoi(ReadBuff), NF(icnt_nf-1).bandwidth_req);
		}

	}

  fclose(ReadFd);

  printf("nf_load\n");

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
