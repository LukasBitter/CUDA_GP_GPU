#include "RayProvider.h"

#include "Ray.h"

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
Animable_I<uchar4>* RayProvider::createAnimable(void)
    {
    DomaineMath domaineMath = DomaineMath(-1.3, -1.4, 1.3, 1.4);

    // Animation;
    uint nMin = 0;
    uint nMax = 100;

    // Dimension
    int dw = 6 * 60 * 2;
    int dh = 6 * 60;

    // Grid Cuda
    dim3 dg = dim3(32, 1, 1);  		// disons a optimiser, depend du gpu
    dim3 db = dim3(480, 1, 1);   	// disons a optimiser, depend du gpu
    Grid grid(dg, db);  // TODO definissez une grille cuda (dg, db)

return new Ray(grid, dw, dh, nMin, nMax, domaineMath);
}

/**
 * Override
 */
Image_I* RayProvider::createImageGL(void)
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

