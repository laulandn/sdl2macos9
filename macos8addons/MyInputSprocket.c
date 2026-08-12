#include <stdio.h>

#include <InputSprocket.h>


#ifdef __cplusplus
extern "C" {
#endif


EXTERN_API_C( OSStatus )
ISpInit(
  UInt32                 count,
  ISpNeed *              needs,
  ISpElementReference *  inReferences,
  OSType                 appCreatorCode,
  OSType                 subCreatorCode,
  UInt32                 flags,
  short                  setListResourceId,
  UInt32                 reserved)
{
  fprintf(stderr,"ISpInit...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
ISpStartup(void)
{
  fprintf(stderr,"ISpStartup...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
ISpSuspend(void)
{
  fprintf(stderr,"ISpSuspend...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
ISpResume(void)
{
  fprintf(stderr,"ISpResume...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
ISpTickle(void)
{
  fprintf(stderr,"ISpTickle...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
ISpElement_GetSimpleState(
  ISpElementReference   inElement,
  UInt32 *              state)
{
  fprintf(stderr,"ISpElement_GetSimpleState...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
ISpElement_Flush(ISpElementReference inElement)
{
  fprintf(stderr,"ISpElement_Flush...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
ISpDevices_ActivateClass(ISpDeviceClass inClass)
{
  fprintf(stderr,"ISpDevices_ActivateClass...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
ISpDevices_ExtractByClass(
  ISpDeviceClass        inClass,
  UInt32                inBufferCount,
  UInt32 *              outCount,
  ISpDeviceReference *  buffer)
{
  fprintf(stderr,"ISpDevices_ExtractByClass...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
ISpShutdown(void)
{
  fprintf(stderr,"ISpShutdown...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
ISpDevice_GetElementList(
  ISpDeviceReference         inDevice,
  ISpElementListReference *  outElementList)
{
  fprintf(stderr,"ISpDevice_GetElementList...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
ISpElementList_Extract(
  ISpElementListReference   inElementList,
  UInt32                    inBufferCount,
  UInt32 *                  outCount,
  ISpElementReference *     buffer)
{
  fprintf(stderr,"ISpElementList_Extract...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
ISpElement_GetInfo(
  ISpElementReference   inElement,
  ISpElementInfoPtr     outInfo)
{
  fprintf(stderr,"ISpElement_GetInfo...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
ISpElement_GetNextEvent(
  ISpElementReference   inElement,
  UInt32                bufSize,
  ISpElementEventPtr    event,
  Boolean *             wasEvent)
{
  fprintf(stderr,"ISpElement_GetNextEvent...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
ISpDevices_Deactivate(
  UInt32                inDeviceCount,
  ISpDeviceReference *  inDevicesToDeactivate)
{
  fprintf(stderr,"ISpDevices_Deactivate...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


EXTERN_API_C( OSStatus )
ISpDevices_Activate(
  UInt32                inDeviceCount,
  ISpDeviceReference *  inDevicesToActivate)
{
  fprintf(stderr,"ISpDevices_Activate...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


#ifdef __cplusplus
};
#endif


