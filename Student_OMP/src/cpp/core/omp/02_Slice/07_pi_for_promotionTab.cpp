#include <omp.h>
#include "MathTools.h"
#include "OmpTools.h"
#include "../02_Slice/00_pi_tools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforPromotionTab_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforPromotionTab(int n);
static void syntaxeSimplifier(double* tabSumThread, int n);
static void syntaxeFull(double* tabSumThread, int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforPromotionTab_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforPromotionTab, n, "Pi OMP for promotion tab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * De-synchronisation avec PromotionTab
 */
double piOMPforPromotionTab(int n)
    {
    const int NB_THREAD = OmpTools::setAndGetNaturalGranularity();
    const double DX = 1 / (double) n;
    double xi;
    double sum = 0;
    double* ptrTabThread = new double[NB_THREAD];
    for (int i = 0; i < NB_THREAD; i++)
	{
	ptrTabThread[i] = 0;
	}

#pragma omp parallel for private(xi)
    for (int i = 1; i <= n; i++)
	{
	int TID = OmpTools::getTid();
	xi = i * DX;
	ptrTabThread[TID] += fpi(xi);
	}

    // Reduction sequentielle
    for (int i = 0; i < NB_THREAD; i++)
	{
	sum += ptrTabThread[i];
	}
    delete[] ptrTabThread;
    return sum / n;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

