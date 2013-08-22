#ifndef xtutils_h
#define xtutils_h

#include <X11/X.h>

/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */
/* Xlib and Xt  utility functions */


extern void watch_cursor(
#ifdef NeedFunctionPrototypes
Widget w
#endif
);

extern void normal_cursor(
#ifdef NeedFunctionPrototypes
Widget w
#endif
);

extern void change_cursor(
#ifdef NeedFunctionPrototypes
Widget w,
int cursor_type
#endif
);

extern Pixel colorpixelofscreen(
#ifdef NeedFunctionPrototypes
Screen *screen,
String color
#endif
);

extern void DestroyShell(
#ifdef NeedFunctionPrototypes
Widget widget,
Widget shell
#endif
);

extern void PopdownShell(
#ifdef NeedFunctionPrototypes
Widget widget,
Widget shell
#endif
);

extern Widget UltimateParent(
#ifdef NeedFunctionPrototypes
Widget w
#endif
);

extern Widget UltimateShell(
#ifdef NeedFunctionPrototypes
Widget w
#endif
);

extern char *FQName(
#ifdef NeedFunctionPrototypes
Widget w
#endif
);

extern void dummyXFlush(
#ifdef NeedFunctionPrototypes
Display *display
#endif
);

#endif /* xtutils_h */
