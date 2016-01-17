#include "plane.hpp"

Plane::Plane(float dx, float dy)
{
	this->dx = dx;
	this->dy = dy;

	forms = vector<Form>(0);

}

int Plane::get_number_of_forms()
{
	return forms.size();
}

bool Plane::get_form_at(int i, Form &form)
{
	if (i<forms.size())
	{
        form = forms[i];
		return true;
	}
	else
		return false;
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
                                          float rotation,
                                          bool mirror)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

    Form form_object = Form(form, 0, 0);

    if (mirror)
    	form_object.mirror();

    if (rotation > GlobalParams::get_tolerance())
    {
    	form_object.rotate(0,
        	               0,
            	           rotation);
    }
    else
    {
    	#ifdef DEBUG
    		printf("No rotation\n");
    	#endif
    }

    form_object.move_rel(pos_x, pos_y);
    
    forms.push_back(form_object);

	#ifdef DEBUG
		printf("Finished %s\n", __PRETTY_FUNCTION__);
	#endif
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