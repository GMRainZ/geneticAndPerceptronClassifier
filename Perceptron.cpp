#include "Perceptron.h"
#include <fstream>

using namespace std;
Perceptron::Perceptron():weights(numWords,0.0),bias(0),
storePerceptron("D:\\��ҵ\\���ܼ���\\IMDA\\storeModel\\Perceptron.txt")
{
    //std::default_random_engine e;

    ////std::uniform_int_distribution<int> u2(0, 5); // ����ұ�����
    ////std::uniform_real_distribution<double> u(-50.0, 50.0); // ����ұ�����
    //std::normal_distribution<double> u(0, 15); // ��ֵΪ0����׼��Ϊ15
    //e.seed(time(0));

    //for (auto& weight : weights) 
    //{
    //    weight = ((long(rand()) + 100) % 101) - 50;//�������һ��-50~50��ֵ��ΪȨ��
    //    //printf("weight== %.4f\n", weight);
    //}
    //bias = ((long(rand()) + 100) % 101) - 50;//�������һ��-50~50��ֵ��ΪȨ��
    //printf("bias== %.4f\n", bias);
}

Perceptron::Perceptron(string _path):storePerceptron(_path), weights(numWords, 0), bias(0)
{
    ifstream ifs(storePerceptron);

    for (auto& weight : weights)ifs >> weight;
    ifs >> bias;
}

Perceptron::Perceptron(bool f):storePerceptron("D:\\��ҵ\\���ܼ���\\IMDA\\storeModel\\Perceptron.txt")
{
    
    ifstream ifs("D:\\��ҵ\\���ܼ���\\liuPR\\��֪��.txt");
    string str; int value;
    std::default_random_engine e;
    //std::uniform_int_distribution<int> u2(0, 5); // ����ұ�����
    //std::uniform_real_distribution<double> u(-50.0, 50.0); // ����ұ�����
    std::normal_distribution<double> u(0, 15); // ��ֵΪ0����׼��Ϊ15
    e.seed(time(0));


    while(ifs >> str)
    {

        ifs >> value;
        mweights[str] = value;
    }
    bias = 0;
}

int Perceptron::predict(const std::vector<double>& inputs)
{

    double sum = bias;
    
    for (int i = 0; i < numWords; ++i)
    {
        if (!inputs[i]||!weights[i])continue;
        sum += weights[i] * inputs[i];

        //cout << "weight & input   " << weights[i] << ' ' << inputs[i] << '\n';
        //cout << "sum == " << sum << '\n';
        //sum %= mod;
        
    }
    //printf("sum==%.4f\n", sum);


    return activation_function(sum);
}

int Perceptron::mpredict(std::ifstream& inputs)
{
    double sum = bias;

    string str;
    while (inputs >> str)
    {
        if (mweights.count(str))
            sum += mweights[str];
    }


    return activation_function(sum);
}

void Perceptron::train(std::vector<Sample>& trainData,const int& max_iterations,const double& learning_rate)
{
    int iteration = 0,i;
    //double localError, globleError;

    const auto& n = trainData.size();

    do {
        //globleError = 0;
        ++iteration;

        for (i = 0; i < n; ++i)
        {
            int yHat = predict(trainData[i].feature);
            //printf("��ǰԤ��Ϊ%d\n", yHat);
            //localError = trainData[i].tag - yHat;
            //printf("%.4f\t", localError);

            int j = 0;
            if (/*localError*/yHat!=trainData[i].tag) {
                for (auto& weight : weights)
                    weight += learning_rate * trainData[i].tag* trainData[i].feature[j++];
                bias += learning_rate * trainData[i].tag;
            }
            //globleError += localError * localError;
        }
        
        //printf("%.4f\n", globleError);
    } while (/*globleError != 0 && */iteration < max_iterations);


}

