#include "inputHandler.hpp"
#include "outputHandler.hpp"
#include "problem.hpp"
#include "plane.hpp"
#include "form.hpp"
#include "geneticFormFitter.hpp"

#include <stdio.h>

int main(int argc, char* argv[])
{
	
#ifdef DEBUG
	cout << "Starging... (Debugging is enabled!)" << endl;
#endif

    if (argc == 1)
    {
        printf("missing filename of input file!\n");
        return 0;
    }

	InputHandler ih;

	ih.get_input(argv[1]);
	ih._d_print_input();
        
	//ih._d_paint_input();

	Problem problem = ih.create_problem();

	problem.create_initial_setting();

    OutputHandler oh(&problem);

    oh.write_setting_to_txt();
    oh.write_setting_to_svg();

    #ifdef DEBUG
        for (int i=0; i<problem.get_number_of_planes(); ++i)
        {
            Plane p = problem.get_plane_at(i);

            for (int j=0; j<p.get_number_of_forms(); ++j)
            {
                Form f = p.get_form_at(j);

                f._d_print_form_to_console();
                f._d_print_convex_hull_to_console();
            }
        }
    #endif

    /*

    unsigned int planes = problem.get_number_of_planes();
    int factor = 100;
    int spacing = 20;
    int planeWidth =  floor(problem.get_plane_width() * factor);
    int planeHeight = floor(problem.get_plane_height() * factor);
      
    svg::Dimensions dimensions((planeWidth + spacing) * planes, planeHeight + spacing);
    svg::Document doc("./output.svg", svg::Layout(dimensions, svg::Layout::TopLeft));

	for (int i=0; i<planes; ++i)
	{
        #ifdef DEBUG
            printf("Plane %i\n",i+1);
        #endif

		Plane p = problem.get_plane_at(i);
        doc << svg::Rectangle(svg::Point(i*(planeWidth+spacing)+(spacing/2), (spacing/2)), planeWidth, planeHeight, svg::Color::White);
		
		for (int j=0; j<p.get_number_of_forms(); ++j)
		{
			Form f = p.get_form_at(j);

            #ifdef DEBUG
                printf("Form %i\n",j+1);
                printf("The size of the form is: %f\n", f.get_mother()->get_size_of_area());
            #endif

			f._d_print_form_to_console();
			f._d_print_convex_hull_to_console();
            f.print_convex_hull_to_svg(&doc, i*(planeWidth+spacing)+(spacing/2), (spacing/2), factor);
            f.print_form_to_svg(&doc, i*(planeWidth+spacing)+(spacing/2), (spacing/2), factor);
            
		}
        #ifdef DEBUG
    		printf("\n");
        #endif
	}
    */
    

/*
#ifdef DEBUG
	// Testing the GeneticFormFitter
    if (problem.get_number_of_planes() > 1)
    {
        Plane first_plane = problem.get_plane_at(0);
        Plane second_plane = problem.get_plane_at(1);
        if (first_plane.get_number_of_forms() > 0 &&
            second_plane.get_number_of_forms() > 0)
        {
            AbstractForm *first_form = first_plane.get_form_at(0).get_mother();
            AbstractForm *second_form = second_plane.get_form_at(1).get_mother();
            
            GeneticFormFitter geneticFormFitter = GeneticFormFitter(first_form, second_form);
            geneticFormFitter.calculcate_best_offset_from_first_to_second_form(500, // Population Size
                                                                               0.5, // Mutation Probability
                                                                               0.5, // Prefer fitter genes
                                                                               0.2, // Probability to mutate a single element of the genestring
                                                                               1000,// Maximum number of generations
                                                                               1.1, // Fitness threshhold
                                                                               1.0);// TODO: This should be chosen depending of the form!
        }      
    }        
#endif
*/
    
    //doc.save();

	return 0;
}