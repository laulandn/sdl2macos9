#include <MacTypes.h>
#include <Quickdraw.h>
#include <Lists.h>
#include <MacWindows.h>
#include <Fonts.h>
#include <Dialogs.h>


#if OPAQUE_TOOLBOX_STRUCTS
#error OPAQUE_TOOLBOX_STRUCTS
#endif

#if ACCESSOR_CALLS_ARE_FUNCTIONS
#error ACCESSOR_CALLS_ARE_FUNCTIONS
#endif


#undef EXTERN_API
#define EXTERN_API(a) a


#ifdef __cplusplus
extern "C" {
#endif


#if NOT_DEFINED_ALREADY

/* Quickdraw */

EXTERN_API( Cursor * )
GetQDGlobalsArrow(Cursor * arrow);

EXTERN_API( Pattern * )
GetQDGlobalsBlack(Pattern * black);

EXTERN_API( Pattern * )
GetQDGlobalsWhite(Pattern * white);

EXTERN_API( Pattern * )
GetQDGlobalsGray(Pattern * gray);

EXTERN_API( BitMap * )
GetQDGlobalsScreenBits(BitMap * screenBits);

EXTERN_API( Rect * )
GetRegionBounds(
  RgnHandle   region,
  Rect *      bounds);
  
EXTERN_API( PixMapHandle )
GetPortPixMap(CGrafPtr port);

EXTERN_API( short )
GetPortTextFont(CGrafPtr port);

EXTERN_API( Style )
GetPortTextFace(CGrafPtr port);

EXTERN_API( short )
GetPortTextSize(CGrafPtr port);

EXTERN_API( RgnHandle )
GetPortVisibleRegion( 
  CGrafPtr    port,
  RgnHandle   visRgn);

EXTERN_API( Boolean ) 
IsRegionRectangular(RgnHandle region);


/* Windows */

EXTERN_API( Rect * )
GetWindowPortBounds(
  WindowRef   window,
  Rect *      bounds);

EXTERN_API( WindowRef )
GetWindowFromPort(CGrafPtr port);

EXTERN_API( OSStatus )
ValidWindowRect(
  WindowRef     window,
  const Rect *  bounds);

EXTERN_API( OSStatus )
InvalWindowRect(
  WindowRef     window,
  const Rect *  bounds);


/* Dialogs */

EXTERN_API( void )
SetPortDialogPort(DialogRef dialog);

EXTERN_API( CGrafPtr )
GetDialogPort(DialogRef dialog);

EXTERN_API( DialogRef )
GetDialogFromWindow(WindowRef window);

EXTERN_API( TEHandle )
GetDialogTextEditHandle(DialogRef dialog);


/* Lists */

EXTERN_API( ControlRef )
GetListVerticalScrollBar(ListRef list);
     
EXTERN_API( ControlRef )
GetListHorizontalScrollBar(ListRef list);

EXTERN_API( Point * )
GetListCellSize(
  ListRef   list,
  Point *   size);

EXTERN_API( Rect * )
GetListViewBounds(
  ListRef   list,
  Rect *    view);

EXTERN_API( ListBounds * )
GetListVisibleCells(
  ListRef       list,
  ListBounds *  visible);

EXTERN_API( OptionBits )
GetListSelectionFlags(ListRef list);

EXTERN_API( void )
SetListSelectionFlags(
  ListRef      list,
  OptionBits   selectionFlags);

EXTERN_API( ListBounds * )
GetListDataBounds(
  ListRef       list,
  ListBounds *  bounds);

EXTERN_API( CGrafPtr )
GetListPort(ListRef list);

EXTERN_API( Boolean )
GetListActive(ListRef list);


/* AEDataModel */

EXTERN_API( OSErr )
AEGetDescData(
  const AEDesc *  theAEDesc,
  void *          dataPtr,
  Size            maximumSize);


/* Controls */

EXTERN_API( Rect * ) 
GetControlBounds(
  ControlRef   control,
  Rect *       bounds);
  
  
/* Printing? */
/*extern void SetPortPrintingReference(TPPrPortRef inRef);*/
  

#endif


 #ifdef __cplusplus
};
#endif


