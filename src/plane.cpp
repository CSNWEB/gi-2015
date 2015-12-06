#include "plane.hpp"

Plane::Plane(float dx, float dy)
{
	this->dx = dx;
	this->dy = dy;

	forms = vector<Form>();
}

int Plane::get_number_of_forms()
{
	return forms.size();
}

Form *Plane::get_form_at(int i)
{
	if (i<forms.size())
		return &forms[i];
	else
		return NULL;
}

void Plane::add_form_at_position(AbstractForm *form, float pos_x, float pos_y)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

    add_form_at_position_rotation(form, pos_x, pos_y, 0.0);
}

void Plane::add_form_at_position_rotation(AbstractForm *form,
                                          float pos_x,
                                          float pos_y,
                                          float rotation)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

    Form form_object = Form(form, pos_x, pos_y);
    Point centroid = form_object.get_centroid();
    if (rotation > TOLERANCE)
    {
    	form_object.rotate(centroid.get_x(),
        	               centroid.get_y(),
            	           rotation);
    }
    else
    {
    	#ifdef DEBUG
    		printf("No rotation\n");
    	#endif
    }
    
    forms.push_back(form_object);
	number_of_forms++;
}

float Plane::compute_utilization()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	float utilization = 0;
	for (int i=0; i<forms.size(); ++i)
		utilization += (forms[i].get_mother())->get_size_of_area();
	return (utilization/(dx*dy));
}

bool Plane::check_if_legal()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

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