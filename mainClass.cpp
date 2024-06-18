#include "mainClass.h"

using namespace std;
void mainClass::estabishBow()
{
	//dp.rgularizeTrainData();
	//dp.calculateTrainBOW();
	dp.establishTrainBOW(trainData);
}

void mainClass::prepareTestSet()
{
	//dp.rgularizeTestData();
	dp.estabishTestBOW(testData);
}

void mainClass::trainModel(int max_iterations, double learning_rate)
{
	//random_shuffle(trainData.begin(), trainData.end());
	//pm.mtrain(trainData, max_iterations, learning_rate);
	pm.train(trainData, max_iterations, learning_rate);
}

void mainClass::preGA()
{
	vector<bool>bestChorosome;
	ga.getBestChorosome(bestChorosome);

	for (const auto& bc : bestChorosome)cout << bc;
	cout << endl;

	int i;
	for (auto& sp : testData)
	{
		for (i = 0; i < 9829; ++i)if (!bestChorosome[i])sp.feature[i] = 0;
	}
}

void mainClass::testModel()
{
	
	preGA();

	//pm.mtestModel(testData);

	pm.testModel(testData);
}

void mainClass::runGeneticAlgorithm()
{
	ga.genetic_algorithm(pm, trainData);
}

void mainClass::setNums(int _numWords, int _numSample)
{
	dp.setNums(_numWords, _numSample);
	pm.setNums(_numWords, _numSample);
	ga.setNums(_numWords);
}

void mainClass::initialize()
{
	//dp.storeModel();
	setNums(9829, 2000);
	dp.accquireStoreModel(pm);

}
