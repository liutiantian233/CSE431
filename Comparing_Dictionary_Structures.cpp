#include <iostream>
#include <vector>
#include <bitset>
#include <ctime>
#include <regex>
#include <random>
#include <iomanip>
#include <fstream>
#include <map>
#include <unordered_map>


using namespace std;


void Random_vector(vector<unsigned int> &v, unsigned int n) {
    v.reserve(n);
    default_random_engine random(time(nullptr));
    uniform_int_distribution<unsigned int> dis1(0, n * n);
    for (unsigned int i = 0; i < n; ++i) {
        v.push_back(dis1(random));
    }
}


long test_hashmap_insert(vector<unsigned int> &v, unsigned int times) {
    unordered_multimap<int, int> hash;

    std::clock_t start_time = std::clock();
    for (unsigned int i = 0; i < times; ++i) {
        hash.clear();
        for (unsigned int &e :v) {
            hash.insert(pair<unsigned int, unsigned int>(e, e));
        }
    }
    std::clock_t tot_time = std::clock() - start_time;
    return tot_time;
}

long test_AVL_insert(vector<unsigned int> &v, unsigned int times) {
    multimap<unsigned int, unsigned int> avl;

    std::clock_t start_time = std::clock();
    for (unsigned int i = 0; i < times; ++i) {
        avl.clear();
        for (unsigned int &e :v) {
            avl.insert(pair<unsigned int, unsigned int>(e, e));
        }
    }
    std::clock_t tot_time = std::clock() - start_time;
    return tot_time;
}


long test_hashmap_delete(vector<unsigned int> &v, unsigned int times) {
    unordered_multimap<int, int> hash;

    default_random_engine random(time(nullptr));
    uniform_int_distribution<unsigned int> dis1(0, v.size());
    std::clock_t tot_time = 0;
    for (unsigned int i = 0; i < times; ++i) {
        hash.clear();
        for (unsigned int &e :v) {
            hash.insert(pair<unsigned int, unsigned int>(e, e));
        }
        std::clock_t start_time = std::clock();

        for (int j = 0; j < v.size() / 2; ++j) {
            hash.erase(dis1(random));
        }

        tot_time += (std::clock() - start_time);
    }

    return tot_time;
}

long test_AVL_delete(vector<unsigned int> &v, unsigned int times) {
    multimap<unsigned int, unsigned int> avl;

    default_random_engine random(time(nullptr));
    uniform_int_distribution<unsigned int> dis1(0, v.size());
    std::clock_t tot_time = 0;
    for (unsigned int i = 0; i < times; ++i) {
        avl.clear();
        for (unsigned int &e :v) {
            avl.insert(pair<unsigned int, unsigned int>(e, e));
        }
        std::clock_t start_time = std::clock();

        for (int j = 0; j < v.size() / 2; ++j) {
            avl.erase(dis1(random));
        }

        tot_time += (std::clock() - start_time);
    }

    return tot_time;
}


int main() {

    vector<int> nums{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210,
                     220, 230, 240, 250,
                     300, 400, 500, 600, 700, 800, 900, 1000, 1500, 2000, 3000, 4000, 10000, 20000};

    ofstream out("3.csv");
    out << "n,avl_insert,hash_insert,n,avl_delete,hash_delete" << endl;
    for (int num : nums) {
        vector<unsigned int> v;
        Random_vector(v, num);


        int times = 20000;

        long avl_insert = test_AVL_insert(v, times);
        long hash_insert = test_hashmap_insert(v, times);
        long hash_delete = test_hashmap_delete(v, times);
        long avl_delete = test_AVL_delete(v, times);

        cout << num << ":" << avl_insert
             << "," << avl_delete
             << "," << hash_insert
             << "," << hash_delete
             << endl;
        out << num << setprecision(6) << "," << static_cast<double>(avl_insert / static_cast<double>(hash_insert))
            << ",1,";
        out << num << setprecision(6) << "," << static_cast<double>(avl_delete / static_cast<double>(hash_delete))
            << ",1" << endl;


    }

    return 0;
}
