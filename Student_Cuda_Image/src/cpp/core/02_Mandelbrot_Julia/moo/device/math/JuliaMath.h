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

class JuliaMath: public FractalMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ JuliaMath(uint n, float c1, float c2) :
		FractalMath(n)
	    {
	    this->c1 = c1;
	    this->c2 = c2;
	    }

	// constructeur copie automatique car pas pointeur dans
	//	JuliaMath
	// 	calibreur
	// 	IntervalF

	__device__
	  virtual ~JuliaMath()
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
	    float a = x;
	    float b = y;
	    int k = 0;
	    float aCopy;

	    while ((a * a + b * b) <= 4 && k <= n)
		{
		aCopy = a;
		a = (a * a - b * b) + c1;
		b = 2 * aCopy * b + c2;
		k++;
		}

	    return k;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:
	// Inputs
	float c1;
	float c2;

    };
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

