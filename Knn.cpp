#include "CsvFunctions.h"
#include <algorithm> 

class Knn {
private:
	int k_numbers;
	int metric;
	int targetColumn;
	vector<vector<double>> trainData;
	vector<vector<double>> learningData;
public:
	Knn(int k = 1, int m = 1) {
		k_numbers = k;
		metric = m;
		targetColumn = 0;
	}

	void setMetric(int number) {
		metric = number;
	}

	void setK(int k) {
		k_numbers = k;
	}

	void loadData(string file, int targetColumnNumber, int trainingPercent = 30) {
		targetColumn = targetColumnNumber;
		vector<vector<double>> data = readFromCsvWithoutLabels(file);
		std::random_shuffle(data.begin(), data.end());
		for (int i = 0; i < data.size(); ++i) {
			for (int j = 0; j < data[i].size(); ++j) {
				cout << data[i][j] << ", ";
			}
			cout << endl;
		}
		int startIndex = (trainingPercent / 100.0) * data.size();
		vector<vector<double>> trainData(data.end() - startIndex, data.begin() + data.size());
		data.erase(data.end() - startIndex, data.begin() + data.size());
		learningData = data;
	}

	double predict(vector<double> features) {

	}

	double validate() {

	}

	double euclideanDistance() {

	}
};



int main() {
	Knn* knn = new Knn(2,3);
	knn->loadData("heart.csv", 14, 30);
	delete knn;
}