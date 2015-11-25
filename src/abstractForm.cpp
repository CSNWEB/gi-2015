#include "abstractForm.hpp"

AbstractForm::AbstractForm(string name, vector<Point> points)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif
		
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

	compute_lambda_and_mu();

	compute_lambda_and_mu(true);

	rotate_convex_hull_to_configuration(find_configuration_with_minimum_bounding_box());
    
    compute_size_of_area();
}

vector<int> AbstractForm::sort_points_dim_x()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
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
		printf("FUNCITON: %s\n", __PRETTY_FUNCTION__);
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

void AbstractForm::compute_lambda_and_mu(bool consider_only_convex_hull)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
		if (consider_only_convex_hull)
			printf("\tfor convex hull\n");
		else
			printf("\tfor all points\n");
	#endif

	vector<int> allindices;

	vector<int> *indices_of_points;

	vector<float> *result_mu;
	vector<float> *result_lambda;
	int n;

	if (consider_only_convex_hull)
	{
		n = convex_hull.size()-1;
		indices_of_points 					= &convex_hull;

		relative_point_position_cv_lambda 	= vector<float>(n, 0);
		relative_point_position_cv_mu 		= vector<float>(n, 0);
		result_mu  							= &relative_point_position_cv_mu;
		result_lambda 						= &relative_point_position_cv_lambda;
	}
	else
	{
		n = points.size();
		allindices = vector<int>(n,0);
		for (int i=0; i<n; ++i)
			allindices[i] = i;
		indices_of_points 					= &allindices;

		relative_point_position_lambda 		= vector<float>(n, 0);
		relative_point_position_mu 			= vector<float>(n, 0);
		result_mu  							= &relative_point_position_mu;
		result_lambda 						= &relative_point_position_lambda;
	}

	/*
	 * d1 = (d1_x/d1_y) : vector from i-2 to i-1
	 * d2 = (d2_x/d2_y) : vector from i-2 to i
	 *
	 * => d2 = lambda[i]*d1 + mu[i]*ort(d1)
	 * => i = i-2 + d2
	 */
	float d1_x, d1_y, d2_x, d2_y;

	for (int i=2; i<n; ++i){
		d1_x = points[(*indices_of_points)[i-1]].get_x() - points[(*indices_of_points)[i-2]].get_x();
		d1_y = points[(*indices_of_points)[i-1]].get_y() - points[(*indices_of_points)[i-2]].get_y();

		d2_x = points[(*indices_of_points)[i]].get_x() - points[(*indices_of_points)[i-2]].get_x();
		d2_y = points[(*indices_of_points)[i]].get_y() - points[(*indices_of_points)[i-2]].get_y();

		#ifdef DEBUG
			printf("Compute lambda and mu for point %i\n\td1 = (%.2f/%.2f)\n\td2 = (%.2f/%.2f)\n", i, d1_x, d1_y, d2_x, d2_y);
		#endif

		(*result_mu)[i]     = compute_mu(d1_x, d1_y, d2_x, d2_y);
		(*result_lambda)[i] = compute_lambda(d1_x, d1_y, d2_x, d2_y, (*result_mu)[i]);
	}

	d1_x = points[(*indices_of_points)[n-1]].get_x() - points[(*indices_of_points)[n-2]].get_x();
	d1_y = points[(*indices_of_points)[n-1]].get_y() - points[(*indices_of_points)[n-2]].get_y();

	d2_x = points[(*indices_of_points)[0]].get_x() - points[(*indices_of_points)[n-2]].get_x();
	d2_y = points[(*indices_of_points)[0]].get_y() - points[(*indices_of_points)[n-2]].get_y();

	#ifdef DEBUG
		printf("Compute lambda and mu for point 0:\n\td1 = (%.2f/%.2f)\n\td2 = (%.2f/%.2f)\n", d1_x, d1_y, d2_x, d2_y);
	#endif

	(*result_mu)[0]     = compute_mu(d1_x, d1_y, d2_x, d2_y);
	(*result_lambda)[0] = compute_lambda(d1_x, d1_y, d2_x, d2_y, (*result_mu)[0]);

	d1_x = points[(*indices_of_points)[0]].get_x() - points[(*indices_of_points)[n-1]].get_x();
	d1_y = points[(*indices_of_points)[0]].get_y() - points[(*indices_of_points)[n-1]].get_y();

	d2_x = points[(*indices_of_points)[1]].get_x() - points[(*indices_of_points)[n-1]].get_x();
	d2_y = points[(*indices_of_points)[1]].get_y() - points[(*indices_of_points)[n-1]].get_y();
	

	#ifdef DEBUG
		printf("Compute lambda and mu for point 1:\n\td1 = (%.2f/%.2f)\n\td2 = (%.2f/%.2f)\n", d1_x, d1_y, d2_x, d2_y);
	#endif

	(*result_mu)[1]     = compute_mu(d1_x, d1_y, d2_x, d2_y);
	(*result_lambda)[1] = compute_lambda(d1_x, d1_y, d2_x, d2_y, (*result_mu)[1]);

	#ifdef DEBUG
		printf("Finished computing lambda and mu\n");
		for (int i=0; i<n; ++i)
			printf("l[%i] = %.2f - m[%i] = %.2f\n",i, (*result_lambda)[i], i, (*result_mu)[i]);
	#endif
}

