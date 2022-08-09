NAME_PROGRAM   = final.exe
MAIN_FILE_NAME = main
SRC            = ./src
INCLUDE        = ./include
OBJ            = ./obj
BIN            = ./bin
FLAGS          = -lm -pedantic -Wall 
COMPILER       = gcc   

C_FILES        = $(wildcard $(SRC)/*.c)
OBJ_PATH_FILES = $(patsubst $(SRC)%,$(OBJ)%,$(C_FILES))
OBJ_FILES      = $(patsubst %.c,%.o,$(OBJ_PATH_FILES))

all: create_dir $(OBJ_FILES) create_final_progam
test: clean all run

create_final_progam: $(BIN)/$(NAME_PROGRAM)

# rule for main file
$(OBJ)/$(MAIN_FILE_NAME).o: $(SRC)/$(MAIN_FILE_NAME).c
	@ echo "Compiling main program... "
	@ $(COMPILER) -c $< -I $(INCLUDE) -o $@ $(FLAGS)

# rule for all o files
$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	@ echo "Compiling program $<..."
	@ $(COMPILER) -c $< -I $(INCLUDE) -o $@ $(FLAGS)

# rule for create_final_progam
$(BIN)/%: 
	@ echo "Creating executable..."
	@ $(COMPILER) $< $(OBJ)/*.o -I $(INCLUDE) -o $@ $(FLAGS)

# create all needed directories
create_dir: 
	@ echo "Creating $(OBJ) directory...\n"
	@ mkdir $(OBJ)
	@ echo "Creating $(BIN) directory..."
	@ mkdir $(BIN)

# rule to run the final program
run: 
	@ echo "Running $(BIN)/$(NAME_PROGRAM)"
	@ ./$(BIN)/$(NAME_PROGRAM)

valgrind: 
	@ echo "Running valgrind on $(BIN)/$(NAME_PROGRAM)"
	@ valgrind ./$(BIN)/$(NAME_PROGRAM)

clean:
	@ echo "Removing temporary files..."
	@ clear
	@ rm -rf $(OBJ) $(NAME_PROGRAM) $(BIN)