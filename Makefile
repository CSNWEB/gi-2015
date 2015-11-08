CXX          = gcc
INCLUDES     = -Iinclude
SFMLINCLUDES = -lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS     = -std=c++0x -O2

#SOURCE = main_test.cpp src/inputHandler.cpp src/abstractForm.cpp
INCDIR = include/

test: main_test.o inputHandler.o abstractForm.o point.o edge.o form.o plane.o problem.o
	$(CXX) -o test $^ $(SFMLINCLUDES)

inputHandler.o: src/inputHandler.cpp include/inputHandler.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) src/inputHandler.cpp -o $@

abstractForm.o: src/abstractForm.cpp include/abstractForm.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) src/abstractForm.cpp -o $@

problem.o: src/problem.cpp include/problem.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) src/problem.cpp -o $@

plane.o: src/plane.cpp include/plane.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) src/plane.cpp -o $@

form.o: src/form.cpp include/form.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) src/form.cpp -o $@

edge.o: src/edge.cpp include/edge.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) src/edge.cpp -o $@

point.o: src/point.cpp include/point.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) src/point.cpp -o $@

main_test.o: main_test.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $^ -o $@


.PHONY:clean
clean:
	rm -f *.o