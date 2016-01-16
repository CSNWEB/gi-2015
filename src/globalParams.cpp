#include "globalParams.hpp"


float GlobalParams::get_tolerance()
{
	#ifdef DEBUG
		//printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
		//printf("TOLERACE is %f\n", tolerance);
	#endif
	return tolerance;
}

void GlobalParams::set_tolerance(double new_tolerance){
    tolerance = new_tolerance;
}



float GlobalParams::tolerance = 1E-4;
bool GlobalParams::option_pre_merge_form = true;
