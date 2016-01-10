
#ifndef POINTSETALGOS_H
#define POINTSETALGOS_H

#include <vector>
#include <algorithm>
#include <math.h>

#include "point.hpp"

using namespace std;

struct PointComparator
{
	vector<Point> *vector_of_points;

	PointComparator(vector<Point> *v) : vector_of_points(v)
	{
		#ifdef DEBUG
			printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
		#endif
	}

	bool operator()(int index_of_point_1, int index_of_point_2)
	{
		#ifdef DEBUG
			printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
		#endif

		if ((*vector_of_points)[index_of_point_2].get_x() - (*vector_of_points)[index_of_point_1].get_x() > GlobalParams::get_tolerance())
			return true;
		else if ((*vector_of_points)[index_of_point_1].get_x() - (*vector_of_points)[index_of_point_2].get_x() > GlobalParams::get_tolerance())
			return false;
		else if ((*vector_of_points)[index_of_point_2].get_y() - (*vector_of_points)[index_of_point_1].get_y() > GlobalParams::get_tolerance())
			return true;
		else return false;
	}
};

class PointSetAlgorithms
{

public:
	/*!
	 *  Sort the points of a given set by their position on x-dimension
	 *
	 *  @param points 	A pointer to a vector of Point, that should be sorted
	 *
	 *  @return 		A vector of ints containing the indices of the points in increasing order.
	 */
	static vector<int> sort_points_by_dim_x(vector<Point> *points);

	/*!
	 *  Computes the convex hull of a given set of 2-dim points.
	 *
	 *  @param points 	A pointer to a vector of Point, for which the convex hull should be computed.
	 *
	 *  @return 		A vector of ints containing the indices of the points of the convex hull.
	 */
	static vector<int> compute_convex_hull(vector<Point> *points);

	/*!
     *  Computes the rotation angle for a rotation that places two specified points parallel to the x-axis, and the second point two a larger x-coordinate
     *
     *  @param points 				A pointer to a vector of Point
     *  @param index_of_point_1     the index of the first point in vector<Point> points
     *  @param index_of_point_2     the index of the second point in vector<Point> points
     *
     *  @return                     the angle defining the specified rotation in degrees
     */
    static float compute_rotation_angle_for_points_parallel_to_axis(vector<Point> *points, int index_of_point_1, int index_of_point_2);

	/*!
     *  For a given set of points, find a rotation of the points such that the area of the bounding box of is minimal. Using algorithm by freeman and shapira. Needs O(n^2) time, where n is the number of points on the convex hull.
     *
     *  @param points 		A pointer to a vector of Point, for which the optimal rotation should be computed.
     *	@param convex_hull 	A pointer to a vector of int, containing all indices of points of the convex hull of the points
     *
     *  @return     		the optimal rotation angle in degrees.
     */
    static float find_rotation_with_minimum_bounding_box(vector<Point> *points, vector<int> *convex_hull);
};

#endif