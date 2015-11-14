#include "form.hpp"


Form::Form(AbstractForm* mother)
{
	// not sure if this does the right thing
	// needs testing!
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
		edges[i] = Edge(&points[i-1], &points[i]);
	}

	edges[number_of_edges-1] = Edge(&points[number_of_edges-2], &points[number_of_edges-1]);
}

Form::Form(AbstractForm *mother, float pos_x, float pos_y)
{
	this->mother = mother;
	
	x_min = pos_x;
	x_max = pos_x + mother->get_dx();
	y_min = pos_y;
	y_max = pos_y + mother->get_dy();

	number_of_edges = mother->get_number_of_points();

	points = vector<Point>(number_of_edges);
	edges  = vector<Edge>(number_of_edges);

	points[0] = mother->get_point_at_index(0);

	for (int i=1; i<number_of_edges; ++i)
	{
		points[i] = mother->get_point_at_index(i);
		points[i].move_rel(pos_x, pos_y);
		edges[i] = Edge(&points[i-1], &points[i]);
	}

	edges[number_of_edges-1] = Edge(&points[number_of_edges-2], &points[number_of_edges-1]);
}

bool Form::check_for_overlap(Form *other)
{
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
	for (int i=0; i<number_of_edges; ++i)
		edges[i].move_rel(dx, dy);
}

void Form::rotate(float center_x, float center_y, float degree)
{
	for (int i=0; i<number_of_edges; ++i)
		edges[i].rotate(center_x, center_y, degree);
}
	
void Form::_d_print_form_to_console()
{
	#ifdef DEBUG
	printf("Number of points: %i\n", points.size());

	for (int i=0; i<points.size(); ++i)
		printf("Point %2i at %.1f/%.1f\n", i, points[i].get_x(), points[i].get_y());
	#endif
}

void Form::_d_print_convex_hull_to_console()
{
	#ifdef DEBUG
	vector<int> hull = mother->get_convex_hull();
	printf("Convex hull of form has %i points\n", hull.size());
	for (int i=0; i<hull.size(); ++i)
		printf("Point %2i at %.1f/%.1f\n", i, points[hull[i]].get_x(), points[hull[i]].get_y());
	#endif
}

void Form::print_form_to_svg(svg::Document * doc, int x_offset, int y_offset, int scale)
{
	#ifdef DEBUG
    	std::cout << "Painting Polygon\n";
    #endif

    svg::Polygon polygon(svg::Color(200, 160, 220), svg::Stroke(1, svg::Color::Black));

    for (int i=0; i<points.size(); ++i)
		polygon << svg::Point(points[i].get_x()*scale + x_offset, points[i].get_y()*scale + y_offset);
    
    (*doc) << polygon;    
}

void Form::print_convex_hull_to_svg(svg::Document * doc, int x_offset, int y_offset, int scale)
{
	#ifdef DEBUG
		cout << "Painting convex hull\n";
	#endif

	vector<int> convex_hull_points = mother->get_convex_hull();

	svg::Polyline convex_hull_line(svg::Stroke(5, svg::Color::Blue));
	for (int i=0; i<convex_hull_points.size(); ++i)
		convex_hull_line << svg::Point(points[convex_hull_points[i]].get_x()*scale + x_offset, points[convex_hull_points[i]].get_y()*scale + y_offset);
	
	(*doc) << convex_hull_line;	
}