#include "form.hpp"


Form::Form(AbstractForm* mother)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif
		
	this->mother = mother;

	x_min = 0;
	x_max = mother->get_dx();
	y_min = 0;
	y_max = mother->get_dy();

	number_of_edges = mother->get_number_of_points();

	points = vector<Point>(number_of_edges);
	edges  = vector<Edge>(number_of_edges);

	points[0] = mother->get_point_at_index(0);

	for (int i=1; i<number_of_edges; ++i)
	{
		points[i] = mother->get_point_at_index(i);
		edges[i-1] = Edge(&(points[i-1]), &(points[i]));
	}

	edges[number_of_edges-1] = Edge(&(points[number_of_edges-1]), &(points[0]));
}

Form::Form(AbstractForm *mother, float pos_x, float pos_y)
{	
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	this->mother = mother;
	
	x_min = pos_x;
	x_max = pos_x + mother->get_dx();
	y_min = pos_y;
	y_max = pos_y + mother->get_dy();

	number_of_edges = mother->get_number_of_points();

	points = vector<Point>(number_of_edges);
	edges  = vector<Edge>(number_of_edges);

	points[0] = Point(mother->get_point_at_index(0));
	points[0].move_rel(pos_x, pos_y);

	for (int i=1; i<number_of_edges; ++i)
	{
		points[i] = Point(mother->get_point_at_index(i));
		points[i].move_rel(pos_x, pos_y);
		edges[i-1] = Edge(&(points[i-1]), &(points[i]));
	}

	edges[number_of_edges-1] = Edge(&(points[number_of_edges-1]), &(points[0]));
}

bool Form::check_for_overlap(Form *other)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif
	// check if both bounding-boxes overlap
	// if no, no overlap
	// else check overlapping of edges pairwise
	
	bool overlap_bounding = false;
	if (x_max > other->x_min && x_min < other->x_max)
		if (y_max > other->y_min && y_min < other->y_max)
			overlap_bounding = true;
	
	if (overlap_bounding)
	{
		bool crossing = false;
		for (int i=0; i<number_of_edges; ++i)
			for (int j=i; j<other->number_of_edges; ++j)
				if (edges[i].check_if_crosses(&(other->edges[j])))
					crossing = true;
		return crossing;
	}
	else
		return false;
}

Point Form::get_centroid()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

    float x = 0.0;
    float y = 0.0;
    
    for (unsigned int index = 0; index < points.size(); index++)
    {
        x += points[index].get_x();
        y += points[index].get_y();
    }
    
    x /= points.size();
    y /= points.size();
    
    return Point(x, y);
}

void Form::move_rel(float dx, float dy)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	for (int i=0; i<points.size(); ++i)
		points[i].move_rel(dx, dy);
	x_min += dx;
	x_max += dx;
	y_min += dy;
	y_max += dy;
}

void Form::rotate(float center_x, float center_y, float angle)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	for (int i=0; i<points.size(); ++i)
	{
		points[i].rotate(center_x, center_y, angle);
		if (points[i].get_x() < x_min)
			x_min = points[i].get_x();
		if (points[i].get_x() > x_max)
			x_max = points[i].get_x();
		if (points[i].get_y() < y_min)
			y_min = points[i].get_y();
		if (points[i].get_y() > y_max)
			y_max = points[i].get_y();
	}

	#ifdef DEBUG
		printf("\tBounding box updated to:\n\t(%.2f,%.2f) - (%.2f,%.2f)\n",x_min, y_min, x_max, y_max);
	#endif
}
	
void Form::_d_print_points_to_console()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
		
		printf("Number of points: %i\n", points.size());

		for (int i=0; i<points.size(); ++i)
			printf("Point %2i at %.1f/%.1f\n", i, points[i].get_x(), points[i].get_y());
	#endif
}

void Form::_d_print_edges_to_console()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);

		printf("Number of edges: %i\n", edges.size());
		for (int i=0; i<edges.size(); ++i)
			edges[i]._d_print_edge_to_console();
	#endif
}

void Form::_d_print_convex_hull_to_console()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);

		vector<int> *hull = mother->get_convex_hull();
		printf("Convex hull of form has %i points\n", hull->size());
		for (int i=0; i<hull->size(); ++i)
			printf("Point %2i at %.1f/%.1f\n", i, points[(*hull)[i]].get_x(), points[(*hull)[i]].get_y());
	#endif
}

void Form::print_form_to_svg(svg::Document * doc, int x_offset, int y_offset, int scale)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
		printf("Painting Polygon\n");
    #endif

    svg::Polygon polygon(svg::Color(200, 160, 220), svg::Stroke(1, svg::Color::Black));

    for (int i=0; i<points.size(); ++i)
		polygon << svg::Point(points[i].get_x()*scale + x_offset, points[i].get_y()*scale + y_offset);
    
    (*doc) << polygon;    
}

void Form::print_convex_hull_to_svg(svg::Document * doc, int x_offset, int y_offset, int scale)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
		printf("Painting convex hull\n");
	#endif

	vector<int> *convex_hull_points = mother->get_convex_hull();

	#ifdef DEBUG
		printf("Got points of hull\n");
	#endif

	svg::Polyline convex_hull_line(svg::Stroke(5, svg::Color::Blue));
	for (int i=0; i<convex_hull_points->size(); ++i)
	{
		#ifdef DEBUG
			printf("Consider the %ith point on convex hull: is point %i\n", i, (*convex_hull_points)[i]);
		#endif
		convex_hull_line << svg::Point(points[(*convex_hull_points)[i]].get_x()*scale + x_offset, points[(*convex_hull_points)[i]].get_y()*scale + y_offset);
	}

	#ifdef DEBUG
		printf("Hull in svg created\n");
	#endif

	(*doc) << convex_hull_line;	
}