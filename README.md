# Splay-Tree as a Container

This project recreates the Map class of the Standard Template Library in C++ using the data structure Splay Trees. The current version of the container is generic and should work with most datatypes. 

## How to Compile
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
| <b> Member Type </b>    | <b> Definition </b>                               |
| -------------           | -------------                                     |
| key_type                | template type of the key in the pair              |
| mapped_type             | template type of the value in the pair            |
| root_                   | stores root node of the splay tree.               |
| iterator                | a bidirectional iterator to mapped_type.          |
| const_iterator          | a bidirectional iterator to constant mapped_type. |
| reverse_iterator        | a bidirectional iterator to mapped_type.          |
| const_reverse_iterator  | a bidirectional iterator to constant mapped_type. |

## Member Functions


| <b> Member Function </b>    | <b> Definition </b>                           |
| -------------           | -------------                                     |
| (constructor)           | Splay tree constuctor.                            |
| (destructor)            | Splay tree destructor.                            |
| operator=               | Copy container contents.                          |
|               |                         |
| <b> Iterators </b>      |                                   |
|               |                         |
| begin                   | Return iterator to first in-order element.               |
| end                     | Return iterator to beyond-the-last element.              |
| cbegin                  | Return a constant iterator to first in-order element.    |
| cend                    | Return a constant iterator to beyond-the-last element.   |
| rbegin                  | Return iterator to last in-order element.                |
| rend                    | Return iterator to beyond-the-first element.             |
| crbegin                 | Return a constant iterator to last in-order element.     |
| crend                   | Return a constant iterator to beyond-the-first element.  |
|               |                         |
| <b> Element Access </b> |                                                       |
|               |                         |
| operator[]              | Access element using key. If not present, (default) value is inserted.      |
| at                      | Access element using key. If not preseed, out_of_range exception is thrown. |
|               |                         |
| <b> Modifiers </b>      |                                                                                                        |
|               |                         |
| insert                  | Insert new key-value pair into the tree. Incase key already exists, update value and return an iterator to inserted element.  |
| erase                   | Delete a key-value pair based on key. If key does not exist, do nothing.                                                      |
| clear                   | Free the entire splay tree.                                                                                                   |
|               |                         |
| <b> Operations </b>     |                                                                                    |
|               |                         |
| find                    | Search for a key-value pair based on a given key. Return an iterator to pair if found else return end()     |
| printTree               | Visually print the splay tree.                                                                              |
