#ifndef CRASHDUMPER_H
#define CRASHDUMPER_H

#include <signal.h>
#include <execinfo.h>
#include <stdio.h>

#include "RxLog.h"

namespace craydl {

const int MAX_STACKFRAMES = 75;

//! This function called by the signal handler.  Use printBacktraceOnSignal
//  to register stack trace print for a signal.
static void printBacktrace_(int signo) {
	void *stack[MAX_STACKFRAMES];
	char **functions;

	int count, i;

        printf("Program caught signal %d.  Here is a backtrace:\n", signo);

	count = backtrace(stack, MAX_STACKFRAMES);
	functions = backtrace_symbols(stack, count);
	for (i=0; i < count; i++) {
	   RxLog(LOG_SYSTEM) << "Frame" << std::setfill('0') << std::right << std::setw(2) << i << ": " << functions[i] << std::endl;
	}
		//printf("Frame %2d: %s\n", i, functions[i]);
	free(functions);
	// restore default action for this signal, and then deliver the signal again
	//signal(signo, SIG_DFL);
	struct sigaction saction;
	memset(&saction, 0, sizeof(struct sigaction));
	saction.sa_handler = SIG_DFL;
	sigaction(signo, &saction, NULL);
	kill(0,signo);
	//exit(-1);
}

//! Call this function one or more times with signal numbers (e.g. SIGSEGV)
//  you would like to have a stack trace printed out for.
//  Notice that "exit" is called after printing.
void printBacktraceOnSignal(int signal_number)
{
   struct sigaction saction;
   memset(&saction, 0, sizeof(struct sigaction));
   saction.sa_handler = printBacktrace_;
   sigaction(signal_number, &saction, NULL);
   //signal(signal_number, printBacktrace_);
}

void printBacktraceOnAnySignal()
{
   int theSignals[] = {
      SIGILL, SIGTRAP, SIGABRT, SIGIOT, SIGBUS, SIGFPE, SIGSEGV, SIGPIPE
   };

   for (int sig = 0; sig < (int)(sizeof(theSignals)/sizeof(int)); ++sig) {
      printBacktraceOnSignal(theSignals[sig]);
   }
}

}

#endif
