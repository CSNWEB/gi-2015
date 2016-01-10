#include "tests.hpp"

#pragma mark - All

/**
 *  Performs all tests.
 *
 *  @return True, if all tests are successful, false if at least one test fails.
 */
bool Tests::test_everything()
{
    std::cout << "Testing everthing:" << std::endl;

    if (!test_edge_cross())
    {
        return false;
    }

    if (!test_form_overlap())
    {
        return false;
    }

    if (!test_validator())
    {
        return false;
    }

    if (!test_bin_packing())
    {
        return false;
    }

    if (!test_point_set_algo())
    {
        return false;
    }
    
    std::cout << "All tests: [SUCCEEDED]" << std::endl;
    return true;
}

#pragma mark - Edges

/**
 *  Tests whether the function detects edges that actually cross each other correctly.
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_crossing_edges()
{
    Point top_left = Point(0.0, 1.0);
    Point top_right = Point(1.0, 1.0);
    Point bottom_left = Point(0.0, 0.0);
    Point bottom_right = Point(1.0, 0.0);

    Edge top_left_to_bottom_right = Edge(&top_left, &bottom_right);
    Edge top_right_to_bottom_left = Edge(&top_right, &bottom_left);

    /**
     *  Both edges cross each other. We check whether the method recognizes
     *  this independently on which one is the receiver.
     *
     *  The test passes if both times the cross is recognized.
     */
    if (top_left_to_bottom_right.check_if_crosses(&top_right_to_bottom_left) &&
        top_right_to_bottom_left.check_if_crosses(&top_left_to_bottom_right))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 *  Tests whether the function detects that edges do not cross each other correctly.
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_parallel_edges()
{
    Point top_left = Point(0.0, 1.0);
    Point top_right = Point(1.0, 1.0);
    Point bottom_left = Point(0.0, 0.0);
    Point bottom_right = Point(1.0, 0.0);

    Edge top_left_to_top_right = Edge(&top_left, &top_right);
    Edge bottom_left_to_bottom_right = Edge(&bottom_left, &bottom_right);

    /**
     *  Both edges are parallel to each other. We check whether the method
     *  recognizes this independently of which one is the receiver.
     *
     *  The test passes if both times it is detected that they don't cross.
     */
    if (!top_left_to_top_right.check_if_crosses(&bottom_left_to_bottom_right) &&
        !bottom_left_to_bottom_right.check_if_crosses(&top_left_to_top_right))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 *  Tests whether the function detects that two edges with the same start and endpoint
 *  do not cross.
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_edges_same_points()
{
    Point top_left = Point(1.0, 0.0);
    Point top_right = Point(1.0, 1.0);

    Edge top_left_to_top_right_1 = Edge(&top_left, &top_right);
    Edge top_left_to_top_right_2 = Edge(&top_left, &top_right);

    /**
     *  Both edges have the same start and endpoint. We check whether the method
     *  recognizes that they're not crossing each other independently of which
     *  one is the receiver.
     *
     *  The test passes if both times it is detected that they don't cross.
     */
    if (!top_left_to_top_right_1.check_if_crosses(&top_left_to_top_right_2) &&
        !top_left_to_top_right_2.check_if_crosses(&top_left_to_top_right_1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 *  Tests whether the function detects edges that share an endpoint correctly.
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_meeting_edges()
{
    Point top_left = Point(0.0, 1.0);
    Point top_right = Point(1.0, 1.0);
    Point bottom_left = Point(0.0, 0.0);

    Edge top_left_to_top_right = Edge(&top_left, &top_right);
    Edge bottom_left_to_top_left = Edge(&bottom_left, &top_left);

    /**
     *  Both edges share one point. We check whether the method recognizes
     *  that they don't cross independently on which one is the receiver.
     *
     *  The test passes if both times it is detected that they don't cross.
     */
    if (!top_left_to_top_right.check_if_crosses(&bottom_left_to_top_left) &&
        !bottom_left_to_top_left.check_if_crosses(&top_left_to_top_right))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 *  Tests whether methods dealing with edge crosses work as intended.
 *
 *  @return True, if all tests are successful, false if at least one test fails.
 */
bool Tests::test_edge_cross()
{
    std::cout << "Testing edge cross: " << std::endl;

    // Crossing edges

    std::cout << "Testing crossing edges: ";
    if (test_crossing_edges())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }

    // Parallel edges

    std::cout << "Testing parallel edges: ";
    if (test_parallel_edges())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }

    // Edges with same points

    std::cout << "Testing edges with same points: ";
    if (test_edges_same_points())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }

    // Meeting edges

    std::cout << "Testing meeting edges: ";
    if (test_meeting_edges())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }

    std::cout << "All edge tests: [SUCCEEDED]" << std::endl;
    return true;
}

#pragma mark - Forms

/**
 *  Test whether two completely disjoint are recognized as not overlapping.
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_overlap_disjoint()
{
    // A square of length one. One corner is at the origin.
    std::vector<Point> square_points {
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(1.0, 1.0),
        Point(1.0, 0.0)
    };

    AbstractForm square = AbstractForm("square", square_points);

    Form first_square = Form(&square);
    Form second_square = Form(&square);

    // Move the second square by 2.0 on the x-axis.
    second_square.move_rel(2.0, 0.0);

    // The squares should not be overlapping now.
    if (!first_square.check_for_overlap(&second_square) &&
        !second_square.check_for_overlap(&first_square))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 *  Test whether two forms that are at the same vertical but not the same
 *  horizontal position that overlap are recognized as overlapping.
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_overlap_disjoint_parallel()
{
    // A square of length one. One corner is at the origin.
    std::vector<Point> square_points {
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(1.0, 1.0),
        Point(1.0, 0.0)
    };

    AbstractForm square = AbstractForm("square", square_points);

    Form first_square = Form(&square);
    Form second_square = Form(&square);

    // Move the second square by 0.5 on the x-axis.
    second_square.move_rel(0.5, 0.0);

    // The squares should be overlapping now.
    if (first_square.check_for_overlap(&second_square) &&
        second_square.check_for_overlap(&first_square))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 *  Test whether two forms that are not at the same vertical and not the
 *  same horizontal position that overlap are recognized as overlapping.
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_overlap_disjoint_non_parallel()
{
    // A square of length one. One corner is at the origin.
    std::vector<Point> square_points {
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(1.0, 1.0),
        Point(1.0, 0.0)
    };

    AbstractForm square = AbstractForm("square", square_points);

    Form first_square = Form(&square);
    Form second_square = Form(&square);

    // Move the second square by 0.5 on the x-axis and on the y-axis.
    second_square.move_rel(0.5, 0.5);

    // The squares should be overlapping now.
    if (first_square.check_for_overlap(&second_square) &&
        second_square.check_for_overlap(&first_square))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 *  Test whether two forms that have one common point but otherwise don't
 *  overlap are recognized as not overlapping.
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_overlap_sharing_point()
{
    // A square of length one. One corner is at the origin.
    std::vector<Point> square_points {
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(1.0, 1.0),
        Point(1.0, 0.0)
    };

    AbstractForm square = AbstractForm("square", square_points);

    Form first_square = Form(&square);
    Form second_square = Form(&square);

    // Move the second square by 0.5 on the x-axis and on the y-axis.
    second_square.move_rel(1.0, 1.0);

    // The squares should be overlapping now.
    if (!first_square.check_for_overlap(&second_square) &&
        !second_square.check_for_overlap(&first_square))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 *  One form is concave and the other convex. The convex one is placed
 *  Within the bounding box of the concave one. They do not overlap.
 *  The test checks whether the function recognizes this.
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_overlap_concave()
{
    // A square of length one. One corner is at the origin.
    std::vector<Point> square_points {
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(1.0, 1.0),
        Point(1.0, 0.0)
    };

    AbstractForm square = AbstractForm("square", square_points);

    // A "bucket" where the square fits in

    std::vector<Point> bucket_points {
        Point(0.0, 0.0),
        Point(0.0, 3.0),
        Point(1.0, 3.0),
        Point(1.0, 1.0),
        Point(4.0, 1.0),
        Point(4.0, 3.0),
        Point(5.0, 3.0),
        Point(5.0, 0.0)
    };

    AbstractForm bucket = AbstractForm("bucket", bucket_points);

    Form square_form = Form(&square);
    Form bucket_form = Form(&bucket);

    // Move the second square by 2.0 on the x-axis and 2.0 on the y-axis.
    bucket_form.move_rel(2.0, 2.0);

    // The square should now be within the bucket, but not overlapping.
    if (!square_form.check_for_overlap(&bucket_form) &&
        !bucket_form.check_for_overlap(&square_form))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 *  Two triangles pointing towards each other and overlapping. The test
 *  checks whether the function recognizes this.
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_overlap_triangle()
{
    // A triangle pointing to the right.
    std::vector<Point> triangle_right_points {
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(0.5, 0.5),
    };
    
    AbstractForm triangle_right = AbstractForm("triangle_right", triangle_right_points);
    
    // A triangle pointing to the left.
    
    std::vector<Point> triangle_left_points {
        Point(0.0, 0.5),
        Point(0.5, 1.0),
        Point(0.5, 0.0),
    };
    
    AbstractForm triangle_left = AbstractForm("triangle_left", triangle_left_points);
    
    Form triangle_right_form = Form(&triangle_right);
    Form triangle_left_form = Form(&triangle_left);
    
    // The triangles are overlapping now.
    if (triangle_right_form.check_for_overlap(&triangle_left_form) &&
        triangle_left_form.check_for_overlap(&triangle_right_form))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 *  Two triangles pointing towards each other but not overlapping. The test
 *  checks whether the function recognizes this.
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_non_overlap_triangle()
{
    // A triangle pointing to the right
    std::vector<Point> triangle_right_points {
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(0.5, 0.5),
    };
    
    AbstractForm triangle_right = AbstractForm("triangle_right", triangle_right_points);
    
    // A triangle pointing to the left
    
    std::vector<Point> triangle_left_points {
        Point(0.0, 0.5),
        Point(0.5, 1.0),
        Point(0.5, 0.0),
    };
    
    AbstractForm triangle_left = AbstractForm("triangle_left", triangle_left_points);
    
    Form triangle_right_form = Form(&triangle_right);
    Form triangle_left_form = Form(&triangle_left);
    
    // Move the triangle so that is doesn't overlap with the other one.
    triangle_left_form.move_rel(0.5, 0.0);
    
    // The triangles should not be not overlapping.
    if (!triangle_right_form.check_for_overlap(&triangle_left_form) &&
        !triangle_left_form.check_for_overlap(&triangle_right_form))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 *  Tests whether methods dealing with edge crosses work as intended.
 *
 *  @return True, if all tests are successful, false if at least one test fails.
 */
bool Tests::test_form_overlap()
{
    std::cout << "Testing form overlap: " << std::endl;

    // Disjoint forms

    std::cout << "Testing disjoint forms overlapping: ";
    if (test_overlap_disjoint())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }

    // Parallel disjoint forms

    std::cout << "Testing disjoint forms parallel overlapping: ";
    if (test_overlap_disjoint_parallel())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }

    // Non parallel disjoint forms

    std::cout << "Testing disjoint forms non parallel overlapping: ";
    if (test_overlap_disjoint_non_parallel())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }

    // Forms sharing a point

    std::cout << "Testing forms sharing a point overlapping: ";
    if (test_overlap_sharing_point())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }

    // Concave

    std::cout << "Testing forms concave overlapping: ";
    if (test_overlap_concave())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }
    
    // Triangle overlapping
    
    std::cout << "Testing forms triangle overlapping: ";
    if (test_overlap_triangle())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }
    
    // Triangle not overlapping
    
    std::cout << "Testing forms triangle not overlapping: ";
    if (test_non_overlap_triangle())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }

    std::cout << "All edge tests: [SUCCEEDED]" << std::endl;
    return true;
}

