#include <iostream>
#include <limits.h>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

#include "MonteCarlo.h"

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMonteCarlo(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMonteCarlo()
    {
    float M = 10;
    int nbFlechettes = INT_MAX / 1000;

    // Partie interessante
	{
	MonteCarlo monteCarlo(M, nbFlechettes);
	monteCarlo.run();
	cout << monteCarlo.getPI() << endl;
	}

    // TODO: bool isOk = VectorTools::isAddVector_Ok(ptrV1, ptrV2, ptrW, n);

    return true; // TODO: isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
