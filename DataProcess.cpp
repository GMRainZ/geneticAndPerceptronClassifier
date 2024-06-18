#include "DataProcess.h"
using namespace std;

void DataProcess::rgularizeTrainData()
{
	GetAllFormatFiles(rawtrainDataNeg);
	GetAllFormatFiles(rawtrainDataPos);
	//files ����ʹ洢����ǧ��ѵ�����ݴ�����


	string strProcess,strPath;
	int times = 0;
	for (const auto& filename : files)
	{
		ifstream ifs(filename);
		strPath = modelData;
		ofstream ofs(strPath.append("\\").append(to_string(++times)).append(".txt"));
		if (!ifs.is_open())
		{
			cout << "���ļ�ʧ��" << endl;
			return;
		}

		getline(ifs, strProcess);
		regularizeStr(strProcess);

		ofs << strProcess;
	}
}

void DataProcess::rgularizeTestData()
{
	GetAllFormatFiles(testDataNeg);
	GetAllFormatFiles(testDataPos);
	//files ����ʹ洢����ǧ��ѵ�����ݴ�����


	string strProcess, strPath;
	int times = 0;
	for (const auto& filename : files)
	{
		ifstream ifs(filename);
		strPath = testSet;
		ofstream ofs(strPath.append("\\").append(to_string(++times)).append(".txt"));
		if (!ifs.is_open())
		{
			cout << "���ļ�ʧ��" << endl;
			return;
		}

		getline(ifs, strProcess);
		regularizeStr(strProcess);

		ofs << strProcess;
	}
}

void DataProcess::regularizeStr(std::string&strProcess)
{
	for (auto&ch: strProcess)
	{
		if (ch <= 'z' && ch >= 'a'|| ch=='\'')continue;
		if (ch<='Z'&&ch>='A')
		{
			ch |= 32;
			continue;
		}

		
		ch = ' ';
	}
}
//
//void DataProcess::estabishTestBOW(std::vector<Sample>&TestData)
//{
//	files.clear();
//	GetAllFormatFiles(modelData);
//	int times = 0;
//	string str, strAid;
//
//	for (const auto& filename : files)
//	{
//		str = testData;
//		ifstream orgfs(str.append("\\testData.txt"));
//
//		TestData[times].tag = times / 1000 ? 1 : -1;
//
//		ifstream ifs(filename);
//		getline(ifs, str);
//
//		int x = 0, pos = 0;
//		while (orgfs >> strAid)
//		{
//			//cout << strAid<<'\n';
//			pos = 0;
//			while ((pos = str.find(strAid, pos)) != str.npos)
//			{
//				++pos;
//				++TestData[times].feature[x];
//			}
//
//			++x;
//		}
//
//		for (const auto& y : TestData[times].feature)
//		{
//			cout << y << ' ';
//		}
//		cout << "���" << TestData[times].tag << '\n';
//
//		if (++times >= 2000)break;
//	}
//}


void DataProcess::calculateTrainBOW()
{
	files.clear();
	GetAllFormatFiles(trainDataNeg);
	GetAllFormatFiles(trainDataPos);

	map<string, int>bow;
	string str;
	for (const auto& filename : files)
	{
		ifstream ifs(filename);
		getline(ifs, str);
		stringstream ss(str);

		while (ss >> str)
		{
			++bow[str];
		}

	}

	//cout << bow.size() << endl;

	//for (const auto&info : bow)
	//{
	//	cout << info.first << '\t' << info.second << endl;
	//}

	vector<pair<string, int>>sortedBow(bow.begin(), bow.end());

	sort(sortedBow.begin(), sortedBow.end(), [](const auto& l, const auto& r) {return l.second > r.second; });

	int times = numWords;
	str = modelData;
	ofstream ofs(str.append("\\").append("modelData.txt"));
	for (const auto& x : sortedBow)
	{
		if (x.second < 3)continue;
		ofs << x.first << '\n';
		if (!--times)break;
		//cout << x.first <<' ' << x.second << endl;
	}
}

//void DataProcess::calculateTFIDF()
//{
//	
//}

