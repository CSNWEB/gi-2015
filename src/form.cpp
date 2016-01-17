#include "form.hpp"

#ifdef DEBUG
	#define DEBUG_FORM
#endif

Form::Form(AbstractForm *mother, float pos_x, float pos_y)  : mother(mother), x_min(pos_x), y_min(pos_y)
{	
	#ifdef DEBUG_FORM
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	x_max = pos_x + mother->get_dx();
	y_max = pos_y + mother->get_dy();

	number_of_edges = mother->get_number_of_points();

	points = vector<Point>(number_of_edges);

	points[0] = Point(mother->get_point_at_index(0));
	points[0].move_rel(pos_x, pos_y);

	for (int i=1; i<number_of_edges; ++i)
	{
		#ifdef DEBUG_FORM
			printf("\tCreate point[%i]\n", i);
		#endif

		points[i] = Point(mother->get_point_at_index(i));
		points[i].move_rel(pos_x, pos_y);
	}

	_d_print_edges_to_console();
}

bool Form::check_for_overlap(Form &other)
{
    #ifdef DEBUG_FORM
        printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
    #endif
    
    return overlap_distance_with_form(other) > GlobalParams::get_tolerance();
}

float Form::overlap_distance_with_form(Form &other)
{
	#ifdef DEBUG_FORM
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif
 
    /**
     * 	check if both bounding-boxes overlap
     *	if no, no overlap
     *	else check overlapping of edges pairwise
     */
	bool overlap_bounding = false;

	// overlap with tolerance:
	if ((x_max - other.x_min > GlobalParams::get_tolerance()) &&
		(other.x_max - x_min > GlobalParams::get_tolerance()))
		if ((y_max - other.y_min > GlobalParams::get_tolerance())&&
			(other.y_max - y_min > GlobalParams::get_tolerance()))
			overlap_bounding = true;

	#ifdef DEBUG_FORM
		if(overlap_bounding)
			printf("Detected overlapping bounding boxes.\n");
	#endif

	// The bounding boxes overlap, so the forms might as well.
	if (overlap_bounding)
	{
		float overlap_size = 0.0;

		gpc_polygon this_form_gpc = {0, NULL, NULL};
		gpc_polygon other_form_gpc = {0, NULL, NULL};
		gpc_polygon result_polygon;

		// Create gpc polygon from THIS
		unsigned int this_number_of_points = points.size();
		gpc_vertex this_vertices[this_number_of_points];
		for (unsigned int index = 0; index < this_number_of_points; index++)
		{
			gpc_vertex vertex;
			vertex.x = points[index].get_x();
			vertex.y = points[index].get_y();

			this_vertices[index] = vertex;
		}

		#ifdef DEBUG_FORM
			printf("Initialized this_vertices:\n");
			for (int i=0; i<this_number_of_points; ++i)
				printf("(%.2f/%.2f) ", this_vertices[i].x, this_vertices[i].y);
			printf("\n");
		#endif

		gpc_vertex_list this_vertex_list = {this_number_of_points, this_vertices};
		//this_vertex_list.num_vertices = this_number_of_points;
		//this_vertex_list.vertex = this_vertices;

		#ifdef DEBUG_FORM
			printf("Initialized this_vertex_list:\n");
			printf("length: %i\n", this_vertex_list.num_vertices);
			for (int i=0; i<this_vertex_list.num_vertices; ++i)
				printf("(%.2f/%.2f) ", this_vertices[i].x, this_vertices[i].y);
			printf("\n");
		#endif

		//this_form_gpc.num_contours = 1;
		//this_form_gpc.contour = &this_vertex_list;
		gpc_add_contour(&this_form_gpc, &this_vertex_list, 0);

		// Create gpc polygon from OTHER
		unsigned int other_number_of_vertices = other.points.size();
		gpc_vertex other_vertices[other_number_of_vertices];
		for (unsigned int index = 0; index < other_number_of_vertices; index++)
		{
			gpc_vertex vertex;
			vertex.x = other.points[index].get_x();
			vertex.y = other.points[index].get_y();

			other_vertices[index] = vertex;
		}

		#ifdef DEBUG_FORM
			printf("Initialized other_vertices:\n");
			for (int i=0; i<other_number_of_vertices; ++i)
				printf("(%.2f/%.2f) ", other_vertices[i].x, other_vertices[i].y);
			printf("\n");
		#endif

		gpc_vertex_list other_vertex_list = {other_number_of_vertices, other_vertices};
		//other_vertex_list.num_vertices = other_number_of_vertices;
		//other_vertex_list.vertex = other_vertices;

		#ifdef DEBUG_FORM
			printf("Initialized other_vertex_list:\n");
			printf("length: %i\n", other_vertex_list.num_vertices);
			for (int i=0; i<other_vertex_list.num_vertices; ++i)
				printf("(%.2f/%.2f) ", other_vertices[i].x, other_vertices[i].y);
			printf("\n");
		#endif

		//other_form_gpc.num_contours = 1;
		//other_form_gpc.contour = &other_vertex_list;
		gpc_add_contour(&other_form_gpc, &other_vertex_list, 0);

		#ifdef DEBUG_FORM
			printf("Finished Initializing\n");
			printf("this_vertex_list:\n");
			printf("length: %i\n", this_vertex_list.num_vertices);
			for (int i=0; i<this_vertex_list.num_vertices; ++i)
				printf("(%.2f/%.2f) ", this_vertices[i].x, this_vertices[i].y);
			printf("\n");

			printf("other_vertex_list:\n");
			printf("length: %i\n", other_vertex_list.num_vertices);
			for (int i=0; i<other_vertex_list.num_vertices; ++i)
				printf("(%.2f/%.2f) ", other_vertices[i].x, other_vertices[i].y);
			printf("\n");
		#endif

		gpc_polygon_clip(GPC_INT, &this_form_gpc, &other_form_gpc, &result_polygon);

		#ifdef DEBUG_FORM
			printf("Finished gpc_polygon_clip\n");
		#endif

		if (result_polygon.num_contours > 0)
		{
            float max_clipped_size = 0.0;
            
            for (int index = 0; index < result_polygon.num_contours; index++)
            {
                gpc_vertex_list vertex_list = result_polygon.contour[index];
                
                std::vector<Point> clipped_form_points = std::vector<Point>(vertex_list.num_vertices);
                
                for (int vertex_index = 0;
                     vertex_index < vertex_list.num_vertices;
                     vertex_index++)
                {

                    clipped_form_points[vertex_index] = Point((float)vertex_list.vertex[vertex_index].x,
                                                               (float)vertex_list.vertex[vertex_index].y);
                }

                #ifdef DEBUG_FORM
               		printf("Check for clipping case %i\n", index);
               	#endif
                
                AbstractForm clipped_form = AbstractForm("clipped", clipped_form_points);
                
                if (clipped_form.get_size_of_area() > max_clipped_size)
                {
                    max_clipped_size = clipped_form.get_size_of_area();
                }
            }
            
            overlap_size = max_clipped_size;
		}

		gpc_free_polygon(&this_form_gpc);
		gpc_free_polygon(&other_form_gpc);
		gpc_free_polygon(&result_polygon);
		
		return overlap_size;
	}
	else
    {
		return 0.0;
    }
}

