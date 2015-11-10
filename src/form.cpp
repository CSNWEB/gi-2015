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
	printf("Number of points: %i\n", points.size());

	for (int i=0; i<points.size(); ++i)
		printf("Point %2i at %.1f/%.1f\n", i, points[i].get_x(), points[i].get_y());
}

void Form::print_form_to_svg(svg::Document doc, int x_offset)
{
    svg::Polygon polygon(svg::Color(200, 160, 220), svg::Stroke(.5, svg::Color(150, 160, 200)));
        for (int i=0; i<points.size(); ++i)
		polygon << svg::Point(points[i].get_x(), points[i].get_y());
    doc << polygon;
}