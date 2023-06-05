# histogram
In this assignment, you are asked to implement three parallel applications by using openmp. You need to write an application that reads a large quantity of floating-point data which are between [0.0-5.0] from an input file and stores those numbers into an array. Then, the application makes a histogram of the data by simply dividing the range of the data up into five equal-sized bins. Note that taking input and printing output can be done serially. The time measurement will be done only for the histogram generation part. 
Ex: 2.9 1.3 0.4 1.3 0.3 4.4 1.7 3.2 0.4 0.3 4.9 2.4 
Output: 
[0-1)   4
[1-2)   3
[2-3)   2
[3-4)   1
[4-5]   2

You need to print also execution times of your implementation for 1,2,4,8,16,32,64 threads.
