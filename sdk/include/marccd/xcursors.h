#ifndef xcursors_h
#define xcursors_h

#include <X11/Xlib.h>
#include <X11/cursorfont.h>

/* Begin our numbering beyond the last number for the standard
   X11 cursor font
*/

#define MMXC_MagGlass	(XC_num_glyphs + 0)

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */


extern Cursor create_cursor_from_internal_bitmap_list(
#if NeedFunctionPrototypes
Display *display,
int cursor_type
#endif
);

extern GC get_cursor_gc(
#if NeedFunctionPrototypes
Widget widget
#endif
);

#endif /* xcursors_h */
