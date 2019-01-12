/************************************************************************
 * Smart Finder
 * 
 *
 *
 *
************************************************************************/

#include	"common.h"

#define		THREAD_MAX_COUNT	10

pthread_t	THREAD_ID[THREAD_MAX_COUNT];

pthread_mutex_t wait1_mux = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  wait1_evt = PTHREAD_COND_INITIALIZER;

void	*ThreadFinder(void *);
int		MSGSEQ;

int	main(int argc, char *argv[])
{
	int	ret, i;

	/* Read Condition Cfg */

	while(1)
	{
		/* Creat Thread as the number of Conditions */
		for(i = 0; i < THREAD_MAX_COUNT; i++)
		{
			ret = pthread_create (&THREAD_ID[i], NULL, &ThreadFinder, NULL);
		}
	}


	/* Kill Threads */
	for(i = 0; i < THREAD_MAX_COUNT; i++)
	{
		pthread_cancel(THREAD_ID[i]);
	}

	return SUCCESS;
}

void *ThreadFinder(void *arg)
{

	/* Basic Option, Detach Resources */ 
	pthread_detach (pthread_self ());

	while (1)
	{
		pthread_mutex_lock (&wait1_mux);
		pthread_cond_wait (&wait1_evt, &wait1_mux);

		/* If satisfied conditions, Order */

		/* Make Order Message */

		/* Send Message Queue */

		pthread_mutex_unlock (&wait1_mux);

	}

	return;
}


