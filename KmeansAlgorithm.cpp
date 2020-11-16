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


#define M 6
#define t 5

float examples[600][2];
int clusters[600];
float distances[M];
float clustering_error;
vector<vector<float>> centroids;
vector<vector<float>> examples_coord;

int main(){
    string line;
    ifstream myfile ("trainingset2.txt");
    if (myfile.is_open())
    {
        int i = 0;
        while ( getline (myfile,line) )
        {
            //cout << line << '\n';
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

        myfile.close();
    }
    else cout << "Unable to open file";

    //Select Random centroids
    int check = -1;
    srand (static_cast <unsigned> (time(0)));
    for (int i=0; i<M ; i++){
        int rand1 = rand() % 600;
        while(check == rand1){
            rand1 = rand() % 600;
        }
        check = rand1;
        vector<float> temp;
        temp.push_back(examples_coord[rand1][0]);
        temp.push_back(examples_coord[rand1][1]);
        centroids.push_back(temp);
        temp.clear();
    }

    ofstream outfile1;
    outfile1.open("centroids_ask2_before.txt");
    for(int i=0; i<M; i++){
        outfile1 << fixed << setprecision(6)<< centroids[i][0] << '\t';
        outfile1 << fixed << setprecision(6) << centroids[i][1] <<'\n';
    }
    outfile1.close();

    //k-means Algoritm
    int min;
    int breakcheck = 0; 
    int counter = 0; 
    float sum_x= 0;
    float sum_y =0;
    float clustering_error_sum = 0;
    float min_error = 100000;
    for (int i=0; i<t; i++){ // Epochs
        for (int j=0; j<600; j++){
            for(int q=0; q<M; q++){
                distances[q] = float(sqrt(pow(double(examples_coord[j][0] - centroids[q][0]),2) + 
                    pow(double(examples_coord[j][1] - centroids[q][1]),2)));
            }
            min = 0;
            clusters[j] = min;
            for(int q=1; q<M; q++){
                if(distances[q] < distances[min]){
                    min = q;
                    clusters[j] = min;
                }
            }
        }

        //Compute New Centroids
        for (int q=0; q<M; q++){
            counter =0;
            sum_x =0;
            sum_y =0;
            breakcheck =0;

            
            for(int j=0; j<600; j++){
                if(clusters[j] == q){
                    counter ++;
                    sum_x += examples_coord[j][0];
                    sum_y += examples_coord[j][1];
                }
            }            

            for(int p=0; p<M; p++){
                if(centroids[p][0] == sum_x/float(counter) && centroids[p][1] == sum_y/float(counter)){
                    breakcheck ++;
                    if(breakcheck == M){
                        cout<<"Breaking";
                        return 1;
                    }
                }
            }
                
            centroids[q][0] = sum_x / float(counter);
            centroids[q][1] = sum_y / float(counter);

        }
    }
    ofstream outfile2;
    outfile2.open("centroids_ask2_after.txt");
    for(int i=0; i<M; i++){
        outfile2 << fixed << setprecision(6) << centroids[i][0] << '\t';
        outfile2 << fixed << setprecision(6) << centroids[i][1] << '\n';
    }
    outfile2.close();

    float min_distance =0;
    for(int i=0; i<600; i++){
        for(int j=0; j<M; j++){
            distances[j] = float(sqrt(pow(double(examples_coord[i][0] - centroids[j][0]),2) + 
                    pow(double(examples_coord[i][1] - centroids[j][1]),2)));
        }
        min = 0;
        for(int q=1; q<M; q++){
            if(distances[q] < distances[min]){
                min = q;
                min_distance = distances[min];
            }
        }
        clustering_error += min_distance;
    }
    cout << "Clustering error is: " << clustering_error << '\n';
    return 1;
}
