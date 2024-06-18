#pragma once
#include"DataProcess.h"
#include"Perceptron.h"
#include"GeneticAlgorithm.h"
class mainClass
{
	DataProcess dp;
	Perceptron pm;
	GeneticAlgorithm ga;

	std::vector<Sample>trainData, testData;

	void setNums(int _numWords, int _numSample);
	void preGA();
public:
	mainClass() :trainData(2000, Sample()), testData(2000, Sample()),pm()
		/*,pm("D:\\作业\\智能计算\\IMDA\\storeModel\\Perceptron.txt")*/{};

	void estabishBow();
	void prepareTestSet();

	void trainModel(int max_iterations, double learning_rate);
	void testModel();

	
	void runGeneticAlgorithm();

	void initialize();


};