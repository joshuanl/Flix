#include "MergeSort.h"
#include <vector>
#include <math.h>

using namespace std;

template <class T>
vector<T> MergeSort<T>::sort(vector<T> v){
     vector<T> left;
     vector<T> right;
    if ( (int)v.size() <= 1){
             return v;
     }
     else{
         typename vector<T>::iterator mid; //Makes the complier see this as the whole type.
         typename vector<T>::iterator it;
         unsigned int midCount = (unsigned int)(v.size() / 2);
         mid = v.begin() + midCount; 
         
         for(it=v.begin(); it < mid; ++it){
             left.push_back(*it);
         }
         
         for(it=mid; it < v.end(); ++it){
              right.push_back(*it);
         }
         left = sort(left); // Sort left half
         right = sort(right); // Sort right Half
         v = merger(left, right);
         return v;
     }//end of else
}

template <class T>
vector<T> MergeSort<T>::merger(vector<T> left, vector<T> right){
           vector<T> result;
           typename vector<T>::iterator it;
           while ( ( (left.end()-left.begin()) > 0) && ( (right.end()-right.begin()) > 0)){
                if (*left.begin() <= *right.begin()){
                    result.push_back(*left.begin());
                    left.erase(left.begin());
                 }
                 else{
                     result.push_back(*right.begin());
                     right.erase(right.begin());
                 }
           }//end of while
           if ( (left.end()-left.begin()) > 0){
                for(it = left.begin(); it < left.end(); ++it){
                       result.push_back(*it);
                }//end of for
           }//end of if
           if ( (right.end()-right.begin()) > 0){
                for(it = right.begin(); it < right.end(); ++it){
                       result.push_back(*it);
                }//end of for
           }
           return result;
}
