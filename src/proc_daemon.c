/*** CFG LOAD, Process Management Daemon ***/

#include	"common.h"
#include    "cfginfo.h"
#include    "shm.h"

#define LOG_FILE  "/home/david/log/proc_daemon.log"

extern struct  ST_INFO *ptr;
extern struct  VM_INFO *pvm;


int main(int argc, char *argv[])
{
	int	i, no;

#if 0
	shm_id = creat_shm(CFG_PROC_SHM, sizeof(struct ST_INFO));

	if (shm_id < 0)
	{
	  printf("Can't get shared memory ID [%d] \n", CFG_PROC_SHM);
	  return 0;
	}
#endif

	/******************************************************************
	 * DECLARE SHM
	 * ***************************************************************/
	ptr = (struct ST_INFO *)SetST_INFO();
	pvm = (struct VM_INFO *)SetVM_INFO();

	/******************************************************************
	 * Creat Message Queue
	 * ***************************************************************/
	for (i=0; i < ptr->ProcCount; i++)
	{
	  PROC(i).rcvQID = CreatMSG(PROC(i).ProcNo);
	  PROC(i).sndQID = CreatMSG(PROC(i).DestProcNo);
	}

	/******************************************************************
	 * Run Process
	 * ***************************************************************/
	_DispLog(LOG_FILE, "[INFO] ptr ProcCount=[%d] \n", ptr->ProcCount);

	while (1)
	{
		for (i=0; i < ptr->ProcCount; i++)
		{
			if (memcmp(PROC(i).ProcType, DEF_VM, sizeof(DEF_VM)) == 0) no = VM(i).vm_no;
			else if (memcmp(PROC(i).ProcType, DEF_VNIC, sizeof(DEF_VNIC)) == 0) no = VNIC(i).vNIC_no;
			else if (memcmp(PROC(i).ProcType, DEF_PNIC, sizeof(DEF_PNIC)) == 0) no = PNIC(i).pNIC_no;
			else if (memcmp(PROC(i).ProcType, DEF_VSWITCH, sizeof(DEF_VSWITCH)) == 0) no = VSWITCH(i).vSwitch_no;
			else if (memcmp(PROC(i).ProcType, DEF_PSWITCH, sizeof(DEF_PSWITCH)) == 0) no = PSWITCH(i).pSwitch_no;

		  if (ProcChk(PROC(i).Command, PROC(i).ProcType, i) != 1 && PROC(i).StartUpFlag == 1 && PROC(i).RevokeCnt <= PROC(i).MaxRevokeCnt)
		  //if (PROC(i).StartUpFlag == 1 && PROC(i).RevokeCnt <= PROC(i).MaxRevokeCnt)
		  {
			  ProcRun(PROC(i).ProcType, i);
			  PROC(i).RevokeCnt++;
		  }

		}
		
		sleep(5);

	}

	_DispLog(LOG_FILE, "[INFO] Process Run Completed [%d] \n", i);

	return;
}

int CreatMSG(int procno)
{
	key_t	q_key;
	int		ret;

	q_key = Q_KEY + procno;
	ret = creat_msg (q_key);

	if (ret < 0) 
		_DispLog(LOG_FILE, "[EROR] Failed creat_msg() [%d] \n", q_key);

	_DispLog(LOG_FILE, "[INFO] Creat MSG Queue Successfully!! QID [%d] \n", ret);

	return ret;
}

