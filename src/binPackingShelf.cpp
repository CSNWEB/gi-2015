#include "binPackingShelf.hpp"

BinPackingShelf::BinPackingShelf(int index_of_plane, float offset_height, float height, float width)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: BinPackingShelf\n");
	#endif

	this->index_of_plane 	= index_of_plane;
	this->offset_height 	= offset_height;
	this->height 			= height;
	remaining_width 		= width;
}

bool BinPackingShelf::add_form(Form *f, int index)
{
	#ifdef DEBUG
		printf("FUNCTION: BinPackingShelf::add_form\n");
	#endif

	if (f->get_bounding_dy() <= height && f->get_bounding_dx() <= remaining_width)
	{
		indices_of_forms.push_back(index);
		remaining_width -= f->get_bounding_dx();

		#ifdef DEBUG
			printf("\tForm fucessfully added to shelf.\n");
		#endif
		return true;
	}
	else
	{
		#ifdef DEBUG
			printf("\tForm could not be added to shelf.\n");
		#endif

		return false;
	}
}

bool BinPackingShelf::check_if_fit(Form *f)
{
	#ifdef DEBUG
		printf("FUNCTION: BinPackingShelf::check_if_fit\n");
	#endif

	if (f->get_bounding_dy() <= height && f->get_bounding_dx() <= remaining_width)
	{
		return true;
	}
	else
		return false;
}

float BinPackingShelf::get_height()
{
	return height;
}

float BinPackingShelf::get_remaining_width()
{
	return remaining_width;
}