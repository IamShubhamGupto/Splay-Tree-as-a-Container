import os
import sys
import getopt
import matplotlib.pyplot as plt

DEBUG = 0


def main():
    # read arguments

    argumentList = sys.argv[1:]
    if DEBUG:
        print("argument list", argumentList)
    # Options
    options = "t:m:k:h"
    # Long options
    long_options = ["testtype=", "max_ops=", "max_keys=", "help"]
    testtype = -1
    max_number_of_operations = -1
    max_number_keys = -1
    try:
        arguments, values = getopt.getopt(argumentList, options, long_options)
        # checking each argument
        for currentArgument, currentValue in arguments:
            if currentArgument in ("-h", "--help"):
                print(
                    "Usage: python3 tests/run_test.py [options] {-t | --testtype}")
                print("\nRequired for execution:")
                print(
                    "\t-t, --testtype <test types>\n\t\tSelect type of test to run"
                )
                print("\n\t<test types>:")
                print("\n\t\t1 - run insertion, delete and updation test at different number of operations")
                print("\n\t\t2 - run insertion test at at different number of operations")
                print("\n\t\t3 - run deletion test at different number of operations")
                print("\n\t\t4 - run updation test at different number of operations")
                print("\noptions:")
                print(
                    "\t-m, --max_ops <maximum operations>\n\t\tMaximum number of operations - insertions/updates/deletions to performed.\n\t\tDefault=1000")
                print()
                print(
                    "\t-k, --max_keys <maximum keys>\n\t\tMaximum number of unique keys stored in container.\n\t\tDefault = 100"
                )
                print()
                print(
                    "\t-h, --help \n\t\tDisplay Help"
                )
                sys.exit(0)
            if currentArgument in ("-t", "testtype"):
                testtype = int(currentValue)

            elif currentArgument in ("-m", "--max_ops"):
                max_number_of_operations = int(currentValue)
                if(max_number_of_operations <= 0):
                    raise Exception(
                        "[-m] or [--max_ops] argument should be greater than or equal to 1")

            elif currentArgument in ("-k", "--max_keys"):
                max_number_keys = int(currentValue)
                if(max_number_keys <= 0):
                    raise Exception(
                        "[-k] or [--max_keys] argument should be greater than or equal to 1")

            
    except getopt.error as err:
        # output error, and return with an error code
        print(str(err))
    if testtype == -1:
        raise Exception("[-t] or [--testtype] argument is required")
    if DEBUG:
        print(testtype)
        print(max_number_of_operations)

    if(not os.path.exists("bin/out")):
        os.system("mkdir bin/out")

    # compile the testfile
    if(testtype == 1):
        os.system(f"make -f makefile.mk clientfile=tests/test1.cpp")
    elif(testtype == 2):
        os.system(f"make -f makefile.mk clientfile=tests/test2.cpp")
    elif(testtype == 3):
        os.system(f"make -f makefile.mk clientfile=tests/test3.cpp")
    elif(testtype == 4):
        os.system(f"make -f makefile.mk clientfile=tests/test4.cpp")
    else:
        raise Exception(
                        "Invalid test-type selected")
    # run test cases
    i = 1
    while(i <= max_number_of_operations):
        os.system(f"./bin/a.out {i} {max_number_keys}")
        i = i*10

    # print logs
    logile = ""
    try:
        logfile = open(r'out/logs.csv', 'r')
    except:
        print("Cannot find logs.csv!!")
    lines = logfile.readlines()
    operations = []
    map_time = []
    tree_time = []
    for line in lines:
        data = line.split(",")
        operations.append(int(data[0]))
        map_time.append(int(data[1]))
        tree_time.append(int(data[2][:-1]))

    if DEBUG:
        print(operations)
        print(map_time)
        print(tree_time)
    plt.plot(operations, map_time, '-', color='r')
    plt.plot(operations, tree_time, '--', color='g')
    plt.legend(["STL::Map", "SplayTree"])
    plt.ylabel("Time in microseconds")
    plt.xlabel("Number of Operations")
    plt.savefig("out/comparison.png")
    print("\nsaved comparison plot to out/comparison.png")


if __name__ == '__main__':
    main()
