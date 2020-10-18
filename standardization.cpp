#include "CsvFunctions.h"

double findAverage(vector<double> data);
double findDeviation(vector<double> data);
void standardize(string outFile, vector< pair<string, vector<double>> >& data);

/*
int main()
{
    vector<pair<string, vector<double>> > out;
    out = readFromCsv("heart.csv");
    standardize("standarization.csv", out);
}
*/

void standardize(string outFile, vector< pair<string, vector<double>> >& data) {
    for (int i = 0; i < data.size(); ++i) {
        if (data[i].first != "target") {
            double avg = findAverage(data[i].second);
            double deviation = findDeviation(data[i].second);
            //standaryzowanie
            for (int j = 0; j < data[i].second.size(); ++j) {
                data[i].second[j] = (data[i].second[j] - avg) / deviation;
            }
        }
    }
    // zapisywanie do pliku
    writeToCsv(outFile, data);
}

double findAverage(vector<double> data) {
    double average = accumulate(data.begin(), data.end(), 0.0) / data.size();
    return average;
}

// https://www.statisticshowto.com/probability-and-statistics/standard-deviation/#HFSSD - pattern
double findDeviation(vector<double> data) {
    double sum = accumulate(data.begin(), data.end(), 0.0);
    double square = sum * sum / data.size();
    double squareSum = 0;
    for (int i = 0; i < data.size(); ++i) {
        squareSum += data[i] * data[i];
    }
    double diff = square - squareSum;
    double variance = diff / (data.size() - 1);
    double deviation = sqrt(variance);

    return variance;
}