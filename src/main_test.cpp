#include "binPacking.hpp"
#include "form.hpp"
#include "geneticFormFitter.hpp"
#include "inputHandler.hpp"
#include "outputHandler.hpp"
#include "problem.hpp"
#include "plane.hpp"
#include "setting.hpp"
#include "tests.hpp"
#include "validator.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
	
    #ifdef DEBUG
        std::cout << "Starging... (Debugging is enabled!)" << std::endl;
        Tests::test_everything();
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
    
    if (Validator::is_setting_valid(&bin_packed))
    {
        printf("The settings has been validated and is correct.\n");
    }
    else
    {
        printf("ERROR: The setting could not be validated!\n");
    }
    
	return 0;
}
