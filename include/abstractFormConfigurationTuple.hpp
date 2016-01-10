/*!
 *  class ABSTRACTFORMCONFIGURATIONTUPLE
 *
 *  stores the configuration (i.e. movement and rotation) of one ore more abstractForms. Is needed to handle combinations of abstractForms (MultiAbstractForm etc.)
 */

#ifndef ABSTRACTFORMCONFIGURATIONTUPLE_H
#define ABSTRACTFORMCONFIGURATIONTUPLE_H

#include <vector>

#include "abstractForm.hpp"
#include "abstractFormConfiguration.hpp"
#include "formCombiner.hpp"

using namespace std;

class AbstractFormConfigurationTuple
{
private:
	/*!
	 *  A vector with all contained AbstractForms
	 */
	vector<AbstractFormConfiguration> abstract_form_configs;

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
	 *  For usage in binPacking
	 */
	int number_of_usages;

	/*!
	 *  Updates the float-values describing the bounding box and used_area after a form-configuration was added to this tuple.
	 */
	void update_bounding_box();

public:
	/*!
	 *  Default constructor
	 */
	AbstractFormConfigurationTuple(){};

	/*!
	 *  Constructor initializing a single form
	 *	
	 *	@param form_config 		an AbstractFormConfiguration describing the form
	 */
	AbstractFormConfigurationTuple(AbstractFormConfiguration form_config);

	/*!
	 *  Constructor initializing a tuple of form
	 *	
	 *	@param form_configs 		a vector of AbstractFormConfigurations describing the forms of this tuple
	 */
	AbstractFormConfigurationTuple(vector<AbstractFormConfiguration> form_config_vector);

	/*!
	 *  Compare-operator, needed to sort configurations by utilization
	 */
	friend bool operator> (const AbstractFormConfigurationTuple &afc1, const AbstractFormConfigurationTuple &afc2)
	{return afc1.utilization > afc2.utilization;};

	friend bool operator< (const AbstractFormConfigurationTuple &afc1, const AbstractFormConfigurationTuple &afc2)
	{return afc1.utilization < afc2.utilization;};

	/*!
	 *
	 */
	void compute_optimal_configuration();

	/*!
	 *
	 */
	void set_number_of_usages(int number);

	/*!
	 *  Adds a rotataion to all contained AbstractFormConfigurations
	 */
	void rotate(float angle);

	/*!
	 *  Moves this tuple to normalized position, such that the bounding box touches (0,0) and all coordinates are >= 0
	 */
	void normalize_position();

	int get_number_of_usages()
	{return number_of_usages;};

	/*!
	 *  Returns maximum number this tuple could be used, i.e. the minimum of all needed amounts of the forms contained in this configuration.
	 */
	//int get_number_of_maximum_usages();

	/*!
	 *  Decrease the number of forms needed for all contained form-configurations
	 */
	//void use_configuration(int number_of_usages);

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
	{return abstract_form_configs.size();};

	/*!
	 *  Test if this configuration contains a specific AbstractForm
	 *
	 *  @param id_of_form	The AbstractForm to test specified by id
	 *
	 *  @return 			true, if configuration contains form. false otherwise.
	 */
	bool contains_form(int id_of_form);

	/*!
	 *  Method to get configuration for a specific AbstractForm of this setting:
	 *
	 *  @param index_of_form 		the local index of the form (within this instance of AbstractFormConfiguration)
	 *
	 *  @return 					the AbstractFormConfiguration specified by index_of_form
	 */
	AbstractFormConfiguration *get_configuration_of_form(int index_of_form);

	#ifdef DEBUG

		#include <string>
		#include <sstream>

		string to_string()
		{
			ostringstream s;
			s << "Tuple_";
			for (int i=0; i<abstract_form_configs.size(); ++i)
				s << abstract_form_configs[i].get_id_of_form() << "_";

			return s.str();
		}
	#endif

};

#endif