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

#ifdef USE_SFML
    #include <SFML/Graphics.hpp>
#endif

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
     *  The points that make up the form.
     */
	vector<Point> points;
	
    /*!
     *  The size of the bounding box of the form in x and y direction.
     */
	float dx,dy;
    
    /*!
     *  The size of the are of the form.
     */
	float size_of_area;
	
    /*!
     *  Sorts points in x-dimension
     *
     *  uses in-place insertion-sort for small amount of points
     *  Maybe implement a merge-sort for forms with high number of points?
     */
    vector<int> sort_points_dim_x();

    /*!
     *  To calculate a point as a linear combination of the vector v defined by the two preceding points and the orthogonal vector to v,
     *  the parameters lambda and mu are computed here.
     *  Given any two adjacent starting points p_0 and p_1, all points of the form then can be calculated as follows
     *
     *  Let i>=0, i<points.size(),  j=(i+1)%points.size(), k=(j+1)%points.size() 
     *  Let v be the vector from p_i to p_j, and let n be the orthogonal vector to v.
     *  Then p_k = p_i+ lambda[k]*v + mu[k]*n
     *
     *  This vector holds all lambda-values.
     */
    vector<float> relative_point_position_lambda;

    /*!
     *  To calculate a point as a linear combination of the vector v defined by the two preceding points and the orthogonal vector to v,
     *  the parameters lambda and mu are computed here.
     *  Given any two adjacent starting points p_0 and p_1, all points of the form then can be calculated as follows
     *
     *  Let i>=0, i<points.size(),  j=(i+1)%points.size(), k=(j+1)%points.size() 
     *  Let v be the vector from p_i to p_j, and let n be the orthogonal vector to v.
     *  Then p_k = p_i+ lambda[k]*v + mu[k]*n
     *
     *  This vector holds all mu-values.
     */
    vector<float> relative_point_position_mu;

    /*!
     *  See vector<float> relative_point_position_lambda
     *  This vector considers only the points on the convex hull
     */
    vector<float> relative_point_position_cv_lambda;

    /*!
     *  See vector<float> relative_point_position_mu
     *  This vector considers only the points on the convex hull
     */
    vector<float> relative_point_position_cv_mu;

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
     *  Computes the size of the area of the shape and stores the result in
     *  float size_of_area.
     */
    void compute_size_of_area();

    /*!
     *  compute the values for
     *      relative_point_position_lambda
     *      relative_point_position_mu
     *
     *  @param consider_only_convex_hull    if true, the lambda- and mu-values for the edges on the convex hull will be computed
     *                                      the results are stored in relative_point_position_cv_lambda and -_mu
     *
     *                                      else, the edges of the original form are considered
     *                                      the results are stored in relative_point_position_lambda and -_mu
     */
    void compute_lambda_and_mu(bool consider_only_convex_hull = false);

    /*!
     *  Subfunction of compute_lambda_and_mu:
     *  compute a certain lambda for a given pair of vertices and a already comuted mu
     *
     *      dx_2 = dx_1 + lambda * dx_1 + mu dy_1
     *  <=> lambda = (dx_2 - dx_1 - (mu * dy_1)) / dx_1
     *
     *  @param d1_x     x-length of first vector
     *  @param d1_y     y-length of first vector
     *  @param d2_x     x-length of second vector
     *  @param d2_y     y-length of second vector
     *  @param mu       value for mu, as computed by compute_mu(float, float, float, float)
     *
     *  @return         float: the lambda value as specified above
     */
    float compute_lambda(float d1_x, float d1_y, float d2_x, float d2_y, float mu);

    /*!
     *  Subfunction of compute_lambda_and_mu:
     *  compute a certain mu for a given pair of vertices
     *
     *      dx_2 = dx_1 + lambda * dx_1 + mu dy_1
     *  <=> lambda = (dx_2 - dx_1 - (mu * dy_1)) / dx_1
     *
     *      dy_2 = dx_1 + lambda * dy_1 - mu dx_1
     *  <=> mu = - (dy_2-dy_1 - ((dx_2 -dx_1- mu * d_y1)/dx_1) * dy_1) / dx_1
     *  <=> mu = - (dy_2 - ((dx_2 * dy_1) / dx_1) / ((dy_1^2)/dx_1 + dx_1)
     *
     *  @param d1_x     x-length of first vector
     *  @param d1_y     y-length of first vector
     *  @param d2_x     x-length of second vector
     *  @param d2_y     y-length of second vector
     *
     *  @return         float: the mu value as specified above
     */
    float compute_mu(float d1_x, float d1_y, float d2_x, float d2_y);

    /*!
     *  Find a rotation of form such that the area of the bounding box is minimal.
     *  using algorithm by freeman and shapira
     *  needs O(n^2) time, where n is the number of points on the convex hull
     *
     *  @return     the index (in te convex hull) of the first point of the pair that defines this configuration
     *              points[convex_hull[i]] and points[convex_hull[i+1]] define a rotation in which both points are placed
     *              on y=0 axis
     */
    int find_configuration_with_minimum_bounding_box();

    /*!
     *  Rotates the abstract form to a position defined by two consecutive points on the convex hull
     *  These points define a rotation by placing them to y=0 and x minimal (i.e. such that all values for x are greater or equal 0)
     *
     *  @param  index_of_point_in_convex_hull      the first point of the pair to be placed on y = 0
     */
    void rotate_convex_hull_to_configuration(int index_of_point_in_convex_hull);

    /*!
     *  Move a form such all points have x- and y-coordinates > 0
     *
     *  @param x_min    current minimal position of any point on x-axis
     *  @param y_min    current minimal position of any point on y-axis
     */
    void normalize_position(float x_min, float y_min);

public:
    
    /*!
     *  Default constructor
     */
	AbstractForm(){};
    
    /*!
     *  Constructor that initializes the form with a name and its points
     *
     *  @param name     A string that represents the name of the form.
     *  @param points   A vector of type "Point" that form the form.
     */
	AbstractForm(string name, vector<Point> points);

    /*!
     *  A Debugging function that prints the properties of the form to the
     *  console
     */
	void _d_print_abstract_form();

    /*!
     *  Get the number of points that this form is made of.
     *
     *  @return The number of points that the form is made of.
     */
	int get_number_of_points();
    
    /*!
     *  Get the name of this abstractform
     *
     *  @return     A string containing the name of this form
     */
    string get_name(){return name;};

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

    /*!
     *  Check if this form fits on a plane with given dimensions, 
     *  i.e. check if there is a rotation for which width and height of this plane are at least as large as the width and height of the plane
     *
     *  @param plane_width      the width of the plane for which the form should be checked
     *  @param plane_height     the height of the plane for which the form should be checked
     *
     *  @return                 an int: if a legal rotation is found, the int specifies a rotation angle (in degrees), for which the form can be placed on the plane, and the area of the bounding box is minimal
     *                          if no legal rotation is found (i.e. the form is too big to be placed on the plane), -1 is returned
     */
    int check_for_optimal_legal_rotation(float plane_width, floatplane_height);

    #ifdef USE_SFML

    /*!
     *  Creates a ConvexShape representation of this AbstractForm.
     *
     *  @param pos_x The position of the form on the x-axis.
     *  @param pos_y The position of the form on the y-axis.
     *  @param scale The scale of the form.
     *
     *  @return An object of type "ConvexShape" that represents this AbstractForm.
     */
	sf::ConvexShape get_shape(int pos_x, int pos_y, int scale);

    /*!
     * TO DO: a function that returns an array of line segments
     */

    #endif
};

#endif
