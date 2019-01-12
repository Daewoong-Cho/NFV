#ifndef _COMMON_H_
#define _COMMON_H_

#include	<stdio.h>

#include	<memory.h>
#include	<stdarg.h>
#include	<time.h>
#include	<signal.h>
#include	<sys/poll.h>
#include	<sys/select.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<stdlib.h>
#include	<fcntl.h>
#include	<math.h>

#include	<errno.h>

/* IPC headers */
#include	<sys/ipc.h>
#include	<sys/msg.h>
#include	<sys/shm.h>

/* TCP/IP headers   */
#include	<sys/socket.h>
#include 	<netinet/in.h>
#include 	<arpa/inet.h>
#include 	<netdb.h>

#include	<pthread.h>
#include 	<time.h>

/*------------------------------------------------------------------------
	Define
------------------------------------------------------------------------*/
#define TM_YEAR_BASE	1900
#define	SYS_NO			errno
#define	SYS_STR			strerror(errno)

#define	FAIL			-1
#define	SUCCESS			1
#define	TCP_TIME_OUT	30
#define	POLL_TIME_OUT	20 * 1000
#define	TIME_OUT_FLAG	0

#define	TCP_SIZE_LEN	1024
#define	BUF_SIZE_LEN	4096

#define	MAX_CONNECT_TRY	3
#define	POLL_SEND		"POLLSEND"
#define	POLL_RECV		"POLLRECV"
#define	BIN_PATH		"/home/david/bin"

#define DEF_VM			"VM"
#define DEF_VNIC		"vNIC"
#define DEF_PNIC		"pNIC"
#define DEF_VSWITCH		"vSwitch"
#define DEF_PSWITCH		"pSwitch"

#define PTP_TCP_SVR		"TCP_SERVER"
#define PTP_TCP_CLT		"TCP_CLIENT"

#define PTP_UDP_SVR		"UDP_SERVER"
#define PTP_UDP_CLT		"UDP_CLIENT"


#define	Q_KEY			30000

/*------------------------------------------------------------------------
	Function Prototypes
------------------------------------------------------------------------*/
int		creat_msg (key_t);
int		creat_excl_msg (key_t);
int		send_msg (int, void *, int, int);
int		recv_msg (int, void *, int, int, int, int);
int		remove_msg (int);

int		creat_shm (key_t, size_t);
int		creat_excl_shm (key_t, size_t);
char	*attach_shm (int);
void	detach_shm (char *);
int		remove_shm (int);

void	_DispLog(char *, char *, ...);
void	_GetDTime(int *, int *, int);
	
int		(*proc_ptr)(char *);


/*------------------------------------------------------------------------
	Structure
------------------------------------------------------------------------*/

/*------------------------------------------------------------------------
	Extern
------------------------------------------------------------------------*/

extern int proc_A0034(char *org_data);
extern int proc_B6034(char *org_data);
extern int proc_A3034(char *org_data);
extern int proc_A6034(char *org_data);
extern int proc_A7034(char *org_data);
extern int proc_H2034(char *org_data);
extern int proc_H3034(char *org_data);
extern int proc_N7034(char *org_data);
extern int proc_M4034(char *org_data);

extern struct KOSPI200_OPT_INFO *koshm;

#if 0
extern struct  ST_INFO *ptr;
extern struct  KOSPI200_OPT_INFO *koshm;
#endif

#endif

//대비부호 정의
typedef enum
{
      VRSS_SIGN_DEFAULT     = '0' // 초기값
    , VRSS_SIGN_HIGHEST     = '1' // 상한
    , VRSS_SIGN_ASCENT      = '2' // 상승
    , VRSS_SIGN_STEADY      = '3' // 보합
    , VRSS_SIGN_LOWEST      = '4' // 하한
    , VRSS_SIGN_DESCENT     = '5' // 하락
    , VRSS_SIGN_ANTC_ASCENT = '6' // 예상체결 상승
    , VRSS_SIGN_ANTC_STEADY = '7' // 예상체결 보합
    , VRSS_SIGN_ANTC_DESCENT= '8' // 예상체결 하락
} MARKET_VRSS_SIGN;
