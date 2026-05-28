# 1. CPLEX Paths 
CPLEXDIR   = /opt/ibm/ILOG/CPLEX_Studio2211/cplex
CONCERTDIR = /opt/ibm/ILOG/CPLEX_Studio2211/concert

# 2. Compiler and Required Flags
CXX        = g++
# -DIL_STD is required for CPLEX to use the std namespace of modern C++
CXXFLAGS   = -O2 -m64 -fPIC -fexceptions -DNDEBUG -DIL_STD

# 3. Where to find the .h files (Includes)
INCLUDES   = -I$(CPLEXDIR)/include -I$(CONCERTDIR)/include

# 4. Where to find the library files (.a)
# The default format for Linux x86-64 is the static_pic folder
LIBPATHS   = -L$(CPLEXDIR)/lib/x86-64_linux/static_pic -L$(CONCERTDIR)/lib/x86-64_linux/static_pic

# 5. The libraries that the author of the AUR mentioned (The order matters in C++)
LIBS       = -lconcert -lilocplex -lcplex -lm -lpthread -ldl

# 6. Code
SRC        = farmer_problem.cpp
TARGET     = farmer_problem

# Compilation rules
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TARGET) $(LIBPATHS) $(LIBS)

clean:
	rm -f $(TARGET)