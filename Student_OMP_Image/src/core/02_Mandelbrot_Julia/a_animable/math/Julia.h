#pragma once

#include <math.h>
#include "MathTools.h"
#include <iostream>

#include "../../../../../../BilatTools_CPP/src/core/tools/header/namespace_cpu/cudaType_CPU.h"
#include "../../../../../../BilatTools_CPP/src/core/tools/header/namespace_cpu/Calibreur_CPU.h"
#include "../../../../../../BilatTools_CPP/src/core/tools/header/namespace_cpu/ColorTools_CPU.h"
#include "../../../../../../BilatTools_CPP/src/core/tools/header/namespace_cpu/Interval_CPU.h"

using namespace cpu;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class JuliaMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	JuliaMath(uint n) :
		calibreur(Interval<float>(-1, 1), Interval<float>(0, 1))
	    {
	    this->n = n;
	    }

	// constructeur copie automatique car pas pointeur dans
	//	JuliaMath
	// 	calibreur
	// 	IntervalF

	virtual ~JuliaMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void colorXY(uchar4* ptrColor, float x, float y, float t)
	    {
	    float z = f(x, y, t);
	    //float z = fDamier(x, y, t);

	    calibreur.calibrer(z);
	    float hue01 = z;

	    ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color

	    ptrColor->w = 255; // opaque
	    }

    private:

	float f(float x, float y, float c1, float c2)
	    {
	    float a = x;
	    float b = y;
	    int k = 0;
	    float aCopy;

	    while ((a * a + b * b) <= 4.0 && k <= n)
		{
		aCopy = a;
		a = (a * a - b * b) + c1;
		b = 2.0 * aCopy * b + c2;
		k++;
		}

	    if (x == 0.0)
		cout << "x: " << x << "/ k: " << k <<endl;
	    if( k > n)
		return h(0);
	    else
		return h(k);
	    }

	float h(int k){
	    return (1.0*k)/n;
	}

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	uint n;

	// Tools
	Calibreur<float> calibreur;

    };
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

