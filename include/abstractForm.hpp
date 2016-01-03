/*!
 *  Class AbstractForm
 *
 *  An AbstractForm describes a form of any shape which is defined
 *  by its "points". An AbstractForm has a name and one can get the size of its
 *  bounding box and its area.
 */
#ifndef ABSTRACTFORM_H
#define ABSTRACTFORM_H

#include <vector>
#include <string>
#include <cmath>

#include "point.hpp"
#include "plane.hpp"
#include "global.hpp"

using namespace std;

class AbstractForm
{
private:
    
    /*!
     *  The number of points that the form is made of.
     */
	int number_of_points;
    
    /*!
     *  The name of the form.
     */
	string name;

    /*!
     *  A global unique id of this abstract form
     */
    int id;

    /*!
     *  The points that make up the form.
     */
	vector<Point> points;
	
    /*!
     *  The size of the bounding box of the form in x direction.
     */
	float dx;

    /*!
     *  The size of the bounding box of the form in y direction.
     */
    float dy;

    /*!
     *  The Minimum position on the x-axis of any point of this form
     */
    float min_x;

    /*!
     *  The Minimum position on the y-axis of any point of this form
     */
    float min_y;
    
    /*!
     *  The size of the area of the form.
     */
	float size_of_area;
	
    /*!
     *  Sorts points in x-dimension.
     *
     *  Uses in-place insertion-sort for small amount of points
     */
    vector<int> sort_points_dim_x();

    /*!
     *  All points that belong to the convex hull, stored by their indices in vector<Point> points
     */
    vector<int> convex_hull;
    
    /*!
     *  Computes the convex hull of this shape using graham scan algorithm
     *
     *  Stores the result in vector<Point> convex_hull
     */
    void compute_convex_hull();
    
    /*!
     *  Computes the size of the area of the shape and stores the result in float size_of_area.
     */
    void compute_size_of_area();

    /*!
     *  Rotates the abstract form to a position defined by two consecutive points on the convex hull. These points define a rotation by placing them to y=0 and x minimal (i.e. such that all values for x are greater or equal 0)
     *
     *  @param  index_of_point_in_convex_hull      the first point of the pair to be placed on y = 0
     */
    void rotate_convex_hull_to_configuration(int index_of_point_in_convex_hull);

public:
    
    /*!
     *  Default constructor
     */
	AbstractForm(){id = -1};
    
    /*!
     *  Constructor that initializes the form with a name and its points.
     *
     *  @param name     A string that represents the name of the form.
     *  @param points   A vector of type "Point" that form the form.
     */
	AbstractForm(string name, vector<Point> points, int id = -1);

    /*!
     *  Computes the rotation angle for a rotation that places two specified points parallel to the x-axis,
     *  and the second point two a larger x-coordinate
     *
     *  @param index_of_point_1     the index of the first point in vector<Point> points
     *  @param index_of_point_2     the index of the second point in vector<Point> points
     *
     *  @return                     the angle defining the specified rotation in degrees
     */
    float compute_rotation_angle_for_points_parallel_to_axis(int index_of_point_1, int index_of_point_2);

    /*!
     *  Check if this form fits on a plane with given dimensions.
     *  Check by brute-force if there is a rotation for which width and height of this plane are at least as large as the width and height of the plane.
     *  Checks all angles in degrees in {0,1,...,180}
     *
     *  @param plane_width      the width of the plane for which the form should be checked
     *  @param plane_height     the height of the plane for which the form should be checked
     *
     *  @return                 an int: if a legal rotation is found, the int specifies a rotation angle (in degrees), for which the form can be placed on the plane, and the area of the bounding box is minimal
     *                          if no legal rotation is found (i.e. the form is too big to be placed on the plane), -1 is returned
     */
    int check_for_optimal_legal_rotation(float plane_width, float plane_height);

    /*!
     *  Find a rotation of this form such that the area of the bounding box is minimal. Using algorithm by freeman and shapira. Needs O(n^2) time, where n is the number of points on the convex hull.
     *  Function does not check if the rotated form can still be placed on a plane of a problem.
     *
     *  @return     the optimal rotation angle in degrees.
     */
    float find_rotation_with_minimum_bounding_box();

    /*!
     *  Rotates the abstract form by a given angle in degrees
     *
     *  @param degrees      the angle in degrees defining the rotation
     */
    void rotate_form_by_degrees(float degrees);

    /*!
     *  Mirrors the form at x-axis
     *
     */
    void mirror();

    /*!
     *  Move a form such all points have x- and y-coordinates >= 0
     *  and also ensure that width >= height, by flipping form at axis x=y (if necessary and possible by size of plane).
     *  Needs curent minimal position and dimensions of plane!
     *
     *  @param x_min        current minimal position of any point on x-axis
     *  @param y_min        current minimal position of any point on y-axis
     *  @param plane_width  width of the planes where this form should be placed on
     *  @param plane_height height of the planes where this form should be placed on
     */
    void normalize_position(float plane_width, float plane_height);

    /*!
     *  A Debugging function that prints the properties of the form to the console
     */
	void _d_print_abstract_form();

    /*!
     *  Get the number of points that this form is made of.
     *
     *  @return The number of points that the form is made of.
     */
	int get_number_of_points();
    
    /*!
     *  Get the name of this abstractform.
     *
     *  @return     A string containing the name of this form
     */
    string get_name(){return name;};

    /*!
     *  Get the id of this abstractform
     *
     *  @return     An int containing the id
     */
    int get_id(){return id;}; 

    /*!
     *  Get the size of the bounding box of the form in x direction.
     *
     *  @return A float representing size of the bounding box of the form in x direction.
     */
	float get_dx();
    
    /*!
     *  Get the size of the bounding box of the form in y direction.
     *
     *  @return A float representing the size of the bounding box of the form in y direction.
     */
	float get_dy();
    
    /*!
     *  The size of the area of the abstract form.
     *
     *  @return A float representing the size of the area of the form.
     */
    float get_size_of_area()
    {
        return size_of_area;
    }
    
    /*!
     *  The indices of the points that are part of the convex hull.
     *
     *  @return A vector containing the indices of all points of the convex hull, in (counter-clockwise) order.
     */
    vector<int> *get_convex_hull()
    {
        return &convex_hull;
    }

    /*!
     *  Get the certain point of the ones that make up the form.
     *
     *  @param index    The index of the point in the array containing the points of the form.
     *
     *  @return         The "Point" at the specified index.
     */
	Point get_point_at_index(int index){return points[index];};
};

#endif
