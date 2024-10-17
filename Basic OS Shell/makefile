all: clean compile run

compile: directory.cpp regularFile.cpp main.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -o test -std=c++11 directory.cpp regularFile.cpp main.cpp

run:
	@echo "-------------------------------------------"
	@echo "Running the tests...."
	@echo "======================================================================="
	@./test
	@echo "======================================================================="
	@echo "Completed tests...."

clean:
	@echo "-------------------------------------------"
	@echo "Cleaning..."
	@rm -f *.o
	@rm -f test
