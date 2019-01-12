#ifndef _CFG_INFO_H_
#define _CFG_INFO_H_

#define	MAX_PROC_COUNT	100
#define MAX_PM_COUNT 	100
#define MAX_VM_COUNT 	30
#define MAX_NF_COUNT 	10
#define MAX_COUNT 	10

#define CFG_PROC_SHM	0x0000001000
#define CFG_VM_SHM	0x0000002000
#define CFG_NF_SHM	0x0000003000
#define CFG_PATH	"/cfg/proc.cfg"
#define CONFIG_PATH	"/cfg/config.cfg"
#define NF_PATH		"/cfg/nf.cfg"

struct NF{
	int	nf_no;
	char	nf_name[32];
	int	cpu_req;
	int	bandwidth_req;
};

struct NF_INFO{
	int	nf_count;
	struct	NF	nf[MAX_NF_COUNT];

};

struct VM{
	int	vm_no;
	int	vNIC_no;
	int	vNIC_latency;
	int	vSwitch_no;
	int	vSwitch_latency;
	int	pNIC_no;
	int	pNIC_latency;
	int	pSwitch_no;
	int	pSwitch_latency;
	int	cpu_limit;
	int	cpu_usage;
	int	bandwidth_limit;
	int	bandwidth_usage;
	char	MessageQueueNo[20];
	int	nf_count;
	struct	NF	nf[MAX_NF_COUNT];
};

struct PM{
	int	pm_no;
	int	cpu_limit;
	int	bandwidth_limit;
	int	vm_count;
	struct	VM	vm[MAX_VM_COUNT];
};

struct vNIC{
	int	vNIC_no;
	int	bandwidth;
	char	MessageQueueNo[20];
};

struct vSWITCH{
	int	vSwitch_no;
	char	MessageQueueNo[20];
};

struct pNIC{
        int     pNIC_no;
        int     bandwidth;
	char	MessageQueueNo[20];
};

struct pSWITCH{
        int     pSwitch_no;
	char	MessageQueueNo[20];
};

struct SC{
	int	sc_no;
	char	sc_name[32];
	struct	NF	nf[MAX_NF_COUNT];
};

struct PROC_INFO{
	short	ProcNo;
	short	DestProcNo;
	char	ProcType[32];
	char	ProcName[32];
	int 	StartUpFlag;
	int	LogFlag;
	int 	MaxRevokeCnt;
	int 	RevokeCnt;
	char	Command[256];
	char	IpAddr[16];
	int	PortNo;
	char	MessageQueueNo[20];
	char	LogFile[256];
	int	rcvQID;
	int	sndQID;
	struct		VM		vm; 
	struct		PM		pm; 
	struct		vNIC		vnic; 
	struct		vSWITCH		vswitch; 
	struct		pNIC		pnic; 
	struct		pSWITCH		pswitch; 
};

struct ST_INFO{
	int		ProcCount;
	int		VMCount;
	int		PMCount;
	int		vNICCount;
	int		pNICCount;
	int		vSwitchCount;
	int		pSwitchCount;
	int		vNIC_Latency;
	int		pNIC_Latency;
	int		vSwitch_Latency;
	int		pSwitch_Latency;
	struct		PROC_INFO	proc_info[MAX_PROC_COUNT]; 
};

struct VM_INFO{
	struct		VM		vm[MAX_VM_COUNT]; 
};
struct  ST_INFO *ptr;
struct	VM_INFO	*pvm;
struct	NF_INFO	*pnf;

#define	PROC(i)		ptr->proc_info[i]
#define	VM(i)		ptr->proc_info[i].vm
#define	PM(i)		ptr->proc_info[i].pm
#define	VNIC(i)		ptr->proc_info[i].vnic
#define	VSWITCH(i)	ptr->proc_info[i].vswitch
#define	PNIC(i)		ptr->proc_info[i].pnic
#define	PSWITCH(i)	ptr->proc_info[i].pswitch

#define	EVM(i)		pvm->vm[i]
#define	NF(i)		pnf->nf[i]

#define _PROC_SHM_SET_(shm_key, shm_max_size) {\
	          int uniq_key; \
	          int shm_size; \
	          int shm_id; \
	          char   *shm_addr; \
	          uniq_key = shm_key; \
	          shm_size = shm_max_size; \
	          if( 0> (shm_id= shmget(uniq_key, shm_size, IPC_CREAT | 0666) ) ) \
	              return( (char *)-1); \
	          if( (char *)NULL== (shm_addr= (char *)shmat(shm_id, 0, 0) ) ) \
	              return( (char *)-1); \
	          return( shm_addr ); \
}

#define _DECLARE_PROC_SHM(type, _func_name, shm_key, shm_max_size) \
	          type Set##_func_name() _PROC_SHM_SET_(shm_key, shm_max_size)

_DECLARE_PROC_SHM(char *, ST_INFO,           CFG_PROC_SHM,           sizeof(struct ST_INFO))
_DECLARE_PROC_SHM(char *, VM_INFO,           CFG_VM_SHM,           sizeof(struct VM_INFO))
_DECLARE_PROC_SHM(char *, NF_INFO,           CFG_NF_SHM,           sizeof(struct NF_INFO))

#if 0
#endif

#endif
