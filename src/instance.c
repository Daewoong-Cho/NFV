#include	"common.h"
#include	"cfginfo.h"
#include	"shm.h"
#include	"com_sub.h"
#include	"krx.h"

int		sockfd;
int		ret;
short	clnt_port;
char	clnt_ip[20]; 
struct	pollfd	poll_events;
int		poll_state;
  
int		init(char *, char *);
void    Register_Signal (void);
void    Catch_Signal (int);

int	interval = 60;

int main(int argc, char *argv[])
{
	int		ret, i, KEY;
	char	msgbuff[BUF_SIZE_LEN];

	ptr = (struct ST_INFO *)SetST_INFO();
	pvm = (struct VM_INFO *)SetVM_INFO();
	OFFSET = atoi(argv[2]);
	KEY = atoi(argv[3]);

	
	while(1)
	{
		if (memcmp(argv[1], "VM", sizeof("VM")) == 0)
		{
			_DispLog(LOG_FILE, "[INFO][VM%d] CPU Usage[%d], Network Usage[%d], NF Count[%d] \n", KEY, EVM(KEY-1).cpu_usage, EVM(KEY-1).bandwidth_usage, EVM(KEY-1).nf_count);
			_DispLog(LOG_FILE, "[INFO][VM%d] vNIC_Latency[%d], pNIC_Latency[%d], vSwitch_latency[%d],pSwitch_latency[%d] \n", KEY, EVM(KEY-1).vNIC_latency, EVM(KEY-1).pNIC_latency, EVM(KEY-1).vSwitch_latency, EVM(KEY-1).pSwitch_latency);
			sleep (interval);
		}
			
		else if (memcmp(argv[1], "vNIC", sizeof("vNIC")) == 0)
		{
			for(i=0; i< ptr->VMCount; i++)
			{
				if(EVM(i).vNIC_no == KEY)
				{
					EVM(i).vNIC_latency = ptr->vNIC_Latency + (rand() % 4);
					_DispLog(LOG_FILE, "[UPDATE][vNIC%d] vNIC_Latency(%d)\n", KEY, EVM(i).vNIC_latency);
				}
			}
			sleep (interval);
		}
		else if (memcmp(argv[1], "pNIC", sizeof("pNIC")) == 0)
		{
			for(i=0; i< ptr->VMCount; i++)
			{
				if(EVM(i).pNIC_no == KEY)
				{
					EVM(i).pNIC_latency = ptr->pNIC_Latency + (rand() % 4);
					_DispLog(LOG_FILE, "[UPDATE][pNIC%d] pNIC_Latency(%d) \n", KEY, EVM(i).pNIC_latency);
				}
			}
			sleep (interval);
		}
		else if (memcmp(argv[1], "vSwitch", sizeof("vSwitch")) == 0)
		{
			for(i=0; i< ptr->VMCount; i++)
			{
				if(EVM(i).vSwitch_no == KEY)
				{
					EVM(i).vSwitch_latency = ptr->vSwitch_Latency + (rand() % 4);
					_DispLog(LOG_FILE, "[UPDATE][vSwitch%d] vSwitch_Latency(%d) \n", KEY, EVM(i).vSwitch_latency);
				}
			}
			sleep (interval);
		}
                else if (memcmp(argv[1], "pSwitch", sizeof("pSwitch")) == 0)
                {
                        for(i=0; i< ptr->VMCount; i++)
                        {
                                if(EVM(i).pSwitch_no == KEY)
                                {
                                        EVM(i).pSwitch_latency = ptr->pSwitch_Latency + (rand() % 4);
                                        _DispLog(LOG_FILE, "[UPDATE][pSwitch%d] pSwitch_Latency(%d) \n", KEY, EVM(i).pSwitch_latency);
                                }
                        }
                        sleep (interval);
		}
                
	}
		
	return 1;
}

/*************************************************************************
    Function        : . Register_Signal
    Parameters IN   : .
    Parameters OUT  : .
    Return Code     : . void
    Comment         : . register signals
*************************************************************************/
/*----------------------------------------------------------------------*/
void    Register_Signal (void)
/*----------------------------------------------------------------------*/
{
    struct sigaction    act;

    sigemptyset (&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = Catch_Signal;

    if (sigaction (SIGPIPE, &act, NULL) < 0)
    {
        _DispLog(LOG_FILE, "[EROR] sigaction (SIGPIPE) {%d:%s}", SYS_NO, SYS_STR);
        return;
    }

    if (sigaction (SIGTERM, &act, NULL) < 0)
    {
        _DispLog(LOG_FILE, "[EROR] sigaction (SIGTERM) {%d:%s}", SYS_NO, SYS_STR);
        return;
    }

    if (sigaction (SIGUSR2, &act, NULL) < 0)
    {
        _DispLog(LOG_FILE, "[EROR] sigaction (SIGUSR2) {%d:%s}", SYS_NO, SYS_STR);
        return;
    }

    if (sigaction (SIGILL, &act, NULL) < 0)
    {
        _DispLog(LOG_FILE, "[EROR] sigaction (SIGILL) {%d:%s}", SYS_NO, SYS_STR);
        return;
    }

    return;
}   /* End of Register_Signal ()    */

/*************************************************************************
    Function        : . Catch_Signal
    Parameters IN   : . signo : signal number
    Parameters OUT  : .
    Return Code     : . void
    Comment         : . catch signal
*************************************************************************/
/*----------------------------------------------------------------------*/
void    Catch_Signal (int signo)
/*----------------------------------------------------------------------*/
{
    _DispLog(LOG_FILE, "[EROR] signal (%d) occurred", signo);
    sleep (2);
	exit(0);
}   /* End of Catch_Signal ()   */

