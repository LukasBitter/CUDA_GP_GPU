#pragma once

#include <math.h>
#include "MathTools.h"
#include <iostream>

#include "Calibreur_GPU.h"
#include "ColorTools_GPU.h"

using namespace gpu;

using std::cout;
using std::endl;
using namespace std;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

struct complexe{
	float re;
	float im;
};

class NewtonMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ NewtonMath(uint n) :
		calibreur(Interval<float>(0, n), Interval<float>(0, 1))
	    {
	    this->n = n;
	    }

	// constructeur copie automatique car pas pointeur dans
	//	NewtonMath
	// 	calibreur
	// 	IntervalF

	__device__
	    virtual ~NewtonMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorXY(uchar4* ptrColor, float x, float y)
	    {
	    complexe c;
	    c.re = x;
	    c.im = y;
	    int z = newton(c);

	    if (z < n)
		{
		float hue01 = z;
		calibreur.calibrer(hue01);
		ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color
		}
	    else
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}

	    ptrColor->w = 255; // opaque
	    }
    private:


	__device__ complexe f1(complexe x) {
		complexe d;
		d.re =  x.re * x.re * x.re - 3 * x.re * x.im * x.im - 1;
		return d;
	}

	__device__ complexe f2(complexe y) {
		complexe d;
		d.im = y.im * y.im * y.im - 3 * y.re * y.re * y.im;
		return d;
		}


	__device__ float newton(complexe x0) {
	  complexe x = x0;
	  float limit = 0.001;
	  int i = 0;
	  while (sqrt(x.re*x.re + x.im*x.im) > limit && i <= n) {
	    i++;
	    x.re = x.re - f1(x).re/f2(x).re;
	    x.im = x.im - f1(x).im/f2(x).im;
	  }
	  return i;
	}
	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    protected:

	// Input
	uint n;

    private:

	// Tools
	Calibreur<float> calibreur;

    };
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


