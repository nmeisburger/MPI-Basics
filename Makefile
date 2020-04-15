all:
	mpicxx -o point point.cpp
	mpicxx -o collective collective.cpp
	mpicxx -o threading -fopenmp threading.cpp

clean:
	rm threading point collective