#ifndef SRC_CPP_CORE_00_TOOLS_REDUCTIONTOOLS_H_
#define SRC_CPP_CORE_00_TOOLS_REDUCTIONTOOLS_H_

#include "Indice2D.h"
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
template<typename T>
class ReductionTools
    {
    public:
    __device__ static void reduce(T* tabSM, T* ptrDevResultatGM)
        {
	reduceIntraBloc(tabSM);
        reduceInterBloc(tabSM, ptrDevResultatGM);
        }

    private:
	__device__
	void reduceIntraBloc(T* tabSM)
	    {
	    int nSM = Indice2D::nbThreadLocal();
	    int moitie = nSM / 2;
	    while (moitie >= 1)
		{
		ecrasement(tabSM, moitie);
		moitie = moitie / 2;
		__synchthreads();
		}
	    }

	__device__
	void ecrasement(T* tabSM, int moitie)
	    {
	    const int NB_THREAD_LOCAL = Indice2D::nbThreadBlock();
	    //const int TID = Indice2D::tidLocal();
	    int s = Indice2D::tidLocal();
	    while (s < moitie)
		{
		tabSM[s] = tabSM[s] + tabSM[s + moitie];
		s += NB_THREAD_LOCAL;
		}
	    }

	__device__
	void reduceInterBloc(T* tabSM, T* ptrDevResGM)
	    {
	    if (Indice2D::tidBlock() == 0)
		{
		atomicAdd(ptrDevResGM, tabSM[0]);
		}
	    }

#endif 

	/*----------------------------------------------------------------------*\
 |*			End	 					*|
	 \*---------------------------------------------------------------------*/
