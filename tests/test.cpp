#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <numeric>
#include <cstdlib>
#include <random>
#include "../src/splaytree/splay_tree.h"
#include "../src/splaytree/splay_tree.cpp"
#include "../src/lru/lrucache.hpp"
// namespace fs = std::filesystem;
using namespace std::chrono;
using namespace std;
void get_splaytree(SplayTree<int, int> &mymap, int ops_size, vector<int> keys)
{
    int i;
    for (i = 0; i < ops_size; ++i)
    {
        mymap.at(keys[i]);
    }
}
void get_map(map<int, int> &mymap, int ops_size, vector<int> keys)
{
    int i;
    for (i = 0; i < ops_size; ++i)
    {
        mymap.at(keys[i]);
    }
}
void get_lru(cache::lru_cache<int, int> &mylru, int ops_size, vector<int> keys)
{
    int i;
    for (i = 0; i < ops_size; ++i)
    {
        mylru.get(keys[i]);
    }
}
void insert_splaytree(SplayTree<int, int> &mymap, int init_size, vector<int> keys, vector<int> values)
{
    int i;
    for (i = 0; i < init_size; ++i)
    {
        mymap.insert({keys[i], values[i]});
    }
}
void insert_map(map<int, int> &mymap, int init_size, vector<int> keys, vector<int> values)
{
    int i;
    for (i = 0; i < init_size; ++i)
    {
        mymap.insert({keys[i], values[i]});
    }
}
void insert_lru(cache::lru_cache<int, int> &mylru, int init_size, vector<int> keys, vector<int> values)
{
    int i;
    for (i = 0; i < init_size; ++i)
    {
        mylru.put(keys[i], values[i]);
    }
}
int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        std::cout << "Need 2 integer argument to execute!!\n";
        exit(1);
    }
    std::stringstream intermediate{argv[1]};
    std::stringstream intermediate2{argv[2]};
    int init_size;
    int number_of_ops;
    intermediate >> init_size;
    intermediate2 >> number_of_ops;
    SplayTree<int, int> splaytree;
    map<int, int> mymap;
    cache::lru_cache<int, int> lru(init_size);

    vector<int> init_keys(init_size);
    vector<int> init_values(init_size);
    vector<int> ops_keys(number_of_ops);
    vector<int> ops_values(number_of_ops);

    auto rand_fn = [&number_of_ops]() -> int { return rand() % number_of_ops; };

    iota(init_keys.begin(), init_keys.end(), 1);
    unsigned seed1 = system_clock::now().time_since_epoch().count();
    shuffle(init_keys.begin(), init_keys.end(), default_random_engine(seed1));

    generate(init_values.begin(), init_values.end(), rand_fn);

    iota(ops_keys.begin(), ops_keys.end(), 1);
    unsigned seed2 = system_clock::now().time_since_epoch().count();
    shuffle(ops_keys.begin(), ops_keys.end(), default_random_engine(seed2));

    generate(ops_values.begin(), ops_values.end(), rand_fn);

    auto tree_insert_start = high_resolution_clock::now();
    insert_splaytree(splaytree, init_size, init_keys, init_values);
    auto tree_insert_end = high_resolution_clock::now();

    auto lru_insert_start = high_resolution_clock::now();
    insert_lru(lru, init_size, init_keys, init_values);
    auto lru_insert_end = high_resolution_clock::now();

    auto map_insert_start = high_resolution_clock::now();
    insert_map(mymap, init_size, init_keys, init_values);
    auto map_insert_end = high_resolution_clock::now();

    auto tree_insert_duration = duration_cast<milliseconds>(tree_insert_end - tree_insert_start);
    auto lru_insert_duration = duration_cast<milliseconds>(lru_insert_end - lru_insert_start);
    auto map_insert_duration = duration_cast<milliseconds>(map_insert_end - map_insert_start);

    auto tree_get_start = high_resolution_clock::now();
    get_splaytree(splaytree, number_of_ops, ops_keys);
    auto tree_get_end = high_resolution_clock::now();

    auto lru_get_start = high_resolution_clock::now();
    get_lru(lru, number_of_ops, ops_keys);
    auto lru_get_end = high_resolution_clock::now();

    auto map_get_start = high_resolution_clock::now();
    get_map(mymap, number_of_ops, ops_keys);
    auto map_get_end = high_resolution_clock::now();

    auto tree_get_duration = duration_cast<milliseconds>(tree_get_end - tree_get_start);
    auto lru_get_duration = duration_cast<milliseconds>(lru_get_end - lru_get_start);
    auto map_get_duration = duration_cast<milliseconds>(map_get_end - map_get_start);

    ofstream testfile1;
    string filename = "bin/tests/insertion.csv";
    testfile1.open(filename, ios::app);
    if (!testfile1)
    {
        cout << "[insertion]failed to open the file\n";
    }
    testfile1 << init_size << ","
              << number_of_ops << "," << lru_insert_duration.count() << ","
              << map_insert_duration.count() << "," << tree_insert_duration.count() << "\n";
    testfile1.close();

    ofstream testfile2;
    filename = "bin/tests/retrieval.csv";
    testfile2.open(filename, ios::app);
    if (!testfile2)
    {
        cout << "[retrieval]failed to open the file\n";
    }
    testfile2 << init_size << ","
              << number_of_ops << "," << lru_get_duration.count() << ","
              << map_get_duration.count() << "," << tree_get_duration.count() << "\n";
    testfile2.close();

    return 0;
}