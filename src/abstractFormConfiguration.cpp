#include "abstractFormConfiguration.hpp"

/*
AbstractFormConfiguration::AbstractFormConfiguration(AbstractForm* form, float position_x, float position_y, float rotation, float min_x, float max_x, float min_y, float max_y)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	abstractforms = vector<AbstractForm*>(1, form);
	position_x_of_forms = vector<float>(1, position_x);
	position_y_of_forms = vector<float>(1, position_y);
	rotation_of_forms = vector<float>(1, rotation);
	mirrored_forms = vector<bool>(1, false);

	this->min_x = min_x;
	this->max_x = max_x;
	this->min_y = min_y;
	this->max_y = max_y;

	dx = max_x-min_x;
	dy = max_y-min_y;

	used_area = form->get_size_of_area();
	utilization = used_area / (dx*dy);

	number_of_forms_needed = -1;
}
*/

AbstractFormConfiguration::AbstractFormConfiguration(AbstractForm *form, float position_x, float position_y, float rotation, bool mirrored, int number_of_forms_needed)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	this->form = form;
	position_x_of_form = position_x;
	position_y_of_form = position_y;
	rotation_of_form   = rotation;
	mirrored_form      = mirrored;

	update_bounding_box(position_x, position_y, rotation, false);

	this->number_of_forms_needed = number_of_forms_needed;
}

void AbstractFormConfiguration::update_bounding_box(float pos_x, float pos_y, float rotation, bool is_initialized)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (!is_initialized)
	{
		Point p_temp = form->get_point_at_index(0);
		p_temp.rotate(rotation);
		p_temp.move_rel(pos_x, pos_y);
		min_x = p_temp.get_x();
		max_x = min_x;
		min_y = p_temp.get_y();
		max_y = min_y;
	}

	for (int i=1; i < form->get_number_of_points(); ++i)
	{
		Point p_temp = form->get_point_at_index(i);
		p_temp.rotate(rotation);
		p_temp.move_rel(pos_x, pos_y);
		
		float temp_x = p_temp.get_x();
		float temp_y = p_temp.get_y();

		if (temp_x < min_x)
			min_x = temp_x;
		else if (temp_x > max_x)
			max_x = temp_x;

		if (temp_y < min_y)
			min_y = temp_y;
		else if (temp_y > max_y)
			max_y = temp_y;
	}
}

void AbstractFormConfiguration::move(float dx, float dy)
{
	position_x_of_form += dx;
	position_y_of_form += dy;

	min_x += dx;
	max_x += dx;
	min_y += dy;
	max_y += dy;
}

void AbstractFormConfiguration::rotate(float angle)
{
	rotation_of_form += angle;

	float s = sin(rotation_of_form * GlobalParams::pi()/180);
    float c = cos(rotation_of_form * GlobalParams::pi()/180);

	float new_x = (position_x_of_form * c) - (position_y_of_form * s);
	float new_y = (position_x_of_form * s) + (position_y_of_form * s);

	position_x_of_form = new_x;
	position_y_of_form = new_y;

	update_bounding_box(position_x_of_form, position_y_of_form, rotation_of_form, false);
}