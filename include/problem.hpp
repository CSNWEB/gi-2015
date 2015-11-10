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

using namespace std;

class Problem {
private:
    /*
     * Datastructure describing the input:
     */

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

    /*
     * Datastructure describing the state of the problem during solving
     * and the solution
     */

    /*
     * The number of planes currently used:
     */
    //	int number_of_planes;

    /**
     * A vector of all planes(sheets) that are generated and optimized while solving the problem
     */
    vector<Plane> planes;


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
     *  Returns number_of_planes
     */
    int get_number_of_planes() {
        return planes.size();
    };

    /**
     * Get the plane width
     * @return int      Width of one Plant
     */
    int get_plane_width() {
        return size_of_sheet_x;
    };

    /**
     * Get the plane height
     * @return int      Width of one Plant
     */
    int get_plane_height() {
        return size_of_sheet_y;
    };

    /**
     *  Get a specific Plane
     *
     *  @param i 	The number of the plane to be return
     *
     *  @return 	the Plane at planes[i]
     */
    Plane get_plane_at(int i) {
        if (i < planes.size()) return planes[i];
        else return Plane();
    };

    /**
     * Function to create an initial legal setting
     * places every form on its own sheet
     */
    void create_initial_setting();

    /**
     * Solve the problem!
     */
    void solve();

};

#endif