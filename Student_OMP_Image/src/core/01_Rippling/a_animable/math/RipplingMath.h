#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_CPU.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*------c--------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingMath
    {
	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	RipplingMath(uint w)
	    {
	    this->dim2 = w / 2;
	    }

	// constructeur copie: pas besoin car pas attribut ptr

	virtual ~RipplingMath(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	void colorIJ(uchar4* ptrColorIJ, int i, int j, float t)
	    {
	    uchar levelGris;

	    f(j, i, t, &levelGris);

	    ptrColorIJ->x = levelGris;
	    ptrColorIJ->y = levelGris;
	    ptrColorIJ->z = levelGris;

	    ptrColorIJ->w = 255; //opaque
	    }

    private:

	void f(int i, int j, float t, uchar* ptrlevelGris)
	    {
	    float dijValue;
	    dij(i, j, &dijValue);
	    *ptrlevelGris = 128 + 127 * cos(dijValue / 10 - t / 7) / (dijValue / 10 + 1);

	    }

	void dij(int i, int j, float* ptrResult)
	    {
	    double fi = i - this->dim2;
	    double fj = j - this->dim2;

	    *ptrResult = sqrt(fi*fi + fj*fj);

	    }

	/*--------------------------------------*\
	|*		Attribut			*|
	 \*-------------------------------------*/

    private:

	// Tools
	double dim2;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
