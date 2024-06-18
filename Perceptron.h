#pragma once
#include"Sample.h"


class Perceptron
{
    int numWords = 9829, numSample = 2000;
    const std::string storePerceptron;
    const int mod = 1e9+7;
    std::vector<double> weights;
    std::map<std::string, double>mweights;
    double bias;

    // ¼¤»îº¯Êý
    int activation_function(double&x) {
        return x > 0 ? 1 : -1;
    }

public:

    Perceptron();
    Perceptron(std::string _path);
    Perceptron(bool f);


    int predict(const std::vector<double>& inputs);
    int mpredict(std::ifstream& inputs);

    void train(std::vector<Sample>&trainData,const int& max_iterations,const double& learning_rate);
    void mtrain(std::vector<Sample>& trainData, const int& max_iterations, const double& learning_rate);

    void testModel(std::vector<Sample>&);
    void mtestModel(std::vector<Sample>&);



    void setWeight(std::ifstream&);

    ~Perceptron();
    void setNums(int& _numWords, int& _numSample);
};

