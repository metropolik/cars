# Coding Challenge: Cars by Hannes Möls

This C++ implementation solves the car coding challenge. It is build with CMake and should compile on every platform. It contains a command-processor/interpreter which can be used to either process commands entered in interactive mode or commands in a file.
The interpreter support seven commands which reflect the five different problem types in the exercise.

## Usage
To input a graph the command
```
GRAPH <Node List in the format "AB1, BA2">
```
is used.

The command to solve problem 1.-5. is
```
DIST <List of nodes in the format "A-B-C">
```

The command to solve problem 6. is
```
TRIP_MAX_STOPS <START_NODE> <END_NODE> <MAX_STOPS>
```

The command to solve problem 7. is
```
TRIP_EQUAL_STOPS <START_NODE> <END_NODE> <MAX_STOPS>
```

The command to solve problem 8. and 9. is
```
SHORT <START_NODE> <END_NODE>
```

The command to solve problem 10. is
```
TRIP_MAX_DIST <START_NODE> <END_NODE> <MAX_DIST>
```

To quit the interactive mode type
```
QUIT
```

All problems of the exercise sheet can be processed by typing
```
GRAPH AB5, BC4, CD8, DC8, DE6, AD5, CE2, EB3, AE7
DIST A-B-C
DIST A-D
DIST A-D-C
DIST A-E-B-C-D
DIST A-E-D
TRIP_MAX_STOPS C C 3
TRIP_EQUAL_STOPS A C 4
SHORT A C
SHORT B B
TRIP_MAX_DIST C C 30
QUIT
```

After building the `Cars` executable like described in chapter Building, one can either launch `Cars` directly on the command line to enter interactive mode or pass a file path as argument.
If the file does not contain the `QUIT` command, the interpreter will resume interactive mode after processing the commands in the file.
Example with file on Windows: `Cars.exe test_files/test_inputs.txt`. A file with all the above commands is located in `test_files/test_file.txt`.
The program output would then look like this:
```
cmd: "GRAPH" args: "AB5, BC4, CD8, DC8, DE6, AD5, CE2, EB3, AE7"
cmd: "DIST" args: "A-B-C"
9
cmd: "DIST" args: "A-D"
5
cmd: "DIST" args: "A-D-C"
13
cmd: "DIST" args: "A-E-B-C-D"
22
cmd: "DIST" args: "A-E-D"
NO SUCH ROUTE
cmd: "TRIP_MAX_STOPS" args: "C C 3"
2
cmd: "TRIP_EQUAL_STOPS" args: "A C 4"
3
cmd: "SHORT" args: "A C"
9
cmd: "SHORT" args: "B B"
9
cmd: "TRIP_MAX_DIST" args: "C C 30"
7
cmd: "QUIT" args: ""
Goodbye!
```

## Building on command line
Building is done with git, cmake and a compiler of your choice e.g., gcc, visual studio. Please make sure to use one of the latest versions of cmake, though older versions will probably work fine too.
CMake can be downloaded from: [https://cmake.org/](https://cmake.org/)
1. Clone the repo
```
git clone https://github.com/metropolik/cars.git
```

2. Go into the repo directory and open a terminal or cmd. Type:
```
mkdir build
cd build
cmake ..
```
Even when not specifying a compiler cmake should pick a suitable one.

3. Compile by going into the parent directory of build with `cd ..` and then compile with
```
cmake --build build
```
This creates the interpreter executable and the tests. On Windows the executable is then located in `build/Debug/Cars.exe`. It does not have any dependencies and can be copied or moved anywhere.

## Testing
The tests are individual executables which get compiled automatically, too. Each test is a group of certain tests. All tests can be launched and tested with
```
cmake -E env CTEST_OUTPUT_ON_FAILURE=1 cmake --build build --target RUN_TESTS
```
To execute this command you need to be in the parent directory of build. If you followed the previous section, you already are.
Output of this command on windows looks like:
```
Microsoft (R) Build Engine version 16.7.0+b89cb5fde for .NET Framework   
Copyright (C) Microsoft Corporation. All rights reserved.                
                                                                         
  Test project C:/Users/Hans/Desktop/daimler_coding/cpp/build            
      Start 1: constructors                                              
  1/6 Test #1: constructors .....................   Passed    0.00 sec   
      Start 2: path_dist                                                 
  2/6 Test #2: path_dist ........................   Passed    0.00 sec   
      Start 3: depth_first_search                                        
  3/6 Test #3: depth_first_search ...............   Passed    0.01 sec   
      Start 4: dijkstra                                                  
  4/6 Test #4: dijkstra .........................   Passed    0.01 sec   
      Start 5: command_processor                                         
  5/6 Test #5: command_processor ................   Passed    0.00 sec   
      Start 6: utils                                                     
  6/6 Test #6: utils ............................   Passed    0.00 sec   
                                                                         
  100% tests passed, 0 tests failed out of 6                             
                                                                         
  Total Test time (real) =   0.04 sec                                    
```

## Project Structure
The project is structured into five classes plus main function and tests.
* `command_processor` implements the interactive interpreter and the processing of commands in files.
* `directed_graph` implements the base of an directed graph and primitive functions as well as the `DIST` command backbone. The graph is stored as an adjacency list.
* `depth_first_search` implements a variety of the depth first search graph algorithms which are used for the `TRIP_MAX_STOPS`, `TRIP_EQUAL_STOPS` and `TRIP_MAX_DIST` commands. As an argument it requires a directed graph on which it works.
* `dijkstra` implements a variation of dijkstra's path finding algorithm, required for the `SHORT` command i.e. the 8. and 9. problem. It requires a graph as an argument when instantiating.
* `utils` provides an implementation for string splitting.

The problems only require the number of possible paths or only their length. The paths/routes themselves are not required. However, they could be easily accessed with some small modifactions, as the actual paths are intermediate result.
The backbone for all graph processing commands discard the intermediate results and only the required values are printed on the terminal.

### Tests
There are six test executables which test the example of the exercise sheet as well as edge cases. The executables of the tests can also be execute manually and will return a negative value on failure. When executing manually, the output is not hidden like when launching via cmake.

## Problem Assumption
1. Edge weights/length are at least 1 or larger. As cycles are allowed, negative weights or 0 weights can lead to 0-weighted-cycles or even negative-weighted-cycles which would interfere with the logic of the algorithms for the 'TRIP_MAX_DIST' and 'SHORT' commands.
2. As shown in the exercise sheets the names of graph nodes are all letters of the alphabet. While this limits the maximum number of nodes, the underlying implementation does not exploit this limitation. If more nodes would be required, only the graph parser would need to be changed.
3. Edge weights are integers.



