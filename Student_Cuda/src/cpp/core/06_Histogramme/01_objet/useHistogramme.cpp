#include <iostream>
#include "Histogramme.h"
#include <assert.h>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useHistogramme(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useHistogramme(void)
    {
    int nDataRange = 256;
    int nTabData = nDataRange * (nDataRange + 1) / 2;
    uchar* tabData = new uchar[nTabData];
    int* ptrHisto = new int;
    bool isOk = false;

    // Remplissage du tableau
    int s = 0;
    for (int i = 0; i < nDataRange; i++)
	{
	for (int j = 0; j <= i; j++)
	    {
	    tabData[s] = i;
	    s++;
	    }
	}
    // vérification que le tableau est rempli avec le bon nombre d'éléments
    assert(s == nTabData);

    Histogramme histo(tabData, nDataRange);
    ptrHisto = histo.run();

    // Vérification des données de l'histogramme
    int check = 0;
    for (int i = 0; i < nDataRange; i++)
	{
	check += (i + 1) % ptrHisto[i];
	}

    if (check == 0)
	{
	isOk = true;
	}

    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

