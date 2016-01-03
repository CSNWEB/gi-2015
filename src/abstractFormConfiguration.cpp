#include "abstractFormConfiguration.hpp"

AbstractFormConfiguration(AbstractForm *form, float position_x, float position_y, float rotation, float min_x, float max_x, float min_y, float max_y)
{
	abstractforms = vector<AbstractForm*>(1, form);
	position_x_of_forms = vector<float>(1, position_x);
	position_y_of_forms = vector<float>(1, position_y);
	rotation_of_forms = vector<float>(1, rotation);

	this->min_x = min_x;
	this->max_x = max_x;
	this->min_y = min_y;
	this->max_y = max_y;

	dx = max_x-min_x;
	dy = max_y-min_y;

	used_area = form->get_size_of_area();
	utilization = used_area / (dx*dy);
}

AbstractFormConfiguration(AbstractForm *form, float position_x, float position_y, float rotation)
{
	abstractforms = vector<AbstractForm*>(1, form);
	position_x_of_forms = vector<float>(1, position_x);
	position_y_of_forms = vector<float>(1, position_y);
	rotation_of_forms = vector<float>(1, rotation);

	update_bounding_box(form, position_x, position_y, rotation, false);
}

void AbstractFormConfiguration::update_bounding_box(AbstractForm *form, float pos_x, float pos_y, float rotation, bool is_initialized)
{
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

	dx = max_x-min_x;
	dy = max_y-min_y;

	used_area = form->get_size_of_area();
	utilization = used_area / (dx*dy);
}

void AbstractFormConfiguration::add_abstract_form(AbstractForm* form, float position_x, float position_y, float rotation)
{
	abstractforms.push_back(form);
	position_x_of_forms.push_back(position_x);
	position_y_of_forms.push_back(position_y);
	rotation_of_forms.push_back(rotation);

	update_bounding_box(form, position_x, position_y, rotation, true);
}

bool AbstractFormConfiguration::get_configuration_of_form(int index_of_form, float &dx, float &dy, float &rotation)
{
	if (index_of_form >= abstractforms.size())
		return false;
	
	dx = position_x_of_forms(index_of_form);
	dy = position_y_of_forms(index_of_form);
	rotation = rotation_of_forms(index_of_form);
}

bool AbstractFormConfiguration::contains_form(int id_of_form)
{
	for (int i=0; i<abstractforms.size(); ++i)
	{
		if (abstractforms[i].get_id() == id_of_form)
			return true;
	}

	return false;
}