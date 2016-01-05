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

#include "abstractForm.hpp"
#include "abstractFormConfiguration.hpp"
#include "binPackingPlane.hpp"
#include "binPackingShelf.hpp"
#include "formCombiner.hpp"
#include "problem.hpp"
#include "setting.hpp"
#include "globalParams.hpp"

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

		if (smaller_edge_box_1 - smaller_edge_box_2 > GlobalParams::get_tolerance())
			return true;
		else if (smaller_edge_box_2 - smaller_edge_box_1 > GlobalParams::get_tolerance())
			return false; 
		else return (bigger_edge_box_1 - bigger_edge_box_2 > GlobalParams::get_tolerance());
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
	 *  The setting that is created during the algorithm
	 */
	Setting setting;

	/*!
	 *  A boolean describing if the algorithm has been initialized
	 */
	bool is_initialized;

	/*!
	 *  An index describing the form which has to be added to the setting in the next step. This index is an index for the internal vector all_forms_sorted_by_size.
	 */
	int index_of_current_form;

	/*!
	 *  The minimum height of any form defined in the problem. Gives a lower bound on the size of a shelf.
	 */
	float minimum_height_of_any_form;

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

	/*!
	 *  Tries to add form specified by form_index (index of form in all_forms_sorted_by_size) on an existing shelf, es described in 2DBP
	 *
	 *  @param
	 *
	 *  @return 		true, if form was placed. False, if form could not be placed on any shelf
	 */
	bool try_add_form_on_existing_shelf(int form_index);

	/*!
	 *  Creates a new shelf (and a new plane, if necessary) and adds the form to the shelf
	 */
	void add_form_on_new_shelf(int form_index);

	void create_shelf(int index_of_mothershelf, float size_x, float size_y, float offset_x, float offset_y);
	void create_subshelf(int index_of_mothershelf, AbstractForm* form_on_top, float remaining_height);

	//bool add_form_to_setting(int shelf_index, form_index);

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
	 *  Add next form to the setting
	 *
	 *  @return 		true   if form was added
	 					false  if all forms are already added to setting
	 */
	bool next_step_of_algorithm();

	/*!
	 *  Get the number of forms that have to be added
	 */
	int get_number_of_missing_forms();

	/*!
	 *  Initialize the algorithm for the given problem. If it was initialized, reset everything.
	 */
	void initialize_algorithm();

	/*!
	 *  Get the current Setting.
	 */
	Setting get_current_setting();

	/*!
	 *  Use 2-dimensional bin-packing with bounding boxes to create a setting
	 *  algorithm sorts bounding boxes by height (and width, if heights are equal)
	 *  then for every form is placed on the first shelf it fits on.
	 *  If there is no approriate shelf, a new shelf is created on the first plane with enough space.
	 */
	Setting get_packed_setting();

};

#endif