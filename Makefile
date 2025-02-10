CC=g++
SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))
BINDIR=bin
BIN=$(BINDIR)/main
OUT=out


all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) -c $< -o $@

run: $(BIN)
	./$(BIN)
	python3 plot.py $(OUT)/sim_data.tsv $(OUT)/sim_plot.pdf 1000

clean:
	$(RM) $(BINDIR)/* $(OBJ)/*

clear_out:
	$(RM) $(OUT)/*

debug: $(OBJS)
	$(CC) $(OBJS) -g -o $(BINDIR)/$@ $(CFLAGS)
