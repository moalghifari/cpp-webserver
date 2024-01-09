CXX := g++
CXXFLAGS := -std=c++11 -I ./libs/boost_1_84_0
LIBS := -lboost_system

SOURCES := main.cpp server.cpp connection.cpp
OBJECTS := $(SOURCES:.cpp=.o)
EXECUTABLE := webserver

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ 

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
