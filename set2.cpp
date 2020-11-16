#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string.h>

using namespace std;

float examples[600][2];


int main(){
  ofstream myfile;
  myfile.open ("trainingset2.txt");

  for(int i=0; i<100; i++){ //A
    float x1 = -0.3 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(0.6))));
    float max_circle_radius = sqrt(0.09 - pow(x1,2));
    float x2 = -max_circle_radius + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(2*max_circle_radius))));

    myfile << fixed << setprecision(6) << x1 << "\t";
    myfile << fixed << setprecision(6) << x2 << "\n";
  }

  for(int i=0; i<100; i++){ //B
    float x1 = -1.1 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(-0.6))));
    float x2 = 0.5 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(0.6))));

    myfile << fixed << setprecision(6) << x1 << "\t";
    myfile << fixed << setprecision(6) << x2 << "\n";
  }
  for(int i=0; i<100; i++){ //G
    float x1 = -1.1 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(-0.6))));
    float x2 = -1.1 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(-0.6))));

    myfile << fixed << setprecision(6) << x1 << "\t";
    myfile << fixed << setprecision(6) << x2 << "\n";
  }
  for(int i=0; i<100; i++){ //D
    float x1 = 0.5 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(0.6))));
    float x2 = -1.1 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(-0.6))));

    myfile << fixed << setprecision(6) << x1 << "\t";
    myfile << fixed << setprecision(6) << x2 << "\n";
  }
  for(int i=0; i<100; i++){ //E
    float x1 = 0.5 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(0.6))));
    float x2 = 0.5 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(0.6))));

    myfile << fixed << setprecision(6) << x1 << "\t";
    myfile << fixed << setprecision(6) << x2 << "\n";
  }
  for(int i=0; i<100; i++){ //ST
    float x1 = -1.0 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(2.0))));
    float x2 = -1.0 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(2.0))));

    myfile << fixed << setprecision(6) << x1 << "\t";
    myfile << fixed << setprecision(6) << x2 << "\n";
  }

  myfile.close();
  return(0);

}
