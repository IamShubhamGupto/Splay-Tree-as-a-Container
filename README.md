# Splay-Tree as a Container

This project recreates the Map class of the Standard Template Library in C++ using the data structure Splay Trees. The current version of the container is generic and should work with most datatypes. 

## How to compile
<details>
  <summary><b> Linux & Mac </b> </summary>
    
  ```shell
  git clone https://github.com/IamShubhamGupto/Splay-Tree-as-a-Container.git
  make -f makefile.mk clientfile=<ENTER PATH TO CLIENT FILE NAME HERE>
  ./a.out
  ```  

  <b>EXAMPLE </b>
  
  ```shell
  make -f makefile.mk clientfile=clientfiles/client1.cpp
  ./bin/a.out
  ```
  ### Clean Up
  In order to clean the generated files, run ```make -f makefile.mk clean```.
</details>  


## Member Types
| <b> Member Type </b> | <b> Definition </b> |
| ------------- | ------------- |
| root_ | stores root node of the splay tree  |
| iterator  | a bidirectional iterator to mapped_type.|
| const_iterator  | a bidirectional iterator to constant mapped_type. |
| reverse_iterator  | a bidirectional iterator to mapped_type.|
| const_reverse_iterator  | a bidirectional iterator to constant mapped_type.|

## Member Functions
