/*!
 *  Class RandomizedFormFitter
 *
 *  The RandomizedFormFitter tries to place two forms side by side, such that the 
 *  ratio between the bounding box that contains the two forms and the convex
 *  hull that contains both forms is as small as possible.
 *
 *  A good vertical and horizontal offset of the second form from the first one,
 *  as well as the rotation of the form is then determined using genetic
 *  evolution.
 *
 *  The RandomizedFormFitter introduces hyperparameters to tweak its performance.
 */

#ifndef GENETIC_FITTING_H
#define GENETIC_FITTING_H

#include <algorithm>
#include <iomanip>
#include <limits>
//#include <random>
#include <sstream>
#include <time.h>
#include <vector>

#include "abstractForm.hpp"
#include "form.hpp"

class AbstractForm;
class Form;

class RandomizedFormFitter
{
private:

    /*!
     *  The first of the two forms that we try to put together
     */
    AbstractForm *first_form;

    /*!
     *  The second of the two forms that we try to put together
     */
    AbstractForm *second_form;
    
    
    /*!
     *  The step size that is used when determining the best offset between the
     *  two forms in vertical and horizontal direction.
     *
     *  The smaller the step size, the more accurate is the calculated offset.
     *  However, a smaller offset could mean that more generations would be
     *  necessary to create a satisfying result.
     */
    float offset_step_size;
    
public:
    
#pragma mark - Constructor
    
    /*!
     *  Constructor that initialized the form fitter with the two forms to be fit
     *
     *  @param firstForm    The first form to be put together with the second one.
     *  @param secondForm   The second form to be put together with the first one.
     */
    RandomizedFormFitter(AbstractForm *first_form, AbstractForm *second_form);

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
    bool calculcate_best_offset_from_first_to_second_form(unsigned int tries,
                                                          float efficiency_threshhold,
                                                          float offset_step_size,
                                                          float &x_offset,
                                                          float &y_offset,
                                                          int &first_rotation,
                                                          int &second_rotation);

#pragma mark - Output
    
    /*!
     * Print the form points to a svg Polygon
     */
//   void print_form_to_svg(svg::Document * doc, int x_offset, int y_offset, int scale);
};

#endif
