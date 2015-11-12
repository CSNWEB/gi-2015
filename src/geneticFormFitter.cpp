#include "GeneticFormFitter.hpp"

#pragma mark - Constructor

/**
 *  Constructor that initialized the form fitter with the two forms to be fit
 *
 *  @param firstForm    The first form to be put together with the second one.
 *  @param secondForm   The second form to be put together with the first one.
 */
GeneticFormFitter::GeneticFormFitter(AbstractForm *first_form, AbstractForm *second_form)
{
    this->first_form = first_form;
    this->second_form = second_form;
}

#pragma mark - Fitness

/**
 *  Returns the fitness of the passed gene string.
 *
 *  @param gene_string The gene string whose fitness is to be determined.
 *
 *  @return A float representing the fitness of the gene string.
 */
void GeneticFormFitter::calculate_fitness_of_chromosome(Chromosome &chromosome)
{
    Form first_form, second_form;
    get_forms_from_chromosome(chromosome, first_form, second_form);
    
    // TODO: calculate the size of the area of the convex hull. Calculate the size of the bounding box. Get overlapping. Create fitness score.
    
    /**
     *  Create an abstract form containing all points of the two forms and
     *  calculate its convex hull.
     */
    
    vector<Point>first_form_points = first_form->points;
    vector<Point>second_form_points = second_form->points;
    
    AbstractForm combined_abstract_form = AbstractForm("combined_form",
                                                       first_form_points.insert(first_form_points.end(), second_form_points.
                                                                                begin(),
                                                                                second_form_points.end())
                                                       );
    
    // Calculate the size of the bounding box of the combined forms.
    float bounding_box_size = (combined_abstract_form.get_dx() * combined_abstract_form.get_dy());
    
    // Calculate the are of the convex hull of the combined form
    combined_abstract_form.compute_convex_hull();
    AbstractForm convex_hull_combined_form = AbstractForm("convex_hull_combined", combined_abstract_form->convex_hull);
    
    float convex_hull_size = convex_hull_combined_form->size_of_area;
    
    /**
     *  The fitness is the ratio of bounding box size to convex hull size.
     *  If this ratio is small, then the bounding box has nearly the same size 
     *  as the convex hull and the fitness will be close to 1.0.
     */
    float fitness_of_chromosome = bounding_box_size / convex_hull_size;
    
    /**
     *  Overlappings are punsihed by doubling the score. Since the score is
     *  better the lower it is.
     */
    if (first_form.check_for_overlap(second_form))
    {
        fitness_of_chromosome *= 2;
    }
    
    chromosome.fitness = fitness_of_chromosome;
}

/**
 *  Calculates the fitness of the population, storing the fitness value in
 *  each gene string
 */
void GeneticFormFitter::calculate_fitness_of_population()
{
    for (unsigned int index = 0; index < population.size(); index++)
    {
        calculate_fitness_of_chromosome(population[index]);
    }
}

/**
 *  Finds the fittest string in the population. I.e. the one with lowest
 *  fitness score.
 *
 *  @return The Chromosome representing the fittest gene in the population.
 */
Chromosome get_fittest_chromosome_from_population()
{
    Chromosome fittest_chromosome = population[0];
    for (unsigned int index = 0; index < population.size(); index++)
    {
        Chromosome challenger = population[index];
        if (challenger.fitness < fittest_chromosome.fitness)
        {
            fittest_chromosome = challenger;
        }
    }
    
    return fittest_chromosome;
}

#pragma mark - Mutation

/**
 *  Traverses all gene strings in the population and mutates them
 */
void GeneticFormFitter::mutate_population()
{
    for (unsigned int index; index < population.size(); index++)
    {
        if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) <= mutation_probability)
        {
            mutate_chromosome(population[index]);
        }
    }
}

/**
 *  Mutates the passed gene string.
 *
 *  @param gene_string The gene string to be mutated.
 */
