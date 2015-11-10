#include "inputHandler.hpp"

void InputHandler::get_input(bool debug)
{
	if (debug)
		printf("Begin reading input...\n");

	scanf("%f", &size_of_sheet_x);
	scanf("%f", &size_of_sheet_y);
	scanf("%i", &number_of_different_forms);
	if (debug)
	{
		printf("Size of sheet: %.1f x %.1f\n",size_of_sheet_x, size_of_sheet_y);
		printf("Number of different forms: %i\n", number_of_different_forms);
	}
	
	forms			 = vector<AbstractForm>(number_of_different_forms);
	number_of_pieces = vector<int>(number_of_different_forms);

	string 	tmp_name_of_form;
	int 	tmp_number_of_points;
	float 	tmp_x, tmp_y;

	for (int i=0; i<number_of_different_forms; ++i)
	{
		if (debug)
			printf("Input of form %i:\n",i);

		scanf(" ");
		getline(cin, tmp_name_of_form);
		scanf(" ");
		scanf("%i", &number_of_pieces[i]);
		scanf("%i", &tmp_number_of_points);

		if (debug)
		{
			printf("Name of form: %s\n", tmp_name_of_form.c_str());
			printf("Required number of pieces: %i\n", number_of_pieces[i]);
			printf("Input all points: number of points: %i\n", tmp_number_of_points);
		}

		vector<Point> points = vector<Point>(tmp_number_of_points);
		for (int j=0; j<tmp_number_of_points; ++j)
		{
			scanf("%f %f", &tmp_x, &tmp_y);
			points[j] = Point(tmp_x, tmp_y);

			if (debug)
				printf("Point %i at position %.1f/%.1f\n", j, tmp_x, tmp_y);
		}
		forms[i] = AbstractForm(tmp_name_of_form, points);

		if (debug)
			printf("Input of form complete!\n\n");
	}

	if (debug)
		printf("Input complete!\n");
}

void InputHandler::_d_print_input()
{
	printf("Size of sheet: %.1f x %.1f\n", size_of_sheet_x, size_of_sheet_y);
	printf("Number of different forms: %i\n", number_of_different_forms);
	for (int i=0; i<number_of_different_forms; ++i)
	{
		forms[i]._d_print_abstract_form();
	}
}


void InputHandler::_d_paint_input(bool debug)
{
	#ifdef USE_SFML

	int scaling = 50;

	if (debug)
		printf("Start creating shapes\n");

	vector<sf::ConvexShape> shapes = vector<sf::ConvexShape>(number_of_different_forms);
	float dx = 0;
	float dy = 0;
	for (int i=0; i<number_of_different_forms; ++i)
	{
		if(debug)
			printf("Create shape %i:\nCreate points:\n",i);

		shapes[i] = forms[i].get_shape(dx,0,scaling);

		dx += forms[i].get_dx()*scaling;
		if (forms[i].get_dy()*scaling > dy)
			dy =  forms[i].get_dy()*scaling;

		if (debug){
			printf("Total x-offset is increased to: %f\n", dx);
			printf("Total y-offset is: %f\n", dy);
		}
	}

	if(debug)
		printf("Finished creating shapes.\nCreate window next\n");

	sf::RenderWindow window(sf::VideoMode(dx, dy), "TEST");

	if (debug)
		printf("Start Displaying.\n");
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
	return Problem(size_of_sheet_x, size_of_sheet_y, forms, number_of_pieces);
}