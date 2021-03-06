#pragma once

#include "cudaTools.h"
#include "Variateur_GPU.h"
#include "Animable_I_GPU.h"
#include "Fractal.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Julia: public Fractal
    {

	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	Julia(const Grid& grid, uint w, uint h, uint nMin, uint nMax, float c1, float c2, const DomaineMath& domaineMath);

	virtual ~Julia(void);

	/*--------------------------------------*\
	 |*		Methode			*|
	 \*-------------------------------------*/

    public:

	void startFractal(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath);

	/*-------------------------*\
	|*   Override Fractal      *|
	 \*------------------------*/

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

	// Inputs
	private:

	    float c1;
	    float c2;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
