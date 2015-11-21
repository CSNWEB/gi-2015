/**
 *  Class Tests
 *
 *  Provides methods to test several functions.
 */
#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <vector>

#include "abstractForm.hpp"
#include "edge.hpp"
#include "form.hpp"
#include "point.hpp"

class Tests
{
private:
    
#pragma mark - Edges (Private)
    
    /**
     *  Tests whether the function detects edges that actually cross each other correctly.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_crossing_edges();
    
    /**
     *  Tests whether the function detects that edges do not cross each other correctly.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_parallel_edges();
    
    /**
     *  Tests whether the function detects that two edges with the same start and endpoint
     *  do not cross.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_edges_same_points();
    
    /**
     *  Tests whether the function detects edges that share an endpoint correctly.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_meeting_edges();
    
#pragma mark - Forms (Private)
    
    /**
     *  Test whether two completely disjoint are recognized as not overlapping.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_overlap_disjoint();
    
    /**
     *  Test whether two forms that are at the same vertical but not the same
     *  horizontal position that overlap are recognized as overlapping.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_overlap_disjoint_parallel();
    
    /**
     *  Test whether two forms that are not at the same vertical and not the 
     *  same horizontal position that overlap are recognized as overlapping.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_overlap_disjoint_non_parallel();
    
    /**
     *  Test whether two forms that have one common point but otherwise don't
     *  overlap are recognized as not overlapping.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_overlap_sharing_point();
    
    /**
     *  One form is concave and the other convex. The convex one is placed
     *  Within the bounding box of the concave one. They do not overlap.
     *  The test checks whether the function recognizes this.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_overlap_concave();
    
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
    
#pragma mark - Forms
    
    /**
     *  Tests whether methods dealing with form overlapping work as intended.
     *
     *  @return True, if all tests are successful, false if at least one test fails.
     */
    static bool test_form_overlap();
    
};

#endif
