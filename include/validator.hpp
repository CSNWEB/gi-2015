/*!
 *  Class Validator
 *
 *  Validator check whether a given Setting or plane is valid.
 *
 *  For a Setting it is checked, wheter the required number of each form is
 *  placed, as well as whether forms exceed the edges of a plane or whether
 *  forms overlap each other.
 *  These are also criteria for which a validity of a plane is checked.
 */
#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <iostream>
#include <vector>

#include "form.hpp"
#include "plane.hpp"
#include "setting.hpp"
#include "globalParams.hpp"

class Validator
{
private:
    
public:
    
    /*!
     *  Checks whether a plane is valid.
     *
     *  Criteria are:
     *  - the forms on the plane do not overlap
     *  - the forms on the plane do not exceed the bounds of the plane
     *
     *  @param plane The plane whose validity is to be checked.
     *
     *  @return true if the plane is valid, false if not.
     */
    static bool is_plane_valid(Plane *plane);
    
    /*!
     * Checks whether a setting is valid.
     *
     * Criteria are:
     * - the required number of each form has been placed on the planes
     * - the forms do not exceed the bounds of the planes
     * - the forms do not overlap
     *
     * @param setting   The Setting which is checked to be valid.
     *
     * @return true, if the setting is valid. false, if not.
     */
    static bool is_setting_valid(Setting *setting);
    
};

#endif
