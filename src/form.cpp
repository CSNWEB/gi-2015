#inlcude "form.hpp"

bool Form::check_for_overlap(Form other)
{
	// check if both bounding-boxes overlap
	// if no, no overlap
	// else check overlapping of edges pairwise
	
	bool overlap_bounding = false;
	if (x_max > other.x_min && x_min < other.x_max)
		if (y_max > other.y_min && y_min < other.y_max)
			overlap_bounding = true;
	
	if (overlap_bounding)
	{
		bool crossing = false;
		for (int i=0; i<number_of_edges; ++i)
			for (int j=i; j<other.number_of_edges; ++j)
				if (edges[i].check_if_crosses(other.edges[j]))
					crossing = tue;
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
	
