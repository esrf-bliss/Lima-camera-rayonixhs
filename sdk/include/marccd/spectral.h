#ifndef spectral_h
#define spectral_h

/*------------------------------------------------------------------*/
/* function declarations (and prototypes) */

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif /* __STDC__ */
#endif /* NeedFunctionPrototypes */

/* Spectral Universally useful code */
extern int spectral_firmware_partnumber(int firmware_configuration);
extern int spectral_firmware_revisionnumber(int firmware_configuration);
extern int extract_spectral_dspcode_revision_code(void *data, int size);
extern int spectral_dsp_checksum(void *data, int size);
extern int spectral_read_dsp_binary(const char *filename, void **binary_data_h, int *binary_data_sizep);

#endif /* spectral_h */
