#include	"common.h"
#include	"cfginfo.h"
#include	"shm.h"
#include	"com_sub.h"
#include	"krx.h"

void    Register_Signal (void);
void    Catch_Signal (int);

int	VNF_PLACE(struct NF, int);
int     NL(int, int);
int     check_redundancy(int [], int);




//int	VNF_PLACE(char, int);
//int 	compare (void, void);

int	SumVMs = 0;

int compareCPU (const void *first, const void *second)
{
	const struct	VM *v1 = (const struct VM *)first;
	const struct	VM *v2 = (const struct VM *)second;

	return v1->cpu_usage - v2->cpu_usage;
}

int compareNetwork (const void *first, const void *second)
{
	const struct	VM *v1 = (const struct VM *)first;
	const struct	VM *v2 = (const struct VM *)second;

	return v1->bandwidth_usage - v2->bandwidth_usage;
}

int compareBoth (const void *first, const void *second)
{
	const struct	VM *v1 = (const struct VM *)first;
	const struct	VM *v2 = (const struct VM *)second;

	return (v1->bandwidth_usage - v2->bandwidth_usage)+(v1->cpu_usage - v2->cpu_usage);
}

int main(int argc, char *argv[])
{
	int		ret, i, j, SORTYN;
	char	msgbuff[BUF_SIZE_LEN];
	int	prev_vm_no=0;
	int	FIND_HOST = 0;
	int	min_latency_seq=0;
	int	Idate, Ifromtime=0, Itotime=0;
	int	vmlist[20];
	struct VM_INFO svm;
	struct NF_INFO	nf;

	int	interval = 60;
	int	SumLatency = 0;
	int	MinLatency = 99999999;
	int	MinLatencyVM = 0;
	int	prev_vm_seq=0;
	char	ORDERBY;

	ptr = (struct ST_INFO *)SetST_INFO();
	pvm = (struct VM_INFO *)SetVM_INFO();
	pnf = (struct NF_INFO *)SetNF_INFO();

	SORTYN = atoi(argv[2]);
	ORDERBY = argv[3][0];

	memset(&svm, 0x00, sizeof(struct VM_INFO));
	memset(&nf, 0x00, sizeof(struct NF_INFO));

	memcpy(&svm, pvm, sizeof(struct VM_INFO));

	if (SORTYN == 1) 
	{
		if(ORDERBY == 'C')
			qsort(svm.vm, ptr->VMCount, sizeof(struct VM), compareCPU);
		else if(ORDERBY == 'N')
			qsort(svm.vm, ptr->VMCount, sizeof(struct VM), compareNetwork);
		else if(ORDERBY == 'B')
			qsort(svm.vm, ptr->VMCount, sizeof(struct VM), compareBoth);
	}
		

	if (memcmp(argv[1], "FF", sizeof("FF")) == 0)
	{
		_GetDTime(&Idate, &Ifromtime, 10000);
		for(j=0; j < pnf->nf_count; j++)
		{
			for(i=0; i < ptr->VMCount; i++)
			{
				if(((svm.vm[i].cpu_limit - svm.vm[i].cpu_usage) >= NF(j).cpu_req) && 
				((svm.vm[i].bandwidth_limit - svm.vm[i].bandwidth_usage) >= NF(j).bandwidth_req))
				{
					FIND_HOST = 1;
					VNF_PLACE(NF(j), svm.vm[i].vm_no);

					svm.vm[i].nf_count++;
					svm.vm[i].cpu_usage += NF(j).cpu_req;
					svm.vm[i].bandwidth_usage += NF(j).bandwidth_req;

					break;
				}
			}
			if(FIND_HOST ==	0)
			{
				printf("No Hosts\n");
				return 1;
			}
			else
				FIND_HOST = 0;

			if(check_redundancy(vmlist, svm.vm[i].vm_no) > 0)
				vmlist[SumVMs++]=svm.vm[i].vm_no;

			if(j!=0) 
				SumLatency = SumLatency + NL(prev_vm_no, svm.vm[i].vm_no);

			prev_vm_no = svm.vm[i].vm_no;


		}

		_GetDTime(&Idate, &Itotime, 10000);
		printf("Algorithm = FF SumLatency = %d SumVMs = %d LeadTime(ms) = %d Sorting = %d Orderby = %c \n", SumLatency, SumVMs, Itotime-Ifromtime, SORTYN, ORDERBY);

	}
	else if (memcmp(argv[1], "BF", sizeof("BF")) == 0)
	{
		_GetDTime(&Idate, &Ifromtime, 10000);
                for(j=0; j < pnf->nf_count; j++)
                {
                        for(i=0; i < ptr->VMCount; i++)
                        {
                                if(((svm.vm[i].cpu_limit - svm.vm[i].cpu_usage) >= NF(j).cpu_req) &&
                                ((svm.vm[i].bandwidth_limit - svm.vm[i].bandwidth_usage) >= NF(j).bandwidth_req) &&
				(NL(prev_vm_no, svm.vm[i].vm_no) < MinLatency))
                                {
					if(j==0) 
					{
						FIND_HOST = 1;
						VNF_PLACE(NF(j), svm.vm[i].vm_no);

						svm.vm[i].nf_count++;
						svm.vm[i].cpu_usage += NF(j).cpu_req;
						svm.vm[i].bandwidth_usage += NF(j).bandwidth_req;

						MinLatencyVM = svm.vm[i].vm_no;

						break;
					}
					FIND_HOST = 1;
					MinLatencyVM = svm.vm[i].vm_no;
					min_latency_seq = i;
					MinLatency = NL(prev_vm_no, svm.vm[i].vm_no);
                                }
                        }

			if(FIND_HOST ==	0)
			{
				printf("No Hosts\n");
				return 1;
			}

			if(check_redundancy(vmlist, svm.vm[min_latency_seq].vm_no) > 0)
				vmlist[SumVMs++]=svm.vm[min_latency_seq].vm_no;

                        if(j!=0) 
			{
                                VNF_PLACE(NF(j), MinLatencyVM);

				svm.vm[min_latency_seq].nf_count++;
				svm.vm[min_latency_seq].cpu_usage += NF(j).cpu_req;
				svm.vm[min_latency_seq].bandwidth_usage += NF(j).bandwidth_req;

                                SumLatency += NL(prev_vm_no, MinLatencyVM);
			}

#if 0
			if(j!=0 && (prev_vm_no != MinLatencyVM))
				SumVMs++;
#endif
			if(j!=0)
			{
				prev_vm_no = MinLatencyVM;
			}

			MinLatency = 99999999;
			FIND_HOST = 0;


                }
		_GetDTime(&Idate, &Itotime, 10000);
		printf("Algorithm = BF SumLatency = %d SumVMs = %d LeadTime(ms) = %d Sorting = %d Orderby = %c \n", SumLatency, SumVMs, Itotime-Ifromtime, SORTYN, ORDERBY);

	}
	else if (memcmp(argv[1], "MV", sizeof("MV")) == 0)
	{

                _GetDTime(&Idate, &Ifromtime, 10000);
                for(j=0; j < pnf->nf_count; j++)
                {
                        for(i=0; i < ptr->VMCount; i++)
                        {

				if(prev_vm_no > 0 &&	
                                ((svm.vm[prev_vm_seq].cpu_limit - svm.vm[prev_vm_seq].cpu_usage) >= NF(j).cpu_req) &&
                                ((svm.vm[prev_vm_seq].bandwidth_limit - svm.vm[prev_vm_seq].bandwidth_usage) >= NF(j).bandwidth_req))
				{
                                        FIND_HOST = 2;
                                        VNF_PLACE(NF(j), svm.vm[prev_vm_seq].vm_no);

                                        svm.vm[prev_vm_seq].nf_count++;
                                        svm.vm[prev_vm_seq].cpu_usage += NF(j).cpu_req;
                                        svm.vm[prev_vm_seq].bandwidth_usage += NF(j).bandwidth_req;

					//No Latency 
                                	//SumLatency += NL(prev_vm_no, MinLatencyVM);
                                	//SumLatency += 

                                        break;
				}
                                else if(((svm.vm[i].cpu_limit - svm.vm[i].cpu_usage) >= NF(j).cpu_req) &&
                                ((svm.vm[i].bandwidth_limit - svm.vm[i].bandwidth_usage) >= NF(j).bandwidth_req) &&
                                (NL(prev_vm_no, svm.vm[i].vm_no) < MinLatency) && (prev_vm_seq != i))
                                {
					if(j==0)
					{
						FIND_HOST = 1;
						VNF_PLACE(NF(j), svm.vm[i].vm_no);

						svm.vm[i].nf_count++;
						svm.vm[i].cpu_usage += NF(j).cpu_req;
						svm.vm[i].bandwidth_usage += NF(j).bandwidth_req;

						MinLatencyVM = svm.vm[i].vm_no;
						min_latency_seq = i;

						prev_vm_no = svm.vm[i].vm_no;
						prev_vm_seq = i;

						break;
					}

                                        FIND_HOST = 1;
                                        MinLatencyVM = svm.vm[i].vm_no;
                                        min_latency_seq = i;
                                        MinLatency = NL(prev_vm_no, svm.vm[i].vm_no);
					//prev_vm_no = MinLatencyVM;
					//prev_vm_seq = i;
                                }

                        }

                        if(FIND_HOST == 0)
                        {
                                printf("No Hosts\n");
                                return 1;
                        }

			
			if(check_redundancy(vmlist, svm.vm[min_latency_seq].vm_no) > 0 && FIND_HOST != 2)
				vmlist[SumVMs++]=svm.vm[min_latency_seq].vm_no;

                        if(j!=0 && FIND_HOST == 1)
                        {
                                VNF_PLACE(NF(j), MinLatencyVM);

                                svm.vm[min_latency_seq].nf_count++;
                                svm.vm[min_latency_seq].cpu_usage += NF(j).cpu_req;
                                svm.vm[min_latency_seq].bandwidth_usage += NF(j).bandwidth_req;

                                SumLatency += NL(prev_vm_no, MinLatencyVM);
                        }

#if 0
                        if(j!=0 && (prev_vm_no != MinLatencyVM))
                                SumVMs++;
#endif

			if(j!=0 && FIND_HOST != 2)
			{
				prev_vm_no = MinLatencyVM;
				prev_vm_seq = min_latency_seq;
			}

                        MinLatency = 99999999;
			FIND_HOST = 0;


                }

                _GetDTime(&Idate, &Itotime, 10000);
		printf("Algorithm = MV SumLatency = %d SumVMs = %d LeadTime(ms) = %d Sorting = %d Orderby = %c \n", SumLatency, SumVMs, Itotime-Ifromtime, SORTYN, ORDERBY);


	}
	

	return 1;
}

