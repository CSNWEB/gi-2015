#ifndef FORM_H
#define FORM_H

#include <vector>

#include "edge.hpp"
#include "abstractForm.hpp"

class AbstractForm;

#define floatmat vector<vector<float>>

using namespace std;

class Form
{
private:
	AbstractForm *mother;
	
	int number_of_edges;

	vector<Edge> edges;
	vector<Point> points;
	
	// bounding box:
	float x_min;
	float x_max;
	float y_min;
	float y_max;
	
public:
	Form();
	
	float get_bounding_xmin();
	float get_bounding_xmax();
	float get_bounding_ymin();
	float get_bounding_ymax();
	
	void move_rel(float dx, float dy);
	void rotate(float center_x, float center_y, float degree);
	
	// checks if this form overlaps with Form other:
	bool check_for_overlap(Form *other);
	// overloaded version saves minimum distance for each two edges in float-matrix; or zero of edges cross.
	bool check_for_overlap(Form *other, floatmat* crossings);
};

#endif
