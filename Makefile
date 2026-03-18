CXX      = g++
CXXFLAGS = -std=c++17 -Wall -O2

COMMON_OBJ = incidenceListGraph.o adjacencyMatrixGraph.o

.PHONY: all clean pro22 pro25 pro31 pro32

all: demo22 demo25 demo31 demo32

incidenceListGraph.o: incidenceListGraph.cpp incidenceListGraph.h graph.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

adjacencyMatrixGraph.o: adjacencyMatrixGraph.cpp adjacencyMatrixGraph.h graph.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

scc.o: scc.cpp scc.h graph.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

diamond.o: diamond.cpp diamond.h graph.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

pro22.o: pro22.cpp incidenceListGraph.h graph.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

pro25.o: pro25.cpp incidenceListGraph.h adjacencyMatrixGraph.h graph.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

pro31.o: pro31.cpp scc.h incidenceListGraph.h adjacencyMatrixGraph.h graph.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

pro32.o: pro32.cpp diamond.h incidenceListGraph.h adjacencyMatrixGraph.h graph.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

demo22: pro22.o $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

demo25: pro25.o $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

demo31: pro31.o scc.o $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

demo32: pro32.o diamond.o $(COMMON_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

pro22: demo22
	demo22

pro25: demo25
	demo25

pro31: demo31
	demo31 --verbose graf.txt

pro32: demo32
	demo32 --verbose diamond_test.txt query.txt

clean:
	del /Q *.o demo22.exe demo25.exe demo31.exe demo32.exe 2>nul || true