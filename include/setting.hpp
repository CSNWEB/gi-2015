/*!
 *  Class Setting
 *
 *  A setting describes a number of planes with forms placed on them.
 *  A setting can be a valid solution, an intermediate step while computing a optimized solution.
 *  A setting may also not be a valid solution (because forms overlap or not all needed forms are placed on planes).
 */
#ifndef SETTING_H
#define SETTING_H

#include <vector>

#include "problem.hpp"
#include "plane.hpp"

class Setting
{
private:
    /*!
     *  A pointer to the problem this setting is based on.
     *  To acess the size of the planes and the forms.
     */ 
	Problem * const problem;

    /*!
     *  A vector of all planes used in this setting
     */
	vector<Plane> planes;

    /*!
     *  A vector of the amount of missing pieces of each form
     */
    vector<int> missing_forms; 

public:
    /*!
     *  Default Constructor.
     */
    //Setting(){};

    /*!
     *  Constructor that initializes the problem.
     */
	Setting(Problem *p);

    /*!
     *  Copy-consructor
     */
    Setting(const Setting &original);

    /*!
     *  Returns number_of_planes
     */
    int get_number_of_planes();

    /*!
     *  Get a specific Plane
     *
     *  @param i 	The number of the plane to be return
     *
     *  @return 	the Plane at planes[i]
     */
    Plane* get_plane_at(int i);
    
    /*!
     *  Returns the problem that the setting was created for.
     *
     *  @return A Problem to which this Setting might be a solution.
     */
    Problem *get_problem();

    /*!
     *  Adds a new, empty plane to the setting
     */
    void add_plane();

    /*!
     *  Adds a form to a plane at a specific position
     *
     *  @param form                 A pointer to the AbstractForm that should be added.
     *  @param index_of_plane       The index of the plane to which the new form should be added.
     *  @param position_x           The x-position of the new form.
     *  @param position_y           The y-position of the new form.
     *  @param rot                  The rotation in degree of the new form.
     *  @param mirror               A bool describing if the form is mirrored
     */
    bool add_form_to_plane_at_position(
        AbstractForm *form,
        int index_of_plane,
        float position_x,
        float position_y,
        float rot,
        bool mirror
        );

    /*!
     *  Compute the total efficiency (i.e. utilization) of the current setting
     *
     *  @return     the utilitation as percentage within [0,1]
     */
    float get_total_utilization();

    /*!
     *  Get the number of missing pieces of a specific form
     *
     *  @param form_index   the index of the form
     *
     *  @return             the number of pieces that still have to be added for form at form_index
     */
    int get_number_of_missing_pieces_of_form(int form_index);

    /*!
     *  Function to create an initial legal setting
     *  places every form on its own sheet
     */
    void create_initial_setting();
};

#endif