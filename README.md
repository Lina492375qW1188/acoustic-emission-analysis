# Acoustic-analysis
This program was originally developed by the previous graduate assistant Hsiu-Wei Yang at Sep 2013 – Jun 2014.  The program was then updated by the author in 2015 and used to measure the [acoustic emission of crumpled paper](https://journals.aps.org/pre/abstract/10.1103/PhysRevE.92.062925), [acoustic emission from breaking bamboo chopstics and spagetti](https://journals.aps.org/prl/abstract/10.1103/PhysRevLett.116.035501), [acoustic emission from twisting paper roll](https://journals.aps.org/pre/abstract/10.1103/PhysRevE.101.053001).
How to use:
1. Run MATLAB file mp3/mp3read.m and choose "Add to path". There might be an error regarding Ln 118. It will say Not enough input argument, which can be ignored.
2. Run ReadMP3.m. If it executes successfully, a figure will appear.
3. Compile records.cpp, e.g. gcc -o records.out records.cpp
4. ./records.out [input_file_name] [output_file_name], e.g. ./records.out 170209_003.txt analysis170209_003.txt
