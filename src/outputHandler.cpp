#include "outputHandler.hpp"

OutputHandler::OutputHandler(Problem *p, Setting *s)
{
	#ifdef DEBUG
		printf("CONSTRUCTOR: %s\n", __PRETTY_FUNCTION__);
	#endif
	problem = p;
	setting = s;

}

void OutputHandler::write_setting_to_txt(string filename)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	FILE *file;
    file = fopen(filename.c_str(), "w");
	fprintf(file, "%i\n", (int)(setting->get_total_utilization()*100));
	fprintf(file, "%i\n", setting->get_number_of_planes());
	for (int i=0; i<setting->get_number_of_planes(); ++i)
	{
		fprintf(file, "%i\n", i+1);
		for (int j=0; j<setting->get_plane_at(i)->get_number_of_forms(); ++j)
		{
			fprintf(file, "%s\n", ((setting->get_plane_at(i))->get_form_at(j)->get_mother())->get_name().c_str());
			vector<Point> points_of_current_form = (setting->get_plane_at(i))->get_form_at(j)->get_points();
			for (int k=0; k<points_of_current_form.size(); ++k)
				fprintf(file, "%.2f %.2f\n", points_of_current_form[k].get_x(), points_of_current_form[k].get_y());
		}
	}
	//close(file);
}

void OutputHandler::write_setting_to_svg(string filename, bool with_covex_hull)
{
	#ifdef DEBUG
		printf("FUNCTION: %s\n", __PRETTY_FUNCTION__);
	#endif

	unsigned int planes = setting->get_number_of_planes();
    int factor = 100;
    int spacing = 20;
    int planeWidth =  floor(problem->get_plane_width() * factor);
    int planeHeight = floor(problem->get_plane_height() * factor);
      
    svg::Dimensions dimensions((planeWidth + spacing) * planes, planeHeight + spacing);
    svg::Document doc(filename, svg::Layout(dimensions, svg::Layout::TopLeft));

	for (int i=0; i<planes; ++i)
	{
        #ifdef DEBUG
            printf("\tPaint plane %i\n",i+1);
        #endif

		Plane *p = setting->get_plane_at(i);
        doc << svg::Rectangle(svg::Point(i*(planeWidth+spacing)+(spacing/2), (spacing/2)), planeWidth, planeHeight, svg::Color(255,255,200));
		
		for (int j=0; j<p->get_number_of_forms(); ++j)
		{
			Form *f = p->get_form_at(j);

            #ifdef DEBUG
                printf("\tPaint form %i\n",j+1);
                printf("\t\tThe size of the form is: %f\n", f->get_mother()->get_size_of_area());
            #endif

            if (with_covex_hull)
            	f->print_convex_hull_to_svg(&doc, i*(planeWidth+spacing)+(spacing/2), (spacing/2), factor);
            f->print_form_to_svg(&doc, i*(planeWidth+spacing)+(spacing/2), (spacing/2), factor);
            
		}
        #ifdef DEBUG
    		printf("\n");
        #endif
	}

	doc.save();
}
