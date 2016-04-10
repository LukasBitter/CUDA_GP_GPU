#include <iostream>
#include <assert.h>

#include <Device.h>
#include "Mandelbrot.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

extern __global__ void mandelbrot(uchar4* ptrTabPixels,uint w, uint h, uint t, DomaineMath domaineMath);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
Mandelbrot::Mandelbrot(const Grid& grid, uint w, uint h, uint nMin, uint nMax, const DomaineMath& domaineMath) :
	Fractal(grid, w, h, nMin, nMax, domaineMath)
    {
    // Tools
    this->t = nMin;					// protected dans super classe Animable

    }

Mandelbrot::~Mandelbrot(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Surcharge		*|
 \*-------------------------------------*/

void Mandelbrot::startFractal(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {

    mandelbrot<<<dg,db>>>(ptrTabPixels,w,h,t, domaineMath);
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

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

