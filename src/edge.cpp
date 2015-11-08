#include "edge.hpp"

Edge::Edge(Point *p1, Point *p2)
{
	this->p1 = p1;
	this->p2 = p2;
}

bool Edge::check_if_crosses(Edge *other)
{
	float dp11 = p1->get_distance_to(other->p1);
	float dp12 = p1->get_distance_to(other->p2);
	float dp21 = p2->get_distance_to(other->p1);
	float dp22 = p2->get_distance_to(other->p2);
	
	float min1 = std::min(dp11, dp12);
	float min2 = std::min(dp21, dp22);
		
	float minimum_distance = std::min(min1, min2);
	
	// check if both edges are close enough for crossing to be possible:
	if (minimum_distance < length()+other->length())
	{		
		// check if both points of other are on the same side of this edge by cross-product

		float z1 = ((p2->get_x()-p1->get_x()) * (other->p1->get_y()-p1->get_y())) - ((other->p1->get_x()-p1->get_x()) * (p2->get_y() - p1->get_y()));
		float z2 = ((p2->get_x()-p1->get_x()) * (other->p2->get_y()-p1->get_y())) - ((other->p2->get_x()-p1->get_x()) * (p2->get_y() - p1->get_y()));
		
		if (z1*z2 >= 0)
		{
			// this and other do not cross
		}
		else
		{
			// check if both edges cross:
			// solve equation p1+ lambda*(p2-p1) = o.p1 + mu*(o.p2-o.p1)
			// and check if x,y are within {0,1}
			float lambda = (p1->get_y() - (other->p1)->get_y() - p1->get_x() + (other->p1)->get_x()) / (- (p2->get_y() - p1->get_y() ) * (1+(p2->get_x() - p1->get_x()) / (p2->get_y() - p2->get_y()) ));
			float mu = (p1->get_x() - (other->p1)->get_x() + lambda*(p2->get_x() - p1->get_x())) / ((other->p2)->get_x() - (other->p1)->get_x());

			if (lambda > 0 && lambda < 1 && mu > 0 && mu < 1)
			{
				// this and other cross!
			}
		}
	}
}

void Edge::move_rel(float dx, float dy)
{
	p1->move_rel(dx, dy);
	p2->move_rel(dx,dy);
}

void Edge::rotate(float center_x, float center_y, float degree)
{
	p1->rotate(center_x, center_y, degree);
	p2->rotate(center_x, center_y, degree);
}
