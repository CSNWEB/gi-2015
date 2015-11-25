#include "binPackingShelf.hpp"

BinPackingShelf::BinPackingShelf(float width, float height)
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

	float max_h = f->get_dy();
	float max_w = f->get_dx();

	if ((max_h <= height) && (max_w <= remaining_width))
	{
		#ifdef DEBUG
			printf("\tForm fucessfully added to shelf:\n");
			printf("\t\tneeded dy = %.2f, height = %.2f\n\t\tneeded dx = %.2f, remaining width = %.2f\n", max_h, height, max_w, remaining_width);
		#endif

		indices_of_forms.push_back(index);
		remaining_width -= f->get_dx();

		return true;
	}
	else
	{
		#ifdef DEBUG
			printf("\tForm could not be added to shelf.\n");
			printf("\t\tneeded dy = %f, height = %f\n\t\tneeded dx = %f, remaining width = %f\n",  max_h, height, max_w, remaining_width);
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