void DataProcess::establishTrainBOW(vector<Sample>&trainData)
{
	
	files.clear();
	//GetAllFormatFiles(modelData);
	GetAllFormatFiles(trainDataNeg);
	GetAllFormatFiles(trainDataPos);
	int times = 0;
	string str,strAid;

	//str = modelData;
	//ifstream orgfs1(str.append("\\modelData.txt"));
	//while (orgfs1 >> strAid)cout << strAid << '\n';

	for (const auto& filename : files)
	{
		str = modelData;
		ifstream orgfs(str.append("\\modelData.txt"));
		if (!orgfs.is_open())
		{
			cerr << "δ�ܳɹ���" << endl;
			break;
		}
		trainData[times].tag = times / 1000 ? 1 : -1;

		ifstream ifs(filename);
		if (!ifs.is_open())
		{
			cerr << "δ�ܳɹ���" << endl;
			break;
		}
		getline(ifs, str);

		int x = 0, pos = 0;
		while (orgfs >> strAid)
		{
			//cout << strAid<<'\n';
			pos = 0;
			while ((pos=str.find(strAid, pos)) != str.npos)
			{
				pos += strAid.size();
				++trainData[times].feature[x];
			}

			++x;
		}

		//for (const auto& y : trainData[times].feature)
		//{
		//	cout << y << ' ';
		//}
		//cout << "���" << trainData[times].tag << '\n';

		if (++times >= numSample)break;
	}

}

void DataProcess::estabishTestBOW(std::vector<Sample>&testData)
{

	files.clear();
	GetAllFormatFiles(testSetPos);
	GetAllFormatFiles(testSetNeg);


	int times = 0;
	string str, strAid;

	vector<string>vs;

	for (const auto& filename : files)
	{
		str = modelData;
		ifstream orgfs(str.append("\\modelData.txt"));

		testData[times].tag = times / 1000 ? -1 : 1;

		vs.clear();

		ifstream ifs(filename);
		while (ifs >> str)vs.emplace_back(str);
		//getline(ifs, str);

		//cout << str << endl;

		int x = 0, pos = 0;
		while (orgfs >> strAid)
		{
			//cout << strAid<<' ';
			if (strAid.size() <= 1)continue;

			testData[times].feature[x] = count(vs.begin(), vs.end(), strAid);


			//pos = 0;
			//while ((pos = str.find(strAid, pos)) != str.npos)
			//{
			//	//cout << strAid << ' ' << pos << '\n';
			//	pos += strAid.size();
			//	++testData[times].feature[x];
			//}

			//cout << strAid << ' ' << pos << '\n';

			++x;
		}

		//cout << x << '\n';


		//for (const auto& y : testData[times].feature)
		//{
		//	cout << y << ' ';
		//}
		//cout << "���" << testData[times].tag << '\n';

		if (++times >= numSample)break;
	}

}

void DataProcess::accquireStoreModel(Perceptron&pm)
{
	//"D:\��ҵ\���ܼ���\IMDA\regularize\modelDataValue.txt"

	ifstream ifs(modelData + "\\modelDataValue.txt");
	if (!ifs.is_open())
	{
		cerr << "δ�ܳɹ���" << endl;
		return;
	}


	pm.setWeight(ifs);

}


void DataProcess::storeModel()
{
	ifstream ifs(storeModelPath);
	ofstream ofs(modelData+"\\modelData.txt");
	ofstream ofsv(modelData + "\\modelDataValue.txt");
	if (!ifs.is_open())
	{
		cerr << "ifs���ļ�ʧ��" << endl;
		return;
	}
	if (!ofs.is_open())
	{
		cerr << "ofs���ļ�ʧ��" << endl;
		return;
	}
	string str; double value;
	while (ifs >> str >> value)
	{
		ofs << str << '\n';
		ofsv << value << '\n';
	}

}

void DataProcess::setNums(int& _numWords, int& _numSample)
{
	numWords = _numWords;
	numSample = _numSample;
}



void DataProcess::GetAllFormatFiles(const string& path, string format)
{
	//�ļ����  
	long hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	
	//fetch 1000 samples
	int times = numSample>>1;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1)  //�и��ļ��ͽ���
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR)) // /*�Ƚ��ļ������Ƿ����ļ��� attrib��
			//�����������ļ������ԣ�__A_ARCH���浵����_A_HIDDEN�����أ���_A_NORMAL����������_A_RDONLY��ֻ������ _A_SUBDIR���ļ��У���_A_SYSTEM��ϵͳ����**/
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
					GetAllFormatFiles(p.assign(path).append("\\").append(fileinfo.name),format);
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0 && --times);

		_findclose(hFile);
	}
}
