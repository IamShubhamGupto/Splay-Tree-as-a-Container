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
#include "../src/splay_tree.h"
#include "../src/splay_tree.cpp"
// namespace fs = std::filesystem;
using namespace std::chrono;
using namespace std;

void insert_map(map<int, int> &mymap, int begin, int end, vector<int> keys, vector<int> values)
{
    int i;
    for (i = begin; i < end; ++i)
    {
        mymap.insert({keys[i], values[i]});
    }
}

void insert_splaytree(SplayTree<int, int> &mymap, int begin, int end, vector<int> keys, vector<int> values)
{
    int i;
    for (i = begin; i < end; ++i)
    {
        mymap.insert({keys[i], values[i]});
    }
}

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        cout << "Need 2 integer argument to execute!!\n";
        exit(1);
    }
    stringstream intermediate{argv[1]};
    stringstream intermediate2{argv[2]};
    int number_of_ops;
    int number_of_keys;
    intermediate >> number_of_ops;
    intermediate2 >> number_of_keys;
    cout << "Running test for " << number_of_ops << " operation(s)\n";
    SplayTree<int, int> splaytree;
    map<int, int> mymap;

    vector<int> all_keys(number_of_ops + number_of_keys);
    vector<int> all_values(number_of_ops + number_of_keys);

    unsigned seed = system_clock::now().time_since_epoch().count();

    auto rand_fn = [&number_of_ops]() -> int { return rand() % number_of_ops; };

    iota(all_keys.begin(), all_keys.end(), 1);
    shuffle(all_keys.begin(), all_keys.end(), default_random_engine(seed));
    generate(all_values.begin(), all_values.end(), rand_fn);

    insert_map(mymap, 0, number_of_keys, all_keys, all_values);
    insert_splaytree(splaytree, 0, number_of_keys, all_keys, all_values);

    auto map_start = high_resolution_clock::now();
    insert_map(mymap, number_of_keys, number_of_ops + number_of_keys, all_keys, all_values);
    auto map_end = high_resolution_clock::now();

    auto map_duration = duration_cast<microseconds>(map_end - map_start);

    // cout << "=====FINISHED MAP TEST=====\n\n";

    // cout << "=====BEGINNING SPLAYTREE TEST=====\n";

    auto tree_start = high_resolution_clock::now();
    insert_splaytree(splaytree, number_of_keys, number_of_ops + number_of_keys, all_keys, all_values);
    auto tree_end = high_resolution_clock::now();

    auto tree_duration = duration_cast<microseconds>(tree_end - tree_start);

    // cout << "=====FINISHED SPLAYTREE TEST=====\n";

    ofstream testfile;
    string filename = "bin/tests/test2.csv";
    testfile.open(filename, ios::app);
    if (!testfile)
    {
        cout << "failed to open the file\n";
    }
    testfile << number_of_ops << ","
             << number_of_keys << "," << map_duration.count() << "," << tree_duration.count() << "\n";
    testfile.close();
    return 0;
}