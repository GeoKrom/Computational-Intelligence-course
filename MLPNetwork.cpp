#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <string.h>
#include <string>
using namespace std;

#define d 2
#define K 3
#define H1 3
#define H2 2
#define FUNC2 0 // 0 for hyperbolic and 1 for linear

float examples[6000][2];
char* categories[6000];
vector< vector<float>> examples_coord;
vector< vector<float>> test_coord;
vector<vector< float>> output_vector;// 1 dianusma gia kathe eksodo
vector< float> desired_output;
float output[3][3];
float HLayer1Weights[3][2];// 2 barh gia kathe neurwna . 1 gia kathe eisodo.
float HLayer1Bias[3];
float HLayer2Weights[2][3];
float HLayer2Bias[2];
float OutLayerWeights[3][2];
float OutBias[3];

float sigmoid(float x){
  float y = 1 / (1 + exp(-x));
  return y;
}
// Training Process
vector<vector<float>> forward_pass(vector<float>vect, int D, vector<vector<float>> vect2, int k){

  cout << HLayer1Weights[0][0];
  vect2.clear();
  vector<float> temp;
  temp.push_back(vect[0]);
  temp.push_back(vect[1]);
  for(int i =0; i<max(H1,H2)-D;i++){
    temp.push_back(0);
  }
  vect2.push_back(temp);
  temp.clear();
  
  //Hidden Layer 1
  //input
  float input_u1_1;
  float output_u1_1;
  for(int i =0; i< H1; i++){
    input_u1_1 = 0;
    output_u1_1 = 0;
    for (int j=0; j<d; j++){
      input_u1_1 += vect[j]*HLayer1Weights[i][j];
    }
    input_u1_1 += HLayer1Bias[i];
    output_u1_1 = sigmoid(input_u1_1);
    temp.push_back(output_u1_1);
    cout<< temp[i];
  }
  vect2.push_back(temp);
  temp.clear();


  //Hidden Layer 2
  //input
  float input_u1_2;
  float output_u1_2;
  for(int i=0; i<H2; i++){
    input_u1_2 =0;
    output_u1_2 =0;
    for(int j=0; j<H1; j++ ){
      input_u1_2 += vect2[1][j]*HLayer2Weights[i][j];
    }
    input_u1_2 += HLayer2Bias[i];
    if(FUNC2 == 0){ // Hyperbolic
      output_u1_2 = float(tanh(double(input_u1_2)));
      cout<< output_u1_2 << '\n';
    }else{ //Linear
      output_u1_2 = input_u1_2;
    }
    temp.push_back(output_u1_2);
  }
  vect2.push_back(temp);
  temp.clear();

  //Output Layer
  //input

  float input_u1_3;
  float o3;
    for(int i =0; i< k; i++){
      input_u1_3 = 0;
      o3 = 0;
      for (int j=0; j<H2; j++){
        input_u1_3 += vect2[2][j]*OutLayerWeights[i][j];
      }
      input_u1_3 += OutBias[i];
      o3 = sigmoid(input_u1_3);
      temp.push_back(o3);
    }
    for(int q =0; q<max(H1, H2)-K; q++){
        temp.push_back(0);
    }
    vect2.push_back(temp);
    temp.clear();

  return vect2;
}

