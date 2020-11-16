#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>
//#include <bits/stdc++.h>
#include <string.h>

using namespace std;

float examples[6000][2];
char* categories[6000];


int main(){
  ofstream myfile;
  ofstream myfile2;
  //ofstream myfile3;
  myfile.open ("trainingset.txt");
  myfile2.open ("testset.txt");
  //myfile3.open("test.txt");

  srand (static_cast <unsigned> (time(0)));
  for(int i = 0; i<6000; i++){
    float x1 = -2 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(4))));
    float x2 = -2 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(4))));
    if(i<3000){
      myfile << fixed << setprecision(6) << x1 << "\t";
      myfile << fixed << setprecision(6) << x2 << "\n";
    }else{
      myfile2 << fixed << setprecision(6) << x1 << "\t";
      myfile2 << fixed << setprecision(6) << x2 << "\n";
    }

    examples[i][0] = x1;
    examples[i][1] = x2;

    if(pow((examples[i][0] - 1),2) + pow((examples[i][1] - 1), 2) <= 0.49){
      categories[i] = "C2";
      if(i<3000){
        float noise = static_cast <float> ((rand()) / (static_cast <float> (RAND_MAX)));
        if(noise <= 0.1){
          categories[i] = "C1";
        }
      }
    }else if(pow((examples[i][0] + 1), 2) + pow((examples[i][1] + 1), 2) <= 0.49){
      categories[i] = "C2";
      //myfile3 << "c2";
      if(i<3000){
        float noise = static_cast <float> ((rand()) / (static_cast <float> (RAND_MAX)));
        if(noise <= 0.1){
          categories[i] = "C1";
        }
      }
    }else if(pow((examples[i][0] + 1), 2) + pow((examples[i][1] - 1), 2) <= 0.49){
      categories[i] = "C3";
      if(i<3000){
        float noise = static_cast <float> ((rand()) / (static_cast <float> (RAND_MAX)));
        if(noise <= 0.1){
          categories[i] = "C1";
        }
      }
    }else if(pow((examples[i][0] - 1), 2) + pow((examples[i][1] + 1), 2) <= 0.49){
      categories[i] = "C3";
      if(i<3000){
        float noise = static_cast <float> ((rand()) / (static_cast <float> (RAND_MAX)));
        if(noise <= 0.1){
          categories[i] = "C1";
        }
      }
    }else{
      categories[i] = "C1";
    }


    //myfile << x1 << "\t";
    //myfile << x2 << "\n";


    //printf("%lf\n", x1);

    //printf("%lf\n", x2);
  }
  printf("%lf, %lf\n", examples[0][0], examples[0][1]);
  printf("%lf, %lf\n", examples[3000][0], examples[3000][1]);

  myfile.close();
  myfile2.close();
  //myfile3.close();

  return (0);
}
