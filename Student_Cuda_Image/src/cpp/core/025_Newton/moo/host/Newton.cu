#include <iostream>
#include <assert.h>

#include <Device.h>
#include "Newton.h"

using std::cout;
using std::endl;


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

extern __global__ void newton(uchar4* ptrTabPixels,uint w, uint h, uint t, DomaineMath domaineMath);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
Newton::Newton(const Grid& grid, uint w, uint h, uint nMin, uint nMax, const DomaineMath& domaineMath) :
	Animable_I<uchar4>(grid, w, h, "Newton_CUDA_rgba_uchar4",domaineMath), variateurAnimation(Interval<int>(nMin, nMax), 1)
    {
    // Tools
    this->t = nMin;					// protected dans super classe Animable

    }

Newton::~Newton(void)
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
void Newton::process(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    Device::lastCudaError("newton rgba uchar4 (before)"); // facultatif, for debug only, remove for release

    // TODO lancer le kernel avec <<<dg,db>>>
    // le kernel est importer ci-dessus (ligne 19)

    newton<<<dg,db>>>(ptrTabPixels,w,h,t, domaineMath);

    Device::lastCudaError("rippling rgba uchar4 (after)"); // facultatif, for debug only, remove for release
    }

/**
 * Override
 */
void Newton::animationStep()
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

