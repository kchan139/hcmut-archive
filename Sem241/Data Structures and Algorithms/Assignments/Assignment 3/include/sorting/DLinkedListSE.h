/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   DLinkedListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 14:13
 */

#ifndef DLINKEDLISTSE_H
#define DLINKEDLISTSE_H
#include "list/DLinkedList.h"
#include "sorting/ISort.h"

template<class T>
class DLinkedListSE: public DLinkedList<T>{
public:
    
    DLinkedListSE(
            void (*removeData)(DLinkedList<T>*)=0, 
            bool (*itemEQ)(T&, T&)=0 ) : 
            DLinkedList<T>(removeData, itemEQ){
        
    };
    
    DLinkedListSE(const DLinkedList<T>& list){
        this->copyFrom(list);
    }
    
    void sort(int (*comparator)(T&,T&)=0){
        //TODO: implement this function
        //     - You should implement the merge sort algorithm
        if (this->count <= 1) return;  // No need to sort if the list is empty or has one element

        T* array = new T[this->count];
        int index = 0;
        
        for (typename DLinkedList<T>::Iterator it = this->begin(); it != this->end(); ++it)
            array[index++] = *it;

        mergeSort(array, 0, this->count - 1, comparator);

        index = 0;
        for (typename DLinkedList<T>::Iterator it = this->begin(); it != this->end(); ++it)
            *it = array[index++];

        delete[] array;
    };
    
protected:
    static int compare(T& lhs, T& rhs, int (*comparator)(T&,T&)=0) {
        if(comparator != 0) 
            return comparator(lhs, rhs);
        else {
            if(lhs < rhs) 
                return -1;
            else if(lhs > rhs) 
                return +1;
            else 
                return 0;
        }
    }

    void mergeSort(T array[], int left, int right, int (*comparator)(T&, T&)) {
        if (left < right) {
            int middle = left + (right - left) / 2;

            mergeSort(array, left, middle, comparator);
            mergeSort(array, middle + 1, right, comparator);

            merge(array, left, middle, right, comparator);
        }
    }

    void merge(T array[], int left, int middle, int right, int (*comparator)(T&, T&)) {
        int n1 = middle - left + 1;
        int n2 = right - middle;

        // Create temporary arrays
        T* L = new T[n1];
        T* R = new T[n2];

        // Copy data to temporary arrays L[] and R[]
        for (int i = 0; i < n1; i++)
            L[i] = array[left + i];

        for (int j = 0; j < n2; j++)
            R[j] = array[middle + 1 + j];

        // Merge the temporary arrays back into array[left..right]
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (compare(L[i], R[j], comparator) <= 0) {
                array[k] = L[i];
                i++;
            } 
            else {
                array[k] = R[j];
                j++;
            }
            k++;
        }

        // Copy the remaining elements of L[], if there are any
        while (i < n1) {
            array[k] = L[i];
            i++; k++;
        }

        // Copy the remaining elements of R[], if there are any
        while (j < n2) {
            array[k] = R[j];
            j++; k++;
        }

        delete[] L;
        delete[] R;
    }
};

#endif /* DLINKEDLISTSE_H */
