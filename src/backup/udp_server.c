/* Market Data Send_side Process */

#include	"common.h"
#include	"cfginfo.h"
#include	"shm.h"
#include	"com_sub.h" 

int		sockfd;
int		ret;
int		clnt_port;
char	clnt_ip[20]; 
struct  pollfd  poll_events;
int     poll_state;
  
int		init(char *, char *);
void    Register_Signal (void);
void    Catch_Signal (int);

FILE	*ReadFd;
char	sfname[256];
char	ReadBuff[BUF_SIZE_LEN];
int		read_size;

long	iCnt = 0;

struct  sockaddr_in sendaddr;

int main(int argc, char *argv[])
{

	sleep(15);
	ptr = (struct ST_INFO *)SetSharedMemory();
	OFFSET = atoi(argv[3]);

	if (argc < 3)
	{
		_DispLog(LOG_FILE, "[ERROR] Please Input IpAddr/PortNo \n");
		return -1;
	}

	Register_Signal ();
	init(argv[1], argv[2]);

	poll_events.fd        = sockfd;
	poll_events.events    = POLLIN | POLLERR;
	poll_events.revents   = 0;

#if 1

	sprintf(sfname, "%s/%s", getenv("HOME"), "dat/TEST_DATA");
	if ((ReadFd = fopen(sfname, "rb")) == NULL)
	{
		printf("Data file find error. [%s] \n", "dat/TEST_DATA");
		return 0;
	}

	sendaddr.sin_family      = AF_INET;
	sendaddr.sin_addr.s_addr = inet_addr("10.0.2.15");
	sendaddr.sin_port        = htons(30002);

#endif

	while(1)
	{

		poll_state = poll ((struct pollfd*)&poll_events, 1, POLL_TIME_OUT);
		//poll_state = poll ((struct pollfd*)&poll_events, 1, 5);

		if(poll_state > 0)
		{
			if(poll_events.revents & POLLIN)
			  ret = Data_Recv ();
		}
		else
		{
			read_size = _ReadLine();
			if (read_size == -1)
				continue;
			else if (read_size == 0)
				continue;

			iCnt++;
			ret = Data_Send(&ReadBuff[45]);

		}

	}


}

int Data_Send (char *buf)
{
	ret = send_udp (0, sockfd, buf, BUF_SIZE_LEN);

	if (ret < 0)
	{
		close(sockfd);
		_DispLog(LOG_FILE, "[EROR] SELECT SEND ERROR[%d]\n", ret);
		return 0;
	}

	_DispLog(LOG_FILE, "[INFO] SEND BUF[%s][%d]\n", buf, iCnt);
#ifdef _DEBUG_
#endif

}
int	Data_Recv()
{
  char	buf[BUF_SIZE_LEN];
  int	rt, timeout_flag;
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
	  _DispLog(LOG_FILE, "[INFO] RECV BUF[%s] \n", buf);
	  break;
  }

  return SUCCESS;
}

int init(char *ipaddr, char *port)
{
  //sockfd = open_udp(atoi(port));
  sockfd = open_mcast_sender(ipaddr, atoi(port));

  if (ret < 0)
  {
	_DispLog(LOG_FILE, "[EROR] Failed open_udp()!!! \n");
    return -1;
  }

  _DispLog(LOG_FILE, "[INFO] SUCCESS open_udp()!!! \n");

  return SUCCESS;

#if 0
  ret = listen_socket(sockfd);
  if (ret < 0)
  {
	_DispLog(LOG_FILE, "[EROR] Failed listen_socket()!!! \n");
    return -1;
  }
#endif
  
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
	exit (0);
}   /* End of Catch_Signal ()   */


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
