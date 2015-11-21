#include "binPackingShelf.hpp"

/*
BinPackingShelf::BinPackingShelf(int index_of_plane, float offset_height, float height, float width)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	this->index_of_plane 	= index_of_plane;
	this->offset_height 	= offset_height;
	this->height 			= height;
	remaining_width 		= width;
}
*/

BinPackingShelf::BinPackingShelf(float height, float width)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	this->height 			= height;
	remaining_width 		= width;
}

bool BinPackingShelf::add_form(AbstractForm *f, int index)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (f->get_dy() <= height && f->get_dx() <= remaining_width)
	{
		indices_of_forms.push_back(index);
		remaining_width -= f->get_dx();

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

bool BinPackingShelf::check_if_fit(AbstractForm *f)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (f->get_dy() <= height && f->get_dx() <= remaining_width)
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

int BinPackingShelf::get_number_of_forms_on_shelf()
{
	return indices_of_forms.size();
}

int BinPackingShelf::get_abstract_index_of_form_at(int index_of_form)
{
	return indices_of_forms[index_of_form];
}