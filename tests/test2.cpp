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

void test_map(map<int, int> &mymap, int operations, vector<int> keys, vector<int> values)
{
    int i;
    for (i = 0; i < operations; ++i)
    {
        mymap.insert({keys[i], values[i]});
    }
}

void test_splaytree(SplayTree<int, int> &mymap, int operations, vector<int> keys, vector<int> values)
{
    int i;
    for (i = 0; i < operations; ++i)
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
    cout << "Running test for " << number_of_ops << " operations\n";
    SplayTree<int, int> splaytree;
    map<int, int> mymap;

    unsigned seed = system_clock::now().time_since_epoch().count();
    int max_base = 10000000;
    int base = 10;

    auto rand_fn = [&number_of_keys]() -> int { return rand() % number_of_keys; };
    vector<int> base_keys(base);
    vector<int> base_values(base);

    iota(base_keys.begin(), base_keys.end(), 1);
    shuffle(base_keys.begin(), base_keys.end(), default_random_engine(seed));
    generate(base_values.begin(), base_values.end(), rand_fn);
    while (base <= max_base)
    {

        base *= 10;
    }

    return 0;
}