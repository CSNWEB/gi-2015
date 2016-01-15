/*!
 * class FORMCOMBINER
 *
 * Computes a optimized combination of two given AbstractFormConfigurations, such that their combined bounding box has better space utilization than the two original bounding boxes.
 */

#ifndef FORMCOMBINER_H
#define FORMCOMBINER_H

#include "abstractForm.hpp"
#include "abstractFormConfiguration.hpp"
#include "abstractFormConfigurationTuple.hpp"
#include "problem.hpp"
#include "pointSetAlgorithms.hpp"

#include <iterator>
#include <vector>

class AbstractFormConfigurationTuple;

using namespace std;

class FormCombiner
{
private:
	/*!
	 *  Two AbstractFormConfigurations for which an optimized Tuple should be computed.
	 */
	AbstractFormConfiguration form_config_1;

	/*!
	 *  Two AbstractFormConfigurations for which an optimized Tuple should be computed.
	 */
	AbstractFormConfiguration form_config_2;

	/*!
	 *  The two AbstractForm according to the AbstractFormConfigurations.
	 */
	AbstractForm *form_1;

	/*!
	 *  The two AbstractForm according to the AbstractFormConfigurations.
	 */
	AbstractForm *form_2;

	/*!
	 *  A mirrored variation of the second form
	 */
	AbstractForm form_2_mirrored;

	/*!
	 *  The two actual Forms, needed to compute area of bounding box and to compute rotations, positions and to check if both forms overlap.
	 */
	Form f1;

	/*!
	 *  The two actual Forms, needed to compute area of bounding box and check if both forms overlap.
	 */
	Form f2;

	/*!
	 *  The two actual Forms, needed to compute area of bounding box and to compute rotations, positions and to check if both forms overlap. The mirrored variant of the second form.
	 */
	Form f2_m;

	/*!
	 *  A pointer to the problem. Needed to decide if a combined form still fits on plane.
	 */
	Problem* problem;

	/*!
	 *  A float describing the area of the bigger bounding box of the two forms. This is an lower bound to the bounding box of any merged configuration of both forms, and used to check if the algorithm can stop.
	 */
	float area_of_biggest_box_of_forms;

	/*!
	 *  A float describing the summed area of both bounding-boxes. This gives an lower bound to the achievable area-utilization.
	 */
	float sum_of_bounding_boxes;


	/*!
	 *  The area of the bounding box of the current configuration.
	 */
	float cur_configuration_area;

	/*!
	 *  The x-position of form 1 in the current configuration
	 */
	float cur_position_form_1_x;
	
	/*!
	 *  The y-position of form 1 in the current configuration
	 */
	float cur_position_form_1_y;

	/*!
	 *  The rotation of form 1 in the current configuration
	 */
	float cur_rotation_form_1;

	/*!
	 *  The x-position of form 2 in the current configuration
	 */
	float cur_position_form_2_x;
	
	/*!
	 *  The y-position of form 2 in the current configuration
	 */
	float cur_position_form_2_y;

	/*!
	 *  The rotation of form 2 in the current configuration
	 */
	float cur_rotation_form_2;

	/*!
	 *  If form 2 is mirrored in the current configuration
	 */
	bool cur_mirror_form_2;

	/*!
	 *  The optimal rotation of the tuple of the current cofiguration, such that the combined bounding box has minimal area
	 */
	float cur_total_rotation;


	/*!
	 *  The area of the bounding box of the best configuration.
	 */
	float opt_configuration_area;

	/*!
	 *  The x-position of form 1 in the best configuration
	 */
	float opt_position_form_1_x;
	
	/*!
	 *  The y-position of form 1 in the best configuration
	 */
	float opt_position_form_1_y;

	/*!
	 *  The rotation of form 1 in the best configuration
	 */
	float opt_rotation_form_1;

	/*!
	 *  The x-position of form 2 in the best configuration
	 */
	float opt_position_form_2_x;
	
	/*!
	 *  The y-position of form 2 in the best configuration
	 */
	float opt_position_form_2_y;

	/*!
	 *  The rotation of form 2 in the best configuration
	 */
	float opt_rotation_form_2;

	/*!
	 *  If form 2 is mirrored in the best configuration
	 */
	bool opt_mirror_form_2;

	/*!
	 *  The optimal rotation of the tuple of the best cofiguration, such that the combined bounding box has minimal area
	 */
	float opt_total_rotation;


	/*!
	 *  A bool to flag if an optimum (or a tuple with sufficient good area utilization) has been found.
	 */
	bool optimum_found;

	/*!
	 *  A flag describing if the algorithm has computed an AbstractFormConfigurationTuple.
	 */
	bool is_finished;


	/*!
	 *  A temporary needed array of points. During the algorithm, it tracks all Points of the combined form in a specific order, such that all points in order give all edges of this tuple of forms
	 */
	vector<Point> allpoints;

	/*!
	 *  A temporary needed array of indices, describes the points in the convex hull of the tuple in the current configuration
	 */
	vector<int> hull_of_tuple;

	/*!
	 *  Initialize the algorithm.
	 */
	void init();

	/*!
	 *  For a given index of a point, compute the configuration of form 1 such that the point lies on (0/0) and the edge to the next point lies on the x-axis.
	 */
	void compute_config_form_1(int index_of_point);

	/*!
	 *  For a given index of a point, compute the configuration of form 2 such that the point lies on (0/0) and the edge to the next point lies on the x-axis.
	 */
	void compute_config_form_2(int index_of_point, bool is_mirrored);

	/*!
	 *  Reset the Form f1 to its initial state after it was potentially moved and rotated during the last iteration of Form 2
	 */
	void reset_form_1();	
	
	/*!
	 *  Computes the convex hull of the current configuration of f1 and f2. Uses the convex hull to compute optimal rotation and the area of the bounding box. Needs indices of the configuration-defining points to create a correct combination of the point-vectors.
	 */
	void compute_optimal_rotation_and_area_for_tuple_config(int index_of_point_1, int index_of_point_2);

	/*!
	 *  Check if the current configuration is better than the best-so-far, and if yes, update values describing the best configuration.
	 */
	bool update_if_better();

	/*!
	 *  Based on the current optimal values, create an AbstractFormConfigurationTuple.
	 */
	AbstractFormConfigurationTuple create_config_tuple();

public:
	/*!
	 *  Empty Constructor
	 */
	//FormCombiner(){};

	/*!
	 *  Default Constructor
	 */
	FormCombiner(Problem *p, AbstractFormConfiguration &form_config_1, AbstractFormConfiguration &form_config_2);

	/*!
	 *  Compute optimal configuration for the two AbstractForms and creates an AbstractFormConfigurationTuple
	 *
	 *  @return 	the constructed AbstractFormConfigurationTuple, or Null if no efficient combination was found
	 */
	void compute_optimal_configuration();

	/*!
	 *  Get the optimal configurated tuple.
	 *
	 *  @return 	the constructed AbstractFormConfigurationTuple.
	 */
	AbstractFormConfigurationTuple get_optimal_configured_tuple();
};

#endif