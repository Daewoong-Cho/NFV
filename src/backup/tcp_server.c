#include	"common.h"
#include	"cfginfo.h"
#include	"shm.h"
#include	"com_sub.h"

int		sockfd, newfd;
int		ret;
int		clnt_port;
char	clnt_ip[20]; 
struct  pollfd  poll_events;
int     poll_state;
  
int		init(char *);
void    Register_Signal (void);
void    Catch_Signal (int);

int main(int argc, char *argv[])
{

	ptr = (struct ST_INFO *)SetSharedMemory();
	OFFSET = atoi(argv[2]);

	if (argc < 2)
	{
		_DispLog(LOG_FILE, "[ERROR] Please Input PortNo \n");
		return -1;
	}

	Register_Signal ();
	init(argv[1]);


	while(1)
	{
		if(newfd < 1)
		{
		  _DispLog(LOG_FILE, "[INFO] Accepting.... \n");
		  newfd = accept_connection(sockfd, clnt_ip, &clnt_port);

		  poll_events.fd        = newfd;
		  poll_events.events    = POLLIN | POLLERR;
		  poll_events.revents   = 0;

		  if (newfd < 0)
		  {
			_DispLog(LOG_FILE, "[EROR] Accpet Error[%d] \n", newfd);
			sleep (5);
			exit (0);
		  }

		  _DispLog(LOG_FILE, "[INFO] IP[%s] PORT[%d] \n", clnt_ip, clnt_port);

		}

		poll_state = poll ((struct pollfd*)&poll_events, 1, POLL_TIME_OUT);

#ifdef _DEBUG_
	    _DispLog(LOG_FILE, "[INFO] Value of Poll State[%d]\n", poll_state);
#endif

		if(poll_state > 0)
		{
			if(poll_events.revents & POLLIN)
			  ret = Data_Recv ();
		}
		else
			continue;

		if (ret <0)
			return;

	  }


}

int	Data_Recv()
{
  char	buf[TCP_SIZE_LEN];
  int	rt, timeout_flag;

  memset (buf, 0x00, sizeof(buf));
  rt = select_recv(newfd, buf, sizeof(buf), &timeout_flag);

  switch (rt)
  {
	case -1:
	  _DispLog(LOG_FILE, "[EROR] SELECT ERROR \n");
	  return (FAIL);
	  break;
  
	case 0:
	  _DispLog(LOG_FILE, "[EROR] TIMEOUT ERROR \n");
	  close(newfd);
	  return (FAIL);
	  break;
	
	default:
	  _DispLog(LOG_FILE, "[INFO] RECV BUF[%s] \n", buf);
	  break;
  }

  if(memcmp(buf, POLL_SEND, sizeof(POLL_SEND)) == 0)
  {
	memset (buf, 0x00, sizeof(buf));
	memcpy (buf, POLL_RECV, sizeof(POLL_RECV));
	ret = select_send(newfd, buf, TCP_SIZE_LEN);
	if (ret < 0)
	{
		close(newfd);
		  _DispLog(LOG_FILE, "[EROR] SELECT SEND ERROR[%d]\n", ret);
			return 0;
	}

	_DispLog(LOG_FILE, "[INFO] SEND BUF[%s]\n", buf);
  }
  
  return;
}

int init(char *port)
{
  sockfd = creat_socket();
  if (sockfd < 0)
  {
	_DispLog(LOG_FILE, "[EROR] Failed creat_socket()!!! \n");
    return -1;
  } 
  ret = bind_socket(sockfd, atoi(port));
  if (ret < 0)
  {
	_DispLog(LOG_FILE, "[EROR] Failed bind_socket()!!! \n");
    close(sockfd);
    return -1;
  }
  ret = listen_socket(sockfd);
  if (ret < 0)
  {
	_DispLog(LOG_FILE, "[EROR] Failed listen_socket()!!! \n");
    return -1;
  }
  
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
    close (sockfd);
    close (newfd);
    sleep (2);
	exit (0);
}   /* End of Catch_Signal ()   */
