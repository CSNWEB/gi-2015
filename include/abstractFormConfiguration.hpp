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
     *  The size of the combined bounding box of the forms in x direction.
     */
	float dx;

	/*!
     *  The size of the combined bounding box of the forms in y direction.
     */
	float dy;

public:
	/*!
	 *  Default constructor
	 */
	AbstractFormConfiguration(){};

	/*!
	 *  Constructor initializing a single form
	 */
	AbstractFormConfiguration(AbstractForm *form, float dx, float dy, float rotation);

    /*!
     *  Get the size of the bounding box in x direction.
     *
     *  @return A float representing size of the bounding box  in x direction.
     */
	float get_dx();
    
    /*!
     *  Get the size of the bounding box in y direction.
     *
     *  @return A float representing the size of the bounding box in y direction.
     */
	float get_dy();

	/*!
	 *  Getter for the number of AbstractForms
	 */
	int get_number_of_forms(){return abstractforms.size();};

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
	 */
	void add_abstract_form(AbstractForm* form, float dx, float dy, float rotation);

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