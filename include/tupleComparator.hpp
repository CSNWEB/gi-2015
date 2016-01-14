#ifndef TUPLECOMPARATOR_H
#define TUPLECOMPARATOR_H

#include "abstractFormConfiguration.hpp"
#include "abstractFormConfigurationTuple.hpp"

#include <vector>
#include <iterator>

using namespace std;

/*!
 *  Struct TupleComparatorUtilization
 *
 *  Struct used in sorting tuples by their utilization
 */
struct TupleComparatorUtilization
{
	vector<AbstractFormConfigurationTuple> *vector_of_tuples;

	TupleComparatorUtilization(vector<AbstractFormConfigurationTuple> *v) : vector_of_tuples(v)
	{
		#ifdef DEBUG
			printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
		#endif
	}

	bool operator()(
		AbstractFormConfigurationTuple tuple_1,
		AbstractFormConfigurationTuple tuple_2
		)
	{
		#ifdef DEBUG
			printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
			//printf("Compare values %.2f and %.2f\n", tuple_1.get_utilization(), tuple_2.get_utilization());
		#endif

		bool result = tuple_1.get_utilization() - tuple_2.get_utilization() > GlobalParams::get_tolerance();
		
		return result;
	};
};

/*!
 *  Struct TupleComparatorDimension
 *
 *  Struct used in sorting tuples by their x- and y-dimension
 */
struct TupleComparatorDimension
{
	vector<AbstractFormConfigurationTuple> *vector_of_tuples;
	AbstractFormConfigurationTuple* tuple_1;
	AbstractFormConfigurationTuple* tuple_2;

	TupleComparatorDimension(vector<AbstractFormConfigurationTuple> *v) : vector_of_tuples(v)
	{
		#ifdef DEBUG
			printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
		#endif
	}

	bool operator()(int index_of_tuple_1, int index_of_tuple_2)
	{
		#ifdef DEBUG
			printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
		#endif

		float smaller_edge_box_1;
		float smaller_edge_box_2;
		float bigger_edge_box_1;
		float bigger_edge_box_2;

		if (index_of_tuple_1 > vector_of_tuples->size())
			return false;
		else if (index_of_tuple_2 > vector_of_tuples->size())
			return true;

		tuple_1 = &(*vector_of_tuples)[index_of_tuple_1];
		tuple_2 = &(*vector_of_tuples)[index_of_tuple_2];

		if (tuple_1->get_dx() < tuple_1->get_dy())
		{
			smaller_edge_box_1 = tuple_1->get_dx();
			bigger_edge_box_1  = tuple_1->get_dy();
		}
		else
		{
			smaller_edge_box_1 = tuple_1->get_dy();
			bigger_edge_box_1  = tuple_1->get_dx();
		}
		if (tuple_2->get_dx() < tuple_2->get_dy())
		{
			smaller_edge_box_2 = tuple_2->get_dx();
			bigger_edge_box_2  = tuple_2->get_dy();
		}
		else
		{
			smaller_edge_box_2 = tuple_2->get_dy();
			bigger_edge_box_2  = tuple_2->get_dx();
		}

		if (smaller_edge_box_1 - smaller_edge_box_2 > GlobalParams::get_tolerance())
			return true;
		else if (smaller_edge_box_2 - smaller_edge_box_1 > GlobalParams::get_tolerance())
			return false; 
		else return (bigger_edge_box_1 - bigger_edge_box_2 > GlobalParams::get_tolerance());
	};
};

#endif