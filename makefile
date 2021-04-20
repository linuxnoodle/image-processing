PROJECT:=bad-apple

CC:=g++
LDFLAGS=-ansi -O2 -std=c++17 -lstdc++fs -static
UNAME:=$(shell uname)

OBJDIR:=objects
OBJ:=$(addprefix $(OBJDIR)/,main.o lodepng.o imageconverting.o)

$(PROJECT): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CC) $(LDFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: all
all: clean $(PROJECT)

.PHONY: clean
clean:
	rm -r objects bad-apple