int backprop(vector<vector<float>> x, int D, vector<float> t, int k){

  //Output Layer
  float delta_output_1 = (x[3][0]*(1-x[3][0])) * (x[3][0] - t[0]);
  float delta_output_2 = (x[3][1]*(1-x[3][1])) * (x[3][1] - t[1]);
  float delta_output_3 = (x[3][2]*(1-x[3][2])) * (x[3][2] - t[2]);

  //Hidden Layer 2
  float delta_hidden2_1;
  float delta_hidden2_2;
  if(FUNC2 == 0){ //Hyperbolic
    delta_hidden2_1 = (1 - float(pow(double(x[2][0]), 2))) *
                (delta_output_1 * OutLayerWeights[0][0] + delta_output_2 * OutLayerWeights[1][0] +
                        delta_output_3 * OutLayerWeights[2][0]);

    delta_hidden2_2 = (1 - float(pow(double(x[2][1]), 2))) *
                (delta_output_1 * OutLayerWeights[0][1] + delta_output_2 * OutLayerWeights[1][1] +
                        delta_output_3 * OutLayerWeights[2][1]);
  }else{ // Linear
    delta_hidden2_1 = (delta_output_1 * OutLayerWeights[0][0] + delta_output_2 * OutLayerWeights[1][0] +
                        delta_output_3 * OutLayerWeights[2][0]);

    delta_hidden2_2 = (delta_output_1 * OutLayerWeights[0][1] + delta_output_2 * OutLayerWeights[1][1] +
                        delta_output_3 * OutLayerWeights[2][1]);

  }

  // Hidden Layer 1
  float delta_hidden1_1 = (x[1][0] * (1 - x[1][0])) * (delta_hidden2_1*HLayer2Weights[0][0] + delta_hidden2_2*HLayer2Weights[1][0]);
  float delta_hidden1_2 = (x[1][1] * (1 - x[1][1])) * (delta_hidden2_1*HLayer2Weights[0][1] + delta_hidden2_2*HLayer2Weights[1][1]);
  float delta_hidden1_3 = (x[1][2] * (1 - x[1][2])) * (delta_hidden2_1*HLayer2Weights[0][2] + delta_hidden2_2*HLayer2Weights[1][2]); 
  
  //Input Layer
  float delta_input1 = delta_hidden1_1*HLayer1Weights[0][0] + delta_hidden1_2*HLayer1Weights[1][0] + delta_hidden1_3*HLayer1Weights[2][0];
  float delta_input2 = delta_hidden1_1*HLayer1Weights[0][1] + delta_hidden1_2*HLayer1Weights[1][1] + delta_hidden1_3*HLayer1Weights[2][1];
  
  vector<vector<float>> BiasDerivatives;
  vector<vector<float>> WeightsDerivatives; 

  //Output Layer
  float bias_der_o1 = delta_output_1;
  float bias_der_o2 = delta_output_2;
  float bias_der_o3 = delta_output_3;

  vector<float> temp;
  temp.push_back(bias_der_o1);
  temp.push_back(bias_der_o2);
  temp.push_back(bias_der_o3);
  BiasDerivatives.push_back(temp);
  temp.clear();

  float weigth_der_11_3 = delta_output_1 * x[2][0]; 
  float weight_der_21_3 = delta_output_2 * x[2][0];
  float weight_der_31_3 = delta_output_3 * x[2][0];
  temp.push_back(weigth_der_11_3);
  temp.push_back(weight_der_21_3);
  temp.push_back(weight_der_31_3);
  WeightsDerivatives.push_back(temp);
  temp.clear();

  float weight_der_12_3 = delta_output_1 * x[2][1];
  float weight_der_22_3 = delta_output_2 * x[2][1];
  float weight_der_32_3 = delta_output_3 * x[2][1];
  temp.push_back(weight_der_12_3);
  temp.push_back(weight_der_22_3);
  temp.push_back(weight_der_32_3);
  WeightsDerivatives.push_back(temp);
  temp.clear();

  //Hidden Layer 2

  float bias_der_h2_1 = delta_hidden2_1;
  float bias_der_h2_2 = delta_hidden2_2;

  temp.push_back(bias_der_h2_1);
  temp.push_back(bias_der_h2_2);
  temp.push_back(0);
  BiasDerivatives.push_back(temp);
  temp.clear();

  float weight_der_11_2 = delta_hidden2_1 * x[1][0];
  float weight_der_21_2 = delta_hidden2_2 * x[1][0];

  temp.push_back(weight_der_11_2);
  temp.push_back(weight_der_21_2);
  temp.push_back(0);
  WeightsDerivatives.push_back(temp);
  temp.clear();


  float weight_der_12_2 = delta_hidden2_1 * x[1][1];
  float weight_der_22_2 = delta_hidden2_2 * x[1][1];

  temp.push_back(weight_der_12_2);
  temp.push_back(weight_der_22_2);
  temp.push_back(0);
  WeightsDerivatives.push_back(temp);
  temp.clear();

  float weight_der_13_2 = delta_hidden2_1 * x[1][2];
  float weight_der_23_2 = delta_hidden2_2 * x[1][2];

  temp.push_back(weight_der_13_2);
  temp.push_back(weight_der_23_2);
  temp.push_back(0);
  WeightsDerivatives.push_back(temp);
  temp.clear();

  //Hidden Layer 1

  float bias_der_h1_1 = delta_hidden1_1;
  float bias_der_h1_2 = delta_hidden1_2;
  float bias_der_h1_3 = delta_hidden1_3;

  temp.push_back(bias_der_h1_1);
  temp.push_back(bias_der_h1_2);
  temp.push_back(bias_der_h1_3);
  BiasDerivatives.push_back(temp);
  temp.clear();

  float weigth_der_11_1 = delta_hidden1_1 * x[0][0]; 
  float weight_der_21_1 = delta_hidden1_2 * x[0][0];
  float weight_der_31_1 = delta_hidden1_3 * x[0][0];
  temp.push_back(weigth_der_11_1);
  temp.push_back(weight_der_21_1);
  temp.push_back(weight_der_31_1);
  WeightsDerivatives.push_back(temp);
  temp.clear();

  float weigth_der_12_1 = delta_hidden1_1 * x[0][1]; 
  float weight_der_22_1 = delta_hidden1_2 * x[0][1];
  float weight_der_32_1 = delta_hidden1_3 * x[0][1];
  temp.push_back(weigth_der_12_1);
  temp.push_back(weight_der_22_1);
  temp.push_back(weight_der_32_1);
  WeightsDerivatives.push_back(temp);
  temp.clear();

  
  return 1;
}


