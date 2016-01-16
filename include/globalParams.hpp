/*!
 *  class GlobalParams
 *
 *  Stores and manages global parameters and constants
 */


#ifndef GLOBALPARAMS_H
#define GLOBALPARAMS_H

#include <math.h>
#include <stdio.h>


class GlobalParams
{
private:


static constexpr float PI = 3.14159265;



public:


	/*!
	 *  The actual tolerance value, as defined by the tolerance_digits
	 */
	static float tolerance;

	/*!
	 *  A bool describing whether or not complex abstractFormConfigurationTuples are precomputed before BinPacking Starts. Default true.
	 */
	static bool option_pre_merge_form;

	/*!
	 *  Getter for global constant pi
	 */
	static float pi()
	{return PI;};
    
    /*!
     * Initializes the values
     */
    void init();

	/*!
	 *  Set option_pre_merge_form
	 */
	static void set_option_pre_merge(bool option)
	{
		option_pre_merge_form = option;
	};

	static bool do_pre_merge_merge()
	{
		return option_pre_merge_form;
	};

	/*!
	 *  Getter for global tolerance which is applied when checking if a form overlaps with another form or the plane borders. If tolerance has not been defined yet, it is initialized to 1E-4
	 */
	static float get_tolerance();
    

    static void set_tolerance(double new_tolerance);
    

};

#endif
