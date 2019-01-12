#include	"common.h"
#include	"cfginfo.h"
#include	"com_sub.h"

#define		_DEBUG_
int         g_fep_hour;

int main(int argc, char *argv[])
{
	int		ret;
	char	msgbuff[BUF_SIZE_LEN];
	char	FRAMEID[5+1];

	ptr = (struct ST_INFO *)SetSharedMemory();
	OFFSET = atoi(argv[1]);

	while(1)
	{

		ret = recv_msg(PROC(OFFSET).QID, msgbuff, BUF_SIZE_LEN, 0, 0, 0);

		if (ret < 0)
			continue;

		memset (FRAMEID, 0x00, sizeof(FRAMEID));
	    memcpy (FRAMEID, msgbuff, sizeof(FRAMEID)-1);

		g_fep_hour = __IntGetTime();

		/* Processing TR */
		if (memcmp(FRAMEID, "A0034", sizeof(FRAMEID)-1) == 0)
			proc_ptr = &proc_A0034;
		else if (memcmp(FRAMEID, "B6034", sizeof(FRAMEID)-1) == 0)
			proc_ptr = &proc_B6034;
		else if (memcmp(FRAMEID, "A3034", sizeof(FRAMEID)-1) == 0)
			proc_ptr = &proc_A3034;
		else if (memcmp(FRAMEID, "G7034", sizeof(FRAMEID)-1) == 0)
			proc_ptr = &proc_A3034;
		else if (memcmp(FRAMEID, "A6034", sizeof(FRAMEID)-1) == 0)
			proc_ptr = &proc_A6034;
		else if (memcmp(FRAMEID, "A7034", sizeof(FRAMEID)-1) == 0)
			proc_ptr = &proc_A7034;
		else if (memcmp(FRAMEID, "H2034", sizeof(FRAMEID)-1) == 0)
			proc_ptr = &proc_H2034;
		else if (memcmp(FRAMEID, "H3034", sizeof(FRAMEID)-1) == 0)
			proc_ptr = &proc_H3034;
		else if (memcmp(FRAMEID, "N7034", sizeof(FRAMEID)-1) == 0)
			proc_ptr = &proc_N7034;
		else if (memcmp(FRAMEID, "M4034", sizeof(FRAMEID)-1) == 0)
			proc_ptr = &proc_M4034;
		else /* Do Nothing */
		{
		//	_DispLog(LOG_FILE, "[INFO] Not a Proper TR [%s] \n", FRAMEID);
			continue;
		}

		/* Run TR */
		proc_ptr(msgbuff);

#ifdef _DEBUG__
		_DispLog(LOG_FILE, "[INFO] TRANS BUFF [%s] \n", msgbuff);
#endif

	}


	return SUCCESS;

}
