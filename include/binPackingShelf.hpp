/*!
 *  class BinPackingShelf
 *
 *  A shelf used in the 2-dim. bin-packing problem. It is a representation of a retangular subset of a plane. 
 *  During the algorithm, shelfs are created and handled as 1-dimensional subtasks
 */

#ifndef BinPackingShelf_H
#define BinPackingShelf_H

#include <vector>

#include "abstractForm.hpp"
#include "globalParams.hpp"

class BinPacking;

class BinPackingShelf
{
private:
	/*!
 	 *  Pointer to the packing this shelf is a part of
	 */
 	BinPacking *packing;

	/*!
	 *  The index of the plane this shelf is placed on:
	 */
	int index_of_plane;

	/*!
	 *  The indices of all forms placed on this shelf,
	 *  in order from left to right.
	 */
	vector<int> indices_of_forms;

	/*!
	 *  The position in y-dim of this shelf on its plane
	 */
	float offset_y;

	/*!
	 *  If this plane is a sub-shelf: the x-position of beginning of plane
	 */
	float offset_x;

	/*!
	 *  If this shelf is a sub-shelf: is it rotated (by 90 degrees)
	 */
	bool is_rotated_subshelf;

	/*!
	 *  The height of the shelf,
	 *  i.e. the maximum size in y-dimension for any form that can be placed on this shelf
	 */
	float height;

	/*!
	 *	The width of the shelf,
	 *  i.e. the remaining width on this shelf at creation
	 */
	float width;

	/*!
	 *  The remaining free width on this shelf that can be filled,
	 *  i.e. the maximum width for any form that can be placed on this shelf
	 */
	float remaining_width;


public:
	/*
	 *  Default Constructor
	 */
	BinPackingShelf(){};

	/*!
	 *  Constructor that creates an empty shelf on a given plane with specified position and size
	 *  has a specific offset in x- and y- dim and also sets if this subshelf is rotated or not
	 *
	 *  @param	plane 				the index of the plane this shelf is placed on
	 *  @param  height 				height of the shelf
	 *  @param  width 				width of the plane
	 *  @param  offset_x 			offset in x-dimension of this shelf
	 *  @param  offset_y 			offset in y-dimension of this shelf
	 *  x @param  is_rotated 			for sub-shelfs: if true, x and y dimensions within shelf have to be swapped for placing actual forms on plane
	 */
	BinPackingShelf(int plane, float width, float height, float offset_x, float offset_y);

	/*!
	 *  Adds a form on this shelf. Also checks if there is enough space on this shelf
	 *  
	 *  @param f 			Pointer to the form that should be added to this shelf
	 *  @param index 		index of Form
	 *
	 *  @return 			a float >=0 if the form could be added to the shelf.
	 *						the float describes the height of the free space below the newly added form
	 * 						returns -1 if the form could not be added
	 */
	float add_form(AbstractForm *f, int index);

	/*!
	 *  Checks if a form could be placed on this sheld
	 *
	 *  @param f 		Pointer to the form that should be checked
	 *  
	 *  @return 		true if there is enough space for f on this shelf, false otherwise
	 */
	bool check_if_fit(AbstractForm *f);

	/*!
	 *  Getter for x-offset of shelf on plane:
	 */
	float get_offset_x();

	/*!
	 *  Getter for x-offset of shelf on plane:
	 */
	float get_offset_y();

	/*!
	 *  Getter for height of shelf
	 */
	float get_height();
	
	/*!
	 *	Getter for width of shelf
	 */
	float get_width();

	/*!
	 *  Getter for remaining width of shelf
	 */
	float get_remaining_width();

	/*!
	 *  Get the index of the plane this shelf is placed on
	 */
	int get_plane();

	/**
	 *  Get number of forms on this shelf
	 */
	int get_number_of_forms_on_shelf();

	/*!
	 *  Get index of AbstractForm of ith form on shelf, i.e. a getter for an int in vector<int> indices_of_forms
	 *
	 *  @param index_of_form 	the position of the form on this shelf, i.e. the index in vector<int> indices_of_forms
	 *
	 *  @return 				the index of the abstractform at the vector of all abstract forms at an instance of the class problem
	 */
	int get_abstract_index_of_form_at(int index_of_form);
};


#endif