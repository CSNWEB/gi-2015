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
    
    bool first_check = first_square.check_for_overlap(&second_square);
    bool second_check = second_square.check_for_overlap(&first_square);
    
    // The squares should be overlapping now.
    if (first_check &&
        second_check)
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
    
    std::cout << "All edge tests: [SUCCEEDED]" << std::endl;
    return true;
}