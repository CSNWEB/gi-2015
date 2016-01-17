#include "binPackingPlane.hpp"

BinPackingPlane::BinPackingPlane(float dx, float dy)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	this->dx = dx;
	this->dy = dy;

	remaining_height = dy;
}

bool BinPackingPlane::add_shelf(float height_of_shelf)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (remaining_height + GlobalParams::get_tolerance() > height_of_shelf)
	{
		remaining_height -= height_of_shelf;
		return true;
	}
	else
		return false;
}

float BinPackingPlane::get_remaining_height()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	return remaining_height;
}