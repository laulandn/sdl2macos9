#include <stdio.h>
#include <dirent.h>


int access(const char *path, int mode)
{
  fprintf(stderr,"access(%s,%d)...\n",path,mode);  fflush(stderr);
  if(!path) { fprintf(stderr,"path was NULL!\n"); fflush(stderr); }
  return -1;
}


int mkdir(const char *path, int/*mode_t*/ mode)
{
  fprintf(stderr,"mkdir(%s,%d)...\n",path,mode);  fflush(stderr);
  if(!path) { fprintf(stderr,"path was NULL!\n"); fflush(stderr); }
  return -1;
}


int chdir(const char *path)
{
  fprintf(stderr,"chdir(%s)...\n",path);  fflush(stderr);
  if(!path) { fprintf(stderr,"path was NULL!\n"); fflush(stderr); }
  return -1;
}


DIR * opendir(const char *filename)
{
  fprintf(stderr,"opendir(%s)...\n",filename);  fflush(stderr);
  if(!filename) { fprintf(stderr,"filename was NULL!\n"); fflush(stderr); }
  return NULL;
}


struct dirent *readdir(DIR *dirp)
{
  fprintf(stderr,"readdir()...\n");  fflush(stderr);
  if(!dirp) { fprintf(stderr,"DIR was NULL!\n"); fflush(stderr); }
  return NULL;
}


int closedir(DIR *dirp)
{
  fprintf(stderr,"closedir()...\n");  fflush(stderr);
  if(!dirp) { fprintf(stderr,"DIR was NULL!\n"); fflush(stderr); }
  return 0;
}