void GeneticFormFitter::mutate_chromosome(Chromosome &chromosome)
{
    for (unsigned int index = 0; index < chromosome.gene_string.length(); index++)
    {
        // Don't mutate the indeces determining the sign. This is left for the breeding.
        if (index != 0 && index != 3)
        {
            // Determine whether we mutate this character at all.
            if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) <= gene_string_mutation_propability)
            {
                // Get the integer represented by this character.
                char number_char = chromosome.gene_string[index];
                int integer_from_char = number_char - '0';
                
                // There's a 50:50 chance that the number is either increased or decreased.
                if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) <= 0.5)
                {
                    integer_from_char++;
                }
                else
                {
                    integer_from_char--;
                }
                
                // Make sure the number is positive.
                if (integer_from_char < 0)
                {
                    integer_from_char += -1;
                }
                
                // Make sure the number has only one digit
                integer_from_char = integer_from_char % 10;
                
                chromosome.gene_string[index] = '0' + integer_from_char;
            }
        }
    }
}

#pragma mark - Population

/**
 *  Creates a random Gene_String.
 *
 *  @return A random Gene_String with fitness FLOAT_MAX.
 */
Chromosome GeneticFormFitter::create_random_chromosome()
{
    Chromosome chromosome;
    
    // The initial fitness is as bad as possible.
    chromosome.fitness = numeric_limits<float>::max();
    
    /*
     *  A gene string consists of 3 parts.
     *
     *  Part 1:
     *  A number describing how many times the second form is moved relative to
     *  the first, using the offset_step_size in horizontal direction.
     *  It consists of 3 digits. The first indicates whether the offset is
     *  positive (0) or negative (1).
     *  The remaining two digits define the number of times of offset_step_size
     *  the second form is moved relative to the first in horizontal direction.
     *
     *  Part 2:
     *  The same as Part 1, but in vertical, instead of horizontal direction.
     *
     *  Part 3:
     *  The angle that the second form is rotated by.
     */
    
    srand (time(NULL));
    
    unsigned int positive_negative_flag_horizontal = rand() % 2;
    unsigned int horizontal_offset = rand() % 100;
    
    unsigned int positive_negative_flag_vertical = rand() % 2;
    unsigned int vertical_offset = rand() % 100;
    
    unsigned int rotation_angle = rand % 360;
    
    stringstream stream;
    stream << setfill('0');
    stream << positive_negative_flag_horizontal;
    stream << setw(2) << horizontal_offset;
    stream << positive_negative_flag_vertical;
    stream << setw(2) << vertical_offset;
    stream << setw(3) << rotation_angle;
    chromosome.gene_string = stream.str();
    
    return chromosome;
}

/**
 *  Gets the offset and rotation represented by the gene string of a
 *  chromosome.
 *
 *  @param chromosome The chromosome containing the gene string.
 *  @param x_offset   The variable to store the horizontal offset in.
 *  @param y_offset   The variable to store the vertical offset in.
 *  @param rotation   The variable to store the rotation of the second form in.
 */
void GeneticFormFitter::get_offset_rotation_from_chromosome(Chromosome chromosome,
                                                            float &x_offset,
                                                            float &y_offset,
                                                            float &rotation)
{
    string positive_negative_flag_horizontal_string = chromosome.gene_string.substr(0, 1);
    string horizontal_offset_string = chromosome.gene_string.substr(1, 2);
    string positive_negative_flag_vertical_string = chromosome.gene_string.substr(3, 1);
    string vertical_offset_string = chromosome.gene_string.substr(4, 2);
    string rotation_angle_string = chromosome.gene_string.substr(6, 3);
    
    unsigned int positive_negative_flag_horizontal = stoi(positive_negative_flag_horizontal_string)
    int horizontal_offset_sign = positive_negative_flag_horizontal > 0 ? -1 : 1;
    unsigned int horizontal_offset = stoi(horizontal_offset_string);
    
    unsigned int positive_negative_flag_vertical = stoi(positive_negative_flag_vertical_string);
    int vertical_offset_sign = positive_negative_flag_vertical > 0 ? -1 : 1;
    unsigned int vertical_offset = stoi(vertical_offset_string);
    
    unsigned int rotation_angle = stoi(rotation_angle_string);
    
    x_offset = horizontal_offset_sign * horizontal_offset * this->offset_step_size;
    y_offset = vertical_offset_sign * vertical_offset * this->offset_step_size;
    rotation = rotation_angle * this->rotation_angle_size;
}

/**
 *  Given a gene string the forms that the string represents are passed to
 *  referenced variables.
 *
 *  @param gene_string The gene string that represents the relative position between two forms.
 *  @param first_form  The first form at the position the gene string defines.
 *  @param second_form The second form at the position the gene string defines.
 */
