#include	"common.h"
#include	"cfginfo.h"
#include	"shm.h"
#include	"com_sub.h"

int		init(char *, char *);
void    Register_Signal (void);
void    Catch_Signal (int);

int main(int argc, char *argv[])
{
	int i;

	ptr = (struct ST_INFO *)SetST_INFO();
	pvm = (struct VM_INFO *)SetVM_INFO();
	pnf = (struct NF_INFO *)SetNF_INFO();

	for(i=0; i < ptr->VMCount; i++)
	{
		EVM(i).cpu_usage = rand() % 4;
		EVM(i).bandwidth_usage = rand() % 50;
		printf("VM%d CPU(%d), NW(%d) \n", i+1, EVM(i).cpu_usage, EVM(i).bandwidth_usage); 

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

