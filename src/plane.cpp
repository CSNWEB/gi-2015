#include "plane.hpp"

int Plane::get_number_of_forms()
{
	return forms.size();
}

Form Plane::get_form_at(int i)
{
	if (i<forms.size())
		return forms[i];
	else
		return Form();
}

void Plane::add_form_at_position(AbstractForm *form, float pos_x, float pos_y)
{
	Form newform = Form(form, pos_x, pos_y);
	forms.push_back(newform);
	number_of_forms++;
}

bool Plane::check_if_legal()
{
	bool ret = true;
	for (int i=0; i<forms.size(); ++i)
		for (int j=i; j<forms.size(); ++j)
			if (overlappings[i][j] == true)
				ret = false;
	for (int i=0; i<forms.size(); ++i)
	{
		if (
				forms[i].get_bounding_xmin() < 0 ||
				forms[i].get_bounding_xmax() > dx ||
				forms[i].get_bounding_ymin() < 0 ||
				forms[i].get_bounding_xmax() > dy
			)
			ret = false;
	}

	return ret;
}