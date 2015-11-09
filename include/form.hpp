/**
 *  Class Form
 *
 *  A Form is the representation of an AbstractForm.
 *  Its 'mother' is the form that this one belongs to. It's made up of points
 *  and edges and has a bounding box. It can be moved, rotated and one can check
 *  whether it crosses another Form.
 */
#ifndef FORM_H
#define FORM_H

#include <vector>

#include "edge.hpp"
#include "abstractForm.hpp"

class AbstractForm;

#define floatmat vector<vector<float>>

using namespace std;

class Form
{
private:
    
    /**
     *  The abstract form this form is derived of
     */
    AbstractForm *mother;
	
	/**
	 *  The number of outer edges this form has.
	 *  Note that this is equal to the number of points that define this form
	 */
    int number_of_edges;

    /**
     *  A vector of edges that make up this Form.
     */
    vector<Edge> edges;
    
    /**
     *  A vector of points that make up this Form.
     */
    vector<Point> points;
	
	/**
	 *  Parameters definind the bounding box of this form:
	 */
    float x_min, x_max, y_min, y_max;
	
public:
	/**
	 *  Default constructor
	 */
    Form(){};

	/**
	 *  Constructor that creates a form specified by an AbstractForm, bit without
     *  a specific position
	 */
    Form(AbstractForm *mother);

	/**
	 *  Constructor that creates a Form at given coordinates (top left corner of
     *  bounding box)
	 */
    Form(AbstractForm *mother, float pos_x, float pos_y); // TODO: Use Point?
	
    /**
     *  The coordinates of the bounding box. Described by the minimum and
     *  maximum values in x- and y-direction that contain the forms points.
     *
     *  @return A float representing the position of the bounding box at minimum and maximum position on the x- and y-axis respectively.
     */
	float get_bounding_xmin(){return x_min;};
	float get_bounding_xmax(){return x_max;};
	float get_bounding_ymin(){return y_min;};
	float get_bounding_ymax(){return y_max;};
	
    /**
     *  Moves the Form relative to its current position by the passed amount in
     *  x- and y-direction.
     *
     *  @param dx A float representing the amount that the Form is moved by on the x-axis.
     *  @param dy A float representing the amount that the Form is moved by on the y-axis.
     */
	void move_rel(float dx, float dy);

    /**
     *  Rotates the form around the passed center by the amount given by degree.
     *
     *  @param center_x The x-coordinate of the center point that the Form is rotated around.
     *  @param center_y The y-coordinate of the center point that the Form is rotated around.
     *  @param degree   The amount that the Form is rotated by.
     */
	void rotate(float center_x, float center_y, float degree);
	
    /**
     *  Checks if the receiver overlaps with the passed Form.
     *
     *  @param other The form that the overlapping is checked against.
     *
     *  @return true, if the receiver and the Form other overlap, false if not.
     */
	bool check_for_overlap(Form *other);
	
    /**
     *  Checks if the receiver overlaps with the passed Form.
     *  Additionally saves the minimum distance for every two edges in a
     *  float-matrix or zero if the edges cross.
     *
     *  @param other     The form that the overlapping is checked against.
     *  @param crossings A two-dimensional float-matrix describing the minimum distance between two points of the form.
     *
     *  @return True if the receiver and the other Form overlap, false if not.
     */
	bool check_for_overlap(Form *other, floatmat* crossings);

    /**
     *  Debug: print form to std_out
     */
    void _d_print_form_to_console();
};

#endif
