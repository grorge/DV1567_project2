#include "Header.h"



//this code is an example of how to read a file in C


int main()
{
	Profiler prof;
	int test1 = prof.startTest();

	std::cout << "Hello World!\n";



	int v[DataSetSize];
	//you can alternatively dynamically allocate the vector
	for (int i = 0; i < DataSetSize; i++)
	{
		v[i] = generateRand(100);
		std::cout << i << std::endl;
	}


	int ds[DataSetSize];

	//// load the dateset in the memory area addressed by ds
	//loadDataset(ds, DataSetSize);
	//// compute the average value of the dataset, i.e. sum_of_dataset_values / num_of_dataset_values
	float avg = average(v);
	//	// find the max value in the dataset
	int max = maxvalue(v);
	//	// find the min value in the dataset
	int min = minvalue(v);
	//	//sort the dataset and copy it into the memory area pointed by sds

	sortDataset(v);

	//insertionSort(v, DataSetSize);
	////write the sorted array into a new file plus the valies of the average, min and max as the first three records.
	writeDataset(v, OutputFilename, DataSetSize, avg, min, max);


	prof.stopTest(test1);

	return 0;
}


//this code is an example of how to read a file in C
int loadDataset(int ds[], int size)
{
	std::ifstream fp;
	std::string v[BufferSize];
	//fopen_s(&fp, DatasetFilename, "r");
	fp.open(DatasetFilename, std::ios::out);

	if (fp.is_open())
	{
		bool filling = true;
		for (int i = 1; i <= size && filling; i++)
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
void sortDataset(int arr[])
{
	int partionDS[BufferSize];
	int itterations = DataSetSize / BufferSize;

	for (int j = 0; j < itterations; j++)
	{
		for (int i = 0; i <= BufferSize; i++)
		{
			partionDS[i] = arr[i + (j*BufferSize)];
		}

		insertionSort(partionDS, BufferSize);

		for (int i = 0; i <= BufferSize; i++)
		{
			arr[i + (j*BufferSize)] = partionDS[i];
		}
	}


	insertionSort(arr, DataSetSize);

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


int writeDataset(int ds[], const char *filename, int Buffersize, float avg, int min, int max)
{
	std::ofstream fp;
	std::string v[BufferSize];

	fp.open(OutputFilename, std::ios::out);

	int itterations = DataSetSize / BufferSize;

	for (int j = 0; j < itterations; j++)
	{
		for (int i = 0; i < BufferSize; i++)
			{
				fp << ds[i+(j*BufferSize)] << std::endl;
			}
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


float average(int dataset[])
{
	float avg = 0.0f;

	for (int i = 0; i < DataSetSize; i++)
	{
		avg += dataset[i];
	}

	avg /= DataSetSize;

	return avg;
}
int maxvalue(int dataset[])
{
	int max = dataset[0];

	for (int i = 0; i < DataSetSize; i++)
	{
		if (dataset[i] > max)
		{
			max = dataset[i];
		}
	}

	return max;
}
int minvalue(int dataset[])
{
	int min = dataset[0];

	for (int i = 0; i < DataSetSize; i++)
	{
		if (dataset[i] < min)
		{
			min = dataset[i];
		}
	}

	return min;
}

