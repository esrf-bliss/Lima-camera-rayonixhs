#ifndef dialog_manager_h
#define dialog_manager_h


#define ROUTINE_PARTIAL_BUSY		-2
#define ROUTINE_BUSY			-1
#define ROUTINE_DISABLE			0
#define ROUTINE_ENABLE			1
#define ROUTINE_ENABLE_AND_FOCUS	2


/* Pointer to a function returning int */
typedef  void (*EnablingRoutine) (int enable);


extern int register_dialog_control(EnablingRoutine routine);

extern int enable_dialog_routines (int enable, int exception);


#endif /* dialog_manager_h */
