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

	compute_convex_hull();

	// To Do: maybe normalize position of form s.t. xmin = ymin = 0
    
    compute_size_of_area();
}

vector<int> AbstractForm::sort_points_dim_x()
{
	#ifdef DEBUG
		printf("FUNCTION: AbstractForm::sort_points_dim_x_in_place()\n");
	#endif

	vector<int> ordered_indices = vector<int>(points.size(),0);
	for (int i=0; i<points.size(); ++i)
		ordered_indices[i] = i;

	for (int i=0; i<points.size()-1; ++i)
	{
		for (int j=i; j<points.size(); ++j)
		{
			if (points[ordered_indices[i]].get_x() > points[ordered_indices[j]].get_x() ||
				(points[ordered_indices[i]].get_x() == points[ordered_indices[j]].get_x() &&
				 points[ordered_indices[i]].get_y() > points[ordered_indices[j]].get_y()) )
			{
				int tmp = ordered_indices[i];
				ordered_indices[i] = ordered_indices[j];
				ordered_indices[j] = tmp;
			}
		}
	}

	#ifdef DEBUG
		printf("finished sorting. result:\n");
		for (int i=0; i<ordered_indices.size(); ++i)
			printf("%i ",ordered_indices[i]);
		printf("\n");
	#endif

	return ordered_indices;
}

void AbstractForm::compute_size_of_area()
{
    // Calculate the size of the area (according to http://www.mathopenref.com/coordpolygonarea.html )

	#ifdef DEBUG
		printf("FUNCITON: AbstractForm::compute_size_of_area()\n");
	#endif
    
    size_of_area = 0.0;
    
    vector<Point> closed_points = points;
    closed_points.push_back(closed_points[0]);
    
    for (unsigned int index = 0; index < closed_points.size() - 1; index++)
    {
        size_of_area += ((closed_points[index].get_x() * closed_points[index + 1].get_y()) - (closed_points[index].get_y() * closed_points[index + 1].get_x()));
    }
    
    size_of_area /= 2.0;
    
    size_of_area = fabs(size_of_area);
}

void AbstractForm::compute_convex_hull()
{
	#ifdef DEBUG
		printf("FUNCTION: AbstractForm::compute_convex_hull()\n");
	#endif

	vector<int> ordered_indices = sort_points_dim_x();

	if (points.size() == 3)
	{
		convex_hull = ordered_indices;
		convex_hull.push_back(ordered_indices[0]);
		return;
	}
	else
	{
		vector<int> convex_hull_lower = vector<int>();
		convex_hull_lower.push_back(ordered_indices[0]);
		convex_hull_lower.insert(convex_hull_lower.end(), ordered_indices.begin(), ordered_indices.end());

		#ifdef DEBUG
			printf("Init lower_hull finished\n");
			for (int i=0; i<convex_hull_lower.size(); ++i)
				printf("point at position %i: %i\n",i, convex_hull_lower[i]);
		#endif

		int i=0;
		while (i < convex_hull_lower.size()-2)
		{
			#ifdef DEBUG
				printf("current index at position %i. length of convex_hull atm: %i\n", i, convex_hull_lower.size());
			#endif

			int ind_p1 = convex_hull_lower[i];
			int ind_p2 = convex_hull_lower[i+1];
			int ind_p3 = convex_hull_lower[i+2];

			if (points[ind_p2].is_left_of(&points[ind_p1], &points[ind_p3]) > 0)
			{
				// p2 is not part of convex hull
				#ifdef DEBUG
					printf("\terase point %i from hull\n", i+1);
					printf("\tthis is: %i\n", *(convex_hull_lower.begin()+(i+1)));
				#endif

				convex_hull_lower.erase(convex_hull_lower.begin()+i+1);
				--i;
			}
			else
				++i;
		}

		convex_hull_lower.erase(convex_hull_lower.begin());

		#ifdef DEBUG
			printf("lower hull complete\n");
			for (int k=0; k<convex_hull_lower.size(); ++k)
				printf("\tpoint %i is %i\n", k, convex_hull_lower[k]);
		#endif

		vector<int> convex_hull_upper = ordered_indices;
		convex_hull_upper.push_back(ordered_indices[ordered_indices.size()-1]);

		#ifdef DEBUG
			printf("Init upper_hull finished\n");
			for (int i=0; i<convex_hull_upper.size(); ++i)
				printf("point at position %i: %i\n",i, convex_hull_upper[i]);
		#endif

		i = convex_hull_upper.size()-1;
		while (i >= 2)
		{
			#ifdef DEBUG
				printf("current index at position %i. length of convex_hull atm: %i\n", i, convex_hull_upper.size());
			#endif
			int ind_p1 = convex_hull_upper[i];
			int ind_p2 = convex_hull_upper[i-1];
			int ind_p3 = convex_hull_upper[i-2];

			#ifdef DEBUG
				printf("now check if %i is left of %i->%i\n", ind_p2, ind_p1, ind_p3);
			#endif

			if (points[ind_p2].is_left_of(&points[ind_p1], &points[ind_p3]) > 0)
			{
				// p2 is not part of convex hull
				#ifdef DEBUG
					printf("\terase point %i from hull\n", i-1);
					printf("\tthis is: %i\n", *(convex_hull_upper.begin()+i-1));
				#endif

				convex_hull_upper.erase(convex_hull_upper.begin()+i-1);
				++i;
			}
			else
				--i;
		}

		#ifdef DEBUG
			printf("upper hull complete:\n");
			for (int k=0; k<convex_hull_upper.size(); ++k)
				printf("\tpoint %i is %i\n", k, convex_hull_upper[k]);
		#endif


		convex_hull = convex_hull_lower;
		for (int k=convex_hull_upper.size()-3; k>=0; --k)
			convex_hull.push_back(convex_hull_upper[k]);
		//convex_hull.insert(convex_hull.end(), convex_hull_upper.begin(), convex_hull_upper.end());
	}

	#ifdef DEBUG
		printf("convex hull finished\n");
		for (int i=0; i<convex_hull.size(); ++i)
			printf("\t%i\n", convex_hull[i]);
	#endif

	// TO DO
	// start with pointers to first three points, do while points left:
		// check if second point is on the left of line defined by first -> third
			// yes: second point is not in convex hull. second = first, first = first from last iteration
			// no: first = second, second = third
		// third = next point
}

void AbstractForm::_d_print_abstract_form()
{
	#ifdef DEBUG
		printf("FUNCTION: AbstractForm::_d_print_abstract_form()\n");
	#endif

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