#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class ArrayElement {
public:
	int value;		 // stored value in array[...]
	sf::Color color; // color of shape

	void initialize(const int value);

	bool operator < (const ArrayElement obj) const;
	bool operator <= (const ArrayElement obj) const;
	bool operator > (const ArrayElement obj) const;
	void operator = (const ArrayElement obj);
};

enum class SortingMethod {
	NONE, BUBLE_SORT, SELECTION_SORT, INSERTION_SORT, QUICK_SORT, MERGE_SORT
};

enum class Status {
	UNSORTED, SORTING, SORTED
};

struct sortFunctionThreadArg {
	ArrayElement* arr; // pointer to array
	int n;    // size of the array
	bool* runningInstance; // pointer to thread's running state
	Status* status;		// pointer to visualizer's status about sorting status
	SortingMethod method;
};

extern int sleep_time;
extern unsigned int nr_compares;
extern unsigned int nr_assigns;

void sort(sortFunctionThreadArg* arg);