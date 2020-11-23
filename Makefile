CXX = g++
CXXFLAGS = -Wall -g

main: debug/GunShell.o debug/Tower.o debug/Model.o debug/Tank.o debug/Shader.o debug/main.o
	$(CXX) $(CXXFLAGS) -o main debug/GunShell.o debug/Tower.o debug/Model.o debug/Tank.o debug/Shader.o debug/main.o -lGL -lGLU -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lXi -lXinerama -lXcursor -lpthread -lfreetype -ldl
debug/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o debug/main.o
debug/Shader.o: Shader/Shader.cpp
	$(CXX) $(CXXFLAGS) -c Shader/Shader.cpp -o debug/Shader.o
debug/Tank.o: Tank/Tank.cpp
	$(CXX) $(CXXFLAGS) -c Tank/Tank.cpp -o debug/Tank.o
debug/Model.o: Model/Model.cpp
	$(CXX) $(CXXFLAGS) -c Model/Model.cpp -o debug/Model.o
debug/Tower.o: Tank/Tower.cpp
	$(CXX) $(CXXFLAGS) -c Tank/Tower.cpp -o debug/Tower.o
debug/GunShell.o: Tank/GunShell.cpp
	$(CXX) $(CXXFLAGS) -c Tank/GunShell.cpp -o debug/GunShell.o
clean: 
	rm -f main debug/GunShell.o debug/Tower.o debug/Model.o debug/Tank.o debug/Shader.o debug/main.o
