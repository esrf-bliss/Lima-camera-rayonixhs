#ifndef license_h
#define license_h
#include <Xm/Xm.h>
/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

extern int check_license (const char *name, const char *license_key, const char *password);
extern int check_password(const char *hash, const char *password);
extern char *generate_hash(const char *plaintext, char *cipher, int *cipherlen);
extern char *key_to_text(const char *key, int keylen, char *text, int textlen);
extern char *text_to_key(const char *text, char *key, int keylen);
extern char *generate_full_license_key(Widget topshell, const char *license_info, const char *password);

#endif /* license_h */
