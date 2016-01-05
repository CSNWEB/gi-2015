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
	 *  A global tolerance applied when checking if a form overlaps with another form or the plane borders
	 *
	 *  If the basic unit is considered to be centimeters, 1E-4 is equal to a micrometer. We assume this is an irrelevant (or even unmeasureable) error in practical applications.
	 */
	static int tolerance_digits;

	/*!
	 *  The actual tolerance value, as defined by the tolerance_digits
	 */
	static float tolerance;

	/*!
	 *  Getter for global constant pi
	 */
	static float pi()
	{return PI;};

	/*!
	 *  Getter for global tolerance which is applied when checking if a form overlaps with another form or the plane borders. If tolerance has not been defined yet, it is initialized to 1E-4 (i.e. tolerance_digits is initialized to 4).
	 */
	static float get_tolerance();

	/*!
	 *  Set the relevant digits of the tolerance 
	 */
	static void set_significant_digits(int digits);
};

#endif