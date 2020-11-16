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

#define M 7

float examples[600][2];
int clusters[600];
vector<vector<float>> centroids;
vector<vector<float>> examples_coord;
float distances[M];
vector<vector<float>> winner;
float h=0.1;
float clustering_error=0;


int main(){
    string line;
    ifstream myfile ("trainingset2.txt");
    if (myfile.is_open()){
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
        myfile.close();
    }
    else cout << "Unable to open file";

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
    outfile1.open("centroids_ask3_before.txt");
    for(int i=0; i<M; i++){
        outfile1 << fixed << setprecision(6)<< centroids[i][0] << '\t';
        outfile1 << fixed << setprecision(6) << centroids[i][1] <<'\n';
    }
    outfile1.close();

    //LVQ Algorithm
    int min;
    for(int t=0; t<5; t++){ //Number of Epochs
        for(int n=0; n<1; n++){ 
            //distances
            winner.clear();
            for(int q=0; q<M; q++){
                distances[q] = float(sqrt(pow(double(examples_coord[n][0] - centroids[q][0]),2) + 
                    pow(double(examples_coord[n][1] - centroids[q][1]),2)));
            }

            //Keep the minimum value
            min = 0;
            vector<float> temp;
            temp.push_back(centroids[min][0]);
            temp.push_back(centroids[min][1]);
            winner.push_back(temp);
            temp.clear();

            for(int q=1; q<M; q++){
                if(distances[q] < distances[min]){
                    min = q;
                    winner.clear();
                    temp.push_back(centroids[min][0]);
                    temp.push_back(centroids[min][1]);
                    winner.push_back(temp);
                    temp.clear();
                }
            }

            //Compute new min value
            centroids[min][0] = winner[0][0] + h*(examples_coord[n][0] - winner[0][0]);
            centroids[min][1] = winner[0][1] + h*(examples_coord[n][1] - winner[0][1]);
        }
        h = 0.95 * h;
    }

    ofstream outfile2;
    outfile2.open("centroids_ask3_after.txt");
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
