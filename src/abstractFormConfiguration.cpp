#include "abstractFormConfiguration.hpp"

#ifdef DEBUG
	#define DEBUG_AFC
#endif

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

	min_x = form->get_x();
	max_x = min_x + form->get_dx();

	min_y = form->get_y();
	max_y = min_y + form->get_dy();

	this->number_of_forms_needed = number_of_forms_needed;
}

void AbstractFormConfiguration::compute_bounding_box()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	vector<Point> p_temp(form->get_number_of_points());

	for (int i=0; i<p_temp.size(); ++i)
	{
		p_temp[i] = form->get_point_at_index(i);
		//p_temp[i].move_rel(position_x_of_form, position_y_of_form);

		if (i==0)
		{
			min_x = p_temp[0].get_x();
			max_x = min_x;
			min_y = p_temp[0].get_y();
			max_y = min_y;
		}
		else
		{
			float x_temp = p_temp[i].get_x();
			if(x_temp < min_x)
				min_x = x_temp;
			else if (x_temp > max_x)
				max_x = x_temp;
			float y_temp = p_temp[i].get_y();
			if(y_temp < min_y)
				min_y = y_temp;
			else if (y_temp > max_y)
				max_y = y_temp;
		}
	}

	if (mirrored_form)
		PointSetAlgorithms::mirror_pointset_at_axis(p_temp, min_y, max_y);

	#ifdef DEBUG_AFC
		printf("Points pre rotation:\n");
		for (int i=0; i<p_temp.size(); ++i)
		{
			printf("(%.2f/%.2f) ", p_temp[i].get_x(), p_temp[i].get_y());
		}
		printf("\n");
	#endif

	PointSetAlgorithms::rotate_pointset_at_point(p_temp, 0, 0, rotation_of_form, min_x, max_x, min_y, max_y);

	#ifdef DEBUG_AFC
		printf("Points post rotation:\n");
		for (int i=0; i<p_temp.size(); ++i)
		{
			printf("(%.2f/%.2f) ", p_temp[i].get_x(), p_temp[i].get_y());
		}
		printf("\n");
	#endif

	min_x += position_x_of_form;
	max_x += position_x_of_form;
	min_y += position_y_of_form;
	max_y += position_y_of_form;

}

void AbstractFormConfiguration::mirror()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	mirrored_form = !mirrored_form;
}

void AbstractFormConfiguration::move(float dx, float dy)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	position_x_of_form += dx;
	position_y_of_form += dy;

	min_x += dx;
	max_x += dx;
	min_y += dy;
	max_y += dy;
}

void AbstractFormConfiguration::rotate(float angle)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	rotation_of_form += angle;
	if (rotation_of_form >= 360)
		rotation_of_form -= 360;
	if (rotation_of_form < 0)
		rotation_of_form += 360;

	float s = sin(angle * GlobalParams::pi()/180);
    float c = cos(angle * GlobalParams::pi()/180);

	float new_pos_x = (position_x_of_form * c) - (position_y_of_form * s);
	float new_pos_y = (position_x_of_form * s) + (position_y_of_form * c);

	position_x_of_form = new_pos_x;
	position_y_of_form = new_pos_y;

	compute_bounding_box();
}

#ifdef DEBUG_AFC
	#undef DEBUG_AFC
#endif