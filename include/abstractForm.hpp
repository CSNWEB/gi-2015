#ifndef ABSTRACTFORM_H
#define ABSTRACTFORM_H

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "point.hpp"
#include "plane.hpp"

using namespace std;

class AbstractForm
{
private:
	int number_of_points;
	string name;

	vector<Point> points;
	
	float dx,dy; // size of bounding box
	float size_of_area;
	
public:
	AbstractForm(){};
	AbstractForm(string name, vector<Point> points);

	// given a Plane and a starting Position, add this form to the plane:
	void create_form_in_plane(Plane *s, float pos_x, float pos_y);

	void _d_print_abstract_form();

	int get_number_of_points(){return number_of_points;};
	float get_dx(){return dx;};
	float get_dy(){return dy;};
	Point get_point_by_number(int num){return points[num];};

	sf::ConvexShape get_shape(int pos_x, int pos_y, int scale);
};

#endif
