import os
import sys
import getopt
import matplotlib.pyplot as plt
import numpy as np
DEBUG = 0


def main():

    os.system(f"make clientfile=tests/test.cpp")
    filename1 = r"bin/tests/insertion.csv"
    filename2 = r"bin/tests/retrieval.csv"
    if(not os.path.exists("bin/tests")):
        os.system(f"mkdir bin/tests && touch {filename1} && touch {filename2}")

    size = 10
    max_size = 10000000
    ops = 10
    max_ops = 10000000

    while size <= max_size:
        ops = 10
        os.system(
            f"echo \"initial_size,operations,lru,std::map,splaytree\" >> {filename1}")
        os.system(
            f"echo \"initial_size,operations,lru,std::map,splaytree\" >> {filename2}")
        print(f"Testing with init size {size}")
        while ops <= size and ops <= max_ops:
            os.system(f"./bin/a.out {size} {ops}")
            print(f"\tWith {ops} operations\n")
            ops *= 10
        size *= 10


if __name__ == '__main__':
    main()