float AbstractForm::compute_lambda(float d1_x, float d1_y, float d2_x, float d2_y, float mu)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (d1_x == 0)
	{
		#ifdef DEBUG
			printf("\t case d1_x = 0\n");
		#endif

		return d2_y / d1_y -1;
	}
	else if (d1_y == 0)
	{
		#ifdef DEBUG
			printf("\t case d1_y = 0\n");
		#endif
		
		return d2_x / d1_x -1;
	}
	else
	{
		#ifdef DEBUG
			printf("\t case else\n");
		#endif
		
		return (d2_x - d1_x - (mu*d1_y))/d1_x;
	}
}

float AbstractForm::compute_mu(float d1_x, float d1_y, float d2_x, float d2_y)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (d1_x == 0)
	{
		#ifdef DEBUG
			printf("\t case d1_x = 0\n");
		#endif

		return d2_x / d1_y;
	}
	else if (d1_y == 0)
	{
		#ifdef DEBUG
			printf("\t case d1_y = 0\n");
		#endif
		
		return - d2_y / d1_x;
	}
	else
	{
		#ifdef DEBUG
			printf("\t case else\n");
		#endif
		
		return - ((d2_y - (d2_x*d1_y)/d1_x)/((d1_y*d1_y)/d1_x + d1_x));	
	}
}

