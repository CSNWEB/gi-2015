#include "globalParams.hpp"

float GlobalParams::get_tolerance()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (tolerance_digits == 0)
	{
		tolerance_digits = 4;
		tolerance = 1E-4;
	}

	return tolerance;
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