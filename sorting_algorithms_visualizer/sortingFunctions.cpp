#include "sortingFunctions.h"


void ArrayElement::initialize(const int value) 
{
	this->value = value;
	color = sf::Color::White;
}

bool ArrayElement:: operator < (const ArrayElement obj) const {
	return value < obj.value ? true : false;
}

bool ArrayElement:: operator<= (const ArrayElement obj) const {
	return value <= obj.value ? true : false;
}

bool ArrayElement:: operator > (const ArrayElement obj) const {
	return value > obj.value ? true : false;
}

void ArrayElement::  operator = (const ArrayElement obj){
	value = obj.value;
	color = obj.color;
}


int sleep_time;
unsigned int nr_compares;
unsigned int nr_assigns;

static void bubleSort(ArrayElement *arr,int n)
{
	nr_assigns = nr_compares = 0;

	int indexOfSortedElements = 0;
	bool isSorted;
	do
	{
		isSorted = true;
		int lastIndex=0;

		for (int i = 0; i < n - 1 - indexOfSortedElements; i++) {

			nr_compares++;
			arr[i].color = sf::Color::Red;
			sf::sleep(sf::milliseconds(sleep_time));

			if (arr[i] > arr[i + 1]) {
				nr_assigns += 3;
				isSorted = false;

				ArrayElement t = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = t;
				/*arr[i].value = arr[i + 1].value;
				arr[i].color = arr[i + 1].color;
				arr[i + 1].value = t.value;
				arr[i + 1].color = t.color*/
				
				//std::swap(arr[i], arr[i + 1]);
			}
			else // this else is optional
				arr[i].color = sf::Color::White;
		}

		indexOfSortedElements++;
		arr[n - indexOfSortedElements].color = sf::Color::Green;

	} while (!isSorted);

	// fill remaining shapes with green color
	for (int i = 0; i < indexOfSortedElements; i++)
		arr[i].color = sf::Color::Green;
}

static void selectionSort(ArrayElement* arr, int n)
{
	ArrayElement* v = arr;
	nr_assigns = nr_compares = 0;

	for (int i = 0; i < n - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < n; j++)
		{
			nr_compares++;
			if (v[j] < v[min]) 
				min = j;

			v[min].color = sf::Color::Red;
			v[j].color = sf::Color::Blue;
			sf::sleep(sf::milliseconds(sleep_time));
			v[min].color = sf::Color::White;
			v[j].color = sf::Color::White;
		}

		v[min].color = sf::Color::Green;
		if (min != i)
		{
			std::swap(v[i], v[min]);
			nr_assigns += 3;
		}
	}
	v[n - 1].color = sf::Color::Green;
}

static void insertionSort(ArrayElement* arr, int n)
{
	ArrayElement* v = arr;

	nr_assigns = nr_compares = 0;

	v[0].color = sf::Color::Green;
	for (int i = 1; i < n; i++)
	{
		int key = v[i].value, j = i - 1;
		nr_assigns++;
		//comp++;
		v[i].color = sf::Color::Green;
		while (key < v[j].value && j >= 0)
		{
			nr_compares++;
			nr_assigns++;
			// 
			//v[j + 1] = v[j];
			std::swap(v[j + 1], v[j]); // swap is used only for visualisation

			v[j].color = sf::Color::Red;
			sf::sleep(sf::milliseconds(sleep_time));
			v[j].color = sf::Color::Green;

			j--;
		}
		//v[j + 1].value = key;
		//atrib++;
	}
}



static int partition(ArrayElement* v, int startIndex, int endIndex)
{
	ArrayElement pivot = v[endIndex]; ///ultimul element ca pivot
	nr_assigns++;
	int i = startIndex - 1;

	for (int j = startIndex; j < endIndex; j++)
	{

		v[endIndex].color = sf::Color::Blue;
		v[startIndex].color = sf::Color::Cyan;
		v[j].color = sf::Color::Red;
		sf::sleep(sf::milliseconds(sleep_time));
		v[endIndex].color = sf::Color::White;
		v[startIndex].color = sf::Color::White;
		v[j].color = sf::Color::White;
		nr_compares++;
		if (v[j] <= pivot)
		{
			i++;
			std::swap(v[i], v[j]);
			nr_assigns += 3;
		}

	}

	std::swap(v[i + 1], v[endIndex]);
	nr_assigns += 3;
	return i + 1;
}


