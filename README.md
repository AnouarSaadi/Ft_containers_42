# Ft_containers_42

## About

Ft_containers is a project of the mandatory part of the cursus.
It's only made in C++ and was about recoding some containers from the STL.

In order to succeed, a good comprehension of how **templates**, **iterators**, **containers** and 
**algorithms** work was necessary. Of course, STL is not allowed. That means 
you cannot use \<iterator\> or even \<utility\>. 

Here are the specificities of the five containers:

- :arrow_right: **Vector:** a dynamic array that allows insertion at the end of the container. Elements can be easily access thanks with the corresponding index, but it's not the most optimal container if a lot of insertion / deletion are needed.
- :arrow_right: **Map:** a sorted container using an Red-Black tree (auto-equilibrates itself to optimize the time to find a value in the tree), in order to store the data like in a dictionnary (a key associated to its value).
- :arrow_right: **Stack:** a container adaptator (LIFO, last in first out).
- :arrow_right: **Set:** a container that store unique elements following a specific order,is implimented as Red-Black tree (auto-equilibrates itself to optimize the time to find a value in the tree).

All my containers use an allocator to manage properly their memory, iterators to access their data, and handle the same constructors / methods than the containers from the STL in C++98.

## Tester

There is a main.cpp file in the root directory of the project, it contains the tests for all the containers.
Run `/bin/sh script.sh` for get the output files of the tests(`ft_out`, `std_out`).