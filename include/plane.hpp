/*!
 *  class Plane
 *
 *  A plane is part of a setting, it describes which forms are placed on a specific plane, and how these forms are positioned.
 */

#ifndef PLANE_H
#define PLANE_H

#include <vector>

#include "form.hpp"
#include "abstractForm.hpp"

class Form;
class AbstractForm;

#define boolmat vector<vector<bool> >

using namespace std;

class Plane
{
private:
	/**
	 *  The width of the plane.
	 */
	float dx;

	/**
	 *  The height of the plane.
	 */
	float dy;
	
	/**
	 *  The number of forms on this plane.
	 */
	int number_of_forms;
	
	/**
	 *  All forms on this plane
	 */
	vector<Form> forms;
	
	/**
	 *  A 2-dimensional bool matrix describing which forms overlap
	 */
	boolmat overlappings;
public:
    /*!
     * default constructor
     */
    Plane(){};
    
    /*!
     * consructor that sets the size of the plane
     */
    Plane(float dx, float dy){this->dx = dx; this->dy = dy;}
    
    /*!
     *  Get number of forms on this plane
     */
    int get_number_of_forms();
    
    /*!
     *  Get the dimensions of the plane.
     *
     *  @return A float representing the dimension of the plane in x-direction.
     */
    float get_dx() {return dx;};

    /*!
     *  Get the dimensions of the plane.
     *
     *  @return A float representing the dimension of the plane in y-direction.
     */
    float get_dy() {return dy;};
    
    /*!
     *  Get a specific form from this plane
     *
     *  @param i 	The number of the form to be returned
     *
     *  @return 	the Form at forms[i]
     */
    Form *get_form_at(int i);
    
    /*!
     * Adds a form at a specific position. Does not check if the result is a legal setting
     *
     * @param form 		The (abstract) form to be added to the plane
     * @param pos_x		x-position on plane where the top-left corner of the bounding-box of form is placed
     * @param pos_y		y-position on plane where the top-left corner of the bounding-box of form is placed
     */
    void add_form_at_position(AbstractForm *form, float pos_x, float pos_y);
    
    /*!
     *  Adds a form at a specific position and rotates it around its centroid. Does not check if the result is a legal setting
     *
     *  @param form     The (abstract) form to be added to the plane
     *  @param pos_x    x-position on plane where the top-left corner of the bounding-box of form is placed
     *  @param pos_y    y-position on plane where the top-left corner of the bounding-box of form is placed
     *  @param rotation A float representing how much the form is rotated around its centroid.
     */
    void add_form_at_position_rotation(AbstractForm *form,
                                       float pos_x,
                                       float pos_y,
                                       float rotation);
    
    /*!
     * computes which forms overlap pairwise and saves result in bool-matrix overlappings
     */
    void compute_all_overlappings();
    
    /*!
     *  Computes percentage of utilization of this plane
     *
     *  @return 	the utilitation as percentage within [0,1]
     */
    float compute_utilization();
    
    /*!
     *  Checks if the positioning of forms on this plane is legal,
     *  i.e. no overlappings and all forms are within the plane
     *
     *  @return 	A boolean: true if plane is legal
     */
    bool check_if_legal();
    
};

#endif
