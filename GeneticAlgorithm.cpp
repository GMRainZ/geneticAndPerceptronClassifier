#include "GeneticAlgorithm.h"

using namespace std;


void GeneticAlgorithm::fitness(Perceptron& pm, 
    const std::vector<Sample>& trainData, std::vector<bool>&chorosome, double&fit)
{
    Sample sp;
    int i;
    const auto& n = trainData.size();
    double accurancy=0;
    for (const auto& td : trainData)
    {
        sp.feature.assign(vocabulary_size, 0);
        for (i = 0; i < vocabulary_size; ++i)if (chorosome[i])sp.feature[i] = td.feature[i];
        sp.tag = td.tag;
        
        accurancy += sp.tag == pm.predict(sp.feature);
    }
    fit = accurancy / n;
}

void GeneticAlgorithm::initialize_population()
{
    uniform_real_distribution<double> u(-1, 1);//随机数的产生范围
    default_random_engine e(time(nullptr));//随机数的种子，用以保证产生的数是随机的
    e.seed(time(0));
    int i, j;
    for (i = 0; i < population_size; ++i)
    {
        for (j = 0; j < vocabulary_size; ++j)
        {
            population[i][j] = u(e) >= 0 ? true : false;
        }
    }
}

void GeneticAlgorithm::select(const std::vector<double>&adaptability, vector<int>&selectedPopulation)
{

    double pSum = accumulate(adaptability.begin(), adaptability.end(), 0.0), random_num;
    vector<double>probability(population_size+1);
    
    int i, j;

    for (i = 0; i <= population_size; ++i)
    {
        for (j = 0; j < i; ++j)
        {
            probability[i] += adaptability[j];
        }
        probability[i] /= pSum;
    }

    uniform_real_distribution<double> u(0.0, 1.0);
    default_random_engine e(time(nullptr));//随机数的种子，用以保证产生的数是随机的
    e.seed(time(0));


    for (i = 0; i < population_size; ++i)
    {
        random_num = u(e);
        int index = 0;

        while (random_num<probability[index] || random_num>probability[index + 1])//当指针落到了第index个扇区之间
            ++index;
        selectedPopulation[i] = index;
    }


}


void GeneticAlgorithm::crossover()
{
    uniform_real_distribution<double> u(0.0, 1.0);
    uniform_int_distribution<int>u0(0, population_size-1);
    default_random_engine e(time(nullptr));//随机数的种子，用以保证产生的数是随机的
    e.seed(time(0));
    double random_num,rn;
    int i,j,other;

    //vector<double>coprobability(vocabulary_size);
    for (i = 0; i < population_size; ++i)
    {
        random_num = u(e);
        if (random_num > probability_crossover)continue;
        other = u0(e);
        
        for (j = 0; j < vocabulary_size; ++j)
        {
            rn = u(e);
            if (rn > 1.0 / (j + 1))continue;
            swap(population[i][j], population[other][j]);
        }
    }
}

void GeneticAlgorithm::mutate()
{
    uniform_real_distribution<double> u(0.0, 1.0);
    uniform_int_distribution<int>u0(0, vocabulary_size);
    default_random_engine e(time(nullptr));//随机数的种子，用以保证产生的数是随机的
    e.seed(time(0));
    double random_num, rn;
    int i, j, times;

    //vector<double>coprobability(vocabulary_size);
    for (i = 0; i < population_size; ++i)
    {
        random_num = u(e);
        if (random_num > probability_mutation)continue;
        times = u(e)*300;

        for (j = 0; j < times; ++j)
        {
            rn = u0(e);
            population[i][j] = ~population[i][j];
        }
    }
}

void GeneticAlgorithm::genetic_algorithm(Perceptron& pm, const std::vector<Sample>& trainData)
{
    initialize_population();
    vector<double>adaptability(population_size);
    int i,iteration,j;
    std::vector<std::vector<bool>>newpopulation(population_size);
    vector<int> selectedPopulation(population_size);


    for (iteration = 0; iteration < max_iterations; ++iteration)
    {
        for (i = 0; i < population_size; ++i)
            fitness(pm, trainData, population[i], adaptability[i]);

        select(adaptability, selectedPopulation);

        //遗传
        for (i = 0; i < population_size; ++i)
        {
            j = selectedPopulation[i];
            newpopulation[i].assign(population[j].begin(), population[j].end());
        }
        population.assign(newpopulation.begin(), newpopulation.end());

        crossover();
        mutate();
    }

    bestChorosome = max_element(adaptability.begin(), adaptability.end()) - adaptability.begin();

}

void GeneticAlgorithm::getBestChorosome(std::vector<bool>&best)
{
    best.assign(population[bestChorosome].begin(), population[bestChorosome].end());
}

void GeneticAlgorithm::setNums(int& _numWords)
{
    vocabulary_size = _numWords;
}
