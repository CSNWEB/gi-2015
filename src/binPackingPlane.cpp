#include "binPackingPlane.hpp"

BinPackingPlane::BinPackingPlane(float dx, float dy)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	this->dx = dx;
	this->dy = dy;

	remaining_height = dy;

	//shelfs = vector<BinPackingShelf>();
}

bool BinPackingPlane::add_shelf(float height_of_shelf)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (remaining_height + GlobalParams::get_tolerance() > height_of_shelf)
	{
		//shelfs.push_back(BinPackingShelf(dx, height_of_shelf));
		remaining_height -= height_of_shelf;
		return true;
	}
	else
		return false;
}

/*
int BinPackingPlane::get_number_of_shelfs()
{

	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	return shelfs.size();
}

BinPackingShelf* BinPackingPlane::get_shelf_at(int index_of_shelf)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (index_of_shelf >= 0 && index_of_shelf <shelfs.size())
		return &(shelfs[index_of_shelf]);
	else
		return NULL;
}
*/

float BinPackingPlane::get_remaining_height()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	return remaining_height;
}