#include "abstractForm.hpp"

AbstractForm::AbstractForm(string name, vector<Point> points)
{
	this->name = name;
	this->points = points;
	number_of_points = points.size();

	float x_min = points[0].get_x();
	float x_max = points[0].get_x();
	float y_min = points[0].get_y();
	float y_max = points[0].get_y();
	for (int i=1; i<number_of_points; ++i)
	{
		if (points[i].get_x() < x_min)
			x_min = points[i].get_x();
		else if (points[i].get_x() > x_max)
			x_max = points[i].get_x();

		if (points[i].get_y() < y_min)
			y_min = points[i].get_y();
		else if (points[i].get_y() > y_max)
			y_max = points[i].get_y();
	}
	dx = x_max-x_min;
	dy = y_max-y_min;

	convex_hull = vector<Point>();

	// To Do: maybe normalize position of form s.t. xmin = ymin = 0
}

void AbstractForm::sort_points_dim_x_in_place()
{
	for (int i=0; i<points.size()-1; ++i)
		for (int j=i; j<points.size(); ++j)
		{
			if (points[i].get_x() > points[j].get_x())
			{
				Point tmp = points[i];
				points[i] = points[j];
				points[j] = tmp;
			}
		}
}

void AbstractForm::compute_convex_hull()
{
	sort_points_dim_x_in_place();

	if (points.size() < 3)
	{
		convex_hull = points;
		return;
	}
	else
	{
		vector<Point> convex_hull_lower = vector<Point>();
		convex_hull_lower.push_back(points[0]);
		convex_hull_lower.insert(convex_hull_lower.end(), points.begin(), points.end());
		int i=0;
		while (i < convex_hull_lower.size()-2);
		{
			Point *p1 = &convex_hull_lower[i];
			Point *p2 = &convex_hull_lower[i+1];
			Point *p3 = &convex_hull_lower[i+2];

			if (p2->is_left_of(p1,p3) > 0)
			{
				// p2 is not part of convex hull
				convex_hull.erase(convex_hull_lower.begin()+i+1);
				--i;
			}
			else
				++i;
		}
		convex_hull_lower.erase(convex_hull_lower.begin());

		vector<Point> convex_hull_upper = points;
		convex_hull_upper.push_back(points[points.size()-1]);
		i = points.size()-1;
		while (i >= 2)
		{
			Point *p1 = &convex_hull_lower[i];
			Point *p2 = &convex_hull_lower[i-1];
			Point *p3 = &convex_hull_lower[i-2];

			if (p2->is_left_of(p1,p3) > 0)
			{
				// p2 is not part of convex hull
				convex_hull.erase(convex_hull_lower.end()-i-2);
				++i;
			}
			else
				--i;
		}

		convex_hull = convex_hull_lower;
		for (int k=convex_hull_upper.size()-2; k>=0; --k)
			convex_hull.push_back(convex_hull_upper[k]);
		//convex_hull.insert(convex_hull.end(), convex_hull_upper.begin(), convex_hull_upper.end());
	}

	// TO DO
	// start with pointers to first three points, do while points left:
		// check if second point is on the left of line defined by first -> third
			// yes: second point is not in convex hull. second = first, first = first from last iteration
			// no: first = second, second = third
		// third = next point
}

void AbstractForm::_d_print_abstract_form()
{
	printf("Name of form: %s\n", name.c_str());
	printf("Number of points: %i\n", number_of_points);

	for (int i=0; i<number_of_points; ++i)
		printf("Point %2i at %.1f/%.1f\n", i, points[i].get_x(), points[i].get_y());
}

#ifdef USE_SFML
sf::ConvexShape AbstractForm::get_shape(int pos_x, int pos_y, int scale)
{
	sf::ConvexShape shape;
	shape.setPointCount(number_of_points);
	for (int i=0; i<number_of_points; ++i)
		shape.setPoint(i, sf::Vector2f(points[i].get_x()*scale+pos_x, points[i].get_y()*scale+pos_y));

	return shape;
}
#endif