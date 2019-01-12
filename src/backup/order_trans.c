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

KRX_SESSION krx;

int main(int argc, char *argv[])
{
	int		ret;
	char	msgbuff[BUF_SIZE_LEN];

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

		ret = recv_msg(PROC(OFFSET).QID, msgbuff, BUF_SIZE_LEN, 0, 0, 0);

		if (ret > 0)
		{
			Data_Send(msgbuff);
			continue;
		}

		poll_state = poll ((struct pollfd*)&poll_events, 1, POLL_TIME_OUT);

		if(poll_state > 0)
		{
			if(poll_events.revents & POLLIN)
				ret = Data_Recv ();
		}
		else /** Polling Send if there are no transactions in 20 seconds **/
			ret = Data_Send ("POLLSEND");

		poll_events.revents = 0;
		poll_state = 0;

		if (ret < 0)
			exit (0); /* Exit Process */

  }


}

int	Data_Send (char *buf)
{
	ret = select_send(sockfd, buf, TCP_SIZE_LEN);
	if (ret < 0)
	{
	  close(sockfd);
	  _DispLog(LOG_FILE, "[EROR] SELECT SEND ERROR[%d]\n", ret);
	  return 0;
	}

	_DispLog(LOG_FILE, "[INFO] SEND BUF[%s]\n", buf);

}

int	Data_Recv ()
{
  char	buf[TCP_SIZE_LEN];
  int	rt, timeout_flag;

  memset (buf, 0x00, sizeof(buf));
  rt = select_recv(sockfd, buf, sizeof(buf), &timeout_flag);

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

  /** IF it is not POLLING MSQ, Send MSG QUEUE **/

  return;
}

#if 0
KRX_SESSION	Make_Session_Msg(char *tr_code)
{
	
	memset (&krx.header, 0x00, sizeof(krx.header));

	memcpy (krx.header.proto_type, PROTOCOL_TYPE, sizeof(krx.header.proto_type));

	__Int2Str(krx.header.body_len, KRX_SESSION_BODY_LEN, sizeof(krx.header.body_len));

	memcpy (krx.header.msg_type, tr_code, sizeof(krx.header.msg_type));

	__Int2Str(krx.header.msg_seq, SEQ, sizeof(krx.header.msg_seq));
	memcpy (krx.header.compid, COMPANY_ID, sizeof(krx.header.compid));

	memset (krx.header.arr_compid, 0x20, sizeof(krx.header.arr_compid));
	memset (krx.header.send_compid, 0x20, sizeof(krx.header.send_compid));

	memcpy (krx.header.send_time, (char *)__IntGetMillTime(), sizeof(krx.header.send_time));
	
	/* 1건 고정 */
	memcpy (krx.header.data_cnt, "000", sizeof(krx.header.data_cnt));

	krx.header.encrypt_yn[0] = ENCRYPT_N;

	return krx;

}
#endif

int init(char *ipaddr, char *port)
{
  int i=0;

  sockfd = creat_socket();
  if (sockfd < 0)
  {
	_DispLog(LOG_FILE, "[EROR] Failed creat_socket()!!! \n");
    return FAIL;
  } 

  _DispLog(LOG_FILE, "[INFO] Creat Socket SUCCESS!! sockfd[%d] !!! \n", sockfd);

  /** Try to Connect N times **/
  for(i=0; i<MAX_CONNECT_TRY; i++)
  {
	ret = connect_socket(sockfd, ipaddr, atoi(port));
	if (ret < 0)
	{
	  _DispLog(LOG_FILE, "[EROR] Failed Connection : connect_socket() [%d]!!! \n", i+1);
	  close(sockfd);
	  sleep(1);
	  if(i>1) return FAIL;
	}
	else
	  break;
  }


  _DispLog(LOG_FILE, "[INFO] Connection SUCCESS!! IpAddr[%s] Port[%d]!!! \n", ipaddr, atoi(port));
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

