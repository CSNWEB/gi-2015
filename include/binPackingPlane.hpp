#ifndef BINPACKINGPLANE_H
#define BINPACKINGPLANE_H

#include <vector>

#include "binPackingShelf.hpp"

class BinPackingPlane
{
private:
	float dx, dy;

	float remaining_height;

	//vector<BinPackingShelf> shelfs;
	
public:
	BinPackingPlane(float dx, float dy);

	/**
	 *  Add a shelf to plane
	 *
	 *  @param: height_of_shelf 	height of the shelf to be added to this plane
	 *
	 *  @return 					true, if there was enough space to add plane and plane was added
	 *								false, if there was not enough space on this plane
	 */
	bool add_shelf(float height_of_shelf);

	/**
	 *  Get remaining height
	 */
	float get_remaining_height();

	/**
	 *  Get size of shelfs
	 */
	//int get_number_of_shelfs();

	/**
	 *  Get a specific shelf
	 *
	 *  @param: index_of_shelf 		index of the shelf in vector shelfs
	 *
	 *	@return: 					a pointer to the shelf if shelf exists
	 *								NULL if shelf does not exists or index_of_shelf < 0
	 */
	//BinPackingShelf* get_shelf_at(int index_of_shelf);
};

#endif