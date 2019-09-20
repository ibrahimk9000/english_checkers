TARGET = checkers
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CC = g++
CFLAGS = -g -Wall
OBJDIR= obj

.PHONY: default all clean

default:$(OBJDIR) $(TARGET) 
$(OBJDIR):
	mkdir $(OBJDIR)

all: default

OBJECTS = $(addprefix $(OBJDIR)/, $(patsubst %.cpp, %.o, $(wildcard *.cpp)))
HEADERS = $(wildcard *.h)

$(OBJDIR)/%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -r $(OBJDIR)
	-rm -f $(TARGET)