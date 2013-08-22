#ifndef configuration_h
#define configuration_h

typedef enum {
   CBOOL,
   CCHAR,
   CSHORT,
   CINT,
   CLONG,
   CFLOAT,
   CDOUBLE,
   CSTRING
} CDataType;

typedef struct {
	char *keyword;
	int  nargs;
	CDataType  type;
	int  nrequired;
	void *data;
	int  nfound;
	} ConfigRecord ;

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

extern int read_config_file(const char *program, const char *filename, ConfigRecord *config_list, int verbose);
extern int write_config_file(const char *program, const char *filename, ConfigRecord *config_list, int verbose);

#endif /* configuration_h */
