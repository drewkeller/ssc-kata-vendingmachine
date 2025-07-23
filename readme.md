# Project

This project is an implementation of the Vending Machine kata found here: https://github.com/ardalis/kata-catalog/blob/main/katas/VendingMachine.md

# GoogleTest Setup (with CMake)

Since the kata is focused on TDD, I set up GoogleTest in Visual Studio Code using the following instructions. These are based on what Google's AI suggested, along with a few of my own notes and solutions that I came up with along the way.

## Prerequisites

1. Visual Studio Code: Download and install
    * https://code.visualstudio.com/download

2. MinGW: Install and ensure it is on your system PATH.

3. CMake: Install and ensure it is on your system PATH (select the option during installation).
    * https://cmake.org/download/
    * Windows installer: cmake-4.0.3-windows-x86_64.msi (or similar)

4. C/C++ Extension in VS Code (by Microsoft): Open the extensions view and search for it.
    * You can install it globally or for a specific workspace.

## Building Google Test

This clones Google Test as a submodule in a subfolder of your project (/lib/googletest). If you want something different, modify as appropriate. For instance, it might be simpler to download GoogleTest as a zip file instead of version controlled.

1. Create a folder for your project and open the folder with VSCode. 
    * When you start VSCode, the start page has the option "Open Folder...", or you can go to File > Open Folder.
    * Might as well save it as a workspace, too (File > Save Worksapce As...)

2. Open a terminal view (View > Terminal or CTRL+`).
    * Poweshell is the default, but if you want to use bash as the default instead...
        * Press F1 and type/select "Terminal: Select Default Profile"
        * Select the bash interpreter you want to use (I had a choice between Git bash and bash in mingw)
    * We'll be entering commands using the bash interpreter, so if the terminal isn't using bash already, switch to bash using the toolbar of the terminal view (downdown next to the "+").

3. Ensure the terminal can see the executables we need.
    * `cmake` - Should output usage information
    * `g++` - Should say something like "g++.exe: fatal error: no input files"
    * If the above don't look right, check `echo $PATH`
    * If that doesn't show everything we need, ensure all terminal and cmd windows (even outside of VSCode) are closed and restart VSCode.

4. Clone the Google Test repository (https://github.com/google/googletest) as a submodule.
    * Visit the repository page and determine which release you want to use, then clone the desired branch.
    ```
    git submodule add https://github.com/google/googletest.git lib/googletest
    git config -f .gitmodules submodule.GoogleTest.branch release-1.11.0 
    git submodule update --remote GoogleTest
    ```

5. Create a build in /lib/googletest/build directory
    ```
    cd lib/googletest
    mkdir build
    cd build    
    ```
6. Run CMake
    * ```cmake .. -G "MinGW Makefiles"```
    * CMake might complain about the versions in googletest cmake files. The easiest way I found to deal with those is to change the lines in a couple files (double click the associates output item in the "PROBLEMS" view to open it conveniently)...

        ```
        # Change this line:
        cmake_minimum_required(VERSION 2.8.12)
        # ...to this...:
        cmake_minimum_required(VERSION 2.8.12...4.10)
        ```

7. Build Google Test
    ```mingw32-make```

## Create your `CMakeLists.txt` files

1. Top project folder
2. In other folders. 
    * There are lots of different ways to organize this. We will use a `tst` folder that contains the tests, so we'll have a `tst/CMakeLists.txt` file.

### Create a basic test

1. Add a `tst` folder
2. Add a `Setup_test.cpp` file with a basic test in it
3. Ensure the `CMakeLists.txt` includes the new file

## Running tests

1. Close and reopen VSCode. When you reopen, VSCode will ask to set up the project. It's not exactly obvious, but the prompt will be in the middle of VSCode's title bar with a dropdown. Select the MinGW option.

2. Build the project
    * Run `CMake: Build` command (use Ctrl-Shift-P and type/select "CMake: Build")

3. Discover tests: Open the Testing view (the beaker icon in left side bar). Click the Refresh button if you don't see your test.

4. Run or Debug tests: You can use the Testing view to run or debug all tests or specific tests.

# GoogleTest Setup (without CMake)

What worked for me was to create a configuration based on this StackOverflow post (titled "The hard way: manually build everything from scratch, using g++ directly without a build system"): https://stackoverflow.com/questions/72108314/how-do-i-build-and-use-googletest-gtest-and-googlemock-gmock-with-gcc-g-or

1. Create a configuration to build GoogleTest (see "Build GoogleTest" task in tasks.json)

2. Create the static libraries (I did this manally on the VSCode terminal, but I imagine a task could be created for it, also)
```
cd lib/googletest
ar -rv libgtest.a gtest-all.o
ar -rv libgtest_main.a gtest_main.o
ar -rv libgmock.a gmock-all.o
ar -rv libgmock_main.a gmock_main.o
mkdir lib
mv {*.a,*.o} lib
```

3. Update the project's build task so that it includes gtest sources and links to the static libraries created in the step above. See "Build VendingMachineTest" task in tasks.json".

4. Add a debugger launch task. 
    1. Open a .cpp file.
    2. Select the debug view on the left hand vertical pane (the icon has a "bug" on it).
    3. Click on the option to create a launch item. Select the gdb option. This will create the launch.json file or add a configuration item if it already exists.
    4. Edit the launch configuration so it has the actual path to your gdb and executable.
    5. In the launch configuration, add a "preLaunchTask" item that calls out the task that builds the project, e.g "Build VendingMachine".

5. Add the "C++ TestMate" extension. This allows the use of VS Code's native "Testing" view (in the left hand vertical pane, click the icon with the beaker). In the Testing view, you can easily run or debug all tests or individial tests. If you don't see any tests there at first, click the Refresh button.