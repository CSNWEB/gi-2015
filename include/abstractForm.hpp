/**
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

#ifdef USE_SFML
#include <SFML/Graphics.hpp>
#endif

#include "point.hpp"
#include "plane.hpp"

using namespace std;

class AbstractForm
{
private:
    
    /**
     *  The number of points that the form is made of.
     */
	int number_of_points;
    
    /**
     *  The name of the form.
     */
	string name;

    /**
     *  The points that make up the form.
     */
	vector<Point> points;
	
    /**
     *  The size of the bounding box of the form in x and y direction.
     */
	float dx,dy;
    
    /**
     *  The size of the are of the form.
     */
	float size_of_area;

    /**
     *  All points that belong to the confex hull
     */
    vector<Point> convex_hull;
	
    /**
     *  Sorts points in x-dimension
     *
     *  uses in-place insertion-sort for small amount of points
     *  Maybe implement a merge-sort for forms with #points > ? 
     */
    void sort_points_dim_x_in_place();

    /**
     *  Computes the convex hull of this shape:
     *
     *  Stores the result in vector<Point> convex_hull
     */
    void compute_convex_hull();

public:
    
    /**
     *  Default constructor
     */
	AbstractForm(){};
    
    /**
     *  Constructor that initializes the form with a name and its points
     *
     *  @param name     A string that represents the name of the form.
     *  @param points   A vector of type "Point" that form the form.
     */
	AbstractForm(string name, vector<Point> points);

    /**
     *  Adds the form to a plane at the given position.
     *
     *  @param s     The plane that the form is to be added to.
     *  @param pos_x The position on the x-axis where the form will be added.
     *  @param pos_y The position on the y-axis where the form will be added.
     *
     *  removed because intended way of adding a form to a plane is via class problem
     *
	//void create_form_in_plane(Plane *s, float pos_x, float pos_y);

    /**
     *  A Debugging function that prints the properties of the form to the
     *  console
     */
	void _d_print_abstract_form();

    /**
     *  Get the number of points that this form is made of.
     *
     *  @return The number of points that the form is made of.
     */
	int get_number_of_points(){return number_of_points;};
    
    /**
     *  Get the position of the form on the x-axis.
     *
     *  @return A float representing he position of the form on the x-axis.
     */
	float get_dx(){return dx;};
    
    /**
     *  Get the position of the form on the y-axis.
     *
     *  @return A float representing he position of the form on the y-axis.
     */
	float get_dy(){return dy;};
    
    /**
     *  Get the certain point of the ones that make up the form.
     *
     *  @param index The index of the point in the array containing the points of the form.
     *
     *  @return The "Point" at the specified index.
     */
	Point get_point_at_index(int index){return points[index];};

    #ifdef USE_SFML

    /**
     *  Creates a ConvexShape representation of this AbstractForm.
     *
     *  @param pos_x The position of the form on the x-axis.
     *  @param pos_y The position of the form on the y-axis.
     *  @param scale The scale of the form.
     *
     *  @return An object of type "ConvexShape" that represents this AbstractForm.
     */
	sf::ConvexShape get_shape(int pos_x, int pos_y, int scale);

    /**
     * TO DO: a function that returns an array of line segments
     */

    #endif
};

#endif