static void quickSort(ArrayElement* arr, int startIndex, int endIndex)
{
	ArrayElement* v = arr;
	if (startIndex < endIndex)
	{
		int q = partition(v, startIndex, endIndex);

		arr[q].color = sf::Color::Yellow;
		sf::sleep(sf::milliseconds(sleep_time));

		quickSort(v, startIndex, q - 1);
		for (int i = startIndex; i <= q; i++)
			arr[i].color = sf::Color::Green;

		quickSort(v, q + 1, endIndex);
		for (int i = q + 1; i <= endIndex; i++)
			arr[i].color = sf::Color::Green;
	}
}


static int n;
static void mergeSort(ArrayElement* arr, const int leftIndex,const int rightIndex)
{
	if (leftIndex >= rightIndex)
		return;

	int middleIndex = (leftIndex + rightIndex) / 2;
	mergeSort(arr, leftIndex, middleIndex);
	mergeSort(arr, middleIndex + 1, rightIndex);

	int v[200];
	int i = leftIndex, k = 0, j = middleIndex + 1;

	while (i <= middleIndex && j <= rightIndex)
	{
		if (arr[i] < arr[j])
		{
			v[k] = arr[i].value;
			arr[i].color = sf::Color::Red;
			sf::sleep(sf::milliseconds(sleep_time));
			arr[i].color = sf::Color::White;
			i++;
		}
		else
		{
			v[k] = arr[j].value;
			arr[j].color = sf::Color::Blue;
			sf::sleep(sf::milliseconds(sleep_time));
			arr[j].color = sf::Color::White;
			j++;
		}
		k++;
		nr_compares++;
		nr_assigns++;
	}
	while (i <= middleIndex) {
		v[k++] = arr[i].value;
		nr_assigns++;
		arr[i].color = sf::Color::Red;
		sf::sleep(sf::milliseconds(sleep_time));
		arr[i++].color = sf::Color::White;
	}
	while (j <= rightIndex) {
		nr_assigns++;
		v[k++] = arr[j].value;
		arr[j].color = sf::Color::Blue;
		sf::sleep(sf::milliseconds(sleep_time));
		arr[j++].color = sf::Color::White;
	}

	k = 0;
	for (int i = leftIndex; i <= rightIndex; i++) {
		nr_assigns++;
		arr[i].value = v[k++];
		arr[i].color = sf::Color::Green;
		sf::sleep(sf::milliseconds(sleep_time));
	}

	if (leftIndex + rightIndex != n)
		for (int i = leftIndex; i <= rightIndex; i++) {
			arr[i].color = sf::Color::White;
		}
}


void sort(sortFunctionThreadArg* arg)
{
	nr_assigns = nr_compares = 0;
	*(arg->status) = Status::SORTING;

	switch (arg->method)
	{
	case SortingMethod::BUBLE_SORT:
		bubleSort(arg->arr, arg->n);
		break;
	case SortingMethod::SELECTION_SORT:
		selectionSort(arg->arr, arg->n);
		break;
	case SortingMethod::INSERTION_SORT:
		insertionSort(arg->arr, arg->n);
		break;
	case SortingMethod::QUICK_SORT:
		quickSort(arg->arr, 0, arg->n - 1);
		break;
	case SortingMethod::MERGE_SORT:
		n = arg->n - 1;
		mergeSort(arg->arr, 0, arg->n - 1);
		break;
	default:
		break;
	}

	*(arg->runningInstance) = false;
	*(arg->status) = Status::SORTED;
}