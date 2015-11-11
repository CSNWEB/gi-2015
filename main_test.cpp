
#include "inputHandler.hpp"
#include "problem.hpp"
#include "plane.hpp"
#include "form.hpp"

#include <stdio.h>


int main()
{
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
                       
			f._d_print_form_to_console();
            f.print_form_to_svg(&doc, i*(planeWidth+spacing)+(spacing/2), (spacing/2), factor);
		}
		printf("\n");
	}
                       

        doc.save();

	return 0;
}