#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <utility>
#include <random>

//template <class T>
//void compexch(T& a, T& b)
//{
//    if (b < a)
//        std::swap(a, b);
//}
//
//template <typename T>
//void shuffle(std::vector<T>& a, std::vector<T>& p1, std::vector<T>& p2, unsigned int l, unsigned int r)
//{
//    /*
//    std::vector<T> tmp(a.size());
//    unsigned int i, j;
//    for (i = l, j = 0; i <= r; i += 2, j++)
//    {
//        tmp[i] = a[l + j];
//        tmp[i + 1] = a[half + j + 1];
//    }
//    for (auto i = 0; i < p1.size(); i++)
//        a[i] = p1[i];
//    for (i = 0, j = half + 1; i <= half; i++, j++)
//        a[j] = p2[i];
//    */
//    for (int i = 0, j = 0; i < p1.size(); i += 2, j++) {
//        a[i] = p1[j];
//    }
//    for (int i = 1, j = 0; j < p2.size(); i += 2, j++) {
//        a[i] = p2[j];
//    }
//
//    std::cout << "unsorted vec: ";
//    for (int num : a) {
//        std::cout << " " << num;
//    }
//    std::cout << std::endl;
//
//    for (int i = 0; i < a.size() - 1; i++) {
//        if (a[i] > a[i + 1]) {
//            std::swap(a[i], a[i + 1]);
//        }
//    }
//}
//
//template <typename T>
//void unshuffle(std::vector<T>& a, std::vector<T>& p1, std::vector<T>& p2, unsigned int l, unsigned int r)
//{
//    auto half = (unsigned int)(l + r) / 2;
//    std::vector<T> tmp(r - l + 1);
//    unsigned int i, j;
//    for (i = l, j = 0; i <= r; i += 2, j++)
//    {
//        tmp[l + j - l] = a[i];
//        tmp[half + j + 1 - l] = a[i + 1];
//    }
//    for (auto i = 0; i <= half; i++)
//        p1[i] = tmp[i];
//
//    for (i = 0, j = half + 1; i <= half; i++, j++)
//        p2[i] = tmp[j];
//}
//
//template <typename T>
//void sort(std::vector<T>& a, std::vector<T>& p1, std::vector<T>& p2, int l, int r) {
//    unshuffle(a, p1, p2, l, r);
//    std::sort(p1.begin(), p1.end());
//    std::sort(p2.begin(), p2.end());
//    shuffle(a, p1, p2, l, r);
//}

std::vector<int> GetRandVector(int size) {
    std::random_device rd;
    std::uniform_int_distribution<int> unif(0, 1000000);
    std::vector<int> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = unif(rd);
    }

    return vec;
}

void fill_missing(std::vector<int> &res, std::vector<int> p1, std::vector<int> p2,
                              int i, int j, int k) {
    if (j >= p1.size()) {
        for (int l = k; l < p2.size(); l += 2) {
            res[i] = p2[l];
            i++;
        }
    }
    else {
        for (int l = j; l < p1.size(); l += 2) {
            res[i] = p1[l];
            i++;
        }
    }
}

void fill_res(std::vector<int>& res, std::vector<int> p1, std::vector<int> p2,
                          int &i, int &j, int &k) {
    for (i = 0; (j < p1.size()) && (k < p2.size()); i++) {
        if (p1[j] <= p2[k]) {
            res[i] = p1[j];
            j += 2;
        }
        else {
            res[i] = p2[k];
            k += 2;
        }
    }
}

std::vector<int> merge(std::vector<int> vec1, std::vector<int> vec2) {
    std::vector<int> res(vec1.size() + vec2.size());
    int i = 0, j = 0, k = 0;

    for (i = 0, j = 0, k = 0; (j < vec1.size()) && (k < vec2.size()); i += 2, j++, k++) {
        res[i] = vec1[j];
        res[i + 1] = vec2[k];
    }

    for (int i = 0; i < res.size() - 1; i++) {
        if (res[i] > res[i + 1]) {
            std::swap(res[i], res[i + 1]);
        }
    }

    return res;
}

std::vector<int> even(std::vector<int> vec) {
    std::vector<int> p1(vec.size() / 2);
    std::vector<int> p2(vec.size() / 2);

    for (int i = 0; i < (vec.size() / 2); i++) {
        p1[i] = vec[i];
        p2[i] = vec[(vec.size() / 2) + i];
    }

    std::sort(p1.begin(), p1.end());
    std::sort(p2.begin(), p2.end());

    std::vector<int> res(p1.size() / 2 + p2.size() / 2 + p1.size() % 2 + p2.size() % 2);
    int i = 0, i1 = 0, i2 = 0;
    
    fill_res(res, p1, p2, i, i1, i2);

    fill_missing(res, p1, p2, i, i1, i2);

    return res;
}

std::vector<int> odd(std::vector<int> vec) {
    std::vector<int> p1(vec.size() / 2);
    std::vector<int> p2(vec.size() / 2);

    for (int i = 0; i < (vec.size() / 2); i++) {
        p1[i] = vec[i];
        p2[i] = vec[(vec.size() / 2) + i];
    }

    std::sort(p1.begin(), p1.end());
    std::sort(p2.begin(), p2.end());

    std::vector<int> res(p1.size() / 2 + p2.size() / 2);
    int i = 0, i1 = 1, i2 = 1;

    fill_res(res, p1, p2, i, i1, i2);

    fill_missing(res, p1, p2, i, i1, i2);

    return res;
}

std::vector<int> batcher_sort(std::vector<int> vec) {
    std::vector<int> even_vec = even(vec);

    /*std::cout << "even: ";
    for (int num : even_vec) {
        std::cout << " " << num;
    }
    std::cout << std::endl;*/

    std::vector<int> odd_vec = odd(vec);

    /*std::cout << "odd: ";
    for (int num : odd_vec) {
        std::cout << " " << num;
    }
    std::cout << std::endl;*/

    std::vector<int> res = merge(even_vec, odd_vec);

    return res;
}