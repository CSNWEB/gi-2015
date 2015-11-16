#ifndef SHELF_H
#define SHELF_H

/**
 *  A "shelf" used in the 2-dim. bin-packing problem
 *  this is a representation of a retangular subset of a plane
 */

#include <vector>

#include "form.hpp"

class Shelf
{
private:
	/**
	 *  The index of the plane this shelf is positioned on:
	 */
	int index_of_plane;

	/**
	 *  The indices of all forms placed on this shelf 
	 *  in order from left to right!
	 */
	vector<int> indices_of_forms;


	/**
	 *  The position in y-dim of this shelf on its plane
	 */
	float offset_height;

	/**
	 *  The height of the shelf,
	 *  i.e. the maximum size in y-dim. for any form that can be placed und this shelf
	 */
	float height;

	/**
	 *  The remaining free width on this shelf that can be filled
	 */
	float remaining_width;


public:
	/**
	 *  Constructor that creates an empty shelf on a given form with specified position and size
	 *
	 *  @param 	index_of_plane 		the index of the plane this shelf will be placed on
	 *  @param  offset_height 		the position of this shelf
	 *  @param  height 				height of the shelf
	 *  @param  width 				width of the plane
	 */
	Shelf(int index_of_plane, float offset_height, float height, float width);

	/**
	 *  Adds a form on this shelf. Also checks if there is enough space on this shelf
	 *  
	 *  @param f 		Pointer to the form that should be added to this shelf
	 *  @param index 	index of Form
	 *
	 *  @return 		true if form was sucessfully placed on shelf, false otherwise
	 */
	bool add_form(Form *f, int index);

	/**
	 *  Checks if a form could be placed on this sheld
	 *
	 *  @param f 		Pointer to the form that should be checked
	 *  
	 *  @return 		true if there is enough space for f on this shelf, false otherwise
	 */
	bool check_if_fit(Form *f);

	/**
	 *  Getter for height of shelf
	 */
	float get_height();

	/**
	 *  Getter for remaining width of shelf
	 */
	float get_remaining_width();
};


#endif