int AbstractForm::find_configuration_with_minimum_bounding_box()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	float minimum_area_of_bounding_box = 0;
	int optimal_configuration = -1;

	for (int configuration = 0; configuration < convex_hull.size()-1; ++configuration)
	{
		// create configuration in which 
		// edge convex_hull[configuration] - convex_hull[configuration+1] lies on y = 0 axis

		// 1) move point of convex_hull[configuration] to position (0/0)
		// 2) move next point to y=0, x>0
		// 3) iterate through all points on convex hull, compute new position. store min/max for x and y values
		// 4) compute area of bounding box

		float p1_x = 0;
		float p1_y = 0;

		float p2_x = points[convex_hull[configuration]].get_distance_to(&points[convex_hull[configuration+1]]);
		float p2_y = 0;

		float p3_x, p3_y;

		float x_min = 0;
		float x_max = p2_x;
		float y_min = 0;
		float y_max = 0;

		#ifdef DEBUG
			printf("Consider next configuration:\n(%.2f/%.2f) (%.2f/%.2f) ", p1_x, p1_y, p2_x, p2_y);
		#endif

		for (int i = 2; i < convex_hull.size(); ++i)
		{
			int point_index = (configuration+i) % (convex_hull.size()-1);

			float dx = p2_x - p1_x;
			float dy = p2_y - p1_y;
			p3_x = p1_x + (1+relative_point_position_cv_lambda[point_index])*dx + relative_point_position_cv_mu[point_index]*dy;
			p3_y = p1_y + (1+relative_point_position_cv_lambda[point_index])*dy - relative_point_position_cv_mu[point_index]*dx;

			#ifdef DEBUG
				printf("(%.2f/%.2f) ", p3_x, p3_y);
			#endif

			if (p3_x < x_min)
				x_min = p3_x;
			else if (p3_x > x_max)
				x_max = p3_x;

			if (p3_y < y_min)
				y_min = p3_y;
			else if (p3_y > y_max)
				y_max = p3_y;

			p1_x = p2_x;
			p1_y = p2_y;

			p2_x = p3_x;
			p2_y = p3_y;
		}

		#ifdef DEBUG
			printf("\n");
		#endif

		float area_of_bounding_box = (x_max-x_min) * (y_max-y_min);

		#ifdef DEBUG
			printf("Calculated size of bounding box is %.2f\n", area_of_bounding_box);
		#endif

		if (optimal_configuration == -1 || area_of_bounding_box < minimum_area_of_bounding_box)
		{
			optimal_configuration = configuration;
			minimum_area_of_bounding_box = area_of_bounding_box;

			#ifdef DEBUG
				printf("Found better configuration!\n\tArea of bounding box is %.2f\n", area_of_bounding_box);
			#endif
		}
	}

	#ifdef DEBUG
		printf("Optimal configuration found!\n\tArea of bounding box is %.2f\n\tAchieved in configuration %i\n", minimum_area_of_bounding_box, optimal_configuration);
	#endif

	return optimal_configuration;
}

