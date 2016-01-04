/*!
 *  class ABSTRACTFORMCONFIGURATION
 *
 *  stores the configuration (i.e. movement and rotation) of one ore more abstractForms. Is needed to handle combinations of abstractForms (MultiAbstractForm etc.)
 */

#ifndef ABSTRACTFORMCONFIGURATION_H
#define ABSTRACTFORMCONFIGURATION_H

#include <vector>

#include "abstractForm.hpp"

using namespace std;

class AbstractFormConfiguration
{
private:
	/*!
	 *  A vector with pointers to all contained AbstractForms
	 */
	vector<AbstractForm*> abstractforms;

	/*!
	 *  A vector of floats describing the movement in dimension x for each form
	 */
	vector<float> position_x_of_forms;

	/*!
	 *  A vector of floats describing the movement in dimension y for each form
	 */
	vector<float> position_y_of_forms;

	/*!
	 *  A vector of floats describing the rotation angle for each form
	 */
	vector<float> rotation_of_forms;

	/*!
	 *  A vector specifiing which forms are mirrored
	 */
	vector<bool> mirrored_forms;

    /*!
     *  The minimum position on the x-axis of any point of this configuration
     */
	float min_x;

    /*!
     *  The maximum position on the x-axis of any point of this configuration
     */
	float max_x;

    /*!
     *  The minimum position on the y-axis of any point of this configuration
     */
	float min_y;

    /*!
     *  The maximum position on the y-axis of any point of this configuration
     */
	float max_y;

	/*!
     *  The size of the combined bounding box of the forms in x direction.
     */
	float dx;

	/*!
     *  The size of the combined bounding box of the forms in y direction.
     */
	float dy;

	/*!
	 *  The total used area by all forms of this configuration
	 */
	float used_area;

	/*!
	 *  The total utilization of this configuration
	 */
	float utilization;

	/*!
	 *  Updates the float-values describing the bounding box and used_area after a form was added to this configuration.
	 *
	 *  @param form 			the new form, which points have to be considered for the update
	 *  @param pos_x 			the distance in x-direction this form has been moved from its normalized position
	 *  @param pos_y 			the distance in y-direction this form has been moved from its normalized position
	 *  @param rotation 		the degree in angle this form has been rotated from its normalized position
	 *  @param is_initialized	set to true, if the bounding box of this configuration is already initialized, set to false, if this is the initial update of this configuration.
	 */
	void update_bounding_box(AbstractForm *form, float pos_x, float pos_y, float rotation, bool is_initialized);

public:
	/*!
	 *  Default constructor
	 */
	AbstractFormConfiguration(){};

	/*!
	 *  Constructor initializing a single form
	 *	
	 *	@param position_x 		the distance in x-direction this form has been moved from its normalized position
	 *	@param position_y 		the distance in y-direction this form has been moved from its normalized position
	 *  @param rotation 		the degree in angle this form has been rotated from its normalized position
	 *  @param min_x 			the minimum x-dimension of the bounding box
	 *  @param max_x			the maximum x-dimension of the bounding box
	 *  @param min_y 			the minimum y-imension of the bounding box
	 *  @param max_y			the maximum y-imension of the bounding box
	 */
	AbstractFormConfiguration(AbstractForm *form, float position_x, float position_y, float rotation, float min_x, float max_x, float min_y, float max_y);

	/*!
	 *  Constructor initializing a single form. This constructor needs less informations than the one above. The bounding box has to be computed.
	 *	
	 *	@param position_x 		the distance in x-direction this form has been moved from its normalized position
	 *	@param position_y 		the distance in y-direction this form has been moved from its normalized position
	 *  @param rotation 		the degree in angle this form has been rotated from its normalized position
	 */
	AbstractFormConfiguration(AbstractForm *form, float position_x, float position_y, float rotation);

	/*!
	 *  Compare-operator, needed to sort configurations by utilization
	 */
	friend bool operator> (const AbstractFormConfiguration &afc1, const AbstractFormConfiguration &afc2)
	{return afc1.utilization > afc2.utilization;};
/*
	bool operator>=(AbstractFormConfiguration &afc1, AbstractFormConfiguration &afc2)
	{return afc1.utilization >= afc2.utilization;};
*/
	friend bool operator< (const AbstractFormConfiguration &afc1, const AbstractFormConfiguration &afc2)
	{return afc1.utilization < afc2.utilization;};
/*
	bool operator<=(AbstractFormConfiguration &afc1, AbstractFormConfiguration &afc2)
	{return afc1.utilization <= afc2.utilization;};
*/
    /*!
     *  Get the size of the bounding box in x direction.
     *
     *  @return A float representing size of the bounding box  in x direction.
     */
	float get_dx()
	{return dx;};
    
    /*!
     *  Get the size of the bounding box in y direction.
     *
     *  @return A float representing the size of the bounding box in y direction.
     */
	float get_dy()
	{return dy;};

	/*!
	 *  Get the total utilization of area of the bounding box of this configuration
	 *
	 *  @return 	A float representing the total utilization of area within the bounding box of this configuration
	 */
	float get_utilization()
	{return utilization;};

	/*!
	 *  Getter for the number of AbstractForms
	 */
	int get_number_of_forms()
	{return abstractforms.size();};

	/*!
	 *  Test if this configuration contains a specific AbstractForm
	 *
	 *  @param id_of_form	The AbstractForm to test specified by id
	 *
	 *  @return 			true, if configuration contains form. false otherwise.
	 */
	bool contains_form(int id_of_form);

	/*!
	 *  Method to add a new abstract form to this setting:
	 *
	 *	@param position_x 		the distance in x-direction this form has been moved from its normalized position
	 *	@param position_y 		the distance in y-direction this form has been moved from its normalized position
	 *  @param rotation 		the degree in angle this form has been rotated from its normalized position
	 *  @param is_mirrored 		true, if this form is mirrored at an axis
	 */
	void add_abstract_form(AbstractForm* form, float position_x, float position_y, float rotation, bool is_mirrored);

	/*!
	 *  Method to get configuration for a specific AbstractForm of this setting:
	 *
	 *  @param index_of_form 		the local index of the form (within this instance of AbstractFormConfiguration)
	 *  @param dx 					the variable to hold the x-position of the form
	 *  @param dy 					the variable to hold the y-position of the form
	 *  @param rotation 			the variable to hold the rotation of the form
	 *
	 *  @return 					true, if data can correctly be returned, false if not
	 */
	bool get_configuration_of_form(int index_of_form, float &dx, float &dy, float &rotation);
};

#endif