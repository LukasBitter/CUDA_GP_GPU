#include <iostream>
#include <assert.h>

#include <Device.h>
#include "Julia.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

extern __global__ void julia(uchar4* ptrTabPixels,uint w, uint h, uint t, float c1, float c2, DomaineMath domaineMath);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
Julia::Julia(const Grid& grid, uint w, uint h, uint nMin, uint nMax, float c1, float c2, const DomaineMath& domaineMath) :
	Fractal(grid, w, h, nMin, nMax, domaineMath)
    {
    //Inputs
    this->c1 = c1;
    this->c2 = c2;

    }

Julia::~Julia(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Surcharge		*|
 \*-------------------------------------*/

void Julia::startFractal(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {

	julia<<<dg,db>>>(ptrTabPixels,w,h, t, c1, c2, domaineMath);
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


/*--------------------------------------*\
 |*		Attributes		*|
 \*-------------------------------------*/


