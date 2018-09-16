# Chaos Game
In short, a Chaos Game creates fractals using the following method:
* Draw a set of vertices placed at random in a 2D space.
* Draw a dot at a random point on the 2D surface.
* Choose a random vertex, and on a line that connects the dot and the vertex, draw a point where the point is of equal distance to the vertex as of the dot. Repeat this step forever.

For more information on why this simple algorithm creates beautifull fractals, see http://www.sfu.ca/~rpyke/chaosgame.pdf

This method is also fun to do yourself using a piece of paper and a marker.
Using three vertices will produce a nice fractal most of the time.

# Installing
This program uses the SFML library, so in order to build the program yourself, you need to have the package
libsfml-dev installed on your machine.
After you have built the program, you can run it in a terminal by using:
./chaos #vertices #frames, where #vertices is the size of the set of random vertices, and #frames is the amount of times the program repeats the last step of the algorithm as described above.
