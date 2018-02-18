all : runsim testsim

runsim : runsim.cpp
	g++ -fpermissive runsim.cpp -o runsim
testsim : testsim.cpp
	g++ testsim.cpp -o testsim

