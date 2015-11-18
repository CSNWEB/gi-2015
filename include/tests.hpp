/**
 *  Class Tests
 *
 *  Provides methods to test several functions.
 */
#ifndef TESTS_H
#define TESTS_H

#include <iostream>

#include "point.hpp"
#include "edge.hpp"

class Tests
{
private:
    
#pragma mark - Edges (Private)
    
    /**
     *  Tests whether the function detects edges that actually cross each other correctly.
     *
     *  @return True if the test passes, fals if not.
     */
    static bool test_crossing_edges();
    
    /**
     *  Tests whether the function detects that edges do not cross each other correctly.
     *
     *  @return True if the test passes, fals if not.
     */
    static bool test_parallel_edges();
    
    /**
     *  Tests whether the function detects that two edges with the same start and endpoint
     *  do not cross.
     *
     *  @return True if the test passes, fals if not.
     */
    static bool test_edges_same_points();
    
    /**
     *  Tests whether the function detects edges that share an endpoint correctly.
     *
     *  @return True if the test passes, fals if not.
     */
    static bool test_meeting_edges();
    
public:
    
#pragma mark - All
    
    /**
     *  Performs all tests.
     *
     *  @return True, if all tests are successful, false if at least one test fails.
     */
    static bool test_everything();
    
#pragma mark - Edges
    
    /**
     *  Tests whether methods dealing with edge crosses work as intended.
     *
     *  @return True, if all tests are successful, false if at least one test fails.
     */
    static bool test_edge_cross();
};

#endif
