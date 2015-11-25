#ifndef BINPACKING_H
#define BINPACKING_H

#include <vector>

#include "problem.hpp"
#include "setting.hpp"
#include "binPackingPlane.hpp"
#include "binPackingShelf.hpp"
#include "abstractForm.hpp"

using namespace std;

struct FormComparator
{
	FormComparator(Problem *p) : problem(p){}

	Problem *problem;
	AbstractForm* form_1;
	AbstractForm* form_2;

	bool operator()(int index_of_box_1, int index_of_box_2)
	{
		#ifndef DEBUG
			printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
		#endif

		int smaller_edge_box_1;
		int smaller_edge_box_2;

		form_1 = problem->get_abstract_form_at_position(index_of_box_1);
		form_2 = problem->get_abstract_form_at_position(index_of_box_2);

		if (form_1->get_dx() < form_1->get_dy())
			smaller_edge_box_1 = form_1->get_dx();
		else
			smaller_edge_box_1 = form_1->get_dy();

		if (form_2->get_dx() < form_2->get_dy())
			smaller_edge_box_2 = form_2->get_dx();
		else
			smaller_edge_box_2 = form_2->get_dy();

		if (smaller_edge_box_1 <= smaller_edge_box_2)
			return false;
		else
			return true; 
	};
};

class BinPacking
{
private:
	Problem *problem;

	Setting packed_setting;


	vector<int> all_forms_sorted_by_size;

	/**
	 *  2-dim vektor to organize the the shelfs of each plane
	 *
	 *  shelfs_on_planes[p][s] is shelf #s on plane #p
	 */
	vector<BinPackingPlane> bp_planes;

	/**
	 *  Sort all forms by the smaller edge and store the sorted indices in 
	 *	all_forms_sorted_by_size
	 */
	void create_initial_sorting();

public:
	BinPacking(Problem *p);

	/**
	 *  Use 2-dimensional bin-packing with bounding boxes to create a setting
	 */
	Setting get_packed_setting();
};

#endif