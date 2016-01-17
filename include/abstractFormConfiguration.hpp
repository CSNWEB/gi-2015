/*!
 *  class ABSTRACTFORMCONFIGURATION
 *
 *  stores the configuration (i.e. movement and rotation) of one abstractForms. Is needed to handle combinations of abstractForms (MultiAbstractForm etc.)
 */

#ifndef ABSTRACTFORMCONFIGURATION_H
#define ABSTRACTFORMCONFIGURATION_H

#include "abstractForm.hpp"

using namespace std;

class AbstractFormConfiguration
{
private:
	/*!
	 *  A pointer to the contained AbstractForm
	 */
	AbstractForm* form;

	/*!
	 *  A float describing the movement in dimension x of the form
	 */
	float position_x_of_form;

	/*!
	 *  A float describing the movement in dimension y of the form
	 */
	float position_y_of_form;

	/*!
	 *  A float describing the rotation angle of the form
	 */
	float rotation_of_form;

	/*!
	 *  A bool specifiing if the form is mirrored
	 */
	bool mirrored_form;

    /*!
     *  The minimum position on the x-axis of any point of the form in this configuration
     */
	float min_x;

    /*!
     *  The maximum position on the x-axis of any point of the form in this configuration
     */
	float max_x;

    /*!
     *  The minimum position on the y-axis of any point of the form in this configuration
     */
	float min_y;

    /*!
     *  The maximum position on the y-axis of any point of the form in this configuration
     */
	float max_y;

	/*!
	 *  For usage in binPacking
	 */
	int number_of_forms_needed;

	/*!
	 *  Compute the bounding box in absolute values for a moved and rotated configuration
	 */
	void compute_bounding_box();

public:
	/*!
	 *  Default constructor
	 */
	AbstractFormConfiguration(){};

	/*!
	 *  Constructor initializing a single form. This constructor needs less informations than the one above. The bounding box has to be computed.
	 *	
	 *	@param position_x 		the distance in x-direction this form has been moved from its normalized position
	 *	@param position_y 		the distance in y-direction this form has been moved from its normalized position
	 *  @param rotation 		the degree in angle this form has been rotated from its normalized position
	 *  @param mirrored 		describes if the form is mirrored or not
	 */
	AbstractFormConfiguration(
		AbstractForm *form,
		float position_x,
		float position_y,
		float rotation,
		bool mirrored,
		int number_of_forms_needed = -1
		);

	/*!
	 *  Constructor initializing a single form. This constructor needs less informations than the one above. The bounding box has to be computed.
	 *	
	 *  form 		the AbstractForm described by this configuration
	 */
	AbstractFormConfiguration(
		AbstractForm *form,
		int number_of_forms_needed = -1
		) : AbstractFormConfiguration(form, 0, 0, 0, false, number_of_forms_needed){};

	/*!
	 *  Destructor
	 *
	 *  Does not delete the element pointed at by form
	 */
	~AbstractFormConfiguration(){};

	AbstractFormConfiguration &operator=(const AbstractFormConfiguration &other)
	{
		form 				= other.form;
		position_x_of_form 	= other.position_x_of_form;
		position_y_of_form	= other.position_y_of_form;
		rotation_of_form 	= other.rotation_of_form;
		mirrored_form 		= other.mirrored_form;
		min_x = other.min_x;
		max_x = other.max_x;
		min_y = other.min_y;
		max_y = other.max_y;
		number_of_forms_needed = other.number_of_forms_needed;
	};

	/*!
	 *  Move the position of this configuration
	 */
	void move(float dx, float dy);

	/*!
	 *  Rotates this configuration. Also rotates the movement that has been done so far
	 */
	void rotate(float angle);

	/*!
	 *  Resets the flag describing if this form is mirrored.
	 */
	void mirror();

	/*!
	 *  Getter for x-position of the first point of the form in this configuration
	 */
	float get_x()
	{return position_x_of_form;};

	/*!
	 *  Getter for y-position of the first point of the form in this configuration
	 */
	float get_y()
	{return position_y_of_form;};

	/*!
	 *  Getter for rotation of form
	 */
	float get_rotation()
	{return rotation_of_form;};

	/*!
	 *  Check if form is mirrored
	 */
	bool is_mirrored()
	{return mirrored_form;};

	/*!
	 *  Get the minimum position on x-dimension of any point of the form in this configuration
	 */
	float get_min_x()
	{return min_x;};

	/*!
	 *  Get the minimum position on x-dimension of any point of the form in this configuration
	 */
	float get_min_y()
	{return min_y;};

    /*!
     *  Get the size of the bounding box in x direction.
     *
     *  @return A float representing size of the bounding box  in x direction.
     */
	float get_dx()
	{return max_x - min_x;};
    
    /*!
     *  Get the size of the bounding box in y direction.
     *
     *  @return A float representing the size of the bounding box in y direction.
     */
	float get_dy()
	{return max_y - min_y;};

	/*!
	 *  Get the area of the form
	 */
	float get_used_area()
	{return form->get_size_of_area();};

	/*!
	 *  Get the id of the form
	 */
	int get_id_of_form()
	{return form->get_id();};

	/*!
	 *  Get the amount of forms needed as defined in the problem
	 */
	int get_number_of_forms_needed()
	{return number_of_forms_needed;};

	/*!
	 *  Get the AbstractForm
	 */
	AbstractForm* get_form()
	{return form;};
};

#endif