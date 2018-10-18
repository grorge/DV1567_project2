#include "Header.h"



//this code is an example of how to read a file in C


int main()
{
	Profiler *prof = new Profiler();

	std::cout << "Hello World!\n";
	
	int v[DataSetSize];
	//you can alternatively dynamically allocate the vector
	for (int i = 0; i < DataSetSize; i++)
	{
		v[i] = generateRand(100);
		std::cout << i << std::endl;
	}

	writeDataset(v, DatasetFilename, DataSetSize, DataSetSize, 0, 0, 0);


	int dataSize = DataSetSize / 4;

	for (int i = 1; i <= 4; i++)
	{
		int t0 = prof->startTest();

		mainFunc(prof, dataSize * i, BufferSize /*DataSetSize/8*/);

		prof->stopTest(t0);
	}

	delete prof;

	return 0;
}

int mainFunc(Profiler *prof, int size, int buffSize)
{
	int *v = new int[DataSetSize];

	int tload = prof->startTest();

	//// load the dateset in the memory area addressed by ds
	loadDataset(v, size);

	prof->stopTest(tload);

	//// compute the average value of the dataset, i.e. sum_of_dataset_values / num_of_dataset_values
	float avg = average(v, size);
	//	// find the max value in the dataset
	int max = maxvalue(v, size);
	//	// find the min value in the dataset
	int min = minvalue(v, size);
	//	//sort the dataset and copy it into the memory area pointed by sds
	
	int tsort = prof->startTest();

	sortDataset(v, size, buffSize);
	prof->stopTest(tsort);
	//insertionSort(v, DataSetSize);
	////write the sorted array into a new file plus the valies of the average, min and max as the first three records.

	int twrite = prof->startTest();
	writeDataset(v, OutputFilename, DataSetSize, buffSize, avg, min, max);
	prof->stopTest(twrite);

	return 1;
}

//this code is an example of how to read a file in C
int loadDataset(int ds[], int size)
{
	std::ifstream fp;
	std::string *v = new std::string[DataSetSize];
	//fopen_s(&fp, DatasetFilename, "r");
	fp.open(DatasetFilename, std::ios::out);

	if (fp.is_open())
	{
		bool filling = true;
		int i;
		for (i = 0; i < size && filling; i++)
		{

			if (std::getline(fp, v[i]))
				ds[i] = std::stoi(v[i]);
			else
				filling = false;
		}
		// TIP you can define you own buffer, buffer size and you can read blocks of data of size > 1
		//fclose(fp);
		fp.close();
	}

	return 1;
}

void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}
void sortDataset(int arr[], int n, int m)
{
	int *partionDS = new int[m];
	int itterations = n / m;

	for (int j = 0; j < itterations; j++)
	{
		for (int i = 0; i < m; i++)
		{
			partionDS[i] = arr[i + (j*m)];
		}

		insertionSort(partionDS, m);

		for (int i = 0; i < m; i++)
		{
			arr[i + (j*m)] = partionDS[i];
		}
	}


	insertionSort(arr, n);

	//delete partionDS;
}
void selectionSort(int arr[], int n)
{
	int i, j, min_idx;
	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;
		// Swap the found minimum element with the first element
		swap(&arr[min_idx], &arr[i]);
	}
}

void insertionSort(int arr[], int n)
{
	int i, current, j;
	for (i = 1; i < n; i++)
	{
		current = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > current)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = current;
	}
}


int writeDataset(int ds[], const char *filename, int n, int Buffersize, float avg, int min, int max)
{
	std::ofstream fp;


	fp.open(filename, std::ios::out);

	int itterations = n / Buffersize;

	for (int j = 0; j < itterations; j++)
	{
		int i;
		for (i = 0; i < Buffersize; i++)
			{
				fp << ds[i+(j*Buffersize)] << std::endl;
			}
		//int k = 1322;
	}

	fp << Buffersize << std::endl;
	fp << avg << std::endl;
	fp << min << std::endl;
	fp << max;
	// TIP you can define you own buffer, buffer size and you can write blocks of data of size > 1
	fp.close();


	return 0;
}

float generateRand(int rmax) {
	//Generate a floating point random number between 0 and rmax
	//srand((unsigned int)time(NULL)); //initialize the random number generator
	return rand() % rmax;
}


float average(int dataset[], int n)
{
	float avg = 0.0f;

	for (int i = 0; i < n; i++)
	{
		avg += dataset[i];
	}

	avg /= n;

	return avg;
}
int maxvalue(int dataset[], int n)
{
	int max = dataset[0];

	for (int i = 0; i < n; i++)
	{
		if (dataset[i] > max)
		{
			max = dataset[i];
		}
	}

	return max;
}
int minvalue(int dataset[], int n)
{
	int min = dataset[0];

	for (int i = 0; i < n; i++)
	{
		if (dataset[i] < min)
		{
			min = dataset[i];
		}
	}

	return min;
}

