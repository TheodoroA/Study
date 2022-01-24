3DEngine: coreEngine.o PPMUtils.o OBJUtils.o
	g++ coreEngine.o PPMUtils.o OBJUtils.o -o 3DEngine

PPMUtils.o: PPMUtils.cpp
	g++ -c PPMUtils.cpp

coreEngine.o: coreEngine.cpp
	g++ -c coreEngine.cpp

OBJUtils.o: OBJUtils.cpp
	g++ -c OBJUtils.cpp

clean:
	rm *.o 3DEngine *.ppm