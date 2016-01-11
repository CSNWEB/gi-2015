#include "abstractForm.hpp"
#include "form.hpp"
#include "outputHandler.hpp"
#include "inputHandler.hpp"
#include "binPacking.hpp"
#include "tests.hpp"
#include "validator.hpp"

#include <stdio.h>

int main(int argc, char* argv[])
{

    GlobalParams::set_option_pre_merge(true);

    #ifdef DEBUG
        printf("Debugging is enabled!\n");
    #endif

        string output_filename_txt;
        string output_filename_svg;

    if (argc < 2)
    {
        printf("Missing filename of input file!\n");
        printf("Usage:\n\tsolver inputfilename.txt [outputfilename]\n");
       
        printf("Test test_everything\n");
        Tests::test_everything();
        
        return 0;
    }

    if (argc < 3)
    {
    
        printf("No output file name given.\n");
        printf("Using default output file names:\n\tout.txt, out.svg\n");
        output_filename_txt = "out.txt";
        output_filename_svg = "out.svg";
    }
    else
    {
        output_filename_txt = argv[2];
        output_filename_txt += ".txt";
        output_filename_svg = argv[2];
        output_filename_svg += ".svg";
    }

    InputHandler ih;

    ih.get_input(argv[1]);
    ih._d_print_input();

    Problem problem = ih.create_problem();

    if (!problem.is_solveable())
        printf("Error! At least one form is too big to be placed on a form.\nPROBLEM NOT SOLVEABLE!\n");
    else
    {
        BinPacking bin_packing(&problem);

        Setting bin_packed = bin_packing.get_packed_setting();

        bool is_valid = Validator::is_setting_valid(&bin_packed);

        if (is_valid)
        {
            printf("A valid setting was created.\n");
        }
        else
        {
            printf("Error! The created setting is not valid!\n");
        }

        OutputHandler oh(&problem, &bin_packed);
        oh.write_setting_to_txt(output_filename_txt);
        oh.write_setting_to_svg(output_filename_svg, true);

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

    }
	return 0;
}
