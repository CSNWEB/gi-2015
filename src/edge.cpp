#include "edge.hpp"

Edge::Edge(Point *p1, Point *p2)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	point_1 = p1;
	point_2 = p2;
}

bool Edge::check_if_crosses(Edge *other)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	float dp11 = point_1->get_distance_to(other->point_1);
	float dp12 = point_1->get_distance_to(other->point_2);
	float dp21 = point_2->get_distance_to(other->point_1);
	float dp22 = point_2->get_distance_to(other->point_2);
	
	float min1 = std::min(dp11, dp12);
	float min2 = std::min(dp21, dp22);
		
	float minimum_distance = std::min(min1, min2);
	
	// check if both edges are close enough for crossing to be possible:
	if (minimum_distance < length()+other->length())
	{		
		// check if both points of other are on the same side of this edge by cross-product

		float z1 = ((point_2->get_x()-point_1->get_x()) * (other->point_1->get_y()-point_1->get_y())) - ((other->point_1->get_x()-point_1->get_x()) * (point_2->get_y() - point_1->get_y()));
		float z2 = ((point_2->get_x()-point_1->get_x()) * (other->point_2->get_y()-point_1->get_y())) - ((other->point_2->get_x()-point_1->get_x()) * (point_2->get_y() - point_1->get_y()));
		
		if (z1*z2 >= 0)
		{
			// this and other do not cross
		}
		else
		{
			// check if both edges cross:
			// solve equation point_1+ lambda*(point_2-point_1) = o.point_1 + mu*(o.point_2-o.point_1)
			// and check if x,y are within {0,1}
			float lambda = (point_1->get_y() - (other->point_1)->get_y() - point_1->get_x() + (other->point_1)->get_x()) / (- (point_2->get_y() - point_1->get_y() ) * (1+(point_2->get_x() - point_1->get_x()) / (point_2->get_y() - point_2->get_y()) ));
			float mu = (point_1->get_x() - (other->point_1)->get_x() + lambda*(point_2->get_x() - point_1->get_x())) / ((other->point_2)->get_x() - (other->point_1)->get_x());

			if (lambda > 0 && lambda < 1 && mu > 0 && mu < 1)
			{
				// this and other cross!
			}
		}
	}
}

void Edge::_d_print_edge_to_console()
{
	#ifdef DEBUG
		printf("Edge from point %.2f/%.2f to point %.2f/%.2f with length %.2f\n", point_1->get_x(), point_1->get_y(), point_2->get_x(), point_2->get_y(), length());
	#endif
}