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

class RayMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ RayMath(uint n) :
		calibreur(Interval<float>(0, n), Interval<float>(0, 1))
	    {
	    this->n = n;
	    }

	// constructeur copie automatique car pas pointeur dans
	//	NewtonMath
	// 	calibreur
	// 	IntervalF

	__device__
	    virtual ~RayMath()
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
	    int z = ray(x, y);

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


	__device__ float ray(int x, int y) {

	  return 0;
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


