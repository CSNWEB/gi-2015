/*!
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

#include "globalParams.hpp"
#include "pointSetAlgorithms.hpp"
#include "edge.hpp"
#include "abstractForm.hpp"
#include "simpleSVG.hpp"
#include "gpc.h"

class AbstractForm;

#define floatmat vector<vector<float> >

using namespace std;

class Form
{
private:
    
    /*!
     *  The abstract form this form is derived of
     */
    AbstractForm * mother;
	
	/*!
	 *  The number of outer edges this form has.
	 *  Note that this is equal to the number of points that define this form
	 */
    int number_of_edges;
    
    /*!
     *  A vector of points that make up this Form.
     */
    vector<Point> points;
	
	/*!
	 *  Parameters definind the bounding box of this form:
	 */
    float x_min, x_max, y_min, y_max;
	
public:
	/*!
	 *  Default constructor
	 */
    Form(){};

	/*!
	 *  Constructor that creates a form specified by an AbstractForm, bit without
     *  a specific position
	 */
    Form(AbstractForm * const mother) : Form(mother, 0, 0){};

	/*!
	 *  Constructor that creates a Form at given coordinates (top left corner of
     *  bounding box)
	 */
    Form(AbstractForm * const mother, float pos_x, float pos_y);

    /*!
     *  Destructor
     */
    ~Form(){};
	
    /*!
     *  The abstract form that this Form represents.
     *
     *  @return An object of type AbstractForm that this Form represents.
     */
    AbstractForm *get_mother()
    {
        return this->mother;
    }
    
    /*!
     *  The coordinates of the bounding box. Described by the minimum and
     *  maximum values in x- and y-direction that contain the forms points.
     *
     *  @return A float representing the position of the bounding box at minimum and maximum position on the x- and y-axis respectively.
     */
	float get_bounding_xmin(){return x_min;};

    /**
     *  The coordinates of the bounding box. Described by the minimum and
     *  maximum values in x- and y-direction that contain the forms points.
     *
     *  @return A float representing the position of the bounding box at minimum and maximum position on the x- and y-axis respectively.
     */
	float get_bounding_xmax(){return x_max;};

    /**
     *  The coordinates of the bounding box. Described by the minimum and
     *  maximum values in x- and y-direction that contain the forms points.
     *
     *  @return A float representing the position of the bounding box at minimum and maximum position on the x- and y-axis respectively.
     */
	float get_bounding_ymin(){return y_min;};

    /**
     *  The coordinates of the bounding box. Described by the minimum and
     *  maximum values in x- and y-direction that contain the forms points.
     *
     *  @return A float representing the position of the bounding box at minimum and maximum position on the x- and y-axis respectively.
     */
	float get_bounding_ymax(){return y_max;};

    /**
     *  Function to get the size of the bounding box
     *
     *  @return     a float representing the width (or height) of the bounding box
     */
    float get_bounding_dx(){return x_max - x_min;};

    /**
     *  Functions to get the size of the bounding box
     *
     *  @return     a float representing the width (or height) of the bounding box
     */
    float get_bounding_dy(){return y_max - y_min;};

    /*!
     *  Getter for a specific point
     *
     *  @param point_index      the index of the point that should be returned
     *
     *  @return                 the pointer to the point at position point_index
     */
    Point get_point_at(int point_index){return points[point_index];};

    /*!
     *  A vector containing the points that belong to the form.
     *
     *  @return A vector containing the points of the form.
     */
    vector<Point> *get_points()
    {
        return &points;
    }
    
    /*!
     *  Get the centroid of the form. The means the mean of the x and y values
     *  of all points.
     *
     *  @return A Point that represents the centroid of the form.
     */
    Point get_centroid();
    
    /*!
     *  Moves the Form relative to its current position by the passed amount in
     *  x- and y-direction.
     *
     *  @param dx A float representing the amount that the Form is moved by on the x-axis.
     *  @param dy A float representing the amount that the Form is moved by on the y-axis.
     */
	void move_rel(float dx, float dy);

    /*!
     *  Rotates the form around the passed center by the amount given by degree.
     *
     *  @param center_x The x-coordinate of the center point that the Form is rotated around.
     *  @param center_y The y-coordinate of the center point that the Form is rotated around.
     *  @param degree   The amount that the Form is rotated by.
     */
	void rotate(float center_x, float center_y, float angle);

    /*!
     *  Mirrors the form at an axis parallel to the x-axis and such that its bounding box is not affected.
     */
    void mirror();
	
    /*!
     *  Checks if the receiver overlaps with the passed Form.
     *
     *  @param other The form that the overlapping is checked against.
     *
     *  @return true, if the receiver and the Form other overlap, false if not.
     */
	bool check_for_overlap(Form &other);
	
    /*!
     *  Determines by how much the receiver overlaps with the passed form.
     *
     *  @param other The form that the overlapping is checked agains
     *
     *  @return The size of the largest area among the ones where the forms overlap.
     */
    float overlap_distance_with_form(Form &other);
    
    /*!
     *  Debug: print points to std_out
     */
    void _d_print_points_to_console();

    /*!
     *  Debug: print edges to std_out
     */
    void _d_print_edges_to_console();

    /*!
     *  Debug: print convex hull to console
     */
    void _d_print_convex_hull_to_console();
    
    /*!
     * Print the form points to a svg Polygon
     *
     *  @param doc          the svg-filge to be written into
     *  @param x_offset     the global x-offset (within the svg-file) of the hull
     *  @param y_offset     the global y-offset (within the svg-file) of the hull
     *  @param scale        the global scaling of all objects written to the svg-file
     */
    void print_form_to_svg(svg::Document * doc, int x_offset, int y_offset, int scale);

    /*!
     *  Print the convex hull of this form to svg polygon
     *
     *  @param doc          the svg-filge to be written into
     *  @param x_offset     the global x-offset (within the svg-file) of the hull
     *  @param y_offset     the global y-offset (within the svg-file) of the hull
     *  @param scale        the global scaling of all objects written to the svg-file
     */
    void print_convex_hull_to_svg(svg::Document * doc, int x_offset, int y_offset, int scale);
};

#endif
