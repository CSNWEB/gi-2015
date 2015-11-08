#include "plane.hpp"

void Plane::add_form_at_position(AbstractForm *form, float pos_x, float pos_y)
{
	Form newform = Form(form, pos_x, pos_y);
	forms.push_back(newform);
	number_of_forms++;
}