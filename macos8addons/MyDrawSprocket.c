// This is just dummy stubs for linking for now...

#include <stdio.h>

#include <DrawSprocket.h>


#ifdef __cplusplus
extern "C" {
#endif


struct NumVersion myVer;
DSpContextReference myContext;
bool myContextAlreadyDone=false;


OSStatus DSpStartup(void)
{
  //fprintf(stderr,"DSpStartup...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


OSStatus DSpShutdown(void)
{
  //fprintf(stderr,"DSpShutdown...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


NumVersion DSpGetVersion(void)
{
  //fprintf(stderr,"DSpGetVersion...MyDrawSprocket...not implemented\n"); fflush(stderr);
  myVer.majorRev=1;
  myVer.minorAndBugRev=0x73;
  myVer.stage=0;
  myVer.nonRelRev=0;
  return myVer;
}


OSStatus DSpFindBestContext(
  DSpContextAttributesPtr   inDesiredAttributes,
  DSpContextReference *     outContext)
{
  fprintf(stderr,"DSpFindBestContext...MyDrawSprocket...not implemented\n"); fflush(stderr);
  if(!outContext) { fprintf(stderr,"outContext was NULL!\n"); fflush(stderr); }
  return noErr;
}


OSStatus DSpContext_Reserve(
  DSpContextReference       inContext,
  DSpContextAttributesPtr   inDesiredAttributes)
{
  fprintf(stderr,"DSpContext_Reserve...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


OSStatus DSpContext_FadeGammaOut(
  DSpContextReference   inContext,
  RGBColor *            inZeroIntensityColor)
{
  fprintf(stderr,"DSpContext_FadeGammaOut...MyDrawSprocket...not implemented\n"); fflush(stderr);
  if(!inZeroIntensityColor) { fprintf(stderr,"inZeroIntensityColor was NULL!\n"); fflush(stderr); }
  return noErr;
}


OSStatus DSpContext_FadeGammaIn(
  DSpContextReference   inContext,
  RGBColor *            inZeroIntensityColor)
{
  fprintf(stderr,"DSpContext_FadeGammaIn...MyDrawSprocket...not implemented\n"); fflush(stderr);
  if(!inZeroIntensityColor) { fprintf(stderr,"inZeroIntensityColor was NULL!\n"); fflush(stderr); }
  return noErr;
}


OSStatus DSpContext_LocalToGlobal(
  DSpContextReferenceConst   inContext,
  Point *                    ioPoint)
{
  fprintf(stderr,"DSpContext_LocalToGlobal...MyDrawSprocket...not implemented\n"); fflush(stderr);
  if(!ioPoint) { fprintf(stderr,"ioPoint was NULL!\n"); fflush(stderr); }
  return noErr;
}


OSStatus DSpContext_Release(DSpContextReference inContext)
{
  fprintf(stderr,"DSpContext_Release...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


OSStatus DSpContext_SwapBuffers(
  DSpContextReference   inContext,
  DSpCallbackUPP        inBusyProc,
  void *                inUserRefCon)
{
  fprintf(stderr,"DSpContext_SwapBuffers...MyDrawSprocket...not implemented\n"); fflush(stderr);
  if(!inUserRefCon) { fprintf(stderr,"inUserRefCon was NULL!\n"); fflush(stderr); }
  return noErr;
}


OSStatus DSpContext_GetBackBuffer(
  DSpContextReference   inContext,
  DSpBufferKind         inBufferKind,
  CGrafPtr *            outBackBuffer)
{
  fprintf(stderr,"DSpContext_GetBackBuffer...MyDrawSprocket...not implemented\n"); fflush(stderr);
  if(!outBackBuffer) { fprintf(stderr,"outBackBuffer was NULL!\n"); fflush(stderr); }
  return noErr;
}


OSStatus DSpContext_GetAttributes(
  DSpContextReferenceConst   inContext,
  DSpContextAttributesPtr    outAttributes)
{
  //fprintf(stderr,"DSpContext_GetAttributes...MyDrawSprocket...not implemented\n"); fflush(stderr);
  if(!outAttributes) { fprintf(stderr,"outAttributes was NULL!\n"); fflush(stderr); return -1; }
  outAttributes->displayBestDepth=32;  // TODO This should be current mode if we aren't switching
  outAttributes->displayWidth=800;  // TODO: This should be window
  outAttributes->displayHeight=600;  // TODO: This should be window
  outAttributes->frequency=60;
  return noErr;
}


OSStatus DSpContext_SetState(
  DSpContextReference   inContext,
  DSpContextState       inState)
{
  fprintf(stderr,"DSpContext_SetState...MyDrawSprocket...not implemented\n"); fflush(stderr);
}


OSStatus DSpProcessEvent(
  EventRecord *  inEvent,
  Boolean *      outEventWasProcessed)
{
  fprintf(stderr,"DSpProcessEvent...MyDrawSprocket...not implemented\n"); fflush(stderr);
  if(!outEventWasProcessed) { fprintf(stderr,"outEventWasProcessed was NULL!\n"); fflush(stderr); }
  return noErr;
}


OSStatus DSpGetFirstContext(
  DisplayIDType          inDisplayID,
  DSpContextReference *  outContext)
{
  //fprintf(stderr,"DSpGetFirstContext...MyDrawSprocket...not implemented\n"); fflush(stderr);
  if(!outContext) { fprintf(stderr,"outContext was NULL!\n"); fflush(stderr); }
  myContextAlreadyDone=true;
  return noErr;
}


OSStatus DSpGetNextContext(
  DSpContextReference    inCurrentContext,
  DSpContextReference *  outContext)
{
  //fprintf(stderr,"DSpGetNextContext...MyDrawSprocket...not implemented\n"); fflush(stderr);
  if(!outContext) { fprintf(stderr,"outContext was NULL!\n"); fflush(stderr); }
  return -1;
}


OSStatus DSpContext_GetMonitorFrequency(
  DSpContextReferenceConst   inContext,
  Fixed *                    outFrequency)
{
  //fprintf(stderr,"DSpContext_GetMonitorFrequency...MyDrawSprocket...not implemented\n"); fflush(stderr);
  if(!outFrequency) { fprintf(stderr,"outFrequency was NULL!\n"); fflush(stderr); return -1; }
  *outFrequency=60;
  return noErr;
}


#ifdef __cplusplus
};
#endif
