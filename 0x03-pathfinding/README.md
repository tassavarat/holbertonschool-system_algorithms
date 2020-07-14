# 0x03. C - Pathfinding

## Requirements
* Allowed editors: vi, vim, emacs
* All your files will be compiled on Ubuntu 14.04 LTS
* Your programs and functions will be compiled with gcc 4.8.4 using the flags -Wall -Werror -Wextra and -pedantic
* All your files should end with a new line
* A README.md file, at the root of the folder of the project, is mandatory
* Your code should use the Betty style. It will be checked using [betty-style.pl](https://github.com/holbertonschool/Betty/blob/master/betty-style.pl) and [betty-doc.pl](https://github.com/holbertonschool/Betty/blob/master/betty-doc.pl)
* You are not allowed to use global variables
* No more than 5 functions per file
* You are allowed to use the standard library
* In the following examples, the main.c files are shown as examples. You can use them to test your functions, but you don’t have to push them to your repo (if you do we won’t take them into account). We will use our own main.c files at compilation. Our main.c files might be different from the one shown in the examples
* The prototypes of all your functions should be included in your header file called pathfinding.h
* Don’t forget to push your header file
* All your header files should be include guarded

### [0. Backtracking - Array](./0-backtracking_array.c)
Write a function that searches for the first path from a starting point to a target point within a two-dimensional array.

* Prototype: queue_t *backtracking_array(char **map, int rows, int cols, point_t const *start, point_t const *target);
* Where:
	* map is the pointer to a read-only two-dimensional array
		* A 0 represents a walkable cell
		* A 1 represents a blocked cell
	* rows and cols are respectively the number of rows and columns of map
	* start stores the coordinates of the starting point
	* target stores the coordinates of the target point
* Your function must return a queue, in which each node is a point in the path from start to target (See example)
* You’ll have to use recursive backtracking to find the first working path from start to target
* For each visited cell, you’ll have to explore neighbour cells in the following order:
	* RIGHT
	* BOTTOM
	* LEFT
	* TOP
* You’ll have to print each visited cell as in the example below

```
alex@~/0x03-pathfinding$ gcc -o 0-backtracking_array -Wall -Wextra -Werror -pedantic 0-main.c 0-backtracking_array.c -lqueues
alex@~/0x03-pathfinding$ ./0-backtracking_array
Checking coordinates [0, 13]
Checking coordinates [1, 13]
Checking coordinates [2, 13]
Checking coordinates [3, 13]
Checking coordinates [4, 13]
Checking coordinates [5, 13]
Checking coordinates [6, 13]
Checking coordinates [7, 13]
Checking coordinates [7, 12]
Checking coordinates [7, 11]
Checking coordinates [8, 11]
Checking coordinates [9, 11]
Checking coordinates [6, 11]
Checking coordinates [5, 11]
Checking coordinates [4, 11]
Checking coordinates [3, 11]
Checking coordinates [3, 10]
Checking coordinates [3, 9]
Checking coordinates [4, 9]
Checking coordinates [5, 9]
Checking coordinates [6, 9]
Checking coordinates [7, 9]
Checking coordinates [5, 8]
Checking coordinates [5, 7]
Checking coordinates [6, 7]
Checking coordinates [7, 7]
Checking coordinates [4, 7]
Checking coordinates [3, 7]
Checking coordinates [3, 6]
Checking coordinates [3, 5]
Checking coordinates [4, 5]
Checking coordinates [5, 5]
Checking coordinates [6, 5]
Checking coordinates [7, 5]
Checking coordinates [8, 5]
Checking coordinates [9, 5]
Checking coordinates [9, 6]
Checking coordinates [9, 7]
Checking coordinates [9, 8]
Checking coordinates [9, 9]
Checking coordinates [10, 9]
Checking coordinates [11, 9]
Checking coordinates [11, 10]
Checking coordinates [11, 11]
Checking coordinates [12, 11]
Checking coordinates [13, 11]
Checking coordinates [14, 11]
Checking coordinates [15, 11]
Checking coordinates [13, 12]
Checking coordinates [13, 13]
Checking coordinates [13, 14]
Checking coordinates [13, 15]
Checking coordinates [12, 13]
Checking coordinates [11, 13]
Checking coordinates [11, 14]
Checking coordinates [11, 15]
Checking coordinates [10, 13]
Checking coordinates [9, 13]
Checking coordinates [9, 14]
Checking coordinates [9, 15]
Checking coordinates [8, 15]
Checking coordinates [7, 15]
Checking coordinates [7, 16]
Checking coordinates [7, 17]
Checking coordinates [7, 18]
Checking coordinates [7, 19]
Checking coordinates [8, 19]
Checking coordinates [9, 19]
Checking coordinates [10, 19]
Checking coordinates [11, 19]
Checking coordinates [12, 19]
Checking coordinates [13, 19]
Checking coordinates [14, 19]
Checking coordinates [15, 19]
Checking coordinates [9, 18]
Checking coordinates [9, 17]
Checking coordinates [10, 17]
Checking coordinates [11, 17]
Checking coordinates [12, 17]
Checking coordinates [13, 17]
Checking coordinates [14, 17]
Checking coordinates [15, 17]
Checking coordinates [16, 17]
Checking coordinates [17, 17]
Checking coordinates [18, 17]
Checking coordinates [19, 17]
Checking coordinates [19, 18]
Checking coordinates [19, 19]
Checking coordinates [18, 19]
Checking coordinates [17, 19]
Checking coordinates [17, 16]
Checking coordinates [17, 15]
Checking coordinates [18, 15]
Checking coordinates [19, 15]
Checking coordinates [16, 15]
Checking coordinates [15, 15]
Checking coordinates [15, 14]
Checking coordinates [15, 13]
Checking coordinates [16, 13]
Checking coordinates [17, 13]
Checking coordinates [18, 13]
Checking coordinates [19, 13]
Checking coordinates [19, 12]
Checking coordinates [19, 11]
Checking coordinates [18, 11]
Checking coordinates [17, 11]
Checking coordinates [17, 10]
Checking coordinates [17, 9]
Checking coordinates [16, 9]
Checking coordinates [15, 9]
Checking coordinates [14, 9]
Checking coordinates [13, 9]
Checking coordinates [13, 8]
Checking coordinates [13, 7]
Checking coordinates [12, 7]
Checking coordinates [11, 7]
Checking coordinates [11, 6]
Checking coordinates [11, 5]
Checking coordinates [11, 4]
Checking coordinates [11, 3]
Checking coordinates [12, 3]
Checking coordinates [13, 3]
Checking coordinates [13, 2]
Checking coordinates [13, 1]
Checking coordinates [12, 1]
Checking coordinates [11, 1]
Checking coordinates [10, 1]
Checking coordinates [9, 1]
Checking coordinates [8, 1]
Checking coordinates [7, 1]
Checking coordinates [6, 1]
Checking coordinates [5, 1]
Checking coordinates [4, 1]
Checking coordinates [3, 1]
Checking coordinates [3, 2]
Checking coordinates [3, 3]
Checking coordinates [2, 3]
Checking coordinates [1, 3]
Checking coordinates [1, 2]
Checking coordinates [1, 1]
Checking coordinates [19, 10]
Checking coordinates [19, 9]
Checking coordinates [19, 8]
Checking coordinates [19, 7]
Checking coordinates [18, 7]
Checking coordinates [17, 7]
Checking coordinates [16, 7]
Checking coordinates [15, 7]
Checking coordinates [15, 6]
Checking coordinates [15, 5]
Checking coordinates [14, 5]
Checking coordinates [13, 5]
Checking coordinates [15, 4]
Checking coordinates [15, 3]
Checking coordinates [16, 3]
Checking coordinates [17, 3]
Checking coordinates [17, 2]
Checking coordinates [17, 1]
Checking coordinates [18, 1]
Checking coordinates [19, 1]
Checking coordinates [19, 2]
Checking coordinates [19, 3]
Checking coordinates [19, 4]
Checking coordinates [19, 5]
Checking coordinates [18, 5]
Checking coordinates [17, 5]
Checking coordinates [16, 1]
Checking coordinates [15, 1]
Checking coordinates [9, 4]
Checking coordinates [9, 3]
Checking coordinates [8, 3]
Checking coordinates [7, 3]
Checking coordinates [6, 3]
Checking coordinates [5, 3]
Checking coordinates [3, 14]
Checking coordinates [3, 15]
Checking coordinates [2, 15]
Checking coordinates [1, 15]
Checking coordinates [1, 16]
Checking coordinates [1, 17]
Checking coordinates [2, 17]
Checking coordinates [3, 17]
Checking coordinates [4, 17]
Checking coordinates [5, 17]
Checking coordinates [5, 16]
Checking coordinates [5, 15]
Checking coordinates [1, 18]
Checking coordinates [1, 19]
Checking coordinates [2, 19]
Checking coordinates [3, 19]
Checking coordinates [4, 19]
Checking coordinates [5, 19]
Checking coordinates [5, 20]
Path found:
 [0, 13]
 [1, 13]
 [2, 13]
 [3, 13]
 [3, 14]
 [3, 15]
 [2, 15]
 [1, 15]
 [1, 16]
 [1, 17]
 [1, 18]
 [1, 19]
 [2, 19]
 [3, 19]
 [4, 19]
 [5, 19]
 [5, 20]
alex@~/0x03-pathfinding$
```