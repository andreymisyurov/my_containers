SUPL = --suppress=missingIncludeSystem --suppress=unmatchedSuppression --suppress=unusedFunction --suppress=useStlAlgorithm

test: test_multi test_set test_arr test_stack test_vector

test_multi:
	g++ test_multiset.cpp -std=c++11 -lgtest
	leaks --atExit -q -- ./a.out
	-cppcheck --language=c++ --enable=all --std=c++17 s21_multiset.inl s21_multiset.h $(SUPL)

test_set:
	g++ test_set.cpp -std=c++17 -lgtest
	leaks --atExit -q -- ./a.out
	-cppcheck --language=c++ --enable=all --std=c++17 s21_set.inl s21_set.h $(SUPL)

test_arr:
	g++ test_array.cpp -std=c++17 -lgtest
	leaks --atExit -q -- ./a.out
	-cppcheck --language=c++ --enable=all --std=c++17 s21_array.inl s21_array.h $(SUPL)

test_stack:
	g++ test_stack.cpp -std=c++17 -lgtest
	leaks --atExit -q -- ./a.out
	-cppcheck --language=c++ --enable=all --std=c++17 s21_stack.inl s21_stack.h $(SUPL)

test_vector:
	g++ test_vector.cpp -std=c++17 -lgtest
	leaks --atExit -q -- ./a.out
	-cppcheck --language=c++ --enable=all --std=c++17 s21_vector.inl s21_vector.h $(SUPL)

clean:
	rm -rf a.out *.gch *.dSYM *.o

linter: 
	cp ./../materials/linters/CPPLINT.cfg .
	-python3 ../materials/linters/cpplint.py *.h
	rm -rf CPPLINT.cfg a.out