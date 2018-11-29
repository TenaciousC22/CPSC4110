all: quantum.cc
	g++ -g -Wall -o quantum quantum.cc


clean:
	$(RM) quantum