#include <iostream>
#include <assert.h>

#include <Device.h>
#include "Fractal.h"

using std::cout;
using std::endl;


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
Fractal::Fractal(const Grid& grid, uint w, uint h, uint nMin, uint nMax, const DomaineMath& domaineMath) :
	Animable_I<uchar4>(grid, w, h, "Fractal_CUDA_rgba_uchar4",domaineMath), variateurAnimation(Interval<int>(nMin, nMax), 1)
    {
    // Tools
    this->t = nMin;					// protected dans super classe Animable

    }

Fractal::~Fractal(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Surcharge			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */
void Fractal::process(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    Device::lastCudaError("mandelbrot rgba uchar4 (before)"); // facultatif, for debug only, remove for release

    // TODO lancer le kernel avec <<<dg,db>>>
    // le kernel est importer ci-dessus (ligne 19)

    startFractal(ptrTabPixels,w,h, domaineMath);

    Device::lastCudaError("rippling rgba uchar4 (after)"); // facultatif, for debug only, remove for release
    }

/**
 * Override
 */
void Fractal::animationStep()
    {
    this->t = variateurAnimation.varierAndGet(); // in [0,2pi]
    }


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
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

