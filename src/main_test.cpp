#include "inputHandler.hpp"
#include "outputHandler.hpp"
#include "problem.hpp"
#include "plane.hpp"
#include "form.hpp"
#include "geneticFormFitter.hpp"
#include "setting.hpp"
#include "binPacking.hpp"

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

    BinPacking bin_packing(&problem);

    Setting bin_packed = bin_packing.get_packed_setting();

    
    OutputHandler oh(&problem, &bin_packed);
    oh.write_setting_to_txt();
    oh.write_setting_to_svg();

    #ifdef DEBUG
        printf("check in %s\n", __PRETTY_FUNCTION__);
        for (int i=0; i<bin_packed.get_number_of_planes(); ++i)
        {
            Plane *p = bin_packed.get_plane_at(i);
            printf("Current plane: %i\n", i);

            for (int j=0; j<p->get_number_of_forms(); ++j)
            {
                printf("Current form: %i\n", j);
                p->get_form_at(j)->_d_print_points_to_console();
                p->get_form_at(j)->_d_print_edges_to_console();
                p->get_form_at(j)->_d_print_convex_hull_to_console();
            }
        }
    #endif
    

	return 0;
}