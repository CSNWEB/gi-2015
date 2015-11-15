CXX          = g++
INCLUDES     = -Iinclude
CXXFLAGS     = -std=c++0x -O2

#SOURCE = main_test.cpp src/inputHandler.cpp src/abstractForm.cpp
INCDIR = include/

test: main_test.o inputHandler.o outputHandler.o abstractForm.o point.o edge.o form.o plane.o problem.o
	$(CXX) -o test $^
	
test_debug: main_test_debug.o inputHandler_debug.o outputHandler_debug.o abstractForm_debug.o point_debug.o edge_debug.o form_debug.o plane_debug.o problem_debug.o
	$(CXX) -o test_debug $^

test_sfml: main_test_sfml.o inputHandler_sfml.o outputHandler.o abstractForm_sfml.o point_sfml.o edge_sfml.o form_sfml.o plane_sfml.o problem_sfml.o
	$(CXX) -o test_sfml $^ -lsfml-graphics -lsfml-window -lsfml-system

inputHandler.o: src/inputHandler.cpp include/inputHandler.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) src/inputHandler.cpp -o $@

outputHandler.o: src/outputHandler.cpp include/outputHandler.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) src/outputHandler.cpp -o $@

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

geneticFormFitter.o: src/geneticFormFitter.cpp include/geneticFormFitter.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) src/geneticFormFitter.cpp -o $@

main_test.o: main_test.cpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) $^ -o $@


inputHandler_sfml.o: src/inputHandler.cpp include/inputHandler.hpp
	$(CXX) $(CXXFLAGS) -D USE_SFML -c $(INCLUDES) src/inputHandler.cpp -o $@

abstractForm_sfml.o: src/abstractForm.cpp include/abstractForm.hpp
	$(CXX) $(CXXFLAGS) -D USE_SFML -c $(INCLUDES) src/abstractForm.cpp -o $@

problem_sfml.o: src/problem.cpp include/problem.hpp
	$(CXX) $(CXXFLAGS) -D USE_SFML -c $(INCLUDES) src/problem.cpp -o $@

plane_sfml.o: src/plane.cpp include/plane.hpp
	$(CXX) $(CXXFLAGS) -D USE_SFML -c $(INCLUDES) src/plane.cpp -o $@

form_sfml.o: src/form.cpp include/form.hpp
	$(CXX) $(CXXFLAGS) -D USE_SFML -c $(INCLUDES) src/form.cpp -o $@

edge_sfml.o: src/edge.cpp include/edge.hpp
	$(CXX) $(CXXFLAGS) -D USE_SFML -c $(INCLUDES) src/edge.cpp -o $@

point_sfml.o: src/point.cpp include/point.hpp
	$(CXX) $(CXXFLAGS) -D USE_SFML -c $(INCLUDES) src/point.cpp -o $@

geneticFormFitter_sfml.o: src/geneticFormFitter.cpp include/geneticFormFitter.hpp
	$(CXX) $(CXXFLAGS) -D USE_SFML -c $(INCLUDES) src/geneticFormFitter.cpp -o $@

main_test_sfml.o: main_test.cpp
	$(CXX) $(CXXFLAGS) -D USE_SFML -c $(INCLUDES) $^ -o $@
	

inputHandler_debug.o: src/inputHandler.cpp include/inputHandler.hpp
	$(CXX) $(CXXFLAGS) -D DEBUG -c $(INCLUDES) src/inputHandler.cpp -o $@

outputHandler_debug.o: src/outputHandler.cpp include/outputHandler.hpp
	$(CXX) $(CXXFLAGS) -c $(INCLUDES) src/outputHandler.cpp -o $@

abstractForm_debug.o: src/abstractForm.cpp include/abstractForm.hpp
	$(CXX) $(CXXFLAGS) -D DEBUG -c $(INCLUDES) src/abstractForm.cpp -o $@

problem_debug.o: src/problem.cpp include/problem.hpp
	$(CXX) $(CXXFLAGS) -D DEBUG -c $(INCLUDES) src/problem.cpp -o $@

plane_debug.o: src/plane.cpp include/plane.hpp
	$(CXX) $(CXXFLAGS) -D DEBUG -c $(INCLUDES) src/plane.cpp -o $@

form_debug.o: src/form.cpp include/form.hpp
	$(CXX) $(CXXFLAGS) -D DEBUG -c $(INCLUDES) src/form.cpp -o $@

edge_debug.o: src/edge.cpp include/edge.hpp
	$(CXX) $(CXXFLAGS) -D DEBUG -c $(INCLUDES) src/edge.cpp -o $@

point_debug.o: src/point.cpp include/point.hpp
	$(CXX) $(CXXFLAGS) -D DEBUG -c $(INCLUDES) src/point.cpp -o $@

geneticFormFitter_debug.o: src/geneticFormFitter.cpp include/geneticFormFitter.hpp
	$(CXX) $(CXXFLAGS) -D DEBUG -c $(INCLUDES) src/geneticFormFitter.cpp -o $@

main_test_debug.o: main_test.cpp
	$(CXX) $(CXXFLAGS) -D DEBUG -c $(INCLUDES) $^ -o $@

.PHONY:clean
clean:
	rm -f *.o
