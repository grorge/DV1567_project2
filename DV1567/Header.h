#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DataSetSize 16384
#define DatasetFilename "filename.txt"
#define OutputFilename "results.txt"
#define ProfilerFilename "profilerData.txt"
#define BufferSize 512


struct test
{
	long startTime;

	test() : startTime(0) {};
};

int mainFunc(int size, int buffSize);

int loadDataset(int ds[], int size);
void swap(int *xp, int *yp);
void sortDataset(int arr[], int n, int m);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);

int writeDataset(int ds[], const char *filename, int n, int Buffersize, float avg, int min, int max);

float generateRand(int rmax);


float average(int dataset[], int n);
int maxvalue(int dataset[], int n);
int minvalue(int dataset[], int n);


class Profiler
{
public:
	Profiler();
	~Profiler();

	int startTest();

	void stopTest(int testNr);

private:
	std::ofstream proFile;
	test *tests;
	int nrOf;
};

Profiler::Profiler()
{
	this->tests = new test[12];
	this->nrOf = 0;

	proFile.open(ProfilerFilename, std::ios::out);

}

Profiler::~Profiler()
{
	delete this->tests;

	proFile.close();
}

inline int Profiler::startTest()
{
	this->tests[this->nrOf].startTime = clock();

	this->nrOf++;

	return this->nrOf-1;
}

inline void Profiler::stopTest(int testNr)
{
	long stopTime = clock();

	long runtime = stopTime - this->tests[testNr].startTime;

	proFile << "Test number: " << testNr << std::endl;
	proFile << "Runtime: " << runtime << "msec" << std::endl;
	
}
