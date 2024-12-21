# Samantha James, RedID: 826078182
# Riley Thompson, RedID: 826526487

# CXX Make variable for compiler
CXX=g++
# -std=c++11  C/C++ variant to use, e.g. C++ 2011
# -Wall       show the necessary warning files
# -g3         include information for symbolic debugger e.g. gdb 
CXXFLAGS=-std=c++11 -Wall -g3 -c

# object files
OBJS = log_helpers.o vaddr_tracereader.o main.o Level.o PageTable.o

# Program name
PROGRAM = pagingwithpr

# Rules format:
# target : dependency1 dependency2 ... dependencyN
#     Command to make target, uses default rules if not specified

# First target is the one executed if you just type make
# make target specifies a specific target
# $^ is an example of a special variable.  It substitutes all dependencies
$(PROGRAM) : $(OBJS)
	$(CXX) -o $(PROGRAM) $^

vaddr_tracereader.o : vaddr_tracereader.h vaddr_tracereader.cpp
	$(CXX) $(CXXFLAGS) vaddr_tracereader.cpp
	
log_helpers.o : log_helpers.h log_helpers.cpp
	$(CXX) $(CXXFLAGS) log_helpers.cpp

PageTable.o : PageTable.h PageTable.cpp
	$(CXX) $(CXXFLAGS) PageTable.cpp

Level.o : Level.h Level.cpp
	$(CXX) $(CXXFLAGS) Level.cpp

main.o : vaddr_tracereader.h vaddr_tracereader.cpp log_helpers.h log_helpers.cpp PageTable.h PageTable.cpp Level.h Level.cpp main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

clean :
	rm -f *.o $(PROGRAM)

