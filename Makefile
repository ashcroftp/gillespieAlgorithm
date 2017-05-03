CC := g++ -std=c++11 # This is the main compiler
SRCDIR := src
INCDIR := include
BUILDDIR := build
TARGET := bin/gillespie.out

SRCEXT := cpp
SOURCES := $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
INC := -I $(INCDIR)
DEBUG := -g
CFLAGS := -Wall -c $(DEBUG)
LFLAGS := -Wall $(DEBUG)

$(TARGET): $(OBJECTS)
	@echo "--Linking--"
	$(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	@echo "--Compiling--"
	$(CC) $(CFLAGS) $(INC) $< -o $@

clean:
	@echo "--Cleaning--"; 
	$(RM) $(BUILDDIR)/*.o *~ $(SRCDIR)/*~ $(INCDIR)/*~ $(TARGET)
