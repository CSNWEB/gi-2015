#include "inputHandler.hpp"

#include <stdio.h>

int main()
{
	InputHandler ih;

	ih.get_input();
	ih._d_print_input();

	ih._d_paint_input();

	return 0;
}