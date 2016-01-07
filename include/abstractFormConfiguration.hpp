/*!
 *  class ABSTRACTFORMCONFIGURATION
 *
 *  stores the configuration (i.e. movement and rotation) of one abstractForms. Is needed to handle combinations of abstractForms (MultiAbstractForm etc.)
 */

#ifndef ABSTRACTFORMCONFIGURATION_H
#define ABSTRACTFORMCONFIGURATION_H

#include "abstractForm.hpp"

using namespace std;

class AbstractFormConfigurationTuple
{
private:
	/*!
	 *  A pointer to the contained AbstractForm
	 */
	vAbstractForm* form;

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
	 *  For usage in binPacking?
	 */
	int number_of_usages;

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
	 *  Getter for x-position of form
	 */
	float get_x()
	{return position_x_of_form;};

	/*!
	 *  Getter for y-position of form
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
	{return is_mirrored;};

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
};

#endif