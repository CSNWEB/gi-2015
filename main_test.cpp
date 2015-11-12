#include "inputHandler.hpp"
#include "problem.hpp"
#include "plane.hpp"
#include "form.hpp"
#include "geneticFormFitter.hpp"

#include <stdio.h>

int main()
{
	
#ifdef DEBUG
	cout << "Starging... (Debugging is enabled!)" << endl;
#endif
	
	InputHandler ih;

	ih.get_input();
	ih._d_print_input();
        
	//ih._d_paint_input();

	Problem problem = ih.create_problem();

	printf("\nCreate_initial_setting...\n\n");

	problem.create_initial_setting();

	printf("Current setting:\n");

        unsigned int planes = problem.get_number_of_planes();
        int factor = 100;
        int spacing = 20;
        int planeWidth =  floor(problem.get_plane_width() * factor);
        int planeHeight = floor(problem.get_plane_height() * factor);
        
        svg::Dimensions dimensions((planeWidth + spacing) * planes, planeHeight + spacing);
        svg::Document doc("./output.svg", svg::Layout(dimensions, svg::Layout::TopLeft));

	for (int i=0; i<planes; ++i)
	{
		Plane p = problem.get_plane_at(i);
        doc << svg::Rectangle(svg::Point(i*(planeWidth+spacing)+(spacing/2), (spacing/2)), planeWidth, planeHeight, svg::Color::White);
		
		printf("Plane %i\n",i+1);
		
		for (int j=0; j<p.get_number_of_forms(); ++j)
		{
			printf("Form %i\n",j+1);
			Form f = p.get_form_at(j);

#ifdef DEBUG
            printf("The size of the form is: %f\n", f.get_mother()->get_size_of_area());
#endif

			f._d_print_form_to_console();
			f._d_print_convex_hull_to_console();
            f.print_convex_hull_to_svg(&doc, i*(planeWidth+spacing)+(spacing/2), (spacing/2), factor);
            f.print_form_to_svg(&doc, i*(planeWidth+spacing)+(spacing/2), (spacing/2), factor);
            
		}
		printf("\n");
	}
    
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
    
    doc.save();

	return 0;
}