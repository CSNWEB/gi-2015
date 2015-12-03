#include "abstractForm.hpp"
#include "form.hpp"
#include "randomizedFormFitter.hpp"
#include "outputHandler.hpp"
#include "validator.hpp"
#include "tests.hpp"
#include <iostream>
#include <chrono>

int main(int argc, char* argv[])
{
    // A square of length one. One corner is at the origin.
    
    Tests::test_everything();
    
    std::vector<Point> triangle_points {
        Point(0.0, 1.0),
        Point(1.0, 0.0),
        Point(2.0, 0.0),
        Point(1.0, 1.0),
        Point(2.0, 2.0),
        Point(1.0, 2.0)
    };
    
    AbstractForm triangle_form = AbstractForm("triangle", triangle_points);
    AbstractForm triangle_form_2 = AbstractForm("triangle_2", triangle_points);

    // The vector containing which abstract forms are used.
    std::vector<AbstractForm> abstract_forms {
        triangle_form,
        triangle_form_2
    };
    
    // The vector defining how many of each abstract form are needed.
    std::vector<int> number_of_forms {
        1,
        1
    };
    
    // Width and height of the planes.
    float plane_width = 10.0;
    float plane_height = 10.0;
    
    // The problem that is to be solved.
    Problem problem = Problem(plane_width,
                              plane_height,
                              abstract_forms,
                              number_of_forms);
    
    // The empty setting that does not really solve the problem.
    Setting setting = Setting(&problem);
    
    /**
     *  Add as many forms to a plane as necessary and don't exceed the bounds
     *  of the plane or overlap the two forms. This should be a valid setting.
     */
    setting.add_plane();
    Plane *plane = setting.get_plane_at(0);
    
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    RandomizedFormFitter randomized_form_fitter = RandomizedFormFitter(&triangle_form,
                                                              &triangle_form_2);
    
    
    float x_offset, y_offset;
    int first_rotation, second_rotation;
    if (randomized_form_fitter.calculcate_best_offset_from_first_to_second_form(1000000,
                                                                                2.5,
                                                                                0.01,
                                                                                x_offset,
                                                                                y_offset,
                                                                                first_rotation,
                                                                                second_rotation))
    {
        std::cout << "Offset: (" << x_offset << ", " << y_offset << "), Rotation 1: " << first_rotation << "° Rotation 2: " << second_rotation << "°" << std::endl;
        
        plane->add_form_at_position_rotation(&triangle_form, 5.0, 5.0, first_rotation);
        plane->add_form_at_position_rotation(&triangle_form_2, 5.0 + x_offset, 5.0 + y_offset, second_rotation);
        
        if (Validator::is_setting_valid(&setting))
        {
            printf("Setting is valid.\n");
        }
        else
        {
            printf("Setting is NOT valid.\n");
        }
     
        std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
        std::cout << "Calculation took " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;
        
        OutputHandler oh(&problem, &setting);
        
        oh.write_setting_to_svg();
    }
    else
    {
        printf("Failed to find a fitting configuration...\n");
        std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
        std::cout << "Calculation took " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;
        
    }
    
	return 0;
}
