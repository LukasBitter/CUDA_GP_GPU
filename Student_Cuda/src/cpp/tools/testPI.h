#include <iostream>
#include <stdlib.h>
#include <math.h>

class TestPI
    {

    public:
	static bool IsPiCorrect(float pi_test)
	    {
	    const float PI = 3.141592653589793f;
	    const float epsylon = 0.005f;
	    float val_abs = pi_test - PI > PI - pi_test ? pi_test - PI : PI - pi_test;

	    return  val_abs <= epsylon;
	    }
    };
