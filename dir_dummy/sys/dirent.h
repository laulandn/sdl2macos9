/* <dirent.h> includes <sys/dirent.h>, which is this file.  On a
   system which supports <dirent.h>, this file is overridden by
   dirent.h in the libc/sys/.../sys directory.  On a system which does
   not support <dirent.h>, we will get this file which uses #error to force
   an error.  */

#ifdef __cplusplus
extern "C" {
#endif
/*#error "<dirent.h> not supported"*/
struct dirent {
  char *d_name;
};
typedef struct dirent DIR;
#ifdef __cplusplus
}
#endif
