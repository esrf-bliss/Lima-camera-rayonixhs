#ifndef marccd_signal_h
#define marccd_signal_h

#include "threads.h"

#if defined(_SVID_SOURCE) && !defined(_BSD_COMPAT) && !defined(_BSD_SIGNALS) && !defined(POSIX_SIGNAL_HANDLING)

#if !defined (SYSV_SIGNAL_HANDLING)
#define SYSV_SIGNAL_HANDLING
#endif
#if defined (BSD_SIGNAL_HANDLING)
#undef BSD_SIGNAL_HANDLING
#endif
#if defined (POSIX_SIGNAL_HANDLING)
#undef POSIX_SIGNAL_HANDLING
#endif

#elif defined(_BSD_SIGNALS)

#if defined (SYSV_SIGNAL_HANDLING)
#undef SYSV_SIGNAL_HANDLING
#endif
#if !defined (BSD_SIGNAL_HANDLING)
#define BSD_SIGNAL_HANDLING
#endif
#if defined (POSIX_SIGNAL_HANDLING)
#undef POSIX_SIGNAL_HANDLING
#endif

#else

#if defined (SYSV_SIGNAL_HANDLING)
#undef SYSV_SIGNAL_HANDLING
#endif
#if defined (BSD_SIGNAL_HANDLING)
#undef BSD_SIGNAL_HANDLING
#endif
#if !defined (POSIX_SIGNAL_HANDLING)
#define POSIX_SIGNAL_HANDLING
#endif

#endif


#if defined(SYSV_SIGNAL_HANDLING)
#include <signal.h>
#elif defined(BSD_SIGNAL_HANDLING)
#include <signal.h>
#elif defined(POSIX_SIGNAL_HANDLING)
#include <signal.h>
#else
#include <signal.h>
#endif


#define SIGEXPOSURE SIGUSR1
#define SIGDMADONE  SIGUSR2

#if defined(SYSV_SIGNAL_HANDLING)
   typedef void * sighandler;
#elif defined(BSD_SIGNAL_HANDLING)
   typedef struct sigvec sighandler;
#elif defined(POSIX_SIGNAL_HANDLING)
   typedef struct sigaction sighandler;
#endif

#if defined(SYSV_SIGNAL_HANDLING)
#define SIGNAL_DEFINITIONS(newmask, oldmask)
#define STATIC_SIGNAL_DEFINITIONS(newmask, oldmask)
#elif defined(BSD_SIGNAL_HANDLING)
#define SIGNAL_DEFINITIONS(newmask, oldmask) \
   int oldmask
#define STATIC_SIGNAL_DEFINITIONS(newmask, oldmask) \
   static int oldmask
#elif defined(POSIX_SIGNAL_HANDLING)
#define SIGNAL_DEFINITIONS(newmask, oldmask) \
   sigset_t  newmask, oldmask
#define STATIC_SIGNAL_DEFINITIONS(newmask, oldmask) \
   static sigset_t  newmask, oldmask
#else
  accck!
#endif

#if defined(SYSV_SIGNAL_HANDLING)
#define ignore_sig(sig, newmask, oldmask) \
   sighold(sig)
#elif defined(BSD_SIGNAL_HANDLING)
#define ignore_sig(sig, newmask, oldmask) \
   { oldmask = sigblock(sigmask(sig)); }
#elif defined(POSIX_SIGNAL_HANDLING)
#if defined(MULTI_THREADING) 
   #define ignore_sig(sig, newmask, oldmask) \
   { \
   sigemptyset(&newmask); \
   sigaddset(&newmask, sig); \
   pthread_sigmask(SIG_BLOCK, &newmask, &oldmask); }
#else
   #define ignore_sig(sig, newmask, oldmask) \
   { \
   sigemptyset(&newmask); \
   sigaddset(&newmask, sig); \
   sigprocmask(SIG_BLOCK, &newmask, &oldmask); }
#endif
#else
  accck!
#endif

#if defined(SYSV_SIGNAL_HANDLING)
#define release_sig(sig, oldmask) \
  { sigset (sig, SIG_DFL); \
    sigrelse (sig); }
#elif defined(BSD_SIGNAL_HANDLING)
#define release_sig(sig, oldmask) \
  sigsetmask (oldmask)
#elif defined(POSIX_SIGNAL_HANDLING)
#if defined(MULTI_THREADING) 
   #define release_sig(sig, oldmask) \
   pthread_sigmask(SIG_SETMASK, &oldmask, 0)
#else
   #define release_sig(sig, oldmask) \
   sigprocmask(SIG_SETMASK, &oldmask, 0)
#endif
#else
  accck!
#endif


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

sighandler set_signal(int the_signal, void *signal_handler);

void do_backtrace(int signo);
void do_backtrace_pretty(int signo);
void setup_default_signal_catching(int use_supplied_routine, void *signal_handler);

#endif /* marccd_signal_h */
