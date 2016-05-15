#pragma once

#include "cpptest.h"

using Test::Suite;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class TestHisto: public Suite
    {
    public:

	TestHisto(int deviceId);

    private:

	void testAdd(void);

    private:

	int deviceId;

    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

