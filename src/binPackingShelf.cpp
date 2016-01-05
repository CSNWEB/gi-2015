#include "binPackingShelf.hpp"

BinPackingShelf::BinPackingShelf(int plane, float width, float height, float offset_x, float offset_y)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	index_of_plane			= plane;

	this->width 			= width;
	this->height 			= height;
	remaining_width 		= width;

	this->offset_x 			= offset_x;
	this->offset_y 			= offset_y;
}

float BinPackingShelf::add_form(AbstractForm *f, int index)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	float max_h = f->get_dy();
	float max_w = f->get_dx();

	if ((max_h < height + GlobalParams::get_tolerance()) && (max_w < remaining_width + GlobalParams::get_tolerance()))
	{
		#ifdef DEBUG
			printf("\tForm sucessfully added to shelf:\n");
			printf("\t\tneeded dy = %.2f, height = %.2f\n\t\tneeded dx = %.2f, remaining width (before adding) = %.2f\n", max_h, height, max_w, remaining_width);
		#endif

		indices_of_forms.push_back(index);
		remaining_width -= max_w;

		return height-max_h;
	}
	else
	{
		#ifdef DEBUG
			printf("\tForm could not be added to shelf.\n");
			printf("\t\tneeded dy = %f, height = %f\n\t\tneeded dx = %f, remaining width = %f\n",  max_h, height, max_w, remaining_width);
		#endif

		return -1;
	}
}

bool BinPackingShelf::check_if_fit(AbstractForm *f)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if ((f->get_dy() < height + GlobalParams::get_tolerance()) && (f->get_dx() < remaining_width + GlobalParams::get_tolerance()))
		return true;
	else
		return false;
}

float BinPackingShelf::get_offset_x()
{
	return offset_x;
}

float BinPackingShelf::get_offset_y()
{
	return offset_y;
}

float BinPackingShelf::get_height()
{
	return height;
}

float BinPackingShelf::get_width()
{
	return width;
}

float BinPackingShelf::get_remaining_width()
{
	return remaining_width;
}

int BinPackingShelf::get_plane()
{
	return index_of_plane;
}

int BinPackingShelf::get_number_of_forms_on_shelf()
{
	return indices_of_forms.size();
}

int BinPackingShelf::get_abstract_index_of_form_at(int index_of_form)
{
	return indices_of_forms[index_of_form];
}