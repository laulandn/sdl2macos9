#include <stdio.h>
#include <sys/select.h>

#ifdef __cplusplus
extern "C" {
#endif


// Just a fake function for now...

int select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds,struct timeval *restrict timeout)
{
  fprintf(stderr,"macos8addons select not implemented!\n"); fflush(stderr);
  if(!readfds) {
    fprintf(stderr,"readfds was NULL!\n"); fflush(stderr);
  }
  if(!writefds) {
    fprintf(stderr,"writefds was NULL!\n"); fflush(stderr);
  }
  if(!errorfds) {
    fprintf(stderr,"errorfds was NULL!\n"); fflush(stderr);
  }
  if(!timeout) {
    fprintf(stderr,"timeout was NULL!\n"); fflush(stderr);
  }
}



 #ifdef __cplusplus
};
#endif


