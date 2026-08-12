#include <stdio.h>

#include "MyAccessors.h"


#ifdef __cplusplus
extern "C" {
#endif


/* Quickdraw */

#ifndef GetQDGlobalsArrow
EXTERN_API( Cursor * )
GetQDGlobalsArrow(Cursor * arrow)
{
  fprintf(stderr,"GetQDGlobalsArrow...MyAssesors...not implemented\n"); fflush(stderr);
  return (Cursor *)NULL;
}
#endif


#ifndef GetQDGlobalsBlack
EXTERN_API( Pattern * )
GetQDGlobalsBlack(Pattern * black)
{
  fprintf(stderr,"GetQDGlobalsBlack...MyAssesors...not implemented\n"); fflush(stderr);
  return (Pattern *)NULL;
}
#endif


#ifndef GetQDGlobalsWhite
EXTERN_API( Pattern * )
GetQDGlobalsWhite(Pattern * white)
{
  fprintf(stderr,"GetQDGlobalsWhite...MyAssesors...not implemented\n"); fflush(stderr);
  return (Pattern *)NULL;
}
#endif


#ifndef GetQDGlobalsGray
EXTERN_API( Pattern * )
GetQDGlobalsGray(Pattern * gray)
{
  fprintf(stderr,"GetQDGlobalsGray...MyAssesors...not implemented\n"); fflush(stderr);
  return (Pattern *)NULL;
}
#endif


#ifndef GetQDGlobalsScreenBits
EXTERN_API( BitMap * )
GetQDGlobalsScreenBits(BitMap * screenBits)
{
  fprintf(stderr,"GetQDGlobalsScreenBits...MyAssesors...not implemented\n"); fflush(stderr);
  return (BitMap *)NULL;
}
#endif


#ifndef GetRegionBounds
EXTERN_API( Rect * )
GetRegionBounds(
  RgnHandle   region,
  Rect *      bounds)
{
  fprintf(stderr,"GetRegionBounds...MyAssesors...not implemented\n"); fflush(stderr);
  return (Rect *)NULL;
}
#endif

  
#ifndef GetPortPixMap
EXTERN_API( PixMapHandle )
GetPortPixMap(CGrafPtr port) 
{
  fprintf(stderr,"GetPortPixMap...MyAssesors...not implemented\n"); fflush(stderr);
  return (PixMapHandle)NULL;
}
#endif


#ifndef GetPortTextFont
EXTERN_API( short )
GetPortTextFont(CGrafPtr port)
{
  fprintf(stderr,"GetPortTextFont...MyAssesors...not implemented\n"); fflush(stderr);
  return 0;
}
#endif


#ifndef GetPortTextFace
EXTERN_API( Style )
GetPortTextFace(CGrafPtr port)
{
  fprintf(stderr,"GetPortTextFace...MyAssesors...not implemented\n"); fflush(stderr);
  return (Style)0;
}
#endif


#ifndef GetPortTextSize
EXTERN_API( short )
GetPortTextSize(CGrafPtr port)
{
  fprintf(stderr,"GetPortTextSize...MyAssesors...not implemented\n"); fflush(stderr);
  return 0;
}
#endif


#ifndef GetPortVisibleRegion
EXTERN_API( RgnHandle )
GetPortVisibleRegion( 
  CGrafPtr    port,
  RgnHandle   visRgn)
{
  fprintf(stderr,"GetPortVisibleRegion...MyAssesors...not implemented\n"); fflush(stderr);
  return (RgnHandle)NULL;
}
#endif


#ifndef IsRegionRectangular
EXTERN_API( Boolean ) 
IsRegionRectangular(RgnHandle region)
{
  fprintf(stderr,"IsRegionRectangular...MyAssesors...not implemented\n"); fflush(stderr);
  return false;
}
#endif


/* AEDataModel */

#ifndef AEGetDescData
EXTERN_API( OSErr )
AEGetDescData(
  const AEDesc *  theAEDesc,
  void *          dataPtr,
  Size            maximumSize)
{
  fprintf(stderr,"AEGetDescData...MyAssesors...not implemented\n"); fflush(stderr);
  return 0;
}
#endif


/* Controls */

#ifndef GetControlBounds
EXTERN_API( Rect * ) 
GetControlBounds(
  ControlPtr   control,
  Rect *       bounds)
{
  fprintf(stderr,"GetControlBounds...MyAssesors...not implemented\n"); fflush(stderr);
  return (Rect *)NULL;
}
#endif


/* Lists */


#ifndef GetListVerticalScrollBar
EXTERN_API( ControlPtr )
GetListVerticalScrollBar(ListPtr list) 
{
  fprintf(stderr,"GetListVerticalScrollBar...MyAssesors...not implemented\n"); fflush(stderr);
  return (ControlPtr)NULL;
}
#endif

     
#ifndef GetListHorizontalScrollBar
EXTERN_API( ControlPtr )
GetListHorizontalScrollBar(ListPtr list)
{
  fprintf(stderr,"GetListHorizontalScrollBar...MyAssesors...not implemented\n"); fflush(stderr);
  return (ControlPtr)NULL;
}
#endif


#ifndef GetListCellSize
EXTERN_API( Point * )
GetListCellSize(
  ListPtr   list,
  Point *   size)
{
  fprintf(stderr,"GetListCellSize...MyAssesors...not implemented\n"); fflush(stderr);
  return (Point *)NULL;
}
#endif


#ifndef GetListViewBounds
EXTERN_API( Rect * )  
GetListViewBounds(
  ListPtr   list,     
  Rect *    view)  
{
  fprintf(stderr,"GetListViewBounds...MyAssesors...not implemented\n"); fflush(stderr);
  return (Rect *)NULL;
}
#endif


#ifndef GetListVisibleCells
EXTERN_API( ListBounds * )
GetListVisibleCells(
  ListPtr       list,
  ListBounds *  visible)
{
  fprintf(stderr,"GetListVisibleCells...MyAssesors...not implemented\n"); fflush(stderr);
  return (ListBounds *)NULL;
}
#endif


#ifndef GetListSelectionFlags
EXTERN_API( OptionBits )
GetListSelectionFlags(ListPtr list)
{
  fprintf(stderr,"GetListSelectionFlags...MyAssesors...not implemented\n"); fflush(stderr);
  return (OptionBits)NULL;
}
#endif


#ifndef SetListSelectionFlags
EXTERN_API( void )
SetListSelectionFlags(
  ListPtr      list,
  OptionBits   selectionFlags)
{
  fprintf(stderr,"SetListSelectionFlags...MyAssesors...not implemented\n"); fflush(stderr);
}
#endif


#ifndef GetListDataBounds
EXTERN_API( ListBounds * )              
GetListDataBounds(                      
  ListPtr       list,
  ListBounds *  bounds)                
{
  fprintf(stderr,"GetListDataBounds...MyAssesors...not implemented\n"); fflush(stderr);
  return (ListBounds *)NULL;
}
#endif


#ifndef GetListPort
EXTERN_API( CGrafPtr )
GetListPort(ListPtr list)           
{
  fprintf(stderr,"GetListPort...MyAssesors...not implemented\n"); fflush(stderr);
  return (CGrafPtr)NULL;
}
#endif


#ifndef GetListActive
EXTERN_API( Boolean )
GetListActive(ListPtr list)
{
  fprintf(stderr,"GetListActive...MyAssesors...not implemented\n"); fflush(stderr);
  return false;
}
#endif

    
/* Windows */


#ifndef GetWindowPortBounds
EXTERN_API( Rect * )
GetWindowPortBounds(  
  WindowPtr   window1,
  Rect *      bounds)
{
  fprintf(stderr,"GetWindowPortBounds...MyAssesors...not implemented\n"); fflush(stderr);
  return (Rect *)NULL;
}
#endif


#ifndef GetWindowFromPort
EXTERN_API( WindowPtr )
GetWindowFromPort(CGrafPtr port)
{
  fprintf(stderr,"GetWindowFromPort...MyAssesors...not implemented\n"); fflush(stderr);
  return (WindowPtr)NULL;
}
#endif


#ifndef ValidWindowRect
EXTERN_API( OSStatus )
ValidWindowRect(
  WindowPtr     window,
  const Rect *  bounds)
{
  fprintf(stderr,"ValidWindowRect...MyAssesors...not implemented\n"); fflush(stderr);
  return noErr;
}
#endif


#ifndef InvalWindowRect
EXTERN_API( OSStatus )
InvalWindowRect(
  WindowPtr     window,
  const Rect *  bounds)
{
  fprintf(stderr,"InvalWindowRect...MyAssesors...not implemented\n"); fflush(stderr);
  return noErr;
}
#endif


/* Dialogs */


#ifndef GetDialogFromWindow
EXTERN_API( DialogRef )
GetDialogFromWindow(WindowPtr window1)
{
  fprintf(stderr,"GetDialogFromWindow...MyAssesors...not implemented\n"); fflush(stderr);
  return (DialogRef)NULL;
}
#endif


#ifndef SetPortDialogPort
EXTERN_API( void )
SetPortDialogPort(DialogRef dialog)
{
  fprintf(stderr,"SetPortDialogPort...MyAssesors...not implemented\n"); fflush(stderr);
}
#endif


#ifndef GetDialogPort
EXTERN_API( CGrafPtr )
GetDialogPort(DialogRef dialog)
{
  fprintf(stderr,"GetDialogPort...MyAssesors...not implemented\n"); fflush(stderr);
  return (CGrafPtr)NULL;
}
#endif


/* Printing? */

/*
extern void SetPortPrintingReference(TPPrPortPtr inPtr)
{
  fprintf(stderr,"SetPortPrintingPtrerence...MyAssesors...not implemented\n"); fflush(stderr);
}*/


 #ifdef __cplusplus
};
#endif


