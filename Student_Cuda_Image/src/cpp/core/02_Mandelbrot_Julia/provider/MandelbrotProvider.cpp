#include "MandelbrotProvider.h"
#include "Mandelbrot.h"

#include "MathTools.h"
#include "Grid.h"

#include "ImageAnimable_GPU.h"
#include "DomaineMath_GPU.h"

using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Surcharge		*|
 \*-------------------------------------*/

/**
 * Override
 */
Animable_I<uchar4>* MandelbrotProvider::createAnimable(void)
    {
    //DomaineMath domaineMath = DomaineMath(0, 0, 2 * PI, 2 * PI);
    //DomaineMath domaineMath = DomaineMath(-2.1, -1.3, 0.8, 1.3);
    //DomaineMath domaineMath = DomaineMath(-1.7, -1.3, 1.3, 0.8);
    DomaineMath domaineMath = DomaineMath(-1.3578, 0.0013973, -1.3968, -0.03362);


    // Animation;
    uint nMin = 20;
    uint nMax = 100;

    // Dimension
    int dw = 6 * 60 * 2;
    int dh = 6 * 60;

    // Grid Cuda
    dim3 dg = dim3(32, 1, 1);  		// disons a optimiser, depend du gpu
    dim3 db = dim3(32, 1, 1);   	// disons a optimiser, depend du gpu
    Grid grid(dg, db);  // TODO definissez une grille cuda (dg, db)

    return new Mandelbrot(grid, dw, dh, nMin, nMax, domaineMath);
    }

/**
 * Override
 */
Image_I* MandelbrotProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 0, 0); // black
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

