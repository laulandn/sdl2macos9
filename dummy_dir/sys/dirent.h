/* <dirent.h> includes <sys/dirent.h>, which is this file.  On a
   system which supports <dirent.h>, this file is overridden by
   dirent.h in the libc/sys/.../sys directory.  On a system which does
   not support <dirent.h>, we will get this file which uses #error to force
   an error.  */

#ifdef __cplusplus
extern "C" {
#endif


#include <sys/param.h>


struct dirent {
  char d_name[MAXPATHLEN];
  int d_ino;
  int d_reclen;
  int d_namlen;
};
typedef struct dirent dirent;


struct DIR {
  char *d_name;  // Still needed?
  int d_ino;  // Still needed?
  int dd_fd;
  int vRefNum;
  int fileIndex;
  dirent dirEntryBuffer;
};
typedef struct DIR DIR;


#ifdef __cplusplus
}
#endif