#pragma mark - Validator

/**
 *  There is an empty setting but the problem specifies that a given
 *  number of forms has to be placed on planes. The test checks whether
 *  the validator recognizes this.
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_validator_empty()
{
    // A square of length one. One corner is at the origin.
    std::vector<Point> square_points {
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(1.0, 1.0),
        Point(1.0, 0.0)
    };
    
    AbstractForm square = AbstractForm("square", square_points);
    
    // The vector containing which abstract forms are used.
    std::vector<AbstractForm> abstract_forms {
        square
    };
    
    // The vector defining how many of each abstract form are needed.
    std::vector<int> number_of_forms {
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
    
    bool empty_setting_is_valid = Validator::is_setting_valid(&setting);
    
    // Add a plane but don't place any forms.
    setting.add_plane();
    
    bool empty_plane_setting_is_valid = Validator::is_setting_valid(&setting);
    
    return (!(empty_setting_is_valid ||
              empty_plane_setting_is_valid));
}

/**
 *  The required number of forms is present, but one is exceeding the bounds
 *  of a plane. The test checks whether the validator recognizes this.
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_validator_exceeding_bounds()
{
    // A square of length one. One corner is at the origin.
    std::vector<Point> square_points {
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(1.0, 1.0),
        Point(1.0, 0.0)
    };
    
    AbstractForm square = AbstractForm("square", square_points);
    
    // The vector containing which abstract forms are used.
    std::vector<AbstractForm> abstract_forms {
        square
    };
    
    // The vector defining how many of each abstract form are needed.
    std::vector<int> number_of_forms {
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
    
    /**
     *  The setting where the form will exceed the plane in the minimum
     *  x-direction.
     */
    Setting setting_minx = Setting(&problem);
    
    // Add a plane
    setting_minx.add_plane();
    
    Plane *plane_minx = setting_minx.get_plane_at(0);
    
    // Add a form out of the planes bounds.
    plane_minx->add_form_at_position(&square, -0.5, 0.0);
    
    /**
     *  Check whether the Validator recognizes if a forms exceeds the bounds
     *  of the plane.
     */
    bool exceeding_minimum_x_is_valid = Validator::is_setting_valid(&setting_minx);

    /**
     *  The setting where the form will exceed the plane in the minimum
     *  y-direction.
     */
    Setting setting_miny = Setting(&problem);
    
    // Add a plane
    setting_miny.add_plane();
    
    Plane *plane_miny = setting_miny.get_plane_at(0);
    
    // Add a form out of the planes bounds.
    plane_miny->add_form_at_position(&square, 0.0, -0.5);
    
    /**
     *  Check whether the Validator recognizes if a forms exceeds the bounds
     *  of the plane.
     */
    bool exceeding_minimum_y_is_valid = Validator::is_setting_valid(&setting_miny);
    
    /**
     *  The setting where the form will exceed the plane in the maximum
     *  x-direction.
     */
    Setting setting_maxx = Setting(&problem);
    
    // Add a plane
    setting_maxx.add_plane();
    
    Plane *plane_maxx = setting_maxx.get_plane_at(0);
    
    // Add a form out of the planes bounds.
    plane_maxx->add_form_at_position(&square, 9.5, 0.0);
    
    /**
     *  Check whether the Validator recognizes if a forms exceeds the bounds
     *  of the plane.
     */
    bool exceeding_maximum_x_is_valid = Validator::is_setting_valid(&setting_maxx);
    
    /**
     *  The setting where the form will exceed the plane in the maximum
     *  y-direction.
     */
    Setting setting_maxy = Setting(&problem);
    
    // Add a plane
    setting_maxy.add_plane();
    
    Plane *plane_maxy = setting_maxy.get_plane_at(0);
    
    // Add a form out of the planes bounds.
    plane_maxy->add_form_at_position(&square, 0.0, 9.5);
    
    /**
     *  Check whether the Validator recognizes if a forms exceeds the bounds
     *  of the plane.
     */
    bool exceeding_maximum_y_is_valid = Validator::is_setting_valid(&setting_maxy);
    
    return (!(exceeding_minimum_x_is_valid ||
              exceeding_minimum_y_is_valid ||
              exceeding_maximum_x_is_valid ||
              exceeding_maximum_y_is_valid));
}

