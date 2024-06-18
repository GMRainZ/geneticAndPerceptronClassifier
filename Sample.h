#pragma once
#include <io.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>
#include <random>
#include <cmath>
#include <numeric>

class Sample {
public:

	std::vector<double>feature;
	int tag;

	Sample() :feature(10000, 0),tag(0) {}
	Sample(int n):feature(n,0){}

	//Sample& operater = (const Sample &);
};
