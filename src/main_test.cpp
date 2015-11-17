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

	Problem problem = ih.create_problem();

	problem.create_initial_setting();
	
	//Solver s(&problem);

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

	return 0;
}