Point Form::get_centroid()
{
	#ifdef DEBUG_FORM
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

    #ifdef DEBUG_FORM
    	printf("Finished get_centroid\n");
    #endif

    return Point(x, y);
}

void Form::move_rel(float dx, float dy)
{
	#ifdef DEBUG_FORM
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	for (unsigned int i=0; i<points.size(); ++i)
		points[i].move_rel(dx, dy);
	x_min += dx;
	x_max += dx;
	y_min += dy;
	y_max += dy;
}

void Form::rotate(float center_x, float center_y, float angle)
{
	#ifdef DEBUG_FORM
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	PointSetAlgorithms::rotate_pointset_at_point(points, center_x, center_y, angle, x_min, x_max, y_min, y_max);

	#ifdef DEBUG_FORM
		printf("\tBounding box updated to:\n\t(%.2f,%.2f) - (%.2f,%.2f)\n",x_min, y_min, x_max, y_max);
	#endif
}

void Form::mirror()
{
	#ifdef DEBUG_FORM
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	PointSetAlgorithms::mirror_pointset_at_axis(points, y_min, y_max);
}
	
void Form::_d_print_points_to_console()
{
	#ifdef DEBUG_FORM
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif
		
		printf("Number of points: %i\n", points.size());

		for (unsigned int i=0; i<points.size(); ++i)
			printf("Point %2i at %.1f/%.1f\n", i, points[i].get_x(), points[i].get_y());
}

void Form::_d_print_edges_to_console()
{
	#ifdef DEBUG_FORM
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);

		printf("Number of edges: %i\n", points.size());
		for (unsigned int i=1; i<points.size(); ++i)
		{
			Edge e(points[i-1], points[i]);
			e._d_print_edge_to_console();
		}
		Edge e(points[points.size()], points[0]);
		e._d_print_edge_to_console();
	#endif
}

void Form::_d_print_convex_hull_to_console()
{
	#ifdef DEBUG_FORM
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);

		vector<int> *hull = mother->get_convex_hull();
		printf("Convex hull of form has %i points\n", hull->size());
		for (unsigned int i=0; i<hull->size(); ++i)
			printf("Point %2i at %.1f/%.1f\n", i, points[(*hull)[i]].get_x(), points[(*hull)[i]].get_y());

	#endif
}

void Form::print_form_to_svg(svg::Document * doc, int x_offset, int y_offset, int scale)
{
	#ifdef DEBUG_FORM
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
		printf("Painting Polygon\n");
    #endif

    svg::Polygon polygon(svg::Color(200, 160, 220), svg::Stroke(1, svg::Color::Black));

    for (unsigned int i=0; i<points.size(); ++i)
		polygon << svg::Point(points[i].get_x()*scale + x_offset, points[i].get_y()*scale + y_offset);

    (*doc) << polygon;
}

void Form::print_convex_hull_to_svg(svg::Document * doc, int x_offset, int y_offset, int scale)
{
	#ifdef DEBUG_FORM
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
		printf("Painting convex hull\n");
	#endif

	vector<int> *convex_hull_points = mother->get_convex_hull();

	#ifdef DEBUG_FORM
		printf("Got points of hull\n");
	#endif

	svg::Polyline convex_hull_line(svg::Stroke(5, svg::Color::Blue));
	for (unsigned int i=0; i<convex_hull_points->size(); ++i)
	{
		#ifdef DEBUG_FORM
			printf("Consider the %ith point on convex hull: is point %i\n", i, (*convex_hull_points)[i]);
		#endif
		convex_hull_line << svg::Point(points[(*convex_hull_points)[i]].get_x()*scale + x_offset, points[(*convex_hull_points)[i]].get_y()*scale + y_offset);
	}

	#ifdef DEBUG_FORM
		printf("Hull in svg created\n");
	#endif

	(*doc) << convex_hull_line;	
}
