How I implemented the multithreading:
From looking over the objective of the program, it is clear
that the rendering of the individual pixels is independent from 
that of any other pixels, hence it is obvious that this is the 
section that should utilize multi-threading.

I isolated this section to be the chunk of for loops that run,
and saw an opportunity for great optimization using multithreading
to 'share the work' of the for loop for increased performance.

Hence I chose to divy up the image into multiple vertical rectangles,
to restrict each thread to a limited number of x values while visiting
all the y co-ordinates. This is a technique used commonly in computer 
vision (found online - hence adopted this strategy as it seemed most 
logical)

Hence start and end were chosen as such.

Issues
Learning the syntax of pthread which is very different and significantly 
more complicated than that of openMP that was taught in my CS 35L class.
Looked at implementations of basic multithreading with pthread online
to understand how exactly the syntax would work.

The idea of worksharing the for loop and how to do it was made easy
by the fact that I understood how it is done in openMP using
the #pragma omp parallel for command.

Performance testing:
time ./srt 1-test.ppm 
real 0m47.104s
user 0m48.032s
sys  0m0.004s

time ./srt 2-test.ppm 
real 0m24.535s
user 0m48.323s
sys  0m0.007s

time ./srt 4-test.ppm 
real 0m15.923s
user 0m49.128s
sys  0m0.006s

time ./srt 8-test.ppm 
real 0m10.551s
user 0m50.073s
sys  0m0.003s

Linear improvement of performance with increase in the number of threads
is evidenced by the data above.
