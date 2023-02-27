SUPPRESS = --suppress=missingIncludeSystem --suppress=unmatchedSuppression --suppress=unusedFunction --suppress=useStlAlgorithm
OS = $(shell uname)
CC = g++ -std=c++17

LEAK_CHECK = leaks --atExit -q -- ./testing.out
CHECK_FLAGS = -lgtest
ifeq ($(OS), Linux)
CHECK_FLAGS += -lpthread -lgtest_main -L/usr/lib
LEAK_CHECK = valgrind --leak-check=full -s -q -- ./testing.out
endif

all: test linter

test: test_array test_stack test_vector linter
	-cppcheck --language=c++ --enable=all --std=c++17 src/*.h $(SUPPRESS)

test_array:
	$(CC) src/test_array.cpp -o ./testing.out $(CHECK_FLAGS)
	$(LEAK_CHECK)

test_stack:
	$(CC) src/test_stack.cpp -o ./testing.out $(CHECK_FLAGS)
	$(LEAK_CHECK)

test_vector:
	$(CC) src/test_vector.cpp -o ./testing.out $(CHECK_FLAGS)
	$(LEAK_CHECK)

clean:
	rm -rf *.out *.gch *.dSYM *.o

linter: 
	cp ./materials/linters/CPPLINT.cfg .
	-python3 ./materials/linters/cpplint.py src/*.h
	rm -rf CPPLINT.cfg

docker-test:
	docker build -t container-test .
	docker run -it --rm --name tests container-test

docker-rm:
	docker rmi container-test
