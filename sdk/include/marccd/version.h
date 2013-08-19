#ifndef version_h
#define version_h


/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

extern void get_program_version( char *program, int psize, char* version, int vsize, char *os, int osize);
extern void get_program_build_info( char *version, int vsize,
			     char *time, int tsize,
			     char *by, int bsize,
			     char *host, int hsize,
			     char *domain, int dsize,
			     char *command, int csize,
			     char *compiler, int ccsize);

extern char *get_license_start_date( void);

#endif /* version_h */
