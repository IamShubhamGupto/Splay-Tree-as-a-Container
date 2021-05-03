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
    options = "t:m:k:"
    # Long options
    long_options = ["testfile=", "max_ops=", "max_keys="]
    testfile = ""
    max_number_of_operations = 0
    max_number_keys = 0
    try:
        arguments, values = getopt.getopt(argumentList, options, long_options)
        # checking each argument
        for currentArgument, currentValue in arguments:

            if currentArgument in ("-t", "--testfile"):
                testfile = currentValue

            elif currentArgument in ("-m", "--max_ops"):
                max_number_of_operations = int(currentValue)

            elif currentArgument in ("-k", "--max_keys"):
                max_number_keys = int(currentValue)
    except getopt.error as err:
        # output error, and return with an error code
        print(str(err))

    if DEBUG:
        print(testfile)
        print(max_number_of_operations)

    # compile the testfile
    os.system(f"make -f makefile.mk clientfile={testfile}")

    # run test cases
    i = 1
    while(i <= max_number_of_operations):
        os.system(f"./bin/a.out {i} {max_number_keys}")
        i = i*10

    # print logs
    logfile = open(r'logs.csv', 'r')
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
    plt.savefig("comparision.png")


if __name__ == '__main__':
    main()
