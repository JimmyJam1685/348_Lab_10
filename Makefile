CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic
TARGET := lab10
SOURCE := James_Orrick_Lab_10.cpp
INPUT ?=

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	@if [ -z "$(INPUT)" ]; then \
		echo "Usage: make run INPUT=path/to/matrix.txt"; \
		exit 1; \
	fi
	@if [ ! -f "$(INPUT)" ]; then \
		echo "Input file not found: $(INPUT)"; \
		exit 1; \
	fi
	./$(TARGET) "$(INPUT)"

clean:
	rm -f $(TARGET)