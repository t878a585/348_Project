# BSD 3-Clause License
# Copyright (c) 2023, Alexandra Stratton, Riley Sirimongkhon-Dyck,
# Timo Aranjo, Victor Maduka, Ellia Morse, Deborah Onuosa


calculator: main.o
	g++ main.o -g3 -o calculator

main.o: main.cpp ErrorReporter.hpp  InfixToPostfix.hpp  IOHandler.hpp  PostfixEvaluator.hpp  Token.hpp testCases.hpp
	g++ main.cpp -g3 -c -o main.o

clean:
	rm *.o calculator

.PHONY: clean
