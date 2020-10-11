CXX = g++
CXXFLAGS = -Wall -g

main: debug/Shader.o debug/main.o
	$(CXX) $(CXXFLAGS) -o main debug/Shader.o debug/main.o -lGL -lGLU -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lXi -lXinerama -lXcursor -lpthread -lfreetype -ldl
debug/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o debug/main.o
debug/Shader.o: Shader/Shader.cpp
	$(CXX) $(CXXFLAGS) -c Shader/Shader.cpp -o debug/Shader.o
clean: 
	rm -f main debug/Shader.o debug/main.o
