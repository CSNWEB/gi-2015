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
	 * The abstract form this form is derived of
	 */
		AbstractForm *mother;
	
	/**
	 * The number of outer edges this form has.
	 * Note that this is equal to the number of points that define this form
	 */
	int number_of_edges;

	vector<Edge> edges;
	vector<Point> points;
	
	/**
	 * parameters definind the bounding box of this form:
	 */
	float x_min;
	float x_max;
	float y_min;
	float y_max;
	
public:
	/**
	 * Default constructor
	 */
		Form();

	/**
	 * Constructor that creates a form specified by an AbstractForm, bit without a specific position
	 */
		Form(AbstractForm *mother);

	/**
	 * Constructor that creates a Form at given coordinates (top left corner of bounding box)
	 */
		Form(AbstractForm *mother, float pos_x, float pos_y);
	
	/**
	 * Getter functions for bounding box
	 */
	float get_bounding_xmin();
	float get_bounding_xmax();
	float get_bounding_ymin();
	float get_bounding_ymax();
	
	/**
	 * Function to move this form relatively
	 */
	void move_rel(float dx, float dy);

	/**
	 * Function to rotate this form around a center by a specified degree
	 */
	void rotate(float center_x, float center_y, float degree);
	
	/**
	 * Function checks if this form overlaps with another form
	 *
	 * @param other		An other form for which overlapping is checked
	 */
	bool check_for_overlap(Form *other);
	
	/**
	 * overloaded version of above function,
	 * that saves minimum distance for each two edges in float-matrix; or zero of edges cross.
	 *
	 * @param other			An other form for which overlapping is checked
	 * @param crossings		a 2-dim float matrix that stores minimum distance for each pair of points
	 */
	bool check_for_overlap(Form *other, floatmat* crossings);
};

#endif
