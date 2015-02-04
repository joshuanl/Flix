#ifndef MERGESORT_H
#define MERGESORT_H 

#include <vector>

using namespace std;

template <class T>
class MergeSort 
{
 public:
 	
    static vector<T> sort (vector<T> a);
	// void Merge_Sort(vector<T> *a, int l, int r);
	// void Merge (vector<T> *a, int l, int r, int m);
	static vector<T> merger(vector<T> left, vector<T> right);
 private: 
	

};

#endif