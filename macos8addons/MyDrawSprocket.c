// This is just dummy stubs for linking for now...

#include <stdio.h>

#include <DrawSprocket.h>


#ifdef __cplusplus
extern "C" {
#endif


struct NumVersion myVer;


EXTERN_API_C( OSStatus )
DSpFindBestContext(
  DSpContextAttributesPtr   inDesiredAttributes,
  DSpContextReference *     outContext)
{
  fprintf(stderr,"DSpFindBestContext...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
DSpContext_Reserve(
  DSpContextReference       inContext,
  DSpContextAttributesPtr   inDesiredAttributes)
{
  fprintf(stderr,"DSpContext_Reserve...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
DSpContext_FadeGammaOut(
  DSpContextReference   inContext,
  RGBColor *            inZeroIntensityColor)
{
  fprintf(stderr,"DSpContext_FadeGammaOut...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
DSpContext_SetState(
  DSpContextReference   inContext,
  DSpContextState       inState)
{
  fprintf(stderr,"DSpContext_SetState...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
DSpContext_FadeGammaIn(
  DSpContextReference   inContext,
  RGBColor *            inZeroIntensityColor)
{
  fprintf(stderr,"DSpContext_FadeGammaIn...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
DSpContext_LocalToGlobal(
  DSpContextReferenceConst   inContext,
  Point *                    ioPoint)
{
  fprintf(stderr,"DSpContext_LocalToGlobal...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
DSpContext_Release(DSpContextReference inContext)
{
  fprintf(stderr,"DSpContext_Release...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
DSpStartup(void)
{
  fprintf(stderr,"DSpStartup...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
DSpShutdown(void)
{
  fprintf(stderr,"DSpShutdown...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
DSpContext_SwapBuffers(
  DSpContextReference   inContext,
  DSpCallbackUPP        inBusyProc,
  void *                inUserRefCon)
{
  fprintf(stderr,"DSpContext_SwapBuffers...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
DSpContext_GetBackBuffer(
  DSpContextReference   inContext,
  DSpBufferKind         inBufferKind,
  CGrafPtr *            outBackBuffer)
{
  fprintf(stderr,"DSpContext_GetBackBuffer...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
DSpContext_GetAttributes(
  DSpContextReferenceConst   inContext,
  DSpContextAttributesPtr    outAttributes)
{
  fprintf(stderr,"DSpContext_GetAttributes...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( NumVersion )
DSpGetVersion(void)
{
  fprintf(stderr,"DSpGetVersion...MyDrawSprocket...not implemented\n"); fflush(stderr);
  myVer.majorRev=0;
  myVer.minorAndBugRev=0;
  myVer.stage=0;
  myVer.nonRelRev=0;
  return myVer;
}


EXTERN_API_C( OSStatus )
DSpProcessEvent(
  EventRecord *  inEvent,
  Boolean *      outEventWasProcessed)
{
  fprintf(stderr,"DSpProcessEvent...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
DSpGetFirstContext(
  DisplayIDType          inDisplayID,
  DSpContextReference *  outContext)
{
  fprintf(stderr,"DSpGetFirstContext...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
DSpGetNextContext(
  DSpContextReference    inCurrentContext,
  DSpContextReference *  outContext)
{
  fprintf(stderr,"DSpGetNextContext...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
DSpContext_GetMonitorFrequency(
  DSpContextReferenceConst   inContext,
  Fixed *                    outFrequency)
{
  fprintf(stderr,"DSpContext_GetMonitorFrequency...MyDrawSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


#ifdef __cplusplus
};
#endif
