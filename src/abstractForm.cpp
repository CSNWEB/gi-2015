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

	convex_hull = vector<int>();

	// To Do: maybe normalize position of form s.t. xmin = ymin = 0
    
    // Calculate the size of the area (according to http://stackoverflow.com/questions/451426/how-do-i-calculate-the-surface-area-of-a-2d-polygon)
    
    size_of_area = 0.0;
    
    vector<Point> closed_even_points = points;
    closed_even_points.push_back(closed_even_points[0]);
    
    if (closed_even_points.size() % 2 != 0)
    {
        closed_even_points.push_back(closed_even_points[0]);
    }
    
    for (unsigned int index = 0; index < closed_even_points.size(); index += 2)
    {
        size_of_area += closed_even_points[index + 1].get_x() * (closed_even_points[index + 2].get_y() - closed_even_points[index].get_y()) + closed_even_points[index + 1].get_y() * (closed_even_points[index].get_x() - closed_even_points[index + 2].get_x());
    }
    size_of_area /= 2.0;
}

vector<int> AbstractForm::sort_points_dim_x_in_place()
{
	vector<int> ordered_indices = vector<int>(0,points.size());
	for (int i=0; i<points.size(); ++i)
		ordered_indices[i] = i;

	for (int i=0; i<points.size()-1; ++i)
		for (int j=i; j<points.size(); ++j)
		{
			if (points[ordered_indices[i]].get_x() > points[ordered_indices[j]].get_x())
			{
				int tmp = ordered_indices[i];
				ordered_indices[i] = ordered_indices[j];
				ordered_indices[j] = tmp;
			}
		}

	return ordered_indices;
}


void AbstractForm::compute_convex_hull()
{
	vector<int> ordered_indices = sort_points_dim_x_in_place();

	if (points.size() < 3)
	{
		convex_hull = ordered_indices;
		return;
	}
	else
	{
		vector<int> convex_hull_lower = vector<int>();
		convex_hull_lower.push_back(ordered_indices[0]);
		convex_hull_lower.insert(convex_hull_lower.end(), ordered_indices.begin(), ordered_indices.end());
		int i=0;
		while (i < convex_hull_lower.size()-2);
		{
			int ind_p1 = convex_hull_lower[i];
			int ind_p2 = convex_hull_lower[i+1];
			int ind_p3 = convex_hull_lower[i+2];

			if (points[ind_p2].is_left_of(&points[ind_p1], &points[ind_p3]) > 0)
			{
				// p2 is not part of convex hull
				convex_hull.erase(convex_hull_lower.begin()+i+1);
				--i;
			}
			else
				++i;
		}
		convex_hull_lower.erase(convex_hull_lower.begin());

		vector<int> convex_hull_upper = ordered_indices;
		convex_hull_upper.push_back(ordered_indices[ordered_indices.size()-1]);
		i = ordered_indices.size()-1;
		while (i >= 2)
		{
			int ind_p1 = convex_hull_lower[i];
			int ind_p2 = convex_hull_lower[i-1];
			int ind_p3 = convex_hull_lower[i-2];

			if (points[ind_p2].is_left_of(&points[ind_p1], &points[ind_p3]) > 0)
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