/**
 *  There is a form, that is not specified in the problem. The test checks
 *  whether the validator recognizes this.
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_validator_unknown_form()
{
    // A square of length one. One corner is at the origin.
    std::vector<Point> square_points {
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(1.0, 1.0),
        Point(1.0, 0.0)
    };
    
    AbstractForm square = AbstractForm("square", square_points);
    
    // The vector containing which abstract forms are used.
    std::vector<AbstractForm> abstract_forms {
        square
    };
    
    // The vector defining how many of each abstract form are needed.
    std::vector<int> number_of_forms {
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
    
    // Add a form to the setting that is not specified in the problem.
    AbstractForm triangle = AbstractForm("triangle", square_points);
    
    setting.add_plane();
    Plane *plane = setting.get_plane_at(0);
    
    plane->add_form_at_position(&triangle, 0.0, 0.0);
    
    return (!Validator::is_setting_valid(&setting));
}

/**
 *  The number of forms added does not match the required number. The test
 *  checks whether the validator recognizes this.
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_validator_wrong_count()
{
    // A square of length one. One corner is at the origin.
    std::vector<Point> square_points {
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(1.0, 1.0),
        Point(1.0, 0.0)
    };
    
    AbstractForm square = AbstractForm("square", square_points);
    
    // The vector containing which abstract forms are used.
    std::vector<AbstractForm> abstract_forms {
        square
    };
    
    // The vector defining how many of each abstract form are needed.
    std::vector<int> number_of_forms {
        2
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
    
    // Add only one form to the plane although 2 are needed.
    setting.add_plane();
    Plane *plane = setting.get_plane_at(0);
    
    plane->add_form_at_position(&square, 0.0, 0.0);
    
    bool not_enough_forms_is_valid = Validator::is_setting_valid(&setting);
    
    /**
     *  Adding two more forms to test whether the validator recognizes if there
     *  are too many forms on the planes. The forms are not overlapping or 
     *  exceeding the bounds of the planes.
     */
    plane->add_form_at_position(&square, 2.0, 0.0);
    plane->add_form_at_position(&square, 4.0, 0.0);
    
    bool too_many_forms_is_valid = Validator::is_setting_valid(&setting);
    
    return (!(not_enough_forms_is_valid ||
              too_many_forms_is_valid));
}

