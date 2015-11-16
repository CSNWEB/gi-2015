#include "2DBP_shelf.hpp"

Shelf::Shelf(int index_of_plane, float offset_height, float height, float width)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: Shelf\n");
	#endif

	this->index_of_plane 	= index_of_plane;
	this->offset_height 	= offset_height;
	this->height 			= height;
	remaining_width 		= width;
}

bool Shelf::add_form(Form *f, int index)
{
	#ifdef DEBUG
		printf("FUNCTION: Shelf::add_form\n");
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

bool Shelf::check_if_fit(Form *f)
{
	#ifdef DEBUG
		printf("FUNCTION: Shelf::check_if_fit\n");
	#endif

	if (f->get_bounding_dy() <= height && f->get_bounding_dx() <= remaining_width)
	{
		return true;
	}
	else
		return false;
}

float Shelf::get_height()
{
	return height;
}

float Shelf::get_remaining_width()
{
	return remaining_width;
}