void Perceptron::mtrain(std::vector<Sample>& trainData, const int& max_iterations, const double& learning_rate)
{
    int iteration = 0,i;
    //double localError, globleError;
    string str1 = "D:\\��ҵ\\���ܼ���\\liuPR\\IMDB\\cleaning_data\\train\\neg";
    string str2 = "D:\\��ҵ\\���ܼ���\\liuPR\\IMDB\\cleaning_data\\train\\pos";
    int times = 0;

    while (iteration++ < max_iterations)
    {
        times = -1;
        while (++times < 1000)
        {
            ifstream ifs(str1 + "\\" + to_string(times) + ".txt");
            if (!ifs.is_open())
            {
                cerr << "δ�ܴ��ļ�" << endl;
                break;
            }
            int yHat = mpredict(ifs);

            
            //Ԥ�����͸���
            int j = 0; i = -1;
            if (/*localError*/yHat != i) {
                for (auto& mweight : mweights)
                    mweight.second += learning_rate * (i - yHat);
                bias += learning_rate * (i-yHat);
            }
        }
        times = -1;
        while (++times < 1000)
        {
            ifstream ifs(str2 + "\\" + to_string(times) + ".txt");
            if (!ifs.is_open())
            {
                cerr << "δ�ܴ��ļ�" << endl;
                break;
            }
            int yHat = mpredict(ifs);


            int j = 0; i = 1;
            if (/*localError*/yHat != i) {
                for (auto& mweight : mweights)
                    mweight.second += learning_rate * (i - yHat);
                bias += learning_rate * (i - yHat);
            }
        }

    }
}

void Perceptron::testModel(std::vector<Sample>&testData)
{
    
    printf("ԭʼ����\tԤ������\n");
    const auto& n = testData.size();
    int x,y;
    double accuracy=0;
    for (int i = 0; i < n; ++i)
    {

        x = predict(testData[i].feature), y = testData[i].tag;
        accuracy += x == y;
        printf("%4d\t%4d\n", y, x);

    }

    accuracy /= n;

    printf("׼ȷ��Ϊ%.4f\n", accuracy);

}

void Perceptron::mtestModel(std::vector<Sample>&)
{
    printf("ԭʼ����\tԤ������\n");
    double accuracy = 0;

    string str1 = "D:\\��ҵ\\���ܼ���\\liuPR\\IMDB\\cleaning_data\\test\\neg";
    string str2 = "D:\\��ҵ\\���ܼ���\\liuPR\\IMDB\\cleaning_data\\test\\pos";
    int times,x,y;
    times = -1;
    while (++times < 1000)
    {
        ifstream ifs(str1 + "\\" + to_string(times) + ".txt");
        if (!ifs.is_open())
        {
            cerr << "δ�ܴ��ļ�" << endl;
            break;
        }
        y = mpredict(ifs); x = -1;
        accuracy += x == y;

        printf("%4d\t%4d\n", x, y);
    }
    times = -1;
    while (++times < 1000)
    {
        ifstream ifs(str2 + "\\" + to_string(times) + ".txt");
        if (!ifs.is_open())
        {
            cerr << "δ�ܴ��ļ�" << endl;
            break;
        }
        y = mpredict(ifs); x = 1;
        accuracy += x == y;

        printf("%4d\t%4d\n", x, y);
    }

    accuracy /= numSample;

    printf("׼ȷ��Ϊ%.4f\n", accuracy);
}

void Perceptron::setWeight(ifstream&ifs)
{
    //int value;
    int times = 0;
    for (auto&weight:weights)
    {
        ifs >> weight;
        //cout << times++ << '\n';
        //cout << weight << '\n';
        //weight /= 10;
        //cout << weight << '\n';
    }

}

Perceptron::~Perceptron()
{
    ofstream ofs(storePerceptron);
    
    for (const auto& weight : weights)
    {
        ofs << weight << '\n';
    }
    ofs << bias << '\n';

    //ofstream ofs(storePerceptron);
    //
    //for (const auto& mweight : mweights)
    //{
    //    ofs << mweight.first << ' ' << mweight.second << '\n';
    //}
    //ofs << bias << '\n';
}

void Perceptron::setNums(int&_numWords, int&_numSample)
{
    numWords = _numWords;
    numSample = _numSample;
}
