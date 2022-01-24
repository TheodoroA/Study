#ifndef OBJ_U
#define OBJ_U

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <math.h>
#include <vector>

using namespace std;

struct vertex{
    float x;
    float y;
    float z;
    void operator=(const vertex& copyVertex);
};

struct face{
    int vertIndex[3];
};

class DotObjWaveFront{
    private:

        int scale;
        vector<vertex> vert;
        vector<face> faces;

    public:

        DotObjWaveFront();
        ~DotObjWaveFront();
        int getScale();
        void setScale(int newScale);
        void loadOBJ(string fileName);
        void saveOBJ(string fileName);
        vertex getVertexByIndex(unsigned int index);
        int* getVertexFromFace(unsigned int faceIndex);
        int getNumberOfFaces();
};

#endif