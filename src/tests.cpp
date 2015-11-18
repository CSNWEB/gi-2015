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
    
    std::cout << "All tests: [SUCCEEDED]" << std::endl;
    return true;
}

#pragma mark - Edges

/**
 *  Tests whether the function detects edges that actually cross each other correctly.
 *
 *  @return True if the test passes, fals if not.
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
 *  @return True if the test passes, fals if not.
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
 *  @return True if the test passes, fals if not.
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
 *  @return True if the test passes, fals if not.
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

bool Tests::test_edge_cross()
{
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