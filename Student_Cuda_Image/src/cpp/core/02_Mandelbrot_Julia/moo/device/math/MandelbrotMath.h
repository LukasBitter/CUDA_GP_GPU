#pragma once

#include <math.h>
#include "MathTools.h"
#include <iostream>

#include "Calibreur_GPU.h"
#include "ColorTools_GPU.h"
#include "FractalMath.h"

using namespace gpu;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath: public FractalMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ MandelbrotMath(uint n) :
		FractalMath(n)
	    {
	    }

	// constructeur copie automatique car pas pointeur dans
	//	MandelbrotMath
	// 	calibreur
	// 	IntervalF

	__device__
	  virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    private:

	__device__
	int f(float x, float y)
	    {
	    float a = 0;
	    float b = 0;
	    int k = 0;
	    float aCopy;

	    while ((a * a + b * b) <= 4 && k <= n)
		{
		aCopy = a;
		a = (a * a - b * b) + x;
		b = 2 * aCopy * b + y;
		k++;
		}

	    return k;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    };
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

