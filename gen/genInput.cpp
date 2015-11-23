/* 
 * File:   genInput.cpp
 * Author: Christoph
 *
 * Created on 22. November 2015, 15:10
 */

#include <cstdlib>
#include <ctime> 
#include <iostream>
#include <cassert> 
#include <cmath>
#include <fstream>

#define PI 3.14159265


using namespace std;

  
int random(int lowerbounds, int upperbounds) 
{ 
   assert(upperbounds - lowerbounds < RAND_MAX); 
   return lowerbounds + std::rand() % (upperbounds - lowerbounds + 1); 
} 

/*
 * Generates valid problem inputs for Testing
 * 
 * 
 */
int main(int argc, char** argv) {
    
    //Iinitialize rand()
    std::srand(static_cast<int>(std::time(NULL)));
    
    //Set variables for generating forms, may be replaced with random values or
    //Commandline input
    unsigned int min_plane_x = 3;
    unsigned int max_plane_x = 20;
    unsigned int min_plane_y = 3;
    unsigned int max_plane_y = 20;
    unsigned int anz_forms = 8;
    unsigned int min_per_form = 1;
    unsigned int max_per_form = 1;
    unsigned int max_points = 10;
    unsigned int min_points = 3;
            
    
    ofstream file;
    file.open ("problem.txt");
    
    int plane_x = random(min_plane_x, max_plane_x);
    int plane_y = random(min_plane_x, max_plane_y);
    
    file << plane_x + 20  << endl << plane_y + 20 << endl << anz_forms << endl;

    
    //Specifies the maxiumum distance between the first point and all other points
    //unsigned int max_dist = min(plane_x, plane_y) / 2;
    unsigned int max_dist = 5;
    
    
    for(int i = 1; i <= anz_forms; i++){
        
        int anz_points = random(min_points, max_points);
        int anz_this_form = random(min_per_form, max_per_form);
        cout << "Generating form " << i << " with " << anz_points  << " points. Used " << anz_this_form << " times" << endl;
        
        // Write form data to file
        file << "Form" << i << endl << anz_this_form << endl << anz_points << endl;
        
        // Initalize angle
        int angle = 0;
                
        //The first Point is always 0 0;
        cout << "10 10" << endl;
        file << "10 10" << endl;
        --anz_points;
        
        for( int h = 1; h <= anz_points; h++){
            int left_angle = 270 - angle; 
            
            //Make sure that there is enough angles left for the rest of the points
            int max_angle = (left_angle-4) * 0.7;
            angle += random(1,max_angle);
            
            int dist = random(1, max_dist);
            double x = cos(angle*PI/180) * dist;
            double y = sin(angle*PI/180) * dist;
            cout << x + 10 << " " << y +10 << " " << angle << " " << dist << " " << endl;
            file << x  + 10 << " " << y+10 << endl;
        }        
        cout << endl << endl;
    }
    
    file.close();
  
    return 0;
}

