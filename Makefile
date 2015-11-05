CXX = g++
INCLUDES = -Iinclude
SFMLINCLUDES = -lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS = -std=c++0x -O2

#SOURCE = main_test.cpp src/inputHandler.cpp src/abstractForm.cpp
INCDIR = include/

test: main_test.o inputHandler.o abstractForm.o
	$(CXX) -o test $^ $(SFMLINCLUDES)

inputHandler.o: src/inputHandler.cpp include/inputHandler.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) src/inputHandler.cpp -o $@

abstractForm.o: src/abstractForm.cpp include/abstractForm.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) src/abstractForm.cpp -o $@

main_test.o: main_test.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $^ -o $@


.PHONY:clean
clean:
	rm -f *.o