.PHONY: build clean run clean-emacs

CC=g++
CCFLAGS=-Wall --std=c++0x
#LIBS=`pkg-config --cflags --libs opencv`

SRC_DIR=src
BUILD_DIR=build
SRC=$(wildcard $(SRC_DIR)/*.cpp)
OBJS=$(patsubst %.cpp,%.o,$(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRC)))
EXEC=dp_slam

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CCFLAGS) $(LIBS) -c $+ -o $@

build: $(OBJS)
	$(CC) $(CCFLAGS) $(LIBS) -o $(EXEC) $(OBJS)

clean:
	rm -rf $(EXEC) $(BUILD_DIR)/*.o
	find . -name '*~' -print0 | xargs -0 rm -f

run: build
	./$(EXEC)