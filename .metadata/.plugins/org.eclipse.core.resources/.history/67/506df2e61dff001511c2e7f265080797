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

class Mandelbrot: public Fractal
    {

	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	Mandelbrot(const Grid& grid, uint w, uint h, uint nMin, uint nMax, const DomaineMath& domaineMath);

	virtual ~Mandelbrot(void);

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

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