int main () {
  string line;
  ifstream myfile ("trainingset.txt");
  ifstream myfile2 ("testset.txt");
  if (myfile.is_open())
  {
    int i = 0;
    while ( getline (myfile,line) ){
      string splitter = "\t";
      examples[i][0] = std::stof (line.substr(0, line.find(splitter)));

      line.erase(0, line.find(splitter) + splitter.length());
      examples[i][1] = stof (line);
      vector<float> coord;
      coord.push_back(examples[i][0]);
      coord.push_back(examples[i][1]);
      examples_coord.push_back(coord);
      coord.clear();
      i++;
    }
    cout << examples[2999][0] << '\n';
    cout << examples_coord[2999][0] << '\n';
    myfile.close();
  }
  else cout << "Unable to open file";

  if (myfile2.is_open()){
    int i = 3000;
    while ( getline (myfile2,line) ){
      string splitter = "\t";
      examples[i][0] = stof (line.substr(0, line.find(splitter)));
      line.erase(0, line.find(splitter) + splitter.length());
      examples[i][1] = stof (line);
      vector<float> coord;
      coord.push_back(examples[i][0]);
      coord.push_back(examples[i][1]);
      test_coord.push_back(coord);
      coord.clear();
      i++;
    }
    cout << examples[5999][0] << '\n';
    cout << test_coord[2999][0] << '\n';
    myfile2.close();
  }
  else cout << "Unable to open file";

  for(int i=0; i<6000; i++){
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

  }

  //Categories Encoding
  
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      if(i==j){
        output[i][j] = 1;
      }else{
        output[i][j] = 0;
      }
      cout << output[i][j] << " ";
    }
    cout << "\n";
  }


  srand (static_cast <unsigned> (time(0)));
  for (int i=0; i<H1; i++){
    for(int j=0; j<d; j++){
      HLayer1Weights[i][j] = -2 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(4))));
    }
  }
  srand (static_cast <unsigned> (time(0)));

  for (int i=0; i < K ; i++){
    for(int j=0; j < H2; j++){
      OutLayerWeights[i][j] = -2 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(4))));
    }
  }
  srand (static_cast <unsigned> (time(0)));


  for (int i=0; i<H2; i++){
    for(int j=0; j<H1; j++){
      HLayer2Weights[i][j] = -2 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(4))));
    }
  }
  srand (static_cast <unsigned> (time(0)));

  for (int i=0; i < H1; i++){
    HLayer1Bias[i] = -2 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(4))));
  }
  srand (static_cast <unsigned> (time(0)));

  for(int i=0; i<H2; i++){
    HLayer2Bias[i] = -2 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(4))));
  }
  srand (static_cast <unsigned> (time(0)));

  for(int i=0; i<K; i++){
    OutBias[i] = -2 + static_cast <float> ((rand()) /( static_cast <float> (RAND_MAX/(4))));
  }

    // Testing Process
    output_vector = forward_pass(examples_coord[2999], d, output_vector, K);
    cout << categories[2999];
    int ti = max(H1,H2);
    for (int i=0; i<4; i++){
      for (int j=0; j<ti; j++){
        cout << output_vector[i][j] << '\n';
      }
    }

  if(categories[2999] == "C1"){
    desired_output.clear();
    desired_output.push_back(1);
    desired_output.push_back(0);
    desired_output.push_back(0);
  }else if(categories[2999] == "C2"){
    desired_output.clear();
    desired_output.push_back(0);
    desired_output.push_back(1);
    desired_output.push_back(0);
  }else if(categories[2999] == "C3"){
    desired_output.clear();
    desired_output.push_back(0);
    desired_output.push_back(0);
    desired_output.push_back(1);
  }

  cout<< '\n' << desired_output[0]<< " " << desired_output[1]<< " " << desired_output[2];


  return 0;
}
