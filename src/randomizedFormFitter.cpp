#include "RandomizedFormFitter.hpp"

#include "point.hpp"
#include <ctype.h>

#pragma mark - Constructor

/**
 *  Constructor that initialized the form fitter with the two forms to be fit
 *
 *  @param firstForm    The first form to be put together with the second one.
 *  @param secondForm   The second form to be put together with the first one.
 */
RandomizedFormFitter::RandomizedFormFitter(AbstractForm *first_form, AbstractForm *second_form)
{
    this->first_form = first_form;
    this->second_form = second_form;
}

#pragma mark - Randomization

/*!
 *  Randomly moves the second form from the first and rotates both
 *  to try and find a configuration that minimizes the size of the bounding
 *  box containing both forms, without the forms overlapping.
 *
 *  @param tries                 The number of tries that are used to find a good fit.
 *  @param efficiency_threshhold If a gived degree of efficiency is reached, stop the search.
 *  @param offset_step_size      How much the second form is set off at least.
 *  @param x_offset              The variable to hold the optimal x-offset.
 *  @param y_offset              The variable to hold the optimal y-offset.
 *  @param first_rotation        The variable to hold the optimal rotation of the first form in degrees.
 *  @param second_rotation       The variable to hold the optimal rotation of the second form in degrees.
 *  @return true, if the target efficiency was reached. false, if the number of tries was reached without achieving the wanted efficiency.
 */
bool RandomizedFormFitter::calculcate_best_offset_from_first_to_second_form(unsigned int tries,
                                                                            float efficiency_threshhold,
                                                                            float offset_step_size,
                                                                            float &x_offset,
                                                                            float &y_offset,
                                                                            int &first_rotation,
                                                                            int &second_rotation)
{
    srand (time(NULL));
    
    float best_fitness = numeric_limits<float>::max();
    x_offset = 0.0;
    y_offset = 0.0;
    first_rotation = 0;
    second_rotation = 0;
    
    for (unsigned int try_count = 0; try_count < tries; try_count++)
    {
        unsigned int first_rotation_angle = rand() % 360;
        unsigned int positive_negative_flag_horizontal = rand() % 2;
        unsigned int horizontal_offset = rand() % 100;
        unsigned int positive_negative_flag_vertical = rand() % 2;
        unsigned int vertical_offset = rand() % 100;
        unsigned int second_rotation_angle = rand() % 360;
        
        int horizontal_offset_sign = positive_negative_flag_horizontal > 0 ? -1 : 1;
        int vertical_offset_sign = positive_negative_flag_vertical > 0 ? -1 : 1;
        
        Form first_form = Form(this->first_form);
        Form second_form = Form(this->second_form);
        
        Point first_form_centroid = first_form.get_centroid();
        
        first_form.rotate(first_form_centroid.get_x(),
                          first_form_centroid.get_y(),
                          (float)first_rotation_angle);
        
        float current_offset_x = (float)horizontal_offset_sign * (float)horizontal_offset * (float)offset_step_size;
        float current_offset_y = (float)vertical_offset_sign * (float)vertical_offset * (float)offset_step_size;
        
        second_form.move_rel(current_offset_x,
                             current_offset_y);
        
        Point second_form_centroid = second_form.get_centroid();
        
        second_form.rotate(second_form_centroid.get_x(),
                           second_form_centroid.get_y(),
                           (float)second_rotation_angle);
        
        /**
         *  Create an abstract form containing all points of the two forms and
         *  calculate its convex hull.
         */
        
        float bounding_x_min = (first_form.get_bounding_xmin() < second_form.get_bounding_xmin()) ? first_form.get_bounding_xmin() : second_form.get_bounding_xmin();
        float bounding_x_max = (first_form.get_bounding_xmax() > second_form.get_bounding_xmax()) ? first_form.get_bounding_xmax() : second_form.get_bounding_xmax();
        float bounding_y_min = (first_form.get_bounding_ymin() < second_form.get_bounding_ymin()) ? first_form.get_bounding_ymin() : second_form.get_bounding_ymin();
        float bounding_y_max = (first_form.get_bounding_ymax() > second_form.get_bounding_ymax()) ? first_form.get_bounding_ymax() : second_form.get_bounding_ymax();
        
        float bounding_box_size = (fabs(bounding_x_max - bounding_x_min) * fabs(bounding_y_max - bounding_y_min));
        
        /**
         *  Calculate the area of each form and add them up
         */
        
        float size_of_first_form = first_form.get_mother()->get_size_of_area();
        float size_of_second_form = second_form.get_mother()->get_size_of_area();
        
        float combined_area = size_of_first_form + size_of_second_form;
        
        /**
         *  The fitness is the ratio of bounding box size to convex hull size.
         *  If this ratio is small, then the bounding box has nearly the same size
         *  as the convex hull and the fitness will be close to 1.0.
         */
        float fitness = bounding_box_size / combined_area;
        
        /**
         *  Overlappings are punsihed by doubling the score. Since the score is
         *  better the lower it is.
         */
        if (first_form.check_for_overlap(&second_form)) // TODO: Maybe make punishment depending on the crossings?
        {
            fitness *= 100;
        }
        
        if (fitness < best_fitness)
        {
            best_fitness = fitness;
            x_offset = current_offset_x;
            y_offset = current_offset_y;
            first_rotation = first_rotation_angle;
            second_rotation = second_rotation_angle;
        }
        
        if (best_fitness < efficiency_threshhold)
        {
            return true;
        }
    }
    
    return false;
}
