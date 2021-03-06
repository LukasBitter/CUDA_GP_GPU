#pragma once

#include "cudaTools.h"
#include "Variateur_GPU.h"
#include "Animable_I_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Fractal: public Animable_I<uchar4>
    {

	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	Fractal(const Grid& grid, uint w, uint h, uint nMin, uint nMax, const DomaineMath& domaineMath);

	virtual ~Fractal(void);

	/*--------------------------------------*\
	 |*		Methode			*|
	 \*-------------------------------------*/

    public:

	virtual void startFractal(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath) =0;

	/*-------------------------*\
	|*   Override Animable_I   *|
	 \*------------------------*/


	/**
	 * Call periodicly by the api
	 */
	virtual void process(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath);

	/**
	 * Call periodicly by the api
	 */
	virtual void animationStep();

    private:


	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:
	// Tools
	Variateur<int> variateurAnimation;

    };


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