/**
 *  The required number of forms is present and none of the forms exceed the
 *  bounds of the planes or overlap each other.
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_validator_correct()
{
    // A square of length one. One corner is at the origin.
    std::vector<Point> square_points {
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(1.0, 1.0),
        Point(1.0, 0.0)
    };
    
    AbstractForm square = AbstractForm("square", square_points);
    
    // The vector containing which abstract forms are used.
    std::vector<AbstractForm> abstract_forms {
        square
    };
    
    // The vector defining how many of each abstract form are needed.
    std::vector<int> number_of_forms {
        2
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
    
    plane->add_form_at_position(&square, 0.0, 0.0);
    plane->add_form_at_position(&square, 4.0, 0.0);
    
    return (Validator::is_setting_valid(&setting));
}

/**
 *  Tests whether the validator works as intended.
 *
 *  @return True, if all tests are successful, false if at least one test fails.
 */
bool Tests::test_validator()
{
    std::cout << "Testing validator: " << std::endl;
    
    // Empty setting
    
    std::cout << "Testing validator empty setting: ";
    if (test_validator_empty())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }
    
    // Exceeding bounds
    
    std::cout << "Testing validator exceeding bounds: ";
    if (test_validator_exceeding_bounds())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }
    
    // Unkown forms
    
    std::cout << "Testing validator unknown form: ";
    if (test_validator_unknown_form())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }
    
    // Wrong count
    
    std::cout << "Testing validator wrong count: ";
    if (test_validator_wrong_count())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }
    
    // Correct
    
    std::cout << "Testing validator correct: ";
    if (test_validator_correct())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }
    
    std::cout << "All validator tests: [SUCCEEDED]" << std::endl;
    return true;
}

