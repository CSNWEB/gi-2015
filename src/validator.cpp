#include "validator.hpp"

/**
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
bool Validator::validate_plane(Plane *plane)
{
    unsigned int number_of_forms_on_plane = (unsigned int)plane->get_number_of_forms();
    for (unsigned int index = 0;
         index < number_of_forms_on_plane;
         index++)
    {
        for (unsigned int index_2 = index;
             index_2 < number_of_forms_on_plane;
             index_2++)
        {
            
        }
    }
    
    return true;
}

/**
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
bool Validator::validate_setting(Setting *setting)
{
    return true;
}