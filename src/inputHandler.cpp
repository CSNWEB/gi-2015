#include "inputHandler.hpp"

void InputHandler::get_input(char* filename)
{
	#ifdef DEBUG
		printf("FUNCTION: InputHandler::get_input()\n");
	#endif

	int scanf_result;

	//ifstream file(filename);
	FILE *file;
	file = fopen(filename, "r");

	scanf_result = fscanf(file, "%f", &size_of_sheet_x);
	scanf_result = fscanf(file, "%f", &size_of_sheet_y);
	scanf_result = fscanf(file, "%i", &number_of_different_forms);

	#ifdef DEBUG
		printf("Size of sheet: %.1f x %.1f\n",size_of_sheet_x, size_of_sheet_y);
		printf("Number of different forms: %i\n", number_of_different_forms);
	#endif
	
	forms			 = vector<AbstractForm>(number_of_different_forms);
	number_of_pieces = vector<int>(number_of_different_forms);

	string 	tmp_name_of_form;
	char	tmp_char_of_name;
	int 	tmp_number_of_points;
	float 	tmp_x, tmp_y;

	for (int i=0; i<number_of_different_forms; ++i)
	{
		#ifdef DEBUG
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

		#ifdef DEBUG
			printf("Name of form: %s\n", tmp_name_of_form.c_str());
			printf("Required number of pieces: %i\n", number_of_pieces[i]);
			printf("Input all points: number of points: %i\n", tmp_number_of_points);
		#endif

		vector<Point> points = vector<Point>(tmp_number_of_points);
		for (int j=0; j<tmp_number_of_points; ++j)
		{
			scanf_result = fscanf(file, "%f %f", &tmp_x, &tmp_y);
			points[j] = Point(tmp_x, tmp_y);

			#ifdef DEBUG
				printf("Point %i at position %.1f/%.1f\n", j, tmp_x, tmp_y);
			#endif
		}
		forms[i] = AbstractForm(tmp_name_of_form, points);

		#ifdef DEBUG
			printf("Input of form complete!\n\n");
		#endif
	}

	fclose(file);

	#ifdef DEBUG
		printf("Input complete!\n");
	#endif
}

void InputHandler::_d_print_input()
{
	#ifdef DEBUG
		printf("FUNCTION: InputHandler::_d_print_input()\n");

		printf("Size of sheet: %.1f x %.1f\n", size_of_sheet_x, size_of_sheet_y);
		printf("Number of different forms: %i\n", number_of_different_forms);
	#endif
		
	for (int i=0; i<number_of_different_forms; ++i)
	{
		forms[i]._d_print_abstract_form();
	}
}


void InputHandler::_d_paint_input()
{
	#ifdef USE_SFML
	#ifdef DEBUG
		printf("FUNCTION: InputHandler::_d_paint_input()\n");
	#endif

	int scaling = 50;

	#ifdef DEBUG
		printf("Start creating shapes\n");
	#endif

	vector<sf::ConvexShape> shapes = vector<sf::ConvexShape>(number_of_different_forms);
	float dx = 0;
	float dy = 0;
	for (int i=0; i<number_of_different_forms; ++i)
	{
		#ifdef DEBUG
			printf("Create shape %i:\nCreate points:\n",i);
		#endif

		shapes[i] = forms[i].get_shape(dx,0,scaling);

		dx += forms[i].get_dx()*scaling;
		if (forms[i].get_dy()*scaling > dy)
			dy =  forms[i].get_dy()*scaling;

		#ifdef DEBUG
			printf("Total x-offset is increased to: %f\n", dx);
			printf("Total y-offset is: %f\n", dy);
		#endif
	}

	#ifdef DEBUG
		printf("Finished creating shapes.\nCreate window next\n");
	#endif

	sf::RenderWindow window(sf::VideoMode(dx, dy), "TEST");

	#ifdef DEBUG
		printf("Start Displaying.\n");
	#endif

	while(window.isOpen())
	{
		window.clear();
		for (int i=0; i<number_of_different_forms; ++i)
		{
			window.draw(shapes[i]);
		}
		window.display();
	}

	#endif
}


Problem InputHandler::create_problem()
{
	#ifdef DEBUG
		printf("FUNCTION: InputHandler::create_problem()\n");
		printf("sx: %.2f\n", size_of_sheet_x);
		printf("sy: %.2f\n", size_of_sheet_y);
	#endif

	return Problem(size_of_sheet_x, size_of_sheet_y, forms, number_of_pieces);
}