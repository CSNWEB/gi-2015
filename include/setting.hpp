#ifndef SETTING_H
#define SETTING_H

#include <vector>

#include "problem.hpp"
#include "plane.hpp"

class Setting
{
private:
	Problem *problem;

	vector<Plane> planes;

public:
    Setting(){};
	Setting(Problem *p);

    /**
     *  Returns number_of_planes
     */
    int get_number_of_planes();

    /**
     *  Get a specific Plane
     *
     *  @param i 	The number of the plane to be return
     *
     *  @return 	the Plane at planes[i]
     */
    Plane* get_plane_at(int i) {
        if (i < planes.size() && i>= 0)
            return &planes[i];
        else
            return NULL;
    };

    /**
     *  Adds a new, empty plane to the setting
     */
    void add_plane();

    /**
     *  Adds a form to a plane at a specific position
     *
     *  @param index_of_plane 		the index of the plane to which the new form should be added
     *  @param index_of_form 		the index of the abstract form that should be added
     *  @param dx 					the x-position of the new form
     *  @param dy 					the y-position of the new form
     *  @param rot					the rotation in degree of the new form
     */
    void add_form_to_plane_at_position(int index_of_plane, int index_of_form, float dx, float dy, float rot);

    /**
     *  Compute the total efficiency (i.e. utilization) of the current setting
     *
     *  @return     the utilitation as percentage within [0,1]
     */
    float get_total_utilization();

    /**
     *  Function to create an initial legal setting
     *  places every form on its own sheet
     */
    void create_initial_setting();
};

#endif