#pragma mark - BinPacking

/*!
 *  Given a vector of AbstractFormConfigurationTuple with different area utilization, test if the relation operator defined in TupleComparatorUtilization orders them correct
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_sort_tuple_utilization_correct()
{
    /**
     *  General Initialization
     */
    bool success_all_tests = true;

    // create an AbstractFormConfiguration with good area utilization:
    vector<Point> pts_form_1{
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(1.0, 1.0),
        Point(1.0, 0.0)
    };
    AbstractForm form_1("form_1", pts_form_1);
    int id_1 = form_1.get_id();

    AbstractFormConfigurationTuple tuple_1(
        AbstractFormConfiguration(
            &form_1, 0, 0, 0, false));

    // create an AbstractFormConfiguration with medium area utilization:
    vector<Point> pts_form_2{
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(1.0, 0.0)
    };

    AbstractForm form_2("form_2", pts_form_2);
    int id_2 = form_2.get_id();

    AbstractFormConfigurationTuple tuple_2(
        AbstractFormConfiguration(
            &form_2, 0, 0, 0, false));

    // create an AbstractFormConfiguration with bad area utilization:
    vector<Point> pts_form_3{
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(0.1, 0.1),
        Point(1.0, 0.0)
    };

    AbstractForm form_3("form_3", pts_form_3);
    int id_3 = form_3.get_id();

    AbstractFormConfigurationTuple tuple_3(
        AbstractFormConfiguration(
            &form_3, 0, 0, 0, false));

    /**
     *  Initialization of test instances and testing:
     */

    // case: vector is sorted:
    vector<AbstractFormConfigurationTuple> afct_vector_1{
        tuple_1,
        tuple_2,
        tuple_3
    };

    TupleComparatorUtilization tcu(&afct_vector_1);

    std::sort(afct_vector_1.begin(), afct_vector_1.end(), tcu);

    if(!(
        afct_vector_1[0].get_configuration_of_form(0)->get_id_of_form() == id_1 &&
        afct_vector_1[1].get_configuration_of_form(0)->get_id_of_form() == id_2 &&
        afct_vector_1[2].get_configuration_of_form(0)->get_id_of_form() == id_3
         ) == true)
        success_all_tests = false;

    // case: vector is reverse sorted:
    vector<AbstractFormConfigurationTuple> afct_vector_2{
        tuple_3,
        tuple_2,
        tuple_1
    };

    tcu = TupleComparatorUtilization(&afct_vector_2);

    std::sort(afct_vector_2.begin(), afct_vector_2.end(), tcu);

    if(!(
        afct_vector_2[0].get_configuration_of_form(0)->get_id_of_form() == id_1 &&
        afct_vector_2[1].get_configuration_of_form(0)->get_id_of_form() == id_2 &&
        afct_vector_2[2].get_configuration_of_form(0)->get_id_of_form() == id_3
         ) == true)
        success_all_tests = false;

    // case: vector is unsorted:
    vector<AbstractFormConfigurationTuple> afct_vector_3{
        tuple_2,
        tuple_1,
        tuple_3
    };

    tcu = TupleComparatorUtilization(&afct_vector_3);

    std::sort(afct_vector_3.begin(), afct_vector_3.end(), tcu);

    if(!(
        afct_vector_3[0].get_configuration_of_form(0)->get_id_of_form() == id_1 &&
        afct_vector_3[1].get_configuration_of_form(0)->get_id_of_form() == id_2 &&
        afct_vector_3[2].get_configuration_of_form(0)->get_id_of_form() == id_3
        ) == true)
        success_all_tests = false;

    return success_all_tests;
}

