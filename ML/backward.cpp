#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <math.h>
#include <set>
using namespace std;

/*
compile
g++ -o data main.cpp
./data.exe
*/

// implement greedy search algorithm with the leave one out validation and NN classifer.
double return_distance(set<int> &features, vector<vector<double>> &data, int first_row, int second_row);
int nearest_neighbor(set<int> &features, vector<vector<double>> &data, int excluded_row);

void backward()
{
    string filename;
    int choice;
    cout << "1. Big dataset" << endl;
    cout << "2. Small dataset" << endl;
    cin >> choice;
    if (choice == 1)
    {
        filename = "./CS170_Spring_2023_Large_data__100.txt";
    }
    else if (choice == 2)
    {
        filename = "./CS170_Spring_2023_Small_data__100.txt";
    }
    else
    {
        cout << "Bad input, so using small test data from part 2" << endl;
        filename = "./small-test-dataset.txt";
    }
    string line;
    double val;
    ifstream fin(filename);
    vector<vector<double>> data;

    while (getline(fin, line))
    {
        stringstream ss(line);
        vector<double> row;
        while (ss >> val)
        {
            row.push_back(val);
        }
        data.push_back(row);
    }

    set<int> current_set;
    for (int i = 1; i < data[0].size(); i++)
    {
        current_set.insert(i);
    }

    set<int> global_features;
    double global_accuracy = -1;

    for (int j = 1; j < data[0].size(); j++) // Start from 1 as first column is label
    {
        set<int> best_feature;
        double best_accuracy = -1;
        double current_accuracy;
        cout << "Evaluating feature " << j << endl;
        for (int k = 1; k < data[0].size(); k++)
        {
            set<int> copy = current_set;
            int correct_count = 0;

            if (!copy.count(k))
            {
                continue;
            }

            copy.erase(k);

            for (int z = 0; z < data.size(); z++)
            {
                int nearest = nearest_neighbor(copy, data, z);
                if (data[z][0] == data[nearest][0])
                {
                    ++correct_count;
                }
            }

            current_accuracy = (double)correct_count / data.size();

            if (current_accuracy > best_accuracy)
            {
                best_accuracy = current_accuracy;
                best_feature = copy;
            }
        }
        current_set = best_feature;
        if (best_accuracy > global_accuracy)
        {
            global_accuracy = best_accuracy;
            global_features = current_set;
            cout << "New global best accuracy: " << global_accuracy << " with features: ";
            for (int feature : global_features)
                cout << feature << " ";
            cout << endl;
        }
    }
    cout << "Final global accuracy " << global_accuracy << endl;
}

double return_distance(set<int> &features, vector<vector<double>> &data, int first_row, int second_row)
{
    double sum = 0.0;
    for (set<int>::iterator it = features.begin(); it != features.end(); ++it)
    {
        sum += pow((data[first_row][*it] - data[second_row][*it]), 2);
    }
    return sqrt(sum);
}

int nearest_neighbor(set<int> &features, vector<vector<double>> &data, int excluded_row)
{
    double min_distance = 100000;
    int min_index = -1;

    for (int i = 0; i < data.size(); ++i)
    {
        if (i != excluded_row)
        {
            double distance = return_distance(features, data, i, excluded_row);
            if (distance < min_distance)
            {
                min_distance = distance;
                min_index = i;
            }
        }
    }

    return min_index;
}
