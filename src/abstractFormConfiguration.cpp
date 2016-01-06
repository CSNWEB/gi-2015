#include "abstractFormConfiguration.hpp"

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

	number_of_usages = -1;
}

AbstractFormConfiguration::AbstractFormConfiguration(AbstractForm *form, float position_x, float position_y, float rotation)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	abstractforms = vector<AbstractForm*>(1, form);
	position_x_of_forms = vector<float>(1, position_x);
	position_y_of_forms = vector<float>(1, position_y);
	rotation_of_forms = vector<float>(1, rotation);
	mirrored_forms = vector<bool>(1, false);

	update_bounding_box(form, position_x, position_y, rotation, false);

	number_of_usages = -1;
}

void AbstractFormConfiguration::update_bounding_box(AbstractForm *form, float pos_x, float pos_y, float rotation, bool is_initialized)
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

	dx = max_x-min_x;
	dy = max_y-min_y;

	used_area = form->get_size_of_area();
	utilization = used_area / (dx*dy);
}

void AbstractFormConfiguration::add_abstract_form(AbstractForm* form, float position_x, float position_y, float rotation, bool is_mirrored)
{
	abstractforms.push_back(form);
	position_x_of_forms.push_back(position_x);
	position_y_of_forms.push_back(position_y);
	rotation_of_forms.push_back(rotation);
	mirrored_forms.push_back(is_mirrored);

	update_bounding_box(form, position_x, position_y, rotation, true);
}

bool AbstractFormConfiguration::get_configuration_of_form(int index_of_form, float &dx, float &dy, float &rotation)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (index_of_form >= abstractforms.size())
		return false;
	
	dx = position_x_of_forms[index_of_form];
	dy = position_y_of_forms[index_of_form];
	rotation = rotation_of_forms[index_of_form];
}

bool AbstractFormConfiguration::contains_form(int id_of_form)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	for (int i=0; i<abstractforms.size(); ++i)
	{
		if (abstractforms[i]->get_id() == id_of_form)
			return true;
	}

	return false;
}