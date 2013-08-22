
#define DSERVER_BUFSIZE 1024
#define DSMAR_IDLE 0
#define DSMAR_AQUIRE 1
#define DSMAR_READOUT 2
#define DSMAR_CORRECT 3

int dserver_init_child( int argc, char **argv) 
int dserver_init_com(char *path)
int dserver_close(void);
int dserver_send(va_alist) 
va_dcl
int dserver_check() 
char *dserver_read() 

/* Called from mar to set size in dserver */
dserver_is_size (x,y) 
{
  char xstr[256], ystr[256];
  sprintf(xstr,"%d",x);
  sprintf(ystr,"%d",y);
  dserver_send ("is_size",xstr,ystr,NULL);
}

/* Called from dserver to ask mar to send size info */
dserver_get_size () 
{
  dserver_send ("get_size",NULL);
}

/* Called from dserver to ask mar to set the size */
dserver_set_size(x,y)
{
  char xstr[256], ystr[256];
  sprintf(xstr,"%d",x);
  sprintf(ystr,"%d",y);
  dserver_send ("set_size",xstr,ystr,NULL);
}  

/* Called from mar to set binning in dserver */
dserver_is_bin (x,y) 
{
  char xstr[256], ystr[256];
  sprintf(xstr,"%d",x);
  sprintf(ystr,"%d",y);
  dserver_send ("is_bin",xstr,ystr,NULL);
}

/*dserver_is_temp (temp) 
{
  char temp_str[16];
  sprintf(temp_str,"%d",temp);
  dserver_send ("is_temp",temp_str,NULL);
}*/

/* Called from dserver to ask mar to send binning info */
dserver_get_bin () 
{
  dserver_send ("get_bin",NULL);
}

/* Called from dserver to ask mar to set the binning */
dserver_set_bin(x,y)
{
  char xstr[256], ystr[256];
  sprintf(xstr,"%d",x);
  sprintf(ystr,"%d",y);
  dserver_send ("set_bin",xstr,ystr,NULL);
}  

/* Called from mar to set preset in dserver */
dserver_is_preset (time)
     double time;
{
   char tstr[256];
  sprintf(tstr,"%10f",time);
  dserver_send ("is_preset",tstr,NULL);
}

/* Called from dserver to ask mar to send binning info */
dserver_get_preset () 
{
  dserver_send ("get_preset",NULL);
}

/* Called from dserver to ask mar to set the preset */
/* If preset is 0 then expose until readout */ 
dserver_set_preset(time)
     double time;
{
  char tstr[256];
  sprintf(tstr,"%10f",time);
  dserver_send ("set_preset",tstr,NULL);
}  

/* Called from mar to set preset in dserver */
dserver_is_state (state)
     int state;
{
  char sstr[256];
  sprintf(sstr,"%d",state);
  dserver_send ("is_state",sstr,NULL);
}

/* Called from dserver to ask mar to send the state */
dserver_get_state () 
{
  dserver_send ("get_state",NULL);
}

dserver_start_acq ()
{
  dserver_send ("start",NULL);
}

dserver_readout (background_flag)
     int background_flag;
{
  char sstr[256];
  sprintf(sstr,"%d",background_flag);
  dserver_send ("readout",sstr, NULL);
}

dserver_writefile (filename, correct_flag)
     int correct_flag;
{
  char sstr[256];
  sprintf(sstr,"%d",correct_flag);
  dserver_send ("readout",filename,sstr, NULL);
}

dserver_correct ()
{
  dserver_send ("correct",NULL);
}

dserver_check_in () 
{ 
  char *cmd, *res;
  int xsize, ysize, xbin, ybin;
  double preset;
  if ((res = dserver_read()) == 0) 
    return 0;
  sscanf(res, "%[^,\n]", cmd);
  if (strcmp(cmd, "get_size") == 0) {
    /* mar sends dserver the actual detector size */
    /* dserver_is_size (xsize,ysize); */
  } else if (strcmp(cmd, "set_size") == 0) {
    if (sscanf(res, "%*[^,],%d,%d", &xsize, &ysize) != 2) 
      perror ("set_size protocol error");
    /* mar has to program a new size and sends the new size if OK*/
    dserver_is_size (xsize,ysize);
  } else if (strcmp(cmd, "get_bin") == 0) {
    /* mar sends dserver the actual binning */
    /* dserver_is_bin (xbin,ybin); */
   } else if (strcmp(cmd, "set_bin") == 0) {
    if (sscanf(res, "%*[^,],%d,%d", &xbin, &ybin) != 2) 
      perror ("set_bin protocol error");
    /* mar has to program a new binning and sends the new bin if OK*/
    dserver_is_bin (xbin,ybin); 
   } else if (strcmp(cmd, "get_preset") == 0) {
    /* mar has to send the preset value to the dserver*/
    /* dserver_is_preset (time); */
   } else if (strcmp(cmd, "set_preset") == 0) {
    if (sscanf(res, "%*[^,],%lf", &preset) != 2) 
      perror ("set_preset protocol error");
    /* mar has to program a preset send the new preset back*/
    dserver_is_preset (preset);
   } else if (strcmp(cmd, "start") == 0) {
    /* mar has to start image taking */
     dserver_is_state (DSMAR_AQUIRE);
   } else if (strcmp(cmd, "readout") == 0) {
    /* mar has to start readout of the ccd and put it to either background 
     or forground image */
     dserver_is_state (DSMAR_READOUT);
   } else if (strcmp(cmd, "correct") == 0) {
    /* mar has to start correct image on line */
     dserver_is_state (DSMAR_CORRECT);
   } else if (strcmp(cmd, "abort") == 0) {
    /* mar has to abort the image taking */
     dserver_is_state (DSMAR_IDLE);
   }
}

dserver_check_in_client ()
{
  char cmd[256], *res;
  char xstr[256], ystr[256];
  if ((res = dserver_read()) == 0) 
    return 0;
  sscanf(res, "%[^,\n]", cmd);
  if (strcmp(cmd, "is_size") == 0) {
    if (sscanf(res, "%*[^,],%d,%d", &dserver_v.x, &dserver_v.y) != 2) 
      perror ("is_size protocol error");
  } else if (strcmp(cmd, "is_bin") == 0) {
    if (sscanf(res, "%*[^,],%d,%d", &dserver_v.xbin, &dserver_v.ybin) != 2) 
      perror ("is_bin protocol error");
  } else if (strcmp(cmd, "is_preset") == 0) {
    if (sscanf(res, "%*[^,] %lf", &dserver_v.preset) != 1) 
      perror ("is_preset protocol error");
  } else if (strcmp(cmd, "is_state") == 0) {
    if (sscanf(res, "%*[^,] %d", &dserver_v.state) != 1) 
      perror ("is_state protocol error");
  }
  return 1;
}