int	check_redundancy(int lst[], int vm_no)
{
	int i=0;

	for(i=0; i < SumVMs; i++)
	{
		if(lst[i] == vm_no)
			return 0;
	}
	return 1;

}

int	NL(int prev, int curr)
{
	int i=0;
	int prev_vm_index = 0, curr_vm_index=0;
	int Latency = 0;

	if(prev == curr) return 0;

        for(i=0; i< ptr->VMCount; i++)
        {
                if(EVM(i).vm_no == prev)
			prev_vm_index = i;
                else if(EVM(i).vm_no == curr)
			curr_vm_index = i;
        }

	Latency = EVM(prev_vm_index).vNIC_latency + EVM(prev_vm_index).vSwitch_latency 
		+ EVM(curr_vm_index).vNIC_latency + EVM(curr_vm_index).vSwitch_latency;
	
	if(EVM(prev_vm_index).vm_no != EVM(curr_vm_index).vm_no)
	{
		Latency += EVM(prev_vm_index).pNIC_latency + EVM(prev_vm_index).pSwitch_latency 
                + EVM(curr_vm_index).pNIC_latency + EVM(curr_vm_index).pSwitch_latency;
	}
	

	return Latency;

}


int	VNF_PLACE(struct NF nf, int vm_no)
{
	int i=0;
	struct	NF s_nf;

	memset(&s_nf, 0x00, sizeof(struct NF));
	memcpy(&s_nf, &nf, sizeof(struct NF));
	
	for(i=0; i< ptr->VMCount; i++)
	{
		if(EVM(i).vm_no == vm_no)
		{
			EVM(i).nf[EVM(i).nf_count++].nf_no = s_nf.nf_no;
			EVM(i).cpu_usage +=  s_nf.cpu_req;
			EVM(i).bandwidth_usage +=  s_nf.bandwidth_req;

			break;
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

