#ifndef dataset_dialog_h
#define dataset_dialog_h

#include "parameters.h"
#include "xmupdate.h"

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

#define DATASET_STATUS_BUSY 1
#define DATASET_STATUS_IDLE 0

extern void config_dataset_dialog( Widget w, int item_no);
extern int dataset_status_access(int option, int input);

extern int rebuild_dataset_dialog_box( void);

extern void update_dataset_dialog( void);

#endif /* dataset_dialog_h */
