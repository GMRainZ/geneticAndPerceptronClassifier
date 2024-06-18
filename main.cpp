#include"mainClass.h"


using namespace std;


int main()
{

	mainClass mc;

	//dp.rgularizeData();
	//dp.calculateBOW();

	mc.initialize();

	mc.estabishBow();

	//mc.trainModel(100,0.7);

	mc.runGeneticAlgorithm();

	mc.prepareTestSet();

	mc.testModel();

	return 0;
}