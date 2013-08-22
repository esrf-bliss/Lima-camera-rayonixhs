#ifndef buddha_stubs_h
#define buddha_stubs_h

/* Two structures coincide with the BUDDHA params.cmn common blocks */
struct buddha_params {
   float flmda,rltce[9],xcntr,ycntr,pltd,pltd2,
	 crs[9],chi,coschi,sinchi,frsize,gam[3];
   int   newprms;
   float swing,sinsw,cossw;
   int   hand,lattice;
   float perphs,peramp,perper;
   int   moterr;
};

struct buddha_nparms {
   float mux,muy,dumprm;
   int   sptn,nwfrsi;
};

extern struct buddha_params params_;
extern struct buddha_nparms nparms_;


/* From parms.for */
int rdprms_(char *mapfile_name, int nlength);

/* From gtspcm.for */
int gtspcm_(char *mapfile_name, int nlength);

/* From xtlsub.for */
void mkbp_(float *ar, float *ang, float *bp, float *fdum27);
void calxp_(int *itype, float *crs, float *ar, float *ang);
void eulertomatrix_(int *flag, float *theta_1, float *theta_2, float *theta_3,float *rotation_matrix);
void matrixtoeuler_(float *rotation_matrix, float *theta_1, float *theta_2, float *theta_3);

/* From matrix.for */
void minvn_(int *dimension, float *iUgonio, float *Ugonio, float *volume);
void mmultn_(int *dim1, int *dim2, int *dim3, float *Ustandard, float *iUgonio, float *Umat);

/* From coords.for */
void ttos_(float *phi, float *xt, float *yt, float *xs, float *ys, int *ifin);
void stot_(float *phi, float *xs, float *ys, float *xt, float *yt, int *ifin);
void stoe_(float *xs, float *ys, float *ecords);
void etos_(float *ecords, float *xs, float *ys);


#endif /* buddha_stubs_h */
