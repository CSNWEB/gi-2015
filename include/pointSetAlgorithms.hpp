
#ifndef POINTSETALGOS_H
#define POINTSETALGOS_H

#include <vector>
#include <list>
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
private:
    /*!
     *  For a set of points, check if there a multiple points describing the same (x/y)-coordinates. This is a necessary pre-computing step for computing the convex hull, because the algorithm cannot deal with points not in general position. Creates an int-vector with indices of points, where each (x/y)-point is contained exactly once.
     *
     *  @param points 		A pointer to a vector of Point, for which the index-vector should be unified.
     *  @param indices 		A sorted vector of ints that containes all indices of points in the vector points.
     *
     *  @return 			True, if points have been deleted. False otherwise.
     */
    static bool unique_indicies_of_points(vector<Point> &points, vector<int> &indices);

public:
	/*!
	 *  Rotates a vector of points in-place around a specified point
	 *
	 *	@param points 		the points to rotate
	 *	@param center_x		x-position of center of rotation
	 *	@param center_y		y-position of center of rotation
	 *	@param angle 		the angle in degrees
	 *
	 *	@return 			true, if points have been rotated. False otherwise or if points was empty.
	 */
	static bool rotate_pointset_at_point(vector<Point> &points, float center_x, float center_y, float angle);

	/*!
	 *  Rotates a vector of points in-place around a specified point. Also computes the minimum and maximum coordinates in each dimension for the rotated point set
	 *
	 *	@param points 		the points to rotate
	 *	@param center_x		x-position of center of rotation
	 *	@param center_y		y-position of center of rotation
	 *	@param angle 		the angle in degrees
	 *	@param x_min 		Field to store the new minimum x position
	 *	@param x_max		Field to store the new maximum x position
	 *	@param y_min		Field to store the new minimum y position
	 *	@param y_max		Field to store the new maximum y position
	 *
	 *	@return 			true, if points have been rotated. False otherwise or if points was empty.
	 */
	static bool rotate_pointset_at_point(
		vector<Point> &points,
		float center_x,
		float center_y,
		float angle,
		float &x_min,
		float &x_max,
		float &y_min,
		float &y_max
	);

	/*!
	 *  Mirrors a vector of points in-place at an axis, that is parallel to the x-axis and centered in y-dimension within the box. The bounding box and the global position of the pointset are unaffected.
	 *
	 *	@param points 		the points to rotate
	 *	@param y_min 		the minimum position of any point on the y-axis
	 *	@param y_max 		the maximum position of any point on the y-axis
	 *
	 *	@return 			true, if points have been mirrored. False otherwise or if points was empty.
	 */
	static bool mirror_pointset_at_axis(vector<Point> &points, float y_min, float y_max);

	/*!
	 *  Sort the points of a given set by their position on x-dimension
	 *
	 *  @param points 	A pointer to a vector of Point, that should be sorted
	 *
	 *  @return 		A vector of ints containing the indices of the points in increasing order.
	 */
	static vector<int> sort_points_by_dim_x(vector<Point> &points);

	/*!
	 *  Computes the convex hull of a given set of 2-dim points.
	 *
	 *  @param points 	A reference to a vector of Point, for which the convex hull should be computed.
	 *  @param hull 	A reference to a vector of ints, where the result as indices of the points of the convex hull will be stored
	 *
	 *  @return 		True, if a convex hull was created. Otherwise false.
	 */
	static bool compute_convex_hull(vector<Point> &points, vector<int> &hull);

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