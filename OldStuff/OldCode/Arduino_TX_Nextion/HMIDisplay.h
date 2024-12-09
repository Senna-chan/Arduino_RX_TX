#ifndef _HMIDISPLAY_h
#define _HMIDISPLAY_h

#include <NexWaveform.h>
#include <NexVariable.h>
#include <NexUpload.h>
#include <NexTouch.h>
#include <Nextion.h>
#include <NexTimer.h>
#include <NexText.h>
#include <NexSlider.h>
#include <NexScrolltext.h>
#include <NexRtc.h>
#include <NexRadio.h>
#include <NexProgressBar.h>
#include <NexPicture.h>
#include <NexPage.h>
#include <NexObject.h>
#include <NexNumber.h>
#include <NexHotspot.h>
#include <NexHardware.h>
#include <NexGpio.h>
#include <NexGauge.h>
#include <NexDualStateButton.h>
#include <NexCrop.h>
#include <NexConfig.h>
#include <NexCheckbox.h>
#include <NexButton.h>
#include <doxygen.h>

extern int currentPage;

extern NexPage page0;
extern NexButton b0p0;
extern NexButton b1p0;
extern NexButton b2p0;

extern NexPage page1;
extern NexButton l0p1;
extern NexNumber r0p1;
extern NexNumber t0p1;
extern NexHotspot m0p1;
extern NexButton h0p1;
extern NexNumber o0p1;
extern NexButton l1p1;
extern NexNumber r1p1;
extern NexNumber t1p1;
extern NexHotspot m1p1;
extern NexButton h1p1;
extern NexNumber o1p1;
extern NexButton l2p1;
extern NexNumber r2p1;
extern NexNumber t2p1;
extern NexHotspot m2p1;
extern NexButton h2p1;
extern NexNumber o2p1;
extern NexButton l3p1;
extern NexNumber r3p1;
extern NexNumber t3p1;
extern NexHotspot m3p1;
extern NexButton h3p1;
extern NexNumber o3p1;
extern NexButton l4p1;
extern NexNumber r4p1;
extern NexNumber t4p1;
extern NexHotspot m4p1;
extern NexButton h4p1;
extern NexNumber o4p1;
extern NexButton l5p1;
extern NexNumber r5p1;
extern NexNumber t5p1;
extern NexHotspot m5p1;
extern NexButton h5p1;
extern NexNumber o5p1;
extern NexButton l6p1;
extern NexNumber r6p1;
extern NexNumber t6p1;
extern NexHotspot m6p1;
extern NexButton h6p1;
extern NexNumber o6p1;
extern NexButton l7p1;
extern NexNumber r7p1;
extern NexNumber t7p1;
extern NexHotspot m7p1;
extern NexButton h7p1;
extern NexNumber o7p1;
extern NexButton saveButton0p1;
extern NexSlider deadzone0p1;
extern NexText deadzonev0p1;

extern NexPage page2;
extern NexNumber n0p2;
extern NexNumber n1p2;
extern NexNumber n2p2;
extern NexNumber n3p2;
extern NexNumber n4p2;
extern NexNumber n5p2;
extern NexNumber n6p2;
extern NexNumber n7p2;
extern NexText t0p2;
extern NexText t1p2;
extern NexText t2p2;
extern NexText t3p2;
extern NexText t4p2;
extern NexText t5p2;
extern NexText t6p2;
extern NexText t7p2;
extern NexText t8p2;
extern NexText t9p2;
extern NexButton b0p2;
extern NexText bools0p2;

extern NexPage page3;
extern NexDSButton rev0p3;
extern NexDSButton rev1p3;
extern NexDSButton rev2p3;
extern NexDSButton rev3p3;
extern NexDSButton rev4p3;
extern NexDSButton rev5p3;
extern NexDSButton rev6p3;
extern NexDSButton rev7p3;
extern NexDSButton rev8p3;
extern NexDSButton rev9p3;
extern NexDSButton rev10p3;
extern NexDSButton rev11p3;
extern NexDSButton rev12p3;
extern NexDSButton rev13p3;
extern NexDSButton rev14p3;
extern NexDSButton rev15p3;
extern NexButton saveButton0p3;


extern NexTouch *Nex_listen_list[];

void InitNextion();

//region usercode

//endregion usercode
#endif
