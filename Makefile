CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -g

TARGET := app.exe
SRCS := Main.cpp GraphIncidence.cpp GraphMatrix.cpp
OBJS := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all