void AbstractForm::rotate_convex_hull_to_configuration(int index_of_point_in_convex_hull)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	// find lambda and mu to next point of form
	int index_of_hullpoint_1 = convex_hull[index_of_point_in_convex_hull];
	int index_of_hullpoint_2 = convex_hull[(index_of_point_in_convex_hull+1) % (convex_hull.size()-1)];
	int index_of_next_point_of_form = (index_of_hullpoint_2+1) % points.size();

	#ifdef DEBUG
		printf("Initial triangle:\n\tPoint %i: %.2f/%.2f\n\tPoint %i: %.2f/%.2f\n\tPoint %i: %.2f/%.2f\n", index_of_hullpoint_1, points[index_of_hullpoint_1].get_x(), points[index_of_hullpoint_1].get_y(), index_of_hullpoint_2, points[index_of_hullpoint_2].get_x(), points[index_of_hullpoint_2].get_y(), index_of_next_point_of_form, points[index_of_next_point_of_form].get_x(), points[index_of_next_point_of_form].get_y());
	#endif

	float d1_x = points[index_of_hullpoint_2].get_x() - points[index_of_hullpoint_1].get_x();
	float d1_y = points[index_of_hullpoint_2].get_y() - points[index_of_hullpoint_1].get_y();

	float d2_x = points[index_of_next_point_of_form].get_x() - points[index_of_hullpoint_1].get_x();
	float d2_y = points[index_of_next_point_of_form].get_y() - points[index_of_hullpoint_1].get_y();

	#ifdef DEBUG
		printf("\td1 = %.2f/%.2f\n\td2 = %.2f/%.2f\n", d1_x, d1_y, d2_x, d2_y);
	#endif

	// new position of first point:
	float p1_x = 0;
	float p1_y = 0;

	// new position of second point:
	float p2_x = points[index_of_hullpoint_1].get_distance_to(&points[index_of_hullpoint_2]);
	float p2_y = 0;

	float p3_x, p3_y;

	float x_min = 0;
	float x_max = p2_x;
	float y_min = 0;
	float y_max = 0;

	// compute new position of first point of form after pair of points from convex hull
	// these lambda- and mu-values are not precomputed
	float mu = compute_mu(d1_x, d1_y, d2_x, d2_y);
	float lambda = compute_lambda(d1_x, d1_y, d2_x, d2_y, mu);
	
	float dx = p2_x;
	float dy = 0;

	#ifdef DEBUG
		printf("\tComputed lambda = %.2f and mu = %.2f\n", lambda, mu);
		printf("\tConsider points p1 = %.2f/%.2f and p2 = %.2f/%.2f\n", p1_x, p1_y, p2_x, p2_y);
	#endif

	int index_of_next_point_to_compute = index_of_next_point_of_form;

	for (int i=0; i<points.size(); ++i)
	{
		#ifdef DEBUG
			printf ("Compute new position for point %i: \n", index_of_next_point_to_compute);
		#endif

		p3_x = p2_x + (lambda * dx) + (mu * dy);
		p3_y = p2_y - (mu * dx) + (lambda * dy);

		if (p3_x < x_min)
			x_min = p3_x;
		else if (p3_x > x_max)
			x_max = p3_x;
		if (p3_y < y_min)
			y_min = p3_y;
		else if (p3_y > y_max)
			y_max = p3_y;

		points[index_of_next_point_to_compute] = Point(p3_x, p3_y);

		#ifdef DEBUG
			printf("\tPoint %i moved to %.2f/%.2f\n", index_of_next_point_to_compute, p3_x, p3_y);
		#endif

		// prepare computation of next point:
		dx = p3_x - p2_x;
		dy = p3_y - p2_y;

		p2_x = p3_x;
		p2_y = p3_y;

		index_of_next_point_to_compute = (index_of_next_point_of_form + 1 + i) % points.size();
		
		#ifdef DEBUG
			printf("\t\tindex = %i\n\t\tindex_of_next_point_to_compute = %i\n", i, index_of_next_point_to_compute);
		#endif

		mu 		= relative_point_position_mu[index_of_next_point_to_compute];
		lambda 	= relative_point_position_lambda[index_of_next_point_to_compute];

		#ifdef DEBUG
			printf("\tdx = %.2f\n\tdy = %.2f\n",dx,dy);
			printf("\tlambda = %.2f and mu = %.2f\n", lambda, mu);
		#endif
	}

	// move form such that minimal positions in x and y dimension are 0
	#ifdef DEBUG
		printf("\tx_range = %.2f - %.2f\n\ty_range = %.2f - %.2f\n",x_min,x_max,y_min,y_max);
	#endif

	normalize_position(x_min, y_min);

	this->dx = x_max-x_min;
	this->dy = y_max-y_min;
}

void AbstractForm::normalize_position(float x_min, float y_min)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	for (int i=0; i<points.size(); ++i)
	{
		points[i].move_rel(-x_min, -y_min);

		#ifdef DEBUG
			printf("\tPoint %i moved to normalized position %.2f/%.2f\n", i, points[i].get_x(), points[i].get_y());
		#endif
	}
}

void AbstractForm::compute_convex_hull()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
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

		// concatenate lower and upper hull:
		convex_hull = convex_hull_lower;

		for (int k=convex_hull_upper.size()-3; k>=0; --k)
			convex_hull.push_back(convex_hull_upper[k]);

		// check if hull and points have equal orientation
		// if not, reverse hull:
		if (convex_hull[2] < convex_hull[1])
		{
			int size_of_hull = convex_hull.size();
			for (int i=0; i < size_of_hull/2; ++i)
			{
				int tmp = convex_hull[i];
				convex_hull[i] = convex_hull[size_of_hull-1-i];
				convex_hull[size_of_hull-1-i] = tmp;
			}
		}
	}

	#ifdef DEBUG
		printf("convex hull finished\n");
		for (int i=0; i<convex_hull.size(); ++i)
			printf("\t%i\n", convex_hull[i]);
	#endif
}

void AbstractForm::_d_print_abstract_form()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);

		printf("Name of form: %s\n", name.c_str());
		printf("Number of points: %i\n", number_of_points);

		for (int i=0; i<number_of_points; ++i)
			printf("Point %2i at %.1f/%.1f\n", i, points[i].get_x(), points[i].get_y());

	#endif
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