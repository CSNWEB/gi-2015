#include "globalParams.hpp"

void GlobalParams::init()
{
    if (tolerance_digits == 0)
    {
        tolerance_digits = 4;
        tolerance = 1E-4;
    }
    is_init = true;
}

float GlobalParams::get_tolerance()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

    //if(!is_init) GlobalParams::init();

	return tolerance;
}

int GlobalParams::get_tolerance_digits()
{
    //if(!is_init) GlobalParams::init();

    return tolerance_digits;
}


void GlobalParams::set_significant_digits(int digits)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	tolerance_digits = digits;
	tolerance = pow(10, (-1)*digits);
}

float GlobalParams::tolerance = 1E-4;
int GlobalParams::tolerance_digits = 4;
bool GlobalParams::is_init = false;