/*!
 *  Given a vector of AbstractFormConfigurationTuple with different dimension, test if the relation operator defined in TupleComparatorDimension orders them correct
 *
 *  @return True if the test passes, false if not.
 */
bool Tests::test_sort_tuple_dimension_correct()
{
    /**
     *  General Initialization
     */

    bool success_all_tests = true;

    // create an AbstractFormConfiguration with large x-dim and large y_dim:
    vector<Point> pts_form_lxly{
        Point(0.0, 0.0),
        Point(0.0, 2.0),
        Point(2.0, 2.0),
        Point(2.0, 0.0)
    };
    AbstractForm form_1("form_1", pts_form_lxly);
    int id_1 = form_1.get_id();
    AbstractFormConfigurationTuple tuple_lxly(
        AbstractFormConfiguration(
            &form_1, 0, 0, 0, false));

    // create an AbstractFormConfiguration with large x-dim and small y_dim:
    vector<Point> pts_form_lxsy{
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(3.0, 1.0),
        Point(3.0, 0.0)
    };
    AbstractForm form_2("form_2", pts_form_lxsy);
    int id_2 = form_2.get_id();
    AbstractFormConfigurationTuple tuple_lxsy(
        AbstractFormConfiguration(
            &form_2, 0, 0, 0, false));

    // create an AbstractFormConfiguration with small x-dim and large y_dim:
    vector<Point> pts_form_sxly{
        Point(0.0, 0.0),
        Point(0.0, 2.0),
        Point(1.0, 2.0),
        Point(1.0, 0.0)
    };
    AbstractForm form_3("form_3", pts_form_sxly);
    int id_3 = form_3.get_id();
    AbstractFormConfigurationTuple tuple_sxly(
        AbstractFormConfiguration(
            &form_3, 0, 0, 0, false));

    // create an AbstractFormConfiguration with small x-dim and small y_dim:
    vector<Point> pts_form_sxsy{
        Point(0.0, 0.0),
        Point(0.0, 1.0),
        Point(1.0, 1.0),
        Point(1.0, 0.0)
    };
    AbstractForm form_4("form_4", pts_form_sxsy);
    int id_4 = form_4.get_id();
    AbstractFormConfigurationTuple tuple_sxsy(
        AbstractFormConfiguration(
            &form_4, 0, 0, 0, false));

    /**
     *  Initialization of test instances and testing:
     */

    // initialize an instance of TupleComparatorDimension:
    vector<AbstractFormConfigurationTuple> afct_vector{
        tuple_sxsy,
        tuple_sxly,
        tuple_lxsy,
        tuple_lxly
    };
    TupleComparatorDimension tcd(&afct_vector);

    // Case 1 - sorted:
    vector<int> case_1{
        3,2,1,0
    };

/*
    #ifdef DEBUG
        printf("Pre sorting case 1:\n");
        for (int i=0; i<4; ++i)
           printf("\tForm %i with id: %i\n\tDimension: %.2f/%.2f\n", i, afct_vector[case_1[i]].get_configuration_of_form(0)->get_id_of_form(), afct_vector[case_1[i]].get_dx(), afct_vector[case_1[i]].get_dy());
    #endif
*/

    std::sort(case_1.begin(), case_1.end(), tcd);

/*
    #ifdef DEBUG
        printf("Post sorting case 1:\n");
        for (int i=0; i<4; ++i)
            printf("\tForm %i with id: %i\n\tDimension: %.2f/%.2f\n", i, afct_vector[case_1[i]].get_configuration_of_form(0)->get_id_of_form(), afct_vector[case_1[i]].get_dx(), afct_vector[case_1[i]].get_dy());
    #endif
*/

    if(!(
        afct_vector[case_1[0]].get_configuration_of_form(0)->get_id_of_form() == id_1 &&
        afct_vector[case_1[1]].get_configuration_of_form(0)->get_id_of_form() == id_2 &&
        afct_vector[case_1[2]].get_configuration_of_form(0)->get_id_of_form() == id_3 &&
        afct_vector[case_1[3]].get_configuration_of_form(0)->get_id_of_form() == id_4
        ) == true)
        success_all_tests = false;

    // Case 2 - reverse sorted:
    vector<int> case_2{
        0,1,2,3
    };

    std::sort(case_2.begin(), case_2.end(), tcd);

    if(!(
        afct_vector[case_2[0]].get_configuration_of_form(0)->get_id_of_form() == id_1 &&
        afct_vector[case_2[1]].get_configuration_of_form(0)->get_id_of_form() == id_2 &&
        afct_vector[case_2[2]].get_configuration_of_form(0)->get_id_of_form() == id_3 &&
        afct_vector[case_2[3]].get_configuration_of_form(0)->get_id_of_form() == id_4
        ) == true)
        success_all_tests = false;

    // Case 3 - unsorted 1:
    vector<int> case_3{
        2,0,3,1
    };

    std::sort(case_3.begin(), case_3.end(), tcd);

    if(!(
        afct_vector[case_3[0]].get_configuration_of_form(0)->get_id_of_form() == id_1 &&
        afct_vector[case_3[1]].get_configuration_of_form(0)->get_id_of_form() == id_2 &&
        afct_vector[case_3[2]].get_configuration_of_form(0)->get_id_of_form() == id_3 &&
        afct_vector[case_3[3]].get_configuration_of_form(0)->get_id_of_form() == id_4
        ) == true)
        success_all_tests = false;

    // Case 4 - unsorted 2:
    vector<int> case_4{
        3,0,1,2
    };

    std::sort(case_4.begin(), case_4.end(), tcd);

    if(!(
        afct_vector[case_4[0]].get_configuration_of_form(0)->get_id_of_form() == id_1 &&
        afct_vector[case_4[1]].get_configuration_of_form(0)->get_id_of_form() == id_2 &&
        afct_vector[case_4[2]].get_configuration_of_form(0)->get_id_of_form() == id_3 &&
        afct_vector[case_4[3]].get_configuration_of_form(0)->get_id_of_form() == id_4
        ) == true)
        success_all_tests = false;

    return success_all_tests;
}