int ProcRun(char *type, int seq)
{
	int		ret;
	char	cmd[256];

	if(memcmp(PROC(seq).ProcType, PTP_TCP_CLT, sizeof(PTP_TCP_SVR)) == 0 )
	  sprintf(cmd, "%s/%s %s %d %d &", BIN_PATH, PROC(seq).Command, PROC(seq).IpAddr, PROC(seq).PortNo, seq);
	else if(memcmp(PROC(seq).ProcType, PTP_TCP_SVR, sizeof(PTP_TCP_SVR)) == 0 )
	  sprintf(cmd, "%s/%s %d %d %d & ", BIN_PATH, PROC(seq).Command, PROC(seq).PortNo, seq);

	else if(memcmp(PROC(seq).ProcType, DEF_VM, sizeof(DEF_VM)) == 0 )
	  sprintf(cmd, "%s/%s %s %d %d & ", BIN_PATH, PROC(seq).Command, DEF_VM, seq, VM(seq).vm_no);
	else if(memcmp(PROC(seq).ProcType, DEF_VNIC, sizeof(DEF_VNIC)) == 0 )
	  sprintf(cmd, "%s/%s %s %d %d & ", BIN_PATH, PROC(seq).Command, DEF_VNIC, seq, VNIC(seq).vNIC_no);
	else if(memcmp(PROC(seq).ProcType, DEF_PNIC, sizeof(DEF_PNIC)) == 0 )
	  sprintf(cmd, "%s/%s %s %d %d & ", BIN_PATH, PROC(seq).Command, DEF_PNIC, seq, PNIC(seq).pNIC_no);
	else if(memcmp(PROC(seq).ProcType, DEF_VSWITCH, sizeof(DEF_VSWITCH)) == 0 )
	  sprintf(cmd, "%s/%s %s %d %d & ", BIN_PATH, PROC(seq).Command, DEF_VSWITCH, seq, VSWITCH(seq).vSwitch_no);
	else if(memcmp(PROC(seq).ProcType, DEF_PSWITCH, sizeof(DEF_PSWITCH)) == 0 )
	  sprintf(cmd, "%s/%s %s %d %d & ", BIN_PATH, PROC(seq).Command, DEF_PSWITCH, seq, PSWITCH(seq).pSwitch_no);
	else
	  sprintf(cmd, "%s/%s %d &", BIN_PATH, PROC(seq).Command, seq);

	ret = system(cmd);

	if (ret < 0)
		_DispLog(LOG_FILE, "[EROR] Failed Excuting Process[%d][%s] \n", ret, cmd);
	
	_DispLog(LOG_FILE, "#############Excuting Process[%s]############ ", cmd);
	_DispLog(LOG_FILE, "ProcNo   : [%d] ", PROC(seq).ProcNo);
	_DispLog(LOG_FILE, "ProcName : [%s] ", PROC(seq).ProcName);
	_DispLog(LOG_FILE, "ProcType : [%s] ", PROC(seq).ProcType);
	_DispLog(LOG_FILE, "LogFile  : [%s] ", PROC(seq).LogFile);
	_DispLog(LOG_FILE, "cmd  : [%s] ", cmd);
	_DispLog(LOG_FILE, "############################################# \n");

	return ret;
}

int ProcChk(char *cmdbuf, char *cmdbuf2, int no)
{
	FILE    *fp;
	char    cmd[512], buf[512], pro_buf[20][256];
	char    pidbuf[20], ppidbuf[20];
	int     findflag=0, pid, ppid;

	memset(cmd, 0x00, sizeof(cmd));
	memset(buf, 0x00, sizeof(buf));
	sprintf(cmd, "ps -ef|grep \"%s %s %d\" | grep -v \"grep\" |grep -v \"gdb\" | sed '/vim/d'|sed '/tail/d'|sed '/grep/d'|sed '/remsh/d'|sed '/rsh/d'|sed '/rcp/d'|sed '/remcp/d'", cmdbuf, cmdbuf2, no);

	if ((fp = popen(cmd, "r")) != NULL)
	{
	  while ((fgets(buf, 512, fp)) != NULL)
	  {
		memset(pro_buf, 0x00, sizeof(pro_buf));
		sscanf(buf,"%s%s%s%s%s"
		,pro_buf[0], pro_buf[1], pro_buf[2], pro_buf[3], pro_buf[4] );
		pid = atoi(pro_buf[1]);
		if (pid == getpid())
		continue;
		findflag = 1;
	  }
	  pclose(fp);
	}
	return (findflag);
}
