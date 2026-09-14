#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Our's, not retro68's...which is mostly empty
// NOTE: Clients MUST use the same one!
#include <dirent.h>

#include <Files.h>


char *getcwd(char *buf, size_t size)
{
  fprintf(stderr,"dummy getcwd()...\n");  fflush(stderr);
  if(!buf) { fprintf(stderr,"buf was NULL!\n"); fflush(stderr); }
  return "::";
}

char *getwd(char *buf)
{
  fprintf(stderr,"dummy getwd()...\n");  fflush(stderr);
  if(!buf) { fprintf(stderr,"buf was NULL!\n"); fflush(stderr); }
  return "::";
}


int access(const char *path, int mode)
{
  fprintf(stderr,"dummy access()...\n");  fflush(stderr);
  if(!path) { fprintf(stderr,"path was NULL!\n"); fflush(stderr); }
  return -1;
}


int mkdir(const char *path, int/*mode_t*/ mode)
{
  fprintf(stderr,"dummy mkdir(%s,%d)...\n",path,mode);  fflush(stderr);
  if(!path) { fprintf(stderr,"path was NULL!\n"); fflush(stderr); }
  return -1;
}


int chdir(const char *path)
{
  fprintf(stderr,"dummy chdir(%s)...\n",path);  fflush(stderr);
  if(!path) { fprintf(stderr,"path was NULL!\n"); fflush(stderr); }
  return -1;
}


/*
 * Open a directory.  This means calling PBOpenWD.
 * The value returned is always the address of opened, or NULL.
 * (I have as yet no use for multiple open directories; this could
 * be implemented by allocating memory dynamically.)
 */
DIR * opendir(const char *path)
{
  if(!path) { fprintf(stderr,"opendir path was NULL!\n"); fflush(stderr); return NULL; }
	
	int i;
	WDPBRec paramBlock;
	char ppath[MAXPATHLEN];
	OSErr error;
	
	
	DIR	*pDir = malloc(sizeof(DIR));
	if (pDir == nil)
		return nil;
	
		
	strncpy(&ppath[1],path,ppath[0]=strlen(path));
	
	for (i = 0; i < strlen(path); i++)
	{
		if (ppath[i+1] == '.')
			ppath[i+1] = ':';
			
		if (ppath[i+1] == '/')
			ppath[i+1] = ':';
	}
	
	paramBlock.ioCompletion = nil;
	paramBlock.ioWDProcID = 0;
	paramBlock.ioWDDirID = 0;
	paramBlock.ioNamePtr = (StringPtr)ppath;
	paramBlock.ioVRefNum = 0;
	
	error = PBOpenWDSync(&paramBlock);
	
	if (error != noErr)
	{
		free(pDir);
		return nil;
	}
		
	pDir->vRefNum = paramBlock.ioVRefNum;
	pDir->fileIndex = 1;
	return pDir;
}


struct dirent *readdir(DIR *dirp)
{
  if(!dirp) { fprintf(stderr,"readdir DIR was NULL!\n"); fflush(stderr); return NULL; }
	CInfoPBRec 	paramBlock;
	OSErr		error;
	
	assert(dirp);
	
	dirp->dirEntryBuffer.d_name[0] = 0;
	
	paramBlock.dirInfo.ioNamePtr = (StringPtr)dirp->dirEntryBuffer.d_name;
	paramBlock.dirInfo.ioVRefNum = dirp->vRefNum;
	paramBlock.dirInfo.ioFDirIndex = dirp->fileIndex++;
	paramBlock.dirInfo.ioDrDirID = 0;
	
	error = PBGetCatInfoSync(&paramBlock);
	if (error != noErr)
		return nil;
		
	dirp->dirEntryBuffer.d_ino = dirp->fileIndex;
	dirp->dirEntryBuffer.d_reclen = 0;
	p2cstr((StringPtr)dirp->dirEntryBuffer.d_name);
	dirp->dirEntryBuffer.d_namlen = strlen(dirp->dirEntryBuffer.d_name);
	
	return &dirp->dirEntryBuffer;
}


int closedir(DIR *dirp)
{
  if(!dirp) { fprintf(stderr,"closedir DIR was NULL!\n"); fflush(stderr); return 0; }
	WDPBRec paramBlock;
	
	paramBlock.ioCompletion = 0;
	paramBlock.ioVRefNum = dirp->vRefNum;
	
	PBCloseWDSync(&paramBlock);
	
	free(dirp);
}


char *realpath(const char *n,char *rn)
{
  fprintf(stderr,"dummy realpath()...\n");  fflush(stderr);
  if(!n) { fprintf(stderr,"n was NULL!\n"); fflush(stderr); }
  if(!rn) { fprintf(stderr,"n was NULL!\n"); fflush(stderr); }
  return (const char *)n;
}


FILE *popen(const char *n,const char *m)
{
  fprintf(stderr,"dummy popen()...\n");  fflush(stderr);
  if(!n) { fprintf(stderr,"n was NULL!\n"); fflush(stderr); }
  if(!m) { fprintf(stderr,"m was NULL!\n"); fflush(stderr); }
  return NULL;
}


int pclose(FILE *f)
{
  fprintf(stderr,"dummy pclose()...\n");  fflush(stderr);
  if(!f) { fprintf(stderr,"f was NULL!\n"); fflush(stderr); }
  return 0;
}