void GeneticFormFitter::get_forms_from_chromosome(Chromosome chromosome,
                                                  Form &first_form,
                                                  Form &second_form)
{
    first_form = Form(this->first_form);
    second_form = Form(this->second_form);
    
    float x_offset, y_offset, rotation;
    
    get_offset_rotation_from_chromosome(chromosome, x_offset, y_offset, rotation);
    
    second_form.move_rel(x_offset,
                         y_offset);
    
    Point second_form_centroid = second_form.get_centroid();
    
    second_form.rotate(second_form_centroid.get_x(),
                       second_form_centroid.get_y(),
                       rotation);
}

/**
 *  Creates a population of random Gene_Strings.
 *
 *  @param size The size of the population to generate
 */
void GeneticFormFitter::create_random_population(unsigned int size)
{
    this->population = vector<Chromosome>(size);
    
    for (unsigned int index = 0; index < size; index++)
    {
        this->population[index] = create_random_gene_string();
    }
}

/**
 *  Shuffles the population such that not always the same two genes are
 *  paired.
 */
void GeneticFormFitter::shuffle_population()
{
    auto engine = std::default_random_engine{};
    shuffle(std::begin(population), std::end(population), engine);
}

void GeneticFormFitter::breed_population()
{
    for (unsigned int index = 0; index < population.size(); index += 2)
    {
        unsigned int fit_index = index;
        unsigned int dead_index = index + 1;
        
        Chromosome fit_chromosome = population[fit_index];
        Chromosome dead_chromosome = population[dead_index];
        
        if (fit_chromosome.fitness > dead_index.fitness)
        {
            fit_index = index + 1;
            dead_index = index;
            
            fit_chromosome = population[fit_index];
            dead_chromosome = population[dead_index];
        }
        
        for (unsigned int character_index = 0;
             character_index < first_chromosome.gene_string.length();
             character_index++)
        {
            // Randomly choose from which string the gene is taken
            if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) <= fitter_preference_probability)
            {
                population[dead_index].gene_string[character_index] = fit_chromosome.gene_string[character_index];
            }
            else
            {
                population[dead_index].gene_string[character_index] = dead_chromosome.gene_string[character_index];
            }
        }
    }
}

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
 *  @param rotation_angle_size
 */
void GeneticFormFitter::calculcate_best_offset_from_first_to_second_form(unsigned int population_size,
                                                                         float mutation_probability,
                                                                         float fitter_preference_probability = 0.5,
                                                                         float gene_string_mutation_propability = 0.2,
                                                                         unsigned int maximum_generations,
                                                                         float fitness_threshhold,
                                                                         float offset_step_size,
                                                                         unsigned int rotation_angle_size)
{
    this->offset_step_size = offset_step_size;
    this->rotation_angle_size = rotation_angle_size;
    this->mutation_probability = mutation_probability;
    this->fitter_preference_probability = fitter_preference_probability;
    this->gene_string_mutation_propability = gene_string_mutation_propability;
    
    // Making sure the number of chromosomes in the population is even.
    (population_size % 2 == 0) ? : population_size++;
    
    create_random_population(population_size);
    
    for (unsigned int generation = 1; generation <= maximum_generations; generation++)
    {
        // Calculate fitness
        calculate_fitness_of_population();
        float fittest_gene_score = get_fittest_chromosome_from_population().fitness;

#ifdef DEBUG
        
        cout << "Generation: " << generation << " - best fitness: " << fittest_gene_score << endl;
        
#endif
        
        // Stop if the fittest gene is fit enough
        if (fittest_gene_score <= fitness_threshhold)
        {
            break;
        }
        
        // Breeding
        breed_population();
        
        // Mutation
        mutate_population();
        
        // Shuffle
        shuffle_population();
    }
}

/**
 *  Get the best relative position from the second form to the first one.
 *
 *  @param x_offset     The variable in which the best horizontal offset from the first to the second form is to be stored
 *  @param y_offset     The variable in which the best vertical offset from the first to the second form is to be stored
 *  @param rotation     THe variable in which the best rotation of the second form is to be stored.
 */
void GeneticFormFitter::get_best_offset_from_first_to_second_form(float &x_offset,
                                                                  float &y_offset,
                                                                  float &rotation)
{
    Chromosome fittest_chromosome = get_fittest_chromosome_from_population();
    
    get_offset_rotation_from_chromosome(chromosome, x_offset, y_offset, rotation);
}