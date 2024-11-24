
CC = g++
CFLAGS = -fsanitize=address,undefined -D _DEBUG -O0 -Wall -Wextra

SOURCES_DIR_AKR = Sources
SOURCES_DIR_TREE = ../Tree/Sources

SOURCES_AKR = $(wildcard $(SOURCES_DIR_AKR)/*cpp ) 
SOURCES_TREE = $(wildcard $(SOURCES_DIR_TREE)/*cpp ) 

OBJECTS_AKR = $(SOURCES_AKR:.cpp =.o) 
OBJECTS_TREE = $(SOURCES_TREE:.cpp =.o)

EXECUTABLE = Akinator


all: $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS_AKR) $(OBJECTS_TREE) 
	$(CC) $(OBJECTS_AKR) $(OBJECTS_TREE) $(CFLAGS) -lSDL2 -lreadline  -o $(EXECUTABLE)


%.o: %.cpp
	$(CC) -c $(CFLAGS) -IHeaders -I../Tree/Headers $< -o $@ 


clean:
	@rm  -rf  $(SOURCES_AKR/*.o) $(SOURCES_TREE/*.o)  $(EXECUTABLE)  ../Tree/TreeGraphh.dot  ../Tree/TreeGraph.svg  ../Tree/TreeGraph.html
