/* Market Data Recv Process*/

#include	"common.h"
#include	"cfginfo.h"
#include	"shm.h"
#include	"com_sub.h"


int		sockfd;
int		ret;
short	clnt_port;
char	clnt_ip[20]; 
struct	pollfd	poll_events;
int		poll_state;
  
int		init(char *, char *);
void    Register_Signal (void);
void    Catch_Signal (int);

int main(int argc, char *argv[])
{

	ptr = (struct ST_INFO *)SetSharedMemory();
	OFFSET = atoi(argv[3]);

	if (argc < 3)
	{
		_DispLog(LOG_FILE, "[EROR] Please Input IpAddr/PortNo \n");
		return FAIL;
	}

	Register_Signal ();
	ret = init(argv[1], argv[2]);

	if (ret < 0)
		exit (0); 

	poll_events.fd		= sockfd;
	poll_events.events	= POLLIN | POLLERR;
	poll_events.revents	= 0;

	while(1)
	{
	
		poll_state = poll ((struct pollfd*)&poll_events, 1, POLL_TIME_OUT);

		if(poll_state > 0)
		{
		  /* Do Nothing */
		  if(poll_events.revents & POLLIN)
			 ret = Data_Recv (); 
		}
		else /** Polling Send if there are no transactions in 20 seconds **/
			continue;
		

		poll_events.revents = 0;
		poll_state = 0;

		if (ret < 0)
		  exit (0); /* Exit Process */

  }


}

int	Data_Send (char *buf)
{
	ret = send_udp (0, sockfd, buf, BUF_SIZE_LEN);
	if (ret < 0)
	{
	  close(sockfd);
	  _DispLog(LOG_FILE, "[EROR] SELECT SEND ERROR[%d]\n", ret);
	  return 0;
	}

	_DispLog(LOG_FILE, "[INFO] SEND BUF[%s]\n", buf);

}

int Data_Recv()
{
  char  buf[BUF_SIZE_LEN];
  int   rt, timeout_flag;
  char  FRAMEID[5+1];

  memset (buf, 0x00, sizeof(buf));
  rt = recv_udp (sockfd, buf);

  memset (FRAMEID, 0x00, sizeof(FRAMEID));
  memcpy (FRAMEID, buf, sizeof(FRAMEID)-1);

  switch (rt)
  {
    case -1:
      _DispLog(LOG_FILE, "[EROR] SELECT ERROR \n");
      return (FAIL);
      break;

    case 0:
      _DispLog(LOG_FILE, "[EROR] TIMEOUT ERROR \n");
      close(sockfd);
      return (FAIL);
      break;

    default:
#ifdef _DEBUG_
      _DispLog(LOG_FILE, "[INFO] RECV BUF[%s] \n", buf);
#endif
      break;
  }

  /* Skip Polling */
  if(memcmp(buf, "I2", 2) == 0)
	  return SUCCESS;

  if( PROC(OFFSET).QID > 0)
	  send_msg(PROC(OFFSET).QID, buf, sizeof(buf), 0);

  return SUCCESS;
}

int init(char *ipaddr, char *port)
{
  //sockfd = open_mcast(ipaddr, atoi(port)); /* Multicast Join */
  sockfd = open_udp (ipaddr, atoi(port)); 

  if (sockfd < 0)
  {
	close(sockfd);
	_DispLog(LOG_FILE, "[EROR] Failed open_client_udp [%d]\n", sockfd);
	return FAIL;
  }

  _DispLog(LOG_FILE, "[INFO] Open SUCCESS!! IpAddr[%s] Port[%d] Sockfd[%d]!!! \n", ipaddr, atoi(port), sockfd);
  return SUCCESS;
  
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
    sleep (2);
	exit(0);
}   /* End of Catch_Signal ()   */

