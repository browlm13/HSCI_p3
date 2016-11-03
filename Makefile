# %load Makefile
#############################################################
######
# Makefile for project 3
# Laurence Brown
# SMU Mathematics
# Math 3316
# 11/2/2016
#############################################################
######
# compiler & flags
CXX = g++
CXXFLAGS = -O -std=c++0x
# makefile targets
#newton_test.exe	:	newton.cpp	test_newton.cpp


all:
	$(CXX) $(CXXFLAGS) test_newton.cpp -o test_newton.exe
	
	chmod 755 *.exe
	chmod 755 *.txt

clean :
	rm -f *.exe *.txt
####### End of Makefile #######
