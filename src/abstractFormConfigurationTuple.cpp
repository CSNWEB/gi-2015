#include "abstractFormConfigurationTuple.hpp"

AbstractFormConfigurationTuple::AbstractFormConfigurationTuple(AbstractFormConfiguration form_config)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	abstract_form_configs = vector<AbstractFormConfiguration>(1, form_config);

	dx = form_config.get_dx();
	dy = form_config.get_dy();

	used_area = form_config.get_used_area();
	utilization = used_area / (dx*dy);

	number_of_usages = -1;
}

AbstractFormConfigurationTuple::AbstractFormConfigurationTuple(vector<AbstractFormConfiguration> form_config_vector)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	abstract_form_configs = form_config_vector;

	if (abstract_form_configs.size() > 0)
	{
		float x_min = abstract_form_configs[0].get_x();
		float x_max = x_min + abstract_form_configs[0].get_dx();
		float y_min = abstract_form_configs[0].get_y();
		float y_max = y_min + abstract_form_configs[0].get_dy();

		used_area = abstract_form_configs[0].get_used_area();

		for (int index_of_form=1; index_of_form < abstract_form_configs.size(); ++index_of_form)
		{
			float x_min_t = abstract_form_configs[index_of_form].get_x();
			float x_max_t = x_min_t + abstract_form_configs[index_of_form].get_dx();
			float y_min_t = abstract_form_configs[index_of_form].get_y();
			float y_max_t = y_min_t + abstract_form_configs[index_of_form].get_dy();

			if (x_min_t < x_min)
				x_min = x_min_t;
			if (x_max_t > x_max)
				x_max = x_max_t;
			if (y_min_t < y_min)
				y_min = y_min_t;
			if (y_max_t > y_max)
				y_max = y_max_t;

			used_area += abstract_form_configs[index_of_form].get_used_area();
		}
		dx = x_max - x_min;
		dy = y_max - y_min;

		utilization = used_area / (dx*dy);
	}
	else
	{
		dx = 0;
		dy = 0;
		used_area = 0;
		utilization = 0;
	}

	number_of_usages = -1;
}

/*
void AbstractFormConfigurationTuple::compute_optimal_configuration()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	FormCombiner fc(this);
	if (!fc.compute_optimal_configuration())
	{
		#ifdef DEBUG
			printf("Computation of optimal configuration failed!\n");
		#endif
	}
}
*/

void AbstractFormConfigurationTuple::update_bounding_box()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif
		
	if (abstract_form_configs.size() > 0)
	{
		float x_min = abstract_form_configs[0].get_x();
		float x_max = x_min + abstract_form_configs[0].get_dx();
		float y_min = abstract_form_configs[0].get_y();
		float y_max = y_min + abstract_form_configs[0].get_dy();

		for (int index_of_form=1; index_of_form < abstract_form_configs.size(); ++index_of_form)
		{
			float x_min_t = abstract_form_configs[index_of_form].get_x();
			float x_max_t = x_min_t + abstract_form_configs[index_of_form].get_dx();
			float y_min_t = abstract_form_configs[index_of_form].get_y();
			float y_max_t = y_min_t + abstract_form_configs[index_of_form].get_dy();

			if (x_min_t < x_min)
				x_min = x_min_t;
			if (x_max_t > x_max)
				x_max = x_max_t;
		}	
	}
}

void AbstractFormConfigurationTuple::set_number_of_usages(int number)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	number_of_usages = number;
}

bool AbstractFormConfigurationTuple::contains_form(int id_of_form)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	for (int i=0; i<abstract_form_configs.size(); ++i)
	{
		if (abstract_form_configs[i].get_id_of_form() == id_of_form)
			return true;
	}

	return false;
}

AbstractFormConfiguration *AbstractFormConfigurationTuple::get_configuration_of_form(int index_of_form)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (index_of_form < abstract_form_configs.size())
	{
		return &abstract_form_configs[index_of_form];
	}	
	else
	{
		#ifdef DEBUG
			printf("ERROR: specified form not contained in AbstractFormConfigurationTuple");
		#endif

		return NULL;
	}
}