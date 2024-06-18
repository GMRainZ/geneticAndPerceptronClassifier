#pragma once
#include"PerCeptron.h"


//���ڴ������ݵ���
//����
//��������
//�����ʴ�ģ��
//or����tf,idf
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

	DataProcess() :rawtrainDataNeg("D:\\��ҵ\\���ܼ���\\IMDA\\aclImdb\\train\\neg"),
		rawtrainDataPos("D:\\��ҵ\\���ܼ���\\IMDA\\aclImdb\\train\\pos"),
		trainDataNeg("D:\\��ҵ\\���ܼ���\\liuPR\\IMDB\\cleaning_data\\train\\neg"),
		trainDataPos("D:\\��ҵ\\���ܼ���\\liuPR\\IMDB\\cleaning_data\\train\pos"),
		testDataNeg("D:\\��ҵ\\���ܼ���\\IMDA\\aclImdb\\test\\neg"),
		testDataPos("D:\\��ҵ\\���ܼ���\\IMDA\\aclImdb\\test\\pos"),
		modelData("D:\\��ҵ\\���ܼ���\\IMDA\\regularize"),
		testSet("D:\\��ҵ\\���ܼ���\\IMDA\\testModel") ,
		testSetNeg("D:\\��ҵ\\���ܼ���\\liuPR\\IMDB\\cleaning_data\\test\\neg"),
		testSetPos("D:\\��ҵ\\���ܼ���\\liuPR\\IMDB\\cleaning_data\\test\\pos"),
		storeModelPath("D:\\��ҵ\\���ܼ���\\liuPR\\��֪��.txt"){}
	
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

