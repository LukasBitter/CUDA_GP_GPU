#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>

#include "Device.h"
#include "cudaTools.h"

#include "RipplingProvider.h"
#include "MandelbrotProvider.h"
#include "JuliaProvider.h"

#include "Settings_GPU.h"
#include "Viewer_GPU.h"
using namespace gpu;

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainDemoImage(Settings& settings);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainDemoImage(Settings& settings)
    {
    cout << "\n[Image] mode" << endl;

    GLUTImageViewers::init(settings.getArgc(), settings.getArgv()); //only once

    // ImageOption : (boolean,boolean) : (isSelection,isAnimation)
    ImageOption zoomable(true);
    ImageOption nozoomable(false);

    Display* d = XOpenDisplay(NULL);
    Screen* s = DefaultScreenOfDisplay(d);
    int w = s->width;
    int h = s->height;

    Viewer<RipplingProvider> vague(nozoomable, 0, 0); // imageOption px py
    Viewer<MandelbrotProvider> mandel(zoomable, 6*60+10, 0); // imageOption px py
    Viewer<JuliaProvider> julia(zoomable, 6*60+10,6*60+60 ); // imageOption px py

    // Common
    GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    cout << "\n[Image] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

