/*!
 *  Class Tests
 *
 *  Provides methods to test several functions.
 */
#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <vector>

#include "abstractForm.hpp"
#include "binPacking.hpp"
#include "edge.hpp"
#include "form.hpp"
#include "point.hpp"
#include "problem.hpp"
#include "setting.hpp"
#include "validator.hpp"

class Tests
{
private:
    
#pragma mark - Edges (Private)
    
    /*!
     *  Tests whether the function detects edges that actually cross each other correctly.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_crossing_edges();
    
    /*!
     *  Tests whether the function detects that edges do not cross each other correctly.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_parallel_edges();
    
    /*!
     *  Tests whether the function detects that two edges with the same start and endpoint
     *  do not cross.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_edges_same_points();
    
    /*!
     *  Tests whether the function detects edges that share an endpoint correctly.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_meeting_edges();
    
#pragma mark - Forms (Private)
    
    /*!
     *  Test whether two completely disjoint are recognized as not overlapping.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_overlap_disjoint();
    
    /*!
     *  Test whether two forms that are at the same vertical but not the same
     *  horizontal position that overlap are recognized as overlapping.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_overlap_disjoint_parallel();
    
    /*!
     *  Test whether two forms that are not at the same vertical and not the 
     *  same horizontal position that overlap are recognized as overlapping.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_overlap_disjoint_non_parallel();
    
    /*!
     *  Test whether two forms that have one common point but otherwise don't
     *  overlap are recognized as not overlapping.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_overlap_sharing_point();
    
    /*!
     *  One form is concave and the other convex. The convex one is placed
     *  Within the bounding box of the concave one. They do not overlap.
     *  The test checks whether the function recognizes this.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_overlap_concave();

    /*!
     *  Two triangles pointing towards each other and overlapping. The test
     *  checks whether the function recognizes this.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_overlap_triangle();
    
    /*!
     *  Two triangles pointing towards each other but not overlapping. The test
     *  checks whether the function recognizes this.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_non_overlap_triangle();
    
#pragma mark - Validator (Private)
    
    /*!
     *  There is an empty setting but the problem specifies that a given
     *  number of forms has to be placed on planes. The test checks whether
     *  the validator recognizes this.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_validator_empty();
    
    /*!
     *  The required number of forms is present, but one is exceeding the bounds
     *  of a plane. The test checks whether the validator recognizes this.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_validator_exceeding_bounds();
    
    /*!
     *  There is a form, that is not specified in the problem. The test checks 
     *  whether the validator recognizes this.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_validator_unknown_form();
    
    /*!
     *  The number of forms added does not match the required number. The test
     *  checks whether the validator recognizes this.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_validator_wrong_count();
    
    /*!
     *  The required number of forms is present and none of the forms exceed the
     *  bounds of the planes or overlap each other.
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_validator_correct();

#pragma mark - Comparator

    /*!
     *  Given two instances of AbstractFormConfigurationTuple with different area utilization, test if the relation operator defined in TupleComparatorUtilization orders them correct
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_sort_tuple_utilization_correct();

    /*!
     *  Given two instances of AbstractFormConfigurationTuple with different dimension, test if the relation operator defined in TupleComparatorDimension orders them correct
     *
     *  @return True if the test passes, false if not.
     */
    static bool test_sort_tuple_dimension_correct();
    
public:
    
#pragma mark - All
    
    /*!
     *  Performs all tests.
     *
     *  @return True, if all tests are successful, false if at least one test fails.
     */
    static bool test_everything();
    
#pragma mark - Edges
    
    /*!
     *  Tests whether methods dealing with edge crosses work as intended.
     *
     *  @return True, if all tests are successful, false if at least one test fails.
     */
    static bool test_edge_cross();
    
#pragma mark - Forms
    
    /*!
     *  Tests whether methods dealing with form overlapping work as intended.
     *
     *  @return True, if all tests are successful, false if at least one test fails.
     */
    static bool test_form_overlap();
    
#pragma mark - Validator
    
    /*!
     *  Tests whether the validator works as intended.
     *
     *  @return True, if all tests are successful, false if at least one test fails.
     */
    static bool test_validator();

#pragma mark - BinPacking

    /*!
     *  Tests whether methods of the bin-packing-algorithm work as intended.
     *
     *  @return True, if all tests are successful, false if at least one test fails.
     */
    static bool test_bin_packing();
    
};

#endif
