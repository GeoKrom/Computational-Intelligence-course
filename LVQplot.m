clc;
clear all;

% Plot file for LVQ Algorithm
% using txt files as input

% Training set 
fileID = fopen('trainingset2.txt');
cell_data = textscan(fileID,'%n %n');
fclose(fileID);

% Centroids with their first position
fID = fopen('centroids_ask3_before.txt');
cell_data_centroids = textscan(fID, '%n %n');
fclose(fID);

% Centroids after the excecution of the algorithm
FILEID = fopen('centroids_ask3_after.txt');
cell_data_centroids_after = textscan(fID, '%n %n');
fclose(FILEID);

matrix_data = [cell_data{:}];
matrix_centroids = [cell_data_centroids{:}];
matrix_centroids_after = [cell_data_centroids_after{:}];

% First plot
figure(1);
plot(matrix_data(:,1),matrix_data(:,2),'r*'); 
hold on;
plot(matrix_centroids(:,1), matrix_centroids(:,2), 'kx', 'MarkerSize', 10, 'LineWidth', 3);
hold off;
xlabel('x1', 'fontsize', 16);
ylabel('x2', 'fontsize', 16);
legend('Data x', 'Centroids', 'Location', 'northwest');
title 'LVQ Algorithm';

% Second Plot
figure(2);
plot(matrix_data(:,1),matrix_data(:,2),'r*'); 
hold on;
plot(matrix_centroids_after(:,1), matrix_centroids_after(:,2), 'kx', 'MarkerSize', 10, 'LineWidth', 3);
hold off;
xlabel('x1', 'fontsize', 16);
ylabel('x2', 'fontsize', 16);
legend('Data x', 'Centroids', 'Location', 'northwest');
title 'LVQ Algorithm';