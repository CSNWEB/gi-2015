#include "edge.hpp"

Edge::Edge(Point *p1, Point *p2)
{
	point_1 = p1;
	point_2 = p2;
}

/**
 *  Finds the point where the receiver and other intersect each other.
 *
 *  Taken from: http://flassari.is/2008/11/line-line-intersection-in-cplusplus/
 *
 *  @param other The edge that may cross this edge.
 *
 *  @return The Point where the receiver and other intersect. NULL if they don't.
 */
Point* Edge::intersection_with_edge(Edge *other)
{
    Point *p3 = other->point_1;
    Point *p4 = other->point_2;
    
    
    // Store the values for fast access and easy
    // equations-to-code conversion
    
    if (point_1 == nullptr)
    {
        printf ("ERROR: p1 is null in %s --- Crash incoming!\n", __PRETTY_FUNCTION__);
    }
    
    if (point_2 == nullptr)
    {
        printf ("ERROR: p2 is null in %s --- Crash incoming!\n", __PRETTY_FUNCTION__);
    }
    
    if (other == nullptr)
    {
        printf ("ERROR: other is null in %s --- Crash incoming!\n", __PRETTY_FUNCTION__);
    }
    
    if (p3 == nullptr)
    {
        printf ("ERROR: p3 is null in %s --- Crash incoming!\n", __PRETTY_FUNCTION__);
    }
    
    if (p4 == nullptr)
    {
        printf ("ERROR: p4 is null in %s --- Crash incoming!\n", __PRETTY_FUNCTION__);
    }
    
    float x1 = point_1->get_x();
    float x2 = point_2->get_x();
    float x3 = p3->get_x();
    float x4 = p4->get_x();
    float y1 = point_1->get_y();
    float y2 = point_2->get_y();
    float y3 = p3->get_y();
    float y4 = p4->get_y();
    
    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0)
    {
        return NULL;
    }
    
    // Get the x and y
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
    float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
    
    // Check if the x and y coordinates are within both lines
    if ( x < std::min(x1, x2) || x > std::max(x1, x2) ||
        x < std::min(x3, x4) || x > std::max(x3, x4) )
    {
        return NULL;
    }
    
    if ( y < std::min(y1, y2) || y > std::max(y1, y2) ||
        y < std::min(y3, y4) || y > std::max(y3, y4) )
    {
        return NULL;
    }
    
    // Return the point of intersection
    return new Point(x, y);
}

bool Edge::check_if_crosses(Edge *other)
{
    Point *intersection = intersection_with_edge(other);
    
    if (intersection == NULL)
    {
        return false;
    }
    else
    {
        /**
         *  Check if none of the points of the edges is equal to the interection.
         */
        float x = intersection->get_x();
        float y = intersection->get_y();
        
        if ((point_1->get_x() == x && point_1->get_y() == y) ||
            (point_2->get_x() == x && point_2->get_y() == y) ||
            (other->point_1->get_x() == x && other->point_1->get_y() == y) ||
            (other->point_2->get_x() == x && other->point_2->get_y() == y))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}
