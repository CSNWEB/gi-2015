/*!
 *  Class Point
 *
 *  Represents a point in two dimensional space.
 */
#ifndef POINT_H
#define POINT_H

#include <math.h>
#include <stdio.h>
#include "globalParams.hpp"

class Point
{
private:
    
    /**
     *  Float representing the x coordinate of the point.
     */
	float x;

    /**
     *  Float representing the y coordinate of the point.
     */
	float y;
	
public:
    
    /*!
     *  Default Constructor.
     *
     *  Initializes a point at the origin in two dimensional space.
     */
	Point(){x=0; y=0;};
    
    /*!
     *  Constructor that initializes the point with the passed x and y coordinates.
     */
	Point(float x, float y){this->x = x; this->y = y;};

    /*!
     *  Copy constructor
     */
    Point(const Point &orig){x = orig.x; y = orig.y;};

    /**
     *  Getter for the x coordinate of the point.
     *
     *  @return A float representing the x coordinate of the point.
     */
	float get_x() {return x;};

    /**
     *  Getter for the y coordinate of the point.
     *
     *  @return A float representing the y coordinate of the point.
     */
	float get_y() {return y;};
    
    /**
     *  Setter for the x coordinate of the point.
     *
     *  @param x        new x value
     */
    void set_x(float newx) {x = newx;};
    
    /**
     *  Setter for the y coordinate of the point.
     *
     *  @param y        new y value
     */
    void set_y(float newy) {y = newy;};
	
    /*!
     *  Calculates the euclidian distance between the receiver and the passed
     *  Point other.
     *
     *  @param other The point to which distance from the receiver has to be calculated.
     *
     *  @return A float resembling the euclidian distance between the receiver and other.
     */
	float get_distance_to(Point *other);

	/*!
	 *  Function to check if this point is left of line defined by p_start -> p_end
	 *
	 * @param p_start 	Pointer to point defining start of line
	 * @param p_end 	Point to point defining direction of line
	 *
	 * @retun 			 0 if this point is on line
	 *					 1 if this point is left of line
	 * 					-1 if this point is on the right of line
	 */
	int is_left_of(Point *p_start, Point *p_end);
	
    /*!
     *  Moves the point in two dimensional space.
     *
     *  @param dx The amount by which the point is moved on the x-axis.
     *  @param dy The amount by which the point is moved on the y-axis.
     */
	void move_rel(float dx, float dy);
    
    /*!
     *  Rotates the point around a given center.
     *
     *  @param center_x The x-coordinate of the center around which the point is rotated.
     *  @param center_y The y-coordinate of the center around which the point is rotated.
     *  @param angle    The angle in degree by which the point will be rotated around the passed center.
     */
	void rotate(float center_x, float center_y, float angle);

    /*!
     *  Rotates the point around the origin (0/0)
     *
     *  @param angle    The angle in degrees by which the point will be rotated around the passed center.
     */
    void rotate(float angle);

    /*!
     *  Computes the new x-coordinate of the point if it was rotated by an angle given in degrees.
     *
     *  @param angle    The angle in degrees
     *
     *  @return         the x-coordinate of this point it would have after rotation by angle
     */
    float compute_pos_after_rotation_x(float angle);


    /*!
     *  Computes the new y-coordinate of the point if it was rotated by an angle given in degrees.
     *
     *  @param angle    The angle in degrees
     *
     *  @return         the y-coordinate of this point it would have after rotation by angle
     */
    float compute_pos_after_rotation_y(float angle);

    /*!
     *  Flips a point along x=y-axis, i.e. swap x- and y-coordinate.
     *  Needed if whole form should be flipped, e.g. when normalize form such that width >= height.
     */
    void flip();
};

#endif
