#include <iostream>
#include <vector>
#include <bitset>
#include <ctime>
#include <regex>
#include<random>
#include <iomanip>
#include <fstream>


using namespace std;

void Merge(vector<unsigned int> &v, unsigned int l, unsigned int r) {

    unsigned int m = (l + r) / 2;
    unsigned int i = l, j = m + 1, k = l;
    vector<unsigned int> tmp;
    tmp.resize(v.size());
    while (i <= m && j <= r) {
        if (v[i] < v[j])
            tmp[k++] = v[i++];
        else
            tmp[k++] = v[j++];
    }
    while (i <= m)
        tmp[k++] = v[i++];
    while (j <= r)
        tmp[k++] = v[j++];
    for (unsigned int n = l; n <= r; ++n) {
        v[n] = tmp[n];
    }

}

void Merge_sort(vector<unsigned int> &v, unsigned int l, unsigned int r) {
    if (l < r) {
        unsigned int m = l + (r - l) / 2;
        Merge_sort(v, l, m);
        Merge_sort(v, m + 1, r);
        Merge(v, l, r);
    }

}

void Insertion_sort(vector<unsigned int> &v, int l, int r) {

    for (int i = l + 1; i < r - l + 1; i++) {
        for (int j = i - 1; j >= l && v[j + 1] < v[j]; j--) {
            swap(v[j], v[j + 1]);
        }
    }
}

void Hybrid_sort(vector<unsigned int> &v, int l, int r) {
    if (l < r) {
        if (r - l > 210) {
            unsigned int m = l + (r - l) / 2;
            Merge_sort(v, l, m);
            Merge_sort(v, m + 1, r);
            Merge(v, l, r);
        } else {
            Insertion_sort(v, l, r);
        }
    }
}

void Random_vector(vector<unsigned int> &v, unsigned int n) {
    v.reserve(n);
    default_random_engine random(time(nullptr));
    uniform_int_distribution<unsigned int> dis1(0, n * n);
    for (unsigned int i = 0; i < n; ++i) {
        v.push_back(dis1(random));
    }
}

long test_Hybrid_sort(vector<unsigned int> &v, unsigned int times) {
    vector<unsigned int> tmp;
    tmp.resize(v.size());
    std::clock_t start_time = std::clock();
    for (unsigned int i = 0; i < times; ++i) {
        copy(v.begin(), v.end(), tmp.begin());
        Hybrid_sort(tmp, 0, tmp.size() - 1);
    }

    std::clock_t tot_time = std::clock() - start_time;
    return tot_time;
//    return ((double) tot_time) / (double) CLOCKS_PER_SEC;
}

long test_Merge_sort(vector<unsigned int> &v, unsigned int times) {

    vector<unsigned int> tmp;
    tmp.resize(v.size());
    std::clock_t start_time = std::clock();
    for (unsigned int i = 0; i < times; ++i) {
        copy(v.begin(), v.end(), tmp.begin());
        Merge_sort(tmp, 0, tmp.size() - 1);
    }

    std::clock_t tot_time = std::clock() - start_time;
    return tot_time;
//    return ((double) tot_time) / (double) CLOCKS_PER_SEC;
}

long test_Insertion_sort(vector<unsigned int> &v, unsigned int times) {
    vector<unsigned int> tmp;
    tmp.resize(v.size());
    std::clock_t start_time = std::clock();
    for (unsigned int i = 0; i < times; ++i) {
        copy(v.begin(), v.end(), tmp.begin());
        Insertion_sort(tmp, 0, tmp.size() - 1);
    }

    std::clock_t tot_time = std::clock() - start_time;
    return tot_time;

}




int main() {

    vector<int> nums{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210,
                     220, 230, 240, 250,
                     300, 400, 500, 600, 700, 800, 900, 1000, 1500, 2000, 3000, 4000, 10000, 20000};

    ofstream out("2.csv");
    out << "n,merge,insert,hybrid" << endl;
    for (int num : nums) {
        vector<unsigned int> v;
        Random_vector(v, num);

        cout << num << ":  " << endl;
        int times;
        if (num < 300)
            times = 20000;
        else if (num < 600)
            times = 200;
        else
            times = 20;

        long merge_time = test_Merge_sort(v, times);
        long insert_time = test_Insertion_sort(v, times);
        long hybrid_time = test_Hybrid_sort(v, times);


        cout << "\tMerge: " << merge_time << endl;

        cout << "\tInsertion: " << insert_time << endl;

        cout << "\tHybrid: " << hybrid_time << endl;

        cout << "\t   " << static_cast<double>(merge_time / static_cast<double>(insert_time)) << "\t1\t"
             << static_cast<double>(hybrid_time / static_cast<double>(insert_time)) << endl;

        out << num << setprecision(6) << "," << static_cast<double>(merge_time / static_cast<double>(insert_time))
            << ",1,"
            << static_cast<double>(hybrid_time / static_cast<double>(insert_time)) << endl;
    }



    return 0;
}
