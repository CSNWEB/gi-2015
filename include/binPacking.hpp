/*!
 *  class BinPacking
 *
 *  This implements a 2-dimensional bin-packing-algorithm.
 *  The algorithm uses shelfs that are filled by forms from left to right, considering only the bounding boxes of the forms.
 *  Starting with the forms with maximum size of the smaller dimension and iterating through all forms by decreasing size, the algorithm
 *  places each form greedily on the first shelf the form fits on. If there is no such shelf, a new shelf is created on the first plane with
 *  sufficient space. If there is no such plane, a new plane is created.
 */

#ifndef BINPACKING_H
#define BINPACKING_H

#include <vector>

#include "problem.hpp"
#include "setting.hpp"
#include "binPackingPlane.hpp"
#include "binPackingShelf.hpp"
#include "abstractForm.hpp"
#include "abstractFormConfiguration.hpp"
#include "global.hpp"

using namespace std;

/*!
 *  Struct FormComparator
 *
 *  Struct used in sorting forms by their x- and y- dimensions
 */
struct FormComparator
{
	FormComparator(Problem *p) : problem(p)
	{
		#ifdef DEBUG
			printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
		#endif
	}

	Problem *problem;
	AbstractForm* form_1;
	AbstractForm* form_2;

	bool operator()(int index_of_box_1, int index_of_box_2)
	{
		#ifdef DEBUG
			printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
		#endif

		float smaller_edge_box_1;
		float smaller_edge_box_2;
		float bigger_edge_box_1;
		float bigger_edge_box_2;

		form_1 = problem->get_abstract_form_at_position(index_of_box_1);
		form_2 = problem->get_abstract_form_at_position(index_of_box_2);

		if (form_1->get_dx() < form_1->get_dy())
		{
			smaller_edge_box_1 = form_1->get_dx();
			bigger_edge_box_1  = form_1->get_dy();
		}
		else
		{
			smaller_edge_box_1 = form_1->get_dy();
			bigger_edge_box_1  = form_1->get_dx();
		}
		if (form_2->get_dx() < form_2->get_dy())
		{
			smaller_edge_box_2 = form_2->get_dx();
			bigger_edge_box_2  = form_2->get_dy();
		}
		else
		{
			smaller_edge_box_2 = form_2->get_dy();
			bigger_edge_box_2  = form_2->get_dx();
		}

		if (smaller_edge_box_1 - smaller_edge_box_2 > TOLERANCE)
			return true;
		else if (smaller_edge_box_2 - smaller_edge_box_1 > TOLERANCE)
			return false; 
		else return (bigger_edge_box_1 - bigger_edge_box_2 > TOLERANCE);
	};
};

class BinPacking
{
private:
	/*!
	 *  A pointer to the problem to acess forms and the size of a plane
	 */
	Problem *problem;

	/*!
	 *  The indices of the abstract forms, sorted by height (and width, if heights are equal) of the bounding box.
	 */
	vector<int> all_forms_sorted_by_size;

	/*!
	 *  vektor to organize the planes during the algorithm
	 *  mainly for checking the remaining space 
	 */
	vector<BinPackingPlane> bp_planes;

	/*!
	 *  vektor to organize all shelves during the algorithm
	 *  
	 *  This should be a priority queue!
	 */
	vector<BinPackingShelf> bp_shelves;

	/*!
	 *  Sort all forms by the smaller edge and store the sorted indices in 
	 *	all_forms_sorted_by_size
	 */
	void create_initial_sorting();

public:
	/*!
	 *  Constructor
	 *
	 *  Needs a pointer to an instance of class Problem, otherwise no bin packing can be computed
	 *
	 *  @param p 	a pointer to a problem for which the binpacking should be computed
	 */
	BinPacking(Problem *p);

	/*!
	 *  Use 2-dimensional bin-packing with bounding boxes to create a setting
	 *  algorithm sorts bounding boxes by height (and width, if heights are equal)
	 *  then for every form is placed on the first shelf it fits on.
	 *  If there is no approriate shelf, a new shelf is created on the first plane with enough space.
	 */
	Setting get_packed_setting();

};

#endif