#ifndef MARCCD_PTHREADS_H
#define MARCCD_PTHREADS_H

#include <pthread.h>

extern pthread_mutex_t SUIDMutex;

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

extern int ncpus(void);

extern int pvt_pthread_create(pthread_t  *  thread, pthread_attr_t * attr, void * (*start_routine)(void *), void * arg);
extern void pvt_pthread_init_thread(void);
extern void pvt_pthread_exit(void *value_ptr);
extern int pvt_pthread_join(pthread_t thread, void **thread_return);
extern int pvt_pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy);

int run_sys_cmd_in_thread(char *command); //Runs command in a thread (blocks) and returns result from command

#endif /* MARCCD_PTHREADS_H */
