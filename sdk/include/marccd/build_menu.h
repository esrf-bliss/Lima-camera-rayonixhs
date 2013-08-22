#ifndef menu_h
#define menu_h

/* data structure type definitions */

#include <X11/Intrinsic.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h>

#define MENU_FLAG_NONE		0x00
#define MENU_FLAG_NORMAL	0x01
#define MENU_FLAG_EXPERT	0x02
#define MENU_FLAG_ADMINISTRATOR	0x04
#define MENU_FLAG_PROPRIETARY	0x08
#define MENU_FLAG_VIEW		0x10
#define MENU_FLAG_ALL		 (MENU_FLAG_VIEW | MENU_FLAG_NORMAL | MENU_FLAG_EXPERT | MENU_FLAG_ADMINISTRATOR | MENU_FLAG_PROPRIETARY)
#define MENU_FLAG_EXP		 (MENU_FLAG_EXPERT | MENU_FLAG_ADMINISTRATOR | MENU_FLAG_PROPRIETARY)
#define MENU_FLAG_ADM		 (MENU_FLAG_ADMINISTRATOR | MENU_FLAG_PROPRIETARY)
#define MENU_FLAG_PRP		 (MENU_FLAG_PROPRIETARY)

typedef struct _menu_item {
   char		*label;		/* item label */
   WidgetClass	*class;		/* pushbutton, label, separator... */
   char		mnemonic;	/* NULL if none */
   char		*accelerator;	/* NULL if none */
   char		*accel_text;	/* will be converted to compound string */
   void 	(*callback)(
#if NeedFunctionPrototypes
   Widget, void *, void *
#endif
   );
   void		*callback_data;	/* client_data for callback(); */
   struct _menu_item *subitems;	/* pullright menu items; NULL if none */
   Widget	id;		/* Widget id  - RETURNED */
   int		flag;		/* Can store flags for prive purposes */
} MenuItem;


/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern Widget BuildMenu(
#if NeedFunctionPrototypes
Widget parent_w,
int menu_type,
const char *menu_title,
char menu_mnemonic,
MenuItem *items,
void *userdata
#endif
);

extern void disable_menu_items(MenuItem *menu_items);

#endif /* menu_h */
