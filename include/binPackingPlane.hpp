/*!
 *  class BinPackingPlane
 *
 *  A binpackingplane is used by the binpacking-algorithm to keep track of the shelfs placed on each plane, and to determine if a shelf of a given height can be placed on a given plane.
 */

#ifndef BINPACKINGPLANE_H
#define BINPACKINGPLANE_H

#include <vector>

#include "binPackingShelf.hpp"

class BinPackingPlane
{
private:
	/*!
	 *  The size of this plane
	 */
	float dx, dy;

	/*!
	 *  The remaining size in y-dimension, i.e. the remaining space below the lowest shelf on this plane
	 */
	float remaining_height;
	
public:
	/*!
	 *  Default constructor
	 */
	BinPackingPlane(float dx, float dy);

	/*!
	 *  Add a shelf to plane
	 *
	 *  @param: height_of_shelf 	height of the shelf to be added to this plane
	 *
	 *  @return 					true, if there was enough space to add plane and plane was added
	 *								false, if there was not enough space on this plane
	 */
	bool add_shelf(float height_of_shelf);

	/*!
	 *  Get remaining height
	 */
	float get_remaining_height();
};

#endif