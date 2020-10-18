#include "CsvFunctions.h"

void normalize(string outFile, vector< pair<string, vector<double>> >& data);
double findMin(vector<double> data);
double findMax(vector<double> data);

/*
int main()
{
    vector<pair<string, vector<double>> > out;
    out = readFromCsv("heart.csv");
    normalize("output.csv", out);
}
*/

void normalize(string outFile, vector< pair<string, vector<double>> >& data) {
    for (int i = 0; i < data.size(); ++i) {
        if (data[i].first != "target") {
            double min = findMin(data[i].second);
            double max = findMax(data[i].second);
            //normalizowanie
            for (int j = 0; j < data[i].second.size(); ++j) {
                data[i].second[j] = (data[i].second[j] - min) / (max - min);
            }
        }
    }
    // zapisywanie do pliku
    writeToCsv(outFile, data);
}

double findMin(vector<double> data) {
    double min = DBL_MAX;
    for (int i = 0; i < data.size(); ++i) {
        if (data[i] < min) {
            min = data[i];
        }
    }
    return min;
}

double findMax(vector<double> data) {
    double max = DBL_MIN;
    for (int i = 0; i < data.size(); ++i) {
        if (data[i] > max) {
            max = data[i];
        }
    }
    return max;
}

