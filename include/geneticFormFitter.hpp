/**
 *  Class GeneticFormFitter
 *
 *  The GeneticFormFitter tries to place two forms side by side, such that the 
 *  ratio between the bounding box that contains the two forms and the convex
 *  hull that contains both forms is as small as possible.
 *
 *  A good vertical and horizontal offset of the second form from the first one,
 *  as well as the rotation of the form is then determined using genetic
 *  evolution.
 *
 *  The GeneticFormFitter introduces hyperparameters to tweak its performance.
 */
#ifndef GENETIC_FITTING_H
#define GENETIC_FITTING_H

#include <algorithm>
#include <iomanip>
#include <limits>
#include <random>
#include <sstream>
#include <time.h>
#include <vector>

#include "abstractForm.hpp"
#include "form.hpp"

class AbstractForm;
class Form;

using namespace std;

struct Chromosome
{
    string gene_string;
    float fitness;
};

class GeneticFormFitter
{
private:

    /**
     *  The first of the two forms that we try to put together
     */
    AbstractForm *first_form;

    /**
     *  The second of the two forms that we try to put together
     */
    AbstractForm *second_form;

#pragma mark - Fitness
    
    /**
     *  Returns the fitness of the passed gene string.
     *
     *  @param chromosome The gene string whose fitness is to be determined.
     *
     *  @return A float representing the fitness of the gene string.
     */
    void calculate_fitness_of_chromosome(Chromosome &chromosome);
    
    /**
     *  Calculates the fitness of the population, storing the fitness value in
     *  each gene string
     */
    void calculate_fitness_of_population();
    
    /**
     *  Finds the fittest string in the population. I.e. the one with lowest
     *  fitness score.
     *
     *  @return The Chromosome representing the fittest gene in the population.
     */
    Chromosome get_fittest_chromosome_from_population();
    
#pragma mark - Mutation
    
    /**
     *  Traverses all gene strings in the population and mutates them
     */
    void mutate_population();
    
    /**
     *  Mutates the passed gene string.
     *
     *  @param gene_string The gene string to be mutated.
     */
    void mutate_chromosome(Chromosome &chromosome);
    
#pragma mark - Population
    
    /**
     *  A vector containing all gene strigns that this population contains
     */
    vector<Chromosome> population;
    
    /**
     *  Creates a random Chromosome.
     *
     *  @return A random Chromosome with fitness FLOAT_MAX.
     */
    Chromosome create_random_chromosome();
    
    /**
    *  Gets the offset and rotation represented by the gene string of a
    *  chromosome.
    *
    *  @param chromosome       The chromosome containing the gene string.
    *  @param x_offset         The variable to store the horizontal offset in.
    *  @param y_offset         The variable to store the vertical offset in.
    *  @param first_rotation   The variable to store the rotation of the first form in.
    *  @param second_rotation  The variable to store the rotation of the second form in.
    */
    void get_offset_rotation_from_chromosome(Chromosome chromosome,
                                             float &x_offset,
                                             float &y_offset,
                                             float &first_rotation,
                                             float &second_rotation);
    
    /**
     *  Given a gene string the forms that the string represents are passed to
     *  referenced variables.
     *
     *  @param gene_string The gene string that represents the relative position between two forms.
     *  @param first_form  The first form at the position the gene string defines.
     *  @param second_form The second form at the position the gene string defines.
     */
    void get_forms_from_chromosome(Chromosome chromosome,
                                   Form &first_form,
                                   Form &second_form);
    
    /**
     *  Creates a population of random Gene_Strings.
     *
     *  @param size The size of the population to generate
     */
    void create_random_population(unsigned int size);
    
    /**
     *  Shuffles the population such that not always the same two genes are
     *  paired.
     */
    void shuffle_population();
    
    /**
     *  Breeds the population by creating offspring from two chromosomes
     *  and replacing the weaker of the parents with the offspring.
     */
    void breed_population();
    
#pragma mark - Hyperparameters
    
    /**
     *  How likely is a chromosome mutated.
     */
    float mutation_probability;
    
    /**
     *  How likely it is that a when breeding two chromosomes the gene is taken
     *  from the fitter chromosome.
     */
    float fitter_preference_probability;
    
    /**
     *  When actually mutating a string how likely is a specfic character mutated.
     */
    float gene_string_mutation_propability;
    
    /**
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
    
    /**
     *  Constructor that initialized the form fitter with the two forms to be fit
     *
     *  @param firstForm    The first form to be put together with the second one.
     *  @param secondForm   The second form to be put together with the first one.
     */
    GeneticFormFitter(AbstractForm *first_form, AbstractForm *second_form);

#pragma mark - Evolution
    
    /**
     *  Calculates the best offset between the first and the second form using 
     *  genetic evolution.
     *  The fitness of an offset is determined by the ratio between the size of
     *  bounding box that contains both forms and the size of the area of their
     *  convex hull. The smaller this value, the better. Overlappings will
     *  increase the fitness value, making it worse.
     *
     *  @param population_size                    The number of offset values that make up the population. This number should be even. If it's not, 1 will be added.
     *  @param mutation_probability               A float determining how likely a chromosome is mutated. (0.0 < mutation_probability < 1.0)
     *  @param fitter_preference_probability      When a chromosome is breeding with another, this probability determines how likely it is to choose the gene from the fitter chromosome.
     *  @param gene_string_mutation_propability   When a chromosome is being mutated, this probability determines how likely it is to actually mutate a specific character in the chromosome.
     *  @param maximum_generations                The number of generations that the evolution should use
     *  @param fitness_threshhold                 A fitness threshhold. If a given fitness e.g. 1.1 is reached, the evolution is stopped.
     *  @param offset_step_size                   The step size that is used when determining the best offset between the two forms in vertical and horizontal direction.
     */
    void calculcate_best_offset_from_first_to_second_form(unsigned int population_size,
                                                          float mutation_probability,
                                                          float fitter_preference_probability,
                                                          float gene_string_mutation_propability,
                                                          unsigned int maximum_generations,
                                                          float fitness_threshhold,
                                                          float offset_step_size);

    /**
     *  Get the best relative position from the second form to the first one.
     *
     *  @param x_offset           The variable in which the best horizontal offset from the first to the second form is to be stored
     *  @param y_offset           The variable in which the best vertical offset from the first to the second form is to be stored
     *  @param first_rotation     The variable in which the best rotation of the first form is to be stored in degrees.
     *  @param second_rotation    The variable in which the best rotation of the second form is to be stored in degrees.
     */
    void get_best_offset_and_rotation(float &x_offset,
                                      float &y_offset,
                                      float &first_rotation,
                                      float &second_rotation);

#pragma mark - Output
    
    /**
     * Print the form points to a svg Polygon
     */
//   void print_form_to_svg(svg::Document * doc, int x_offset, int y_offset, int scale);
};

#endif
