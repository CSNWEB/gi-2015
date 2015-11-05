#ifndef PLANE_H
#define PLANE_H

#include <vector>

#include "form.hpp"

#define boolmat vector<vector<bool>>

using namespace std;

class Plane
{
private:
	float dx;
	float dy;
	
	int number_of_forms;
	
	vector<Form> forms;
	
	boolmat overlappings;

public:
	// computes which forms overlap pairwise and saves result in bool-matrix overlappings 
	void compute_all_overlappings();

};

#endif
