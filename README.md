# Annotation Tool
The Annotation Tool (AT) is an open source tool for easily annotating 
videos and sets of images.

## Requirements

AT requires the following packeges to build:

* OpenCV (< 3.0)
* Boost
* Qt4

## How to build

AT works under Linux and Mac Os environments. We recommend a so-called out of source build 
which can be achieved by the following command sequence:

* mkdir build
* cd build
* cmake ../
* make -j<number-of-cores+1>

## How to use

Once the build phase has been successfully, you can use AT by launching the _annotationtool_
file, located in the _bin_ folder.

For more information, you can visit the following link: [here](http://www.dis.uniroma1.it/~pennisi).