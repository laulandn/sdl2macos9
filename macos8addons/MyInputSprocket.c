// This is just dummy stubs for linking for now...

#include <stdio.h>

#include <InputSprocket.h>


#ifdef __cplusplus
extern "C" {
#endif


OSStatus ISpInit(
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
  if(!needs) { fprintf(stderr,"needs was NULL!\n"); fflush(stderr); }
  if(!inReferences) { fprintf(stderr,"inReferences was NULL!\n"); fflush(stderr); }
  return noErr;
}


OSStatus ISpStartup(void)
{
  //fprintf(stderr,"ISpStartup...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


OSStatus ISpShutdown(void)
{
  //fprintf(stderr,"ISpShutdown...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


OSStatus ISpSuspend(void)
{
  //fprintf(stderr,"ISpSuspend...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


OSStatus ISpResume(void)
{
  //fprintf(stderr,"ISpResume...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


OSStatus ISpTickle(void)
{
  //fprintf(stderr,"ISpTickle...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


OSStatus ISpElement_GetSimpleState(
  ISpElementReference   inElement,
  UInt32 *              state)
{
  fprintf(stderr,"ISpElement_GetSimpleState...MyInputSprocket...not implemented\n"); fflush(stderr);
  if(!state) { fprintf(stderr,"state was NULL!\n"); fflush(stderr); }
  return noErr;
}


OSStatus ISpElement_Flush(ISpElementReference inElement)
{
  fprintf(stderr,"ISpElement_Flush...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


OSStatus ISpDevices_ActivateClass(ISpDeviceClass inClass)
{
  switch(inClass) {
    case kISpDeviceClass_Joystick:
      fprintf(stderr,"ISpDevices_ActivateClass...kISpDeviceClass_Joystick...not implemented\n"); fflush(stderr);
      break;
    case FOUR_CHAR_CODE('gmpd'):
      fprintf(stderr,"ISpDevices_ActivateClass...kISpDeviceClass_Gamepad...not implemented\n"); fflush(stderr);
      break;
    case kISpDeviceClass_Wheel:
      fprintf(stderr,"ISpDevices_ActivateClass...kISpDeviceClass_Wheel...not implemented\n"); fflush(stderr);
      break;
    case kISpDeviceClass_Mouse:
      // We can PROBABLY assume we will always have a mouse!
      fprintf(stderr,"ISpDevices_ActivateClass...kISpDeviceClass_Mouse...not implemented\n"); fflush(stderr);
      break;
    default:
      fprintf(stderr,"ISpDevices_ActivateClass...unknown class...not implemented\n"); fflush(stderr);
      break;
  }
  return noErr;
}


OSStatus ISpDevices_ExtractByClass(
  ISpDeviceClass        inClass,
  UInt32                inBufferCount,
  UInt32 *              outCount,
  ISpDeviceReference *  buffer)
{
  if(!outCount) { fprintf(stderr,"outCount was NULL!\n"); fflush(stderr); }
  if(!buffer) { fprintf(stderr,"buffer was NULL!\n"); fflush(stderr); }
  switch(inClass) {
    case kISpDeviceClass_Joystick:
      fprintf(stderr,"ISpDevices_ExtractByClass...kISpDeviceClass_Joystick...not implemented\n"); fflush(stderr);
      break;
    case FOUR_CHAR_CODE('gmpd'):
      fprintf(stderr,"ISpDevices_ExtractByClass...kISpDeviceClass_Gamepad...not implemented\n"); fflush(stderr);
      break;
    case kISpDeviceClass_Wheel:
      fprintf(stderr,"ISpDevices_ExtractByClass...kISpDeviceClass_Wheel...not implemented\n"); fflush(stderr);
      break;
    case kISpDeviceClass_Mouse:
      // We can PROBABLY assume we will always have a mouse!
      fprintf(stderr,"ISpDevices_ExtractByClass...kISpDeviceClass_Mouse...not implemented\n"); fflush(stderr);
      break;
    default:
      fprintf(stderr,"ISpDevices_ExtractByClass...unknown class...not implemented\n"); fflush(stderr);
      break;
  }
  return noErr;
}


OSStatus ISpDevice_GetElementList(
  ISpDeviceReference         inDevice,
  ISpElementListReference *  outElementList)
{
  fprintf(stderr,"ISpDevice_GetElementList...MyInputSprocket...not implemented\n"); fflush(stderr);
  if(!outElementList) { fprintf(stderr,"outElementList was NULL!\n"); fflush(stderr); }
  return noErr;
}


OSStatus ISpElementList_Extract(
  ISpElementListReference   inElementList,
  UInt32                    inBufferCount,
  UInt32 *                  outCount,
  ISpElementReference *     buffer)
{
  fprintf(stderr,"ISpElementList_Extract...MyInputSprocket...not implemented\n"); fflush(stderr);
  if(!outCount) { fprintf(stderr,"outCount was NULL!\n"); fflush(stderr); }
  if(!buffer) { fprintf(stderr,"buffer was NULL!\n"); fflush(stderr); }
  return noErr;
}


OSStatus ISpElement_GetInfo(
  ISpElementReference   inElement,
  ISpElementInfoPtr     outInfo)
{
  fprintf(stderr,"ISpElement_GetInfo...MyInputSprocket...not implemented\n"); fflush(stderr);
  return noErr;
}


OSStatus ISpElement_GetNextEvent(
  ISpElementReference   inElement,
  UInt32                bufSize,
  ISpElementEventPtr    event,
  Boolean *             wasEvent)
{
  fprintf(stderr,"ISpElement_GetNextEvent...MyInputSprocket...not implemented\n"); fflush(stderr);
  if(!wasEvent) { fprintf(stderr,"wasEvent was NULL!\n"); fflush(stderr); }
  return noErr;
}


OSStatus ISpDevices_Deactivate(
  UInt32                inDeviceCount,
  ISpDeviceReference *  inDevicesToDeactivate)
{
  fprintf(stderr,"ISpDevices_Deactivate...MyInputSprocket...not implemented\n"); fflush(stderr);
  if(!inDevicesToDeactivate) { fprintf(stderr,"inDevicesToDeactivate was NULL!\n"); fflush(stderr); }
  return noErr;
}


OSStatus ISpDevices_Activate(
  UInt32                inDeviceCount,
  ISpDeviceReference *  inDevicesToActivate)
{
  fprintf(stderr,"ISpDevices_Activate...MyInputSprocket...not implemented\n"); fflush(stderr);
  if(!inDevicesToActivate) { fprintf(stderr,"inDevicesToActivate was NULL!\n"); fflush(stderr); }
  return noErr;
}


#ifdef __cplusplus
};
#endif


