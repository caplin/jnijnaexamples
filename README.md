Comparison of JNI and JNA
==============

Even though the examples would work on all platforms, the Makefile only works on Linux and OSX. Therefore those are the only supported platforms


This repository contains two subprojects, one for JNI, and one for JNA. The use cases implemented are
- generate a random number in C and print the result from Java
- populate a list of files in a directory, pass it to Java and print the list

To compile and run the examples the following steps are necessary:
- set JAVA_HOME
- cd jna or cd jni
- make run

