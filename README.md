# Splay-Tree as a Container

This project recreates the Map class of the Standard Template Library in C++ using the data structure Splay Trees. The current version of the container is generic and should work with most datatypes. 

## 1. How to Compile
<details>
  <summary><b> 1.1. Linux & Mac </b> </summary>
    
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


## 2. Member Types
| <b> Member Type </b>    | <b> Definition </b>                               |
| -------------           | -------------                                     |
| root_                   | stores root node of the splay tree.               |
| iterator                | a bidirectional iterator to mapped_type.          |
| const_iterator          | a bidirectional iterator to constant mapped_type. |
| reverse_iterator        | a bidirectional iterator to mapped_type.          |
| const_reverse_iterator  | a bidirectional iterator to constant mapped_type. |

## 3. Member Functions
| <b> Member Function </b>    | <b> Definition </b>                           |
| -------------           | -------------                                     |
| (constructor)           | splay tree constuctor.                            |
| (destructor)            | asplay tree destructor.                           |
| operator=               | copy container contents.                          |

| <b> Iterators </b>      | <b> Definition </b>                               |
| -------------           | -------------                                     |
| begin                   | return iterator to first in-order element.                    |
| end                     | return iterator to beyond-the-last element.                   |
| cbegin                  | return a constant iterator to first in-order element.        |
| cend                    | return a constant iterator to beyond-the-last element.       |
| rbegin                  | return iterator to last in-order element.        |
| rend                    | return iterator to beyond-the-first element.       |
| crbegin                 | return a constant iterator to last in-order element.       |
| crend                   | return a constant iterator to beyond-the-first element.       |
