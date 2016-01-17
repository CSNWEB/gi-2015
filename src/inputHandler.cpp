#include "inputHandler.hpp"

#ifdef DEBUG
	#define DEBUG_IH
#endif

InputHandler::InputHandler()
{
	#ifdef DEBUG_IH
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif

	size_of_sheet_x = 0;
	size_of_sheet_y = 0;
	number_of_different_forms = 0;

	has_data = false;

}

void InputHandler::get_input(char* filename)
{
	#ifdef DEBUG_IH
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	int scanf_result;

	FILE *file;
	file = fopen(filename, "r");

	scanf_result = fscanf(file, "%f", &size_of_sheet_x);
	scanf_result = fscanf(file, "%f", &size_of_sheet_y);
	scanf_result = fscanf(file, "%i", &number_of_different_forms);

	#ifdef DEBUG_IH
		printf("Size of sheet: %.1f x %.1f\n",size_of_sheet_x, size_of_sheet_y);
		printf("Number of different forms: %i\n", number_of_different_forms);
	#endif
	
	forms			 = vector<AbstractForm>(number_of_different_forms);
	number_of_pieces = vector<int>(number_of_different_forms);
    name_of_forms = vector<string>(number_of_different_forms);

	string 	tmp_name_of_form;
	char	tmp_char_of_name;
	int 	tmp_number_of_points;
	float 	tmp_x, tmp_y;

	for (int i=0; i<number_of_different_forms; ++i)
	{
		#ifdef DEBUG_IH
			printf("Input of form %i:\n",i);
		#endif

		tmp_name_of_form = "";

		scanf_result = fscanf(file, " ");
		scanf_result = fscanf(file, "%c", &tmp_char_of_name);
		while (tmp_char_of_name >= 32)
		{
			tmp_name_of_form += tmp_char_of_name;
			scanf_result = fscanf(file, "%c", &tmp_char_of_name);
		}	
		scanf_result = fscanf(file, " ");
		scanf_result = fscanf(file, "%i", &number_of_pieces[i]);
		scanf_result = fscanf(file, "%i", &tmp_number_of_points);

		#ifdef DEBUG_IH
			printf("Name of form: %s\n", tmp_name_of_form.c_str());
			printf("Required number of pieces: %i\n", number_of_pieces[i]);
			printf("Input all points: number of points: %i\n", tmp_number_of_points);
		#endif

        name_of_forms[i] = tmp_name_of_form;

		vector<Point> points = vector<Point>(tmp_number_of_points);
		for (int j=0; j<tmp_number_of_points; ++j)
		{
			scanf_result = fscanf(file, "%f %f", &tmp_x, &tmp_y);
			points[j] = Point(tmp_x, tmp_y);

			#ifdef DEBUG_IH
				printf("Point %i at position %.1f/%.1f\n", j, tmp_x, tmp_y);
			#endif
		}
		forms[i] = AbstractForm(tmp_name_of_form, points);

		#ifdef DEBUG_IH
			printf("Input of form complete!\n\n");
		#endif
	}

	fclose(file);

	has_data = true;

	#ifdef DEBUG_IH
		printf("Input complete!\n");
	#endif
}

void InputHandler::_d_print_input()
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);

		if(has_data)
		{	
			printf("Size of sheet: %.1f x %.1f\n", size_of_sheet_x, size_of_sheet_y);
			printf("Number of different forms: %i\n", number_of_different_forms);

			for (int i=0; i<number_of_different_forms; ++i)
			{
				forms[i]._d_print_abstract_form();
			}
		}
		else
			printf("No data available!\n");
	#endif
}

Problem InputHandler::create_problem()
{
	#ifdef DEBUG_IH
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	if (has_data)
	{
		#ifdef DEBUG_IH
			printf("Return problem\n");
		#endif

	    return Problem(size_of_sheet_x, size_of_sheet_y, forms, number_of_pieces, name_of_forms);
	}
	else
	{
		printf("ERROR! No data available to create problem! Return empty problem.\n");

		return Problem(0,0,vector<AbstractForm>(0), vector<int>(0), vector<string>(0));
	}
}
