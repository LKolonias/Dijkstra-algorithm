LEDAROOT := /usr/local/LEDA
BOOSTROOT := /usr/local/include/

TARGET := project
OBJS   := run.cpp

CXX := g++

#CXXFLAGS := -O3
CXXFLAGS := $(CXXFLAGS) -I  $(BOOSTROOT) -I $(LEDAROOT)/incl
LIBS     += -L $(LEDAROOT) -L/usrX11R6/lib64/ -lm -lX11 -lleda

all: run

run: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

#MST.o:
#	$(CXX) $(CXXFLAGS) MST.hpp $(LDFLAGS) $(LIBS) -o MST

clean:
	rm -rf $(TARGET) 
