#ifndef _AXLIB_H_
#define _AXLIB_H_

//#define AXLIB_DEBUG_MODE 1

#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include "wx/graphics.h"
#include "wx/popupwin.h"
#include "wx/dir.h"

#define _EVENT_

#define axID_ANY wxID_ANY

#define AX_TYPEDEF(x) typedef wx ## x ax ## x

AX_TYPEDEF(App);
AX_TYPEDEF(Window);
AX_TYPEDEF(Frame);
AX_TYPEDEF(Panel);
AX_TYPEDEF(Bitmap);
AX_TYPEDEF(Image);
AX_TYPEDEF(Color);
AX_TYPEDEF(Point);
AX_TYPEDEF(Size);
AX_TYPEDEF(Brush);
AX_TYPEDEF(Pen);
AX_TYPEDEF(Rect);
AX_TYPEDEF(String);
AX_TYPEDEF(MenuBar);
AX_TYPEDEF(Menu);
AX_TYPEDEF(Dir);

typedef wxAutoBufferedPaintDC axDC; // Always use double buffer when possible

// EVENTS
AX_TYPEDEF(SizeEvent);
AX_TYPEDEF(MaximizeEvent);
AX_TYPEDEF(MouseEvent);
AX_TYPEDEF(CommandEvent);
AX_TYPEDEF(PaintEvent);

#define axT wxT
#define axGetCwd() wxGetCwd()

#include "axDebug.h"

#include "axMultipleBitmap.h"

#include "axButton.h"

#include "axToggle.h"

#include "axScrollBar.h"

#include "axTreeMenu.h"

#include "axSlider.h"

#endif