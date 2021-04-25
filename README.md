# Splay-Tree as a Container

This project recreates the Map class of the Standard Template Library in C++ using the data structure Splay Trees. The current version of the container is generic and should work with most datatypes.  

## How to compile  
<b> DOES NOT COMPILE ON WINDOWS MINGW32 </b>  
Run the following commands - 
```shell
cd src2
make -f makefile.mk clientfile=<ENTER CLIENT FILE NAME HERE>
```  

In case no errors, execute ```./a.out``` to run the program.  

<b>EXAMPLE </b>
```shell
cd src2
make -f makefile.mk clientfile=client1.cpp
./a.out
```
### Clean Up
In order to clean the generated files, run ```./clear.sh```
