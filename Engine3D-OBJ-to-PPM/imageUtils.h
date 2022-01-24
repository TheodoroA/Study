#ifndef PPM_U
#define PPM_U

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <math.h>

using namespace std;

struct kernel{
    public:
        int Matrix[3][3];
};

struct color{
    public:
        int r;
        int g;
        int b;
};

class image{
    private:
        int **r;
        int **g;
        int **b;
    //Numero de colunas
        int width;
    //Numero de linhas
        int height;
        int maxColorValue;

        int* changeBasedOnKernel(int x, int y, kernel m, bool isEdgeDetection = false);
    public:
    //Metodos construtores e destrutores
        image();
        ~image();
        image(int imageWidth, int imageHeight, int rValue, int gValue, int bValue);
        void operator=(const image& copyImage);

    //Metodos Set e get

        void putPixel(int x, int y,int rValue, int gValue, int bValue);
        int* getPixel(int x, int y);
        int getWidth();
        int getHeight();
        int getMaxColor();
    //Metodos de Save e load

        void saveImage(string imageName);
        void loadImage(string imageName);

    //Metodos de modificação da imagem

        void invertColors();
        void reflectX();
        void reflectY();
        void stampImage(image& stamp, int x, int y);
        void applyGausianBlur(int numberOfPasses = 1);
        void applyMedianBlur(int numberOfPasses = 1);
        void applyGrayScale();
        void applyStepTransformation(int StepValue = 128);
        void applySobelEdgeDetection(bool saveSeparatedXYFiles = false);
        void drawLine(int origX, int origY, int destX, int destY, color lineColor);
};

#endif