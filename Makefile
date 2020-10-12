INCLUDE = -I/usr/local/include/freetype2/

main: debug/Button.o debug/Shader.o debug/Display.o debug/TextRenderer.o debug/BaseControl.o debug/Label.o debug/DirectoryReader.o debug/FileViewer.o debug/FileViewerItem.o debug/Main.o
	g++ debug/Button.o debug/Shader.o debug/Display.o debug/TextRenderer.o debug/BaseControl.o debug/Label.o debug/DirectoryReader.o debug/Main.o debug/FileViewerItem.o debug/FileViewer.o -o FileCopyApp -lGL -lGLU -lGLEW -lglfw3 -lX11 -lXxf86vm -lXrandr -lXi -lXinerama -lXcursor -lpthread -lfreetype -ldl
debug/Button.o: Controls/Button.cpp
	g++ -c Controls/Button.cpp -o debug/Button.o
debug/Label.o: Controls/Label.cpp
	g++ -c Controls/Label.cpp -o debug/Label.o
debug/BaseControl.o: Controls/BaseControl.cpp
		g++ -c Controls/BaseControl.cpp -o debug/BaseControl.o
debug/FileViewer.o: Controls/FileViewer.cpp
		g++ -c Controls/FileViewer.cpp -o debug/FileViewer.o
debug/FileViewerItem.o: Controls/FileViewerItem.cpp
		g++ -c Controls/FileViewerItem.cpp -o debug/FileViewerItem.o
debug/DirectoryReader.o: BusinessLogic/DirectoryReader.cpp
		g++ -c BusinessLogic/DirectoryReader.cpp -o debug/DirectoryReader.o
debug/Main.o: Main.cpp
	g++ -c Main.cpp $(INCLUDE) -o debug/Main.o
debug/TextRenderer.o: TextRenderer/TextRenderer.cpp
	g++ -c TextRenderer/TextRenderer.cpp $(INCLUDE) -o debug/TextRenderer.o
debug/Shader.o: Shader/Shader.cpp
	g++ -c Shader/Shader.cpp -o debug/Shader.o
debug/Display.o: Display/Display.cpp
	g++ -c Display/Display.cpp -o debug/Display.o
clean:
	rm -f FileCopyApp debug/FileViewerItem.o debug/BaseControl.o debug/Label.o debug/FileViewer.o debug/DirectoryReader.o debug/Button.o debug/Main.o debug/Shader.o debug/TextRenderer.o debug/Display.o
install:
	cp FileCopyApp /usr/local/bin/FileCopyApp
uninstall:
	rm -f /usr/local/bin/FileCopyApp
