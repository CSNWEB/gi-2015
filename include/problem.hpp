/**
 *  Class Problem
 *  
 *  An object of Problem describes an instance of the problem defined in the task.
 *  A problem is described by a set of AbstractForms, the corresponding numbers (describing
 *  how many of this specific form should be placed), and the size of the sheet
 *  (x and y dimension).
 *  
 *  To solve the problem, a set of planes is created onto which actual forms are placed.
 *  The class has functions to create planes and place forms on them, and to check if the
 *  setting of a plane is legal (i.e. no two forms overlap).
 */
#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>
//#include <list>

#include "abstractForm.hpp"
#include "plane.hpp"
//#include "2DBP_shelf.hpp"

using namespace std;

class Problem {
private:
    /**
     *  The size of the sheet in x-dimension
     */
    float size_of_sheet_x;

    /**
     *  The size of the sheet in y-dimension
     */
    float size_of_sheet_y;

    /**
     * The number of different forms to be handled
     */
    int number_of_different_forms;

    /**
     * All abstract forms describing the forms(shape, name)
     * needed in this problem
     */
    vector<AbstractForm> abstract_forms;

    /**
     * The number of forms needed for each abstract form
     */
    vector<int> number_of_forms_needed;

public:

    /**
     *  Default constructor
     */
    Problem() {
    };

    /**
     *  Constructor called by inputHandler
     *
     *  @param sx 				A float describing the size of the sheet in dim x
     *  @param sy 				A float describing the size of the sheet in dim y
     *  @param abst_forms 		A vector of abstract forms
     *  @param num_of_forms 	A vector of integers describing the number of forms needed (for each abstract form)
     */
    Problem(float sx, float sy, vector<AbstractForm> abst_forms, vector<int> num_of_forms);

    /**
     * Get the plane width
     * @return int      Width of one Plant
     */
    float get_plane_width();

    /**
     * Get the plane height
     * @return int      Width of one Plant
     */
    float get_plane_height();

    /**
     *  Get the number of different abstract forms
     */
    int get_number_of_different_forms();

    /**
     *  Get a specific abstract form
     *
     *  @param i    the index of the abstract form to be returned
     *
     *  @return     a pointer to the abstract form at abstract_forms[i]
     */
    AbstractForm *get_abstract_form_at_position(int i);

    /**
     *  Get the number of forms needed of abstract form [i]
     *
     *  @param i    the index of the abstract form in question
     *
     *  @return     the number of forms needed for abstract_form[i]
     */
    int get_number_of_form_needed(int i);

    /**
     *  Get the total number of all forms that have to be placed
     *
     *  @return     int: the total number of all forms
     */
    int get_total_number_of_all_forms();
    
};

#endif