CC = g++
CFLAGS = --std=gnu++11
INCLUDE_DIR = Include
BUILD_DIR = Bin
SOURCE_SUBDIRS = Heuristics Generator Exact
BUILD_SUBDIRS = $(BUILD_DIR)/$(INCLUDE_DIR)/ $(addprefix $(BUILD_DIR)/,$(SOURCE_SUBDIRS))
SOURCE_DIR = Src
SOURCE_DIR_FULL = $(addprefix $(SOURCE_DIR)/,$(SOURCE_SUBDIRS))
OBJECTS = Graph.o Solution.o
GENERATOR_SRC = $(wildcard $(SOURCE_DIR)/Generator/*.cpp)
GENERATOR_RUN = $(patsubst $(SOURCE_DIR)%.cpp,$(BUILD_DIR)%.run,$(GENERATOR_SRC))
EXACT_SRC = $(wildcard $(SOURCE_DIR)/Exact/*.cpp)
EXACT_RUN = $(patsubst $(SOURCE_DIR)%.cpp,$(BUILD_DIR)%.run,$(EXACT_SRC))
HEURISTICS_SRC = $(wildcard $(SOURCE_DIR)/Heuristics/*.cpp)
HEURISTICS_RUN = $(patsubst $(SOURCE_DIR)%.cpp,$(BUILD_DIR)%.run,$(HEURISTICS_SRC))

OBJECTS_FULL = $(addprefix $(BUILD_DIR)/$(INCLUDE_DIR)/,$(OBJECTS))

vpath %.cpp $(SOURCE_DIR_FULL)


all: checkdirs includes modules

checkdirs: $(BUILD_SUBDIRS) 

includes: $(OBJECTS_FULL)

modules: heuristics generators exact

heuristics: $(HEURISTICS_RUN) 

generators: $(GENERATOR_RUN)

exact: $(EXACT_RUN)

$(BUILD_SUBDIRS):
	mkdir -p $@

$(BUILD_DIR)/$(INCLUDE_DIR)/Solution.o: $(SOURCE_DIR)/$(INCLUDE_DIR)/Solution.cpp $(BUILD_DIR)/$(INCLUDE_DIR)/Graph.o
	$(CC) $(CFLAGS) -c $< -o $@ -I$(SOURCE_DIR)/$(INCLUDE_DIR)

$(BUILD_DIR)/$(INCLUDE_DIR)/%.o: $(SOURCE_DIR)/$(INCLUDE_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -I$(SOURCE_DIR)/$(INCLUDE_DIR)  

$(BUILD_DIR)/Heuristics/%.run: $(OBJECTS_FULL) %.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I$(SOURCE_DIR)/$(INCLUDE_DIR) 

$(BUILD_DIR)/Exact/%.run: $(OBJECTS_FULL) %.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I$(SOURCE_DIR)/$(INCLUDE_DIR)

$(BUILD_DIR)/Generator/%.run: $(OBJECTS_FULL) %.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I$(SOURCE_DIR)/$(INCLUDE_DIR) 

clean:
	rm -rf $(BUILD_DIR)/*
