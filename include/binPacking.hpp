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
#include <map>

#include "abstractForm.hpp"
#include "abstractFormConfiguration.hpp"
#include "abstractFormConfigurationTuple.hpp"
#include "binPackingPlane.hpp"
#include "binPackingShelf.hpp"
#include "formCombiner.hpp"
#include "tupleComparator.hpp"
#include "problem.hpp"
#include "setting.hpp"
#include "globalParams.hpp"

using namespace std;

class BinPacking
{
private:
	/*!
	 *  The problem for which a packed setting has to be created. To acess forms and the size of a plane
	 */
	Problem problem;

	/*!
	 *  The setting that is created during the algorithm
	 */
	Setting setting;

	/*!
	 *  A boolean describing if the algorithm has been initialized
	 */
	bool is_initialized;

	/*!
	 *  An index describing the tuple which has to be added to the setting in the next step. This index is an index for the internal vector all_tuples_to_use_sorted_by_size.
	 */
	int index_of_current_tuple;

	/*!
	 *  The number of different AbstractForms to pack.
	 */
	int number_of_different_forms;

	/*!
	 *  The minimum height of any form defined in the problem. Gives a lower bound on the size of a shelf.
	 */
	float minimum_height_of_any_tuple;

	/*!
	 *  All AbstractFormConfigurationTuples that contain only a single AbstractForm
	 */
	vector<AbstractFormConfigurationTuple> all_single_form_tuples;

	/*!
	 *  All computed area-efficient AbstractFormConfigurationTuples, i.e. tuples that are more efficient than using the single forms
	 */
	vector<AbstractFormConfigurationTuple> all_efficient_form_tuples;

	/*!
	 * vector only with configtuples to use
	 */
	vector<AbstractFormConfigurationTuple> all_form_tuples_to_use;

	/*!
	 *  The indices of the AbstractFormConfigurationTuples, sorted by height (and width, if heights are equal) of the bounding box.
	 */
	vector<int> all_tuples_to_use_sorted_by_size;

	/*!
	 *  Vector to organize the planes during the algorithm
	 *  mainly for checking the remaining space 
	 */
	vector<BinPackingPlane> bp_planes;

	/*!
	 *  Vector to organize all shelves during the algorithm
	 *  
	 *  This should be a priority queue!
	 */
	vector<BinPackingShelf> bp_shelves;

	/*!
	 *  Map to store the amount of forms needed. forms are specified by their id
	 */
	map<int, int> number_of_forms_needed;

	/*!
	 *  Initializes the map number_of_forms_needed
	 */
	void init_number_of_forms();

	/*!
	 *  Initially compute all efficient configuration_tuples
	 */
	void create_configuration_tuples();

	/*!
	 *  Initialize the vector all_form_tuples_to_use, such that the vector is filled with only the most efficient tuples that should be used. Every tuple in the vector has also its value for number_of_usages initialized.
	 */
	void create_all_tuples_to_use();

	/*!
	 *  Sort the vector all_form_tuples_to_use by the smaller edge and store the sorted indices in 
	 *	all_tuples_to_use_sorted_by_size
	 */
	void create_initial_sorting();

	/*!
	 *  Tries to add a tuple on an existing shelf, as described in 2DBP
	 *
	 *  @param tuple 	a pointer to the AbstractFormConfigurationTuple to add.
	 *
	 *  @return 			true, if form was placed. False, if form could not be placed on any shelf
	 */
	bool try_add_form_configuration_tuple_on_existing_shelf(AbstractFormConfigurationTuple &tuple);

	/*!
	 *  Creates a new shelf (and a new plane, if necessary) and adds the tuple to the shelf
	 */
	void add_form_configuration_tuple_on_new_shelf(AbstractFormConfigurationTuple &tuple);

	void create_shelf(int index_of_mothershelf, float size_x, float size_y, float offset_x, float offset_y);
	
	void create_subshelf(int index_of_mothershelf, AbstractForm &form_on_top, float remaining_height);

	void create_subshelf(int index_of_mothershelf, AbstractFormConfigurationTuple &tuple_on_top, float remaining_height);

	/*!
	 *  Adds a AbstractFormConfigurationTuple to the setting.
	 *
	 *  @param tuple 		A pointer to the AbstractFormConfigurationTuple to be added to setting.
	 *  @param plane_index 	The index of the plane of the setting on which the tuple should be added
	 *  @param position_x 	The x-offset of the tuple on the plane
	 *  @param  position_y 	The y-offset of the tuple on the plane
	 */
	void add_form_config_tuple_to_setting(AbstractFormConfigurationTuple &tuple, int plane_index, float position_x, float position_y);

public:
	/*!
	 *  Constructor
	 *
	 *  Needs a reference to an instance of class Problem, otherwise no bin packing can be computed
	 *
	 *  @param p 	a reference to a problem for which the binpacking should be computed
	 */
	BinPacking(Problem &p); 
    
    BinPacking &operator= (const BinPacking &other){                
    	problem = other.problem;
    	is_initialized = false;
        return *this;
    }

	/*!
	 *  Update the problem, reinitialize the algorithm
	 *
	 *  @param 		a reference to a problem.
	 */
	void update_problem(Problem &new_problem);

	/*!
	 *  Add next form to the setting
	 *
	 *  @return 		true   if form was added
	 					false  if all forms are already added to setting
	 */
	bool next_step_of_algorithm();

	/*!
	 *  Get the number of tuples that have to be added
	 */
	int get_number_of_missing_tuples();

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
	 *
	 *  @return 	true, if a packed setting was created. False, if problem is not solveable.
	 */
	bool  create_packed_setting();

	/*!
	 *  Get a specific used AbstractFormConfigurationTuple, specified by index of vector all_form_tuples_to_use
	 */
	AbstractFormConfigurationTuple *get_used_tuple_at_position(int tuple_index)
	{return &all_form_tuples_to_use[tuple_index];};
};

#endif
