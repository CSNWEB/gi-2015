#include "validator.hpp"

#include <map>

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
bool Validator::is_plane_valid(Plane *plane)
{
    #ifdef DEBUG
        printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
    #endif
    
    float plane_width = plane->get_dx();
    float plane_height = plane->get_dy();
    
    unsigned int number_of_forms_on_plane = (unsigned int)plane->get_number_of_forms();
    for (unsigned int index = 0;
         index < number_of_forms_on_plane;
         index++)
    {
        Form *first_form = plane->get_form_at(index);
        
        // Check whether the form fits on the plane.
        if (first_form->get_bounding_xmin() < 0.0 ||
            first_form->get_bounding_ymin() < 0.0 ||
            first_form->get_bounding_xmax() > plane_width ||
            first_form->get_bounding_ymax() > plane_height)
        {
            #ifdef DEBUG
                printf("ERROR: The form at index (%d) is exceeding the bounds of the plane!", index);
            #endif
            
            // If a form is exceeding the plane's bounds, the plane is not valid!
            return false;
        }
        
        for (unsigned int index_2 = index + 1;
             index_2 < number_of_forms_on_plane;
             index_2++)
        {
            Form *second_form = plane->get_form_at(index_2);
            
            bool forms_are_overlapping = first_form->check_for_overlap(second_form);
            
            if (forms_are_overlapping)
            {
                #ifdef DEBUG
                    printf("ERROR: The forms at indices (%d) and (%d) are overlapping!", index, index_2);
                #endif
                
                // If two forms are overlapping, the plane is not valid!
                return false;
            }
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
bool Validator::is_setting_valid(Setting *setting)
{
    #ifdef DEBUG
        printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
    #endif
    
    Problem *problem = setting->get_problem();
    
    /**
     *  Keep track of the number of forms of each abstract form that are placed
     *  on the planes.
     */
    std::map<string, unsigned int>found_forms;
    
    for (unsigned int index = 0;
         index < problem->get_number_of_different_forms();
         index++)
    {
        AbstractForm *abstract_form = problem->get_abstract_form_at_position(index);
        found_forms.insert(std::pair<string, unsigned int>(abstract_form->get_name(), 0));
    }
    
    unsigned int number_of_planes = setting->get_number_of_planes();
    for (unsigned int index = 0;
         index < number_of_planes;
         index++)
    {
        Plane *plane = setting->get_plane_at(index);
        
        // Check if the plane is valid.
        #ifdef DEBUG
            printf("Checking validity of plane at index (%d).", index);
        #endif
        
        if (!Validator::is_plane_valid(plane))
        {
            #ifdef DEBUG
                printf("ERROR: Plane at index (%d) is not valid!", index);
            #endif
            
            // If the plane is not valid, the setting can't be either.
            return false;
        }
        
        // Collect the number of forms of each type that are placed on the plane.
        unsigned int number_of_forms_on_plane = (unsigned int)plane->get_number_of_forms();
        for (unsigned int form_index = 0;
             form_index < number_of_forms_on_plane;
             form_index++)
        {
            Form *form = plane->get_form_at(form_index);
            AbstractForm *mother = form->get_mother();
            
            if (found_forms.count(mother->get_name()) == 0)
            {
                // There is a form on the plane that is not part of the problem!
                #ifdef DEBUG
                    printf("ERROR: The form at index (%d) on plane with index (%d) is not part of the problem!", form_index, index);
                #endif
                
                return false;
            }
            else
            {
                found_forms[mother->get_name()] += 1;
            }
        }
    }
    
    #ifdef DEBUG
        printf("Checking whether the number of found forms matches the required number!", form_index, index);
    #endif
    for (unsigned int index = 0;
         index < problem->get_number_of_different_forms();
         index++)
    {
        AbstractForm *abstract_form = problem->get_abstract_form_at_position(index);
        std::string name_of_form = abstract_form->get_name();
        unsigned int required_number_of_forms = problem->get_number_of_form_needed(index);
        unsigned int found_number_of_forms = found_forms[name_of_form];
        
        #ifdef DEBUG
            printf("%s: required: %d - found: %d", required_number_of_forms, found_number_of_forms);
        #endif
        
        if (required_number_of_forms != found_number_of_forms)
        {
            // There is a form on the plane that is not part of the problem!
            #ifdef DEBUG
                printf("ERROR: The required number of forms (%d) of type %s does not match the found number of forms (%d)!", required_number_of_forms, found_number_of_forms, name_of_form);
            #endif
            
            return false;
        }
    }
    
    return true;
}