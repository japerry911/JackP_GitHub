//
// Created by John Perry on 2019-04-12.
//

#ifndef ASSIGNMENT_2_MERGESORT_H
#define ASSIGNMENT_2_MERGESORT_H

#include <math.h>
#include <vector>

template<typename T>
void MergeSort(std::vector<T> &values, int left_index, int right_index);

template<typename T>
void Merge(std::vector<T> &values, int left_index, int mid_index, int right_index);

//MergeSort
//  - Based on psuedocode provided
template<typename T>
void MergeSort(std::vector<T> &values, int left_index, int right_index) {
    int mid_index;

    if (left_index < right_index) {
        mid_index = floor((left_index + right_index) / 2);
        MergeSort(values, left_index, mid_index);
        MergeSort(values, mid_index + 1, right_index);
        Merge(values, left_index, mid_index, right_index);
    }
}

//Merge
//  - based on pseudocode provided + some changes:
//     1.) Line 58 -> Added i != n1 + j == n2 conditions to prevent it from pulling from empty vector spot
//     2.) Lines 48 & 51, took out - 1 in line 48, and added + 1 in line 51
template<typename T>
void Merge(std::vector<T> &values, int left_index, int mid_index, int right_index) {
    int n1 = mid_index - left_index + 1;
    int n2 = right_index - mid_index;

    std::vector<T> left_vector(n1 + 1);
    std::vector<T> right_vector(n2 + 1);

    int i;
    int j;
    int k;

    for (i = 0; i < n1; i++) {
        left_vector[i] = values[left_index + i];
    }
    for (j = 0; j < n2; j++) {
        right_vector[j] = values[mid_index + j + 1];
    }

    i = 0;
    j = 0;

    for (k = left_index; k < right_index + 1; k++) {
        if ((left_vector[i] <= right_vector[j] && i != n1) || j == n2) {
            values[k] = left_vector[i];
            i++;
        } else {
            values[k] = right_vector[j];
            j++;
        }
    }
}

#endif //ASSIGNMENT_2_MERGESORT_H
