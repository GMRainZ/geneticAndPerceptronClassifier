#pragma once
#include"PerCeptron.h"


//用于处理数据的类
//包括
//正则化数据
//建立词袋模型
//or计算tf,idf
class DataProcess
{
	int numWords = 9829,numSample=2000;
	const std::string rawtrainDataNeg, rawtrainDataPos;
	const std::string trainDataNeg, trainDataPos;
	const std::string testDataNeg, testDataPos;
	const std::string modelData,testSet;
	const std::string testSetNeg, testSetPos;
	const std::string storeModelPath;
	std::vector<std::string>files;

	//std::vector<Sample>trainData;

	void regularizeStr(std::string&);
	bool sortedRule(std::pair<std::string, int>& l,std::pair<std::string, int>& r)
	{
		return l.second < r.second;
	}
public:

	DataProcess() :rawtrainDataNeg("D:\\作业\\智能计算\\IMDA\\aclImdb\\train\\neg"),
		rawtrainDataPos("D:\\作业\\智能计算\\IMDA\\aclImdb\\train\\pos"),
		trainDataNeg("D:\\作业\\智能计算\\liuPR\\IMDB\\cleaning_data\\train\\neg"),
		trainDataPos("D:\\作业\\智能计算\\liuPR\\IMDB\\cleaning_data\\train\pos"),
		testDataNeg("D:\\作业\\智能计算\\IMDA\\aclImdb\\test\\neg"),
		testDataPos("D:\\作业\\智能计算\\IMDA\\aclImdb\\test\\pos"),
		modelData("D:\\作业\\智能计算\\IMDA\\regularize"),
		testSet("D:\\作业\\智能计算\\IMDA\\testModel") ,
		testSetNeg("D:\\作业\\智能计算\\liuPR\\IMDB\\cleaning_data\\test\\neg"),
		testSetPos("D:\\作业\\智能计算\\liuPR\\IMDB\\cleaning_data\\test\\pos"),
		storeModelPath("D:\\作业\\智能计算\\liuPR\\感知器.txt"){}
	
	void rgularizeTrainData();
	void rgularizeTestData();

	void calculateTrainBOW();
	void calculateTestBOW();

	//void calculateTFIDF();
	void establishTrainBOW(std::vector<Sample>&);
	void estabishTestBOW(std::vector<Sample>&);



	void GetAllFormatFiles(const std::string& path, std::string format=".txt");

	void accquireStoreModel(Perceptron&);
	void storeModel();

	void setNums(int& _numWords, int& _numSample);
};