/*!
 *  Tests whether methods of the bin-packing-algorithm work as intended.
 *
 *  @return True, if all tests are successful, false if at least one test fails.
 */
bool Tests::test_bin_packing()
{

    bool success = true;
    std::cout << "Testing TupleComparatorUtilization: ";
    if (test_sort_tuple_utilization_correct())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        success = false;
        std::cout << "[FAILED]" << std::endl;
    }

    std::cout << "Testing TupleComparatorDimension: ";
    if (test_sort_tuple_dimension_correct())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        success = false;
        std::cout << "[FAILED]" << std::endl;
    }

    return success;
}

#pragma mark - PointSetAlgorithms

bool Tests::test_sort_points_by_x_dimension_correct()
{
    bool success_all_tests = true;

    // case 1: sorted
    vector<Point> points_1{
        Point(1,2),
        Point(2,2),
        Point(3,1),
        Point(4,2)
    };

    vector<int> res_1{
        0,1,2,3
    };

    PointComparator pc_1(&points_1);

    std::sort(res_1.begin(), res_1.end(), pc_1);

    if(!(
        res_1[0] == 0 &&
        res_1[1] == 1 &&
        res_1[2] == 2 &&
        res_1[3] == 3 
        ) == true)
        success_all_tests = false;

    // Case 2: reverse sorted
    vector<int> res_2{
        3,2,1,0
    };

    PointComparator pc_2(&points_1);

    std::sort(res_2.begin(), res_2.end(), pc_2);

    if(!(
        res_2[0] == 3 &&
        res_2[1] == 2 &&
        res_2[2] == 1 &&
        res_2[3] == 0 
        ) == true)
        success_all_tests = false;

    // Case 3: sorted, but with all x equal:
    vector<Point> points_3{
        Point(1,4),
        Point(1,3),
        Point(1,2),
        Point(1,1)
    };

    vector<int> res_3{
        0,1,2,3
    };

    PointComparator pc_3(&points_3);

    std::sort(res_3.begin(), res_3.end(), pc_3);

    if(!(
        res_3[0] == 0 &&
        res_3[1] == 1 &&
        res_3[2] == 2 &&
        res_3[3] == 3 
        ) == true)
        success_all_tests = false;

    // Case 4: unsorted
    vector<Point> points_4{
        Point(1,5),  // 0
        Point(5,4),  // 7
        Point(3,1),  // 5
        Point(1,1),  // 1
        Point(5,2),  // 8
        Point(2,2),  // 3
        Point(2,1),  // 4
        Point(2,3),  // 2
        Point(4,1)   // 6
    };

    vector<int> res_4{
        0,1,2,3,4,5,6,7,8
    };

    PointComparator pc_4(&points_4);

    std::sort(res_4.begin(), res_4.end(), pc_4);

    if(!(
        res_4[0] == 0 &&
        res_4[1] == 3 &&
        res_4[2] == 7 &&
        res_4[3] == 5 && 
        res_4[4] == 6 &&
        res_4[5] == 2 &&
        res_4[6] == 8 &&
        res_4[7] == 1 &&
        res_4[8] == 4
        ) == true)
        success_all_tests = false;
}

bool Tests::test_point_set_algo()
{
    std::cout << "Testing PointSetAlgorithms: " << std::endl;
    
    std::cout << "Testing sort points by x dimension: ";
    if (test_sort_points_by_x_dimension_correct())
    {
        std::cout << "[SUCCEEDED]" << std::endl;
    }
    else
    {
        std::cout << "[FAILED]" << std::endl;
        return false;
    }

}