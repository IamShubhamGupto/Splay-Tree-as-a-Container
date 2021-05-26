#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <filesystem>
#include <cstdlib>
#include "../src/splay_tree.h"
#include "../src/splay_tree.cpp"
// namespace fs = std::filesystem;
using namespace std::chrono;
using namespace std;

void test_map(map<int, int> &mymap, vector<int> operations, vector<int> keys, vector<int> values)
{
    int i;
    for (i = 0; i < operations.size(); ++i)
    {
        switch (operations[i])
        {
        //insertions
        case 0:
            mymap[keys[i]] = values[i];
            break;
        //access pairs
        case 1:
            mymap.find(keys[i]);
            break;
        //delete
        case 2:
            mymap.erase(keys[i]);
            break;
        }
    }
}

void test_splaytree(SplayTree<int, int> &mymap, vector<int> operations, vector<int> keys, vector<int> values)
{
    int i;
    for (i = 0; i < operations.size(); ++i)
    {
        switch (operations[i])
        {
        //insertions
        case 0:
            mymap[keys[i]] = values[i];
            break;
        //access pairs
        case 1:
            mymap.find(keys[i]);
            break;
        //delete
        case 2:
            mymap.erase(keys[i]);
            break;
        }
    }
}
int main(int argc, char *argv[])
{
    //ios_base::sync_with_stdio(false);
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
    // cout << "Enter number of operations: \n";
    // cin >> number_of_ops;
    SplayTree<int, int> splaytree;
    map<int, int> mymap;

    vector<int> operations(number_of_ops);
    vector<int> keys(number_of_ops);
    vector<int> values(number_of_ops);

    auto op_fn = []() -> int { return rand() % 3; };
    auto rand_fn = [&number_of_keys]() -> int { return rand() % number_of_keys; };

    generate(operations.begin(), operations.end(), op_fn);
    generate(keys.begin(), keys.end(), rand_fn);
    generate(values.begin(), values.end(), rand_fn);

    // cout << "=====BEGINNING MAP TEST=====\n";

    auto map_start = high_resolution_clock::now();
    test_map(mymap, operations, keys, values);
    auto map_end = high_resolution_clock::now();

    auto map_duration = duration_cast<microseconds>(map_end - map_start);

    // cout << "=====FINISHED MAP TEST=====\n\n";

    // cout << "=====BEGINNING SPLAYTREE TEST=====\n";

    auto tree_start = high_resolution_clock::now();
    test_splaytree(splaytree, operations, keys, values);
    auto tree_end = high_resolution_clock::now();

    auto tree_duration = duration_cast<microseconds>(tree_end - tree_start);

    // cout << "=====FINISHED SPLAYTREE TEST=====\n";

    ofstream testfile;
    string filename = "bin/tests/test1.csv";
    testfile.open(filename, ios::app);
    if (!testfile)
    {
        cout << "failed to open the file\n";
    }
    testfile << number_of_ops << "," << map_duration.count() << "," << tree_duration.count() << "\n";
    testfile.close();
    //cout << "Current path is " << fs::current_path() << '\n';
    return 0;
}