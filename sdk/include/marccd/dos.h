
extern void *init_eisa(const char *device);
extern void *inpaddr(int address);
extern unsigned char inp(int address);
extern void outp(int address, char data);
extern unsigned short inpw(int address);
extern void outpw(int address, short data);
