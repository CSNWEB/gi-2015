#include "inputHandler.hpp"
#include "problem.hpp"
#include "plane.hpp"
#include "form.hpp"

#include <stdio.h>

int main()
{
	InputHandler ih;

	ih.get_input();
	ih._d_print_input();

	//ih._d_paint_input();

	Problem problem = ih.create_problem();

	printf("\nCreate_initial_setting...\n\n");

	problem.create_initial_setting();

	printf("Current setting:\n");

	for (int i=0; i<problem.get_number_of_planes(); ++i)
	{
		Plane p = problem.get_plane_at(i);
		printf("Plane %i\n",i+1);
		for (int j=0; j<p.get_number_of_forms(); ++j)
		{
			printf("Form %i\n",j+1);
			Form f = p.get_form_at(j);
			f._d_print_form_to_console();
		}
		printf("\n");
	}

	return 0;
}