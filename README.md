# C++ Templates

## Background

The purpose of this repository is to exercise and practice C++ programming with templates.

## Contents

(1) The directory `compiling_and_linking` largely explains how to define and declare templated classes properly so that the code can be built and link without errors. Examples are shown for how to properly write templated classes, whether it be with the inclusion technique, explicit instantiation, or a combination of the two.

(2) The directory `polymorphism` overviews the intricacies of polymorphism with templates.


## Dependencies

This project requires cmake >= 3.12 and gcc/g++ >= 6 for building and testing. Googletest will automatically be cloned and built during the build process, and therefore is not a dependency.

GCC/G++ Install:  

```bash
# gcc/g++
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update
sudo apt install gcc-6
sudo apt install g++-6
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-6 60 --slave /usr/bin/g++ g++ /usr/bin/g++-6
```

cmake Install:

```bash
# cmake
wget https://cmake.org/files/v3.12/cmake-3.12.4.tar.gz
tar -xvzf cmake-3.12.4.tar.gz
cd cmake-3.12.4
./configure
make
sudo make install
sudo update-alternatives --install /usr/bin/cmake cmake /usr/local/bin/cmake 1 --force
cmake --version
```

## Building

Clone the repository and run the build.sh script.

```sh
git clone https://github.com/alisonbelow/cpp-templates.git
cd cpp-templates

# Run build shell script
./build.sh
```

## Test

GTest executables live in the `test/bin` directory of each subfolder (`compiling_and_linking`, etc.). Each one is appropriately named with what template functionality is being tested. Run the respective test for which example you wish to test.

```sh
cd <folder>/test/bin/<folder>
./test_ex*      # Run test
```