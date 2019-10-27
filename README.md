# Acoustic-analysis
Author: Sun-Ting Tsai 
This program was originally developed by the previous graduate assistant Hsiu-Wei Yang at Sep 2013 – Jun 2014.  The program was then stabilized by the author in 2015 and used to measure the acoustic emission of crumpled  paper, acoustic emission from breaking bamboo chopstics and spagetti, acoustic emission from twisting paper roll.
How to use:
1. Run MATLAB file mp3/mp3read.m and choose "Add to path". There might be an error regarding Ln 118. It will say Not enough input argument, which can be ignored.
2. Run ReadMP3.m. If it executes successfully, a figure will appear.
3. Compile records.cpp, e.g. gcc -o records.out records.cpp
4. ./records.out [input_file_name] [output_file_name], e.g. ./records.out 170209_003.txt analysis170209_003.txt
