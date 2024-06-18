#pragma once

#include "Perceptron.h"


class GeneticAlgorithm
{
	const int max_iterations = 1000;//迭代次数
	//const double mutation_rate = 0.1;
	const int population_size=10;
	int vocabulary_size=9829;
	const double probability_crossover = 0.25;//交叉率
	const double probability_mutation = 0.1;//变异率
	std::vector<std::vector<bool>>population;
	int bestChorosome;
	//const vector<double>& probability


	void fitness(Perceptron&pm,const std::vector<Sample>&trainData,std::vector<bool>&,double&);

	void initialize_population();
	
	void select(const std::vector<double>&,std::vector<int>&);

	void crossover();

	void mutate();


public:
	GeneticAlgorithm():population(population_size, std::vector<bool>(vocabulary_size)){}
	void genetic_algorithm(Perceptron& pm, const std::vector<Sample>& trainData);
	void getBestChorosome(std::vector<bool>&);
	void setNums(int& _numWords);
	
};

