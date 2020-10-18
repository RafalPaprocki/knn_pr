#include "CsvFunctions.h"
#include <algorithm> 

class Knn {
private:
	int k_numbers;
	int metric;
	int targetColumn;
public:
	vector<vector<double>> trainData;
	vector<vector<double>> learningData;
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
		targetColumn = targetColumnNumber - 1;
		vector<vector<double>> data = readFromCsvWithoutLabels(file);
		std::random_shuffle(data.begin(), data.end());
		for (int i = 0; i < data.size(); ++i) {
			for (int j = 0; j < data[i].size(); ++j) {
				cout << data[i][j] << ", ";
			}
			cout << endl;
		}
		int startIndex = (trainingPercent / 100.0) * data.size();
		vector<vector<double>> train(data.end() - startIndex, data.begin() + data.size());
		data.erase(data.end() - startIndex, data.begin() + data.size());
		learningData = data;
		trainData = train;
	}

	int predict(vector<double> features) {
		vector<pair<double, int>> distancesAndLabels = {};
		for (int i = 0; i < learningData.size(); ++i) {
			double dist;
			if (metric == 0) {
				dist = euclideanDistance(learningData[i], features);
			}
			int ff = (int)learningData[i][targetColumn];
			distancesAndLabels.push_back({ dist, ff });
		}

		sort(distancesAndLabels.begin(), distancesAndLabels.end());
		vector<int> nearestResults = {0, 0};
		for (int i = 0; i < k_numbers; ++i) {
			nearestResults[(int)distancesAndLabels[i].second]++;
		}
		if (nearestResults[0] > nearestResults[1]) {
			return 0;
		}
		else {
			return 1;
		}
	}

	double checkAccuracy() {
		int good = 0;
		int bad = 0;
		for (int i = 0; i < trainData.size(); ++i) {
			int predictedTarget = predict(trainData[i]);
			if (predictedTarget == trainData[i][targetColumn]) {
				++good;
			}
			else {
				++bad;
			}
		}

		return good / (double)(good + bad);
	}

	double euclideanDistance(vector<double> learning, vector<double> target) {
		vector<double> distanceSquares = {};
		double euclideanDistance = 0;
		for (int i = 0; i < learning.size(); ++i) {
			if (i != targetColumn) {
				double diff = learning[i] - target[i];
				distanceSquares.push_back(diff * diff);
			}
		}

		for (int i = 0; i < distanceSquares.size(); ++i) {
			euclideanDistance += distanceSquares[i];
		}

		euclideanDistance = sqrt(euclideanDistance);
		return euclideanDistance;
	}
};


int main(int argc, char* argv[]) {
	for (int i = 0; i < argc; ++i) {
		cout << argv[i] << endl;
	}

	int a = stoi(argv[1]);
	string s = argv[2];
	cout << s;
	/*
	Knn* knn = new Knn(7,0);
	knn->loadData("output.csv", 14, 30);
	double accuracy = knn->checkAccuracy();
	cout << endl << accuracy;
	delete knn;
	*/
}