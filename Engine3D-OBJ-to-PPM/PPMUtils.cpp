#include "imageUtils.h"

using namespace std;

int* image::changeBasedOnKernel(int x, int y, kernel m, bool isEdgeDetection){
    float rSum = 0;
    float gSum = 0;
    float bSum = 0;
    float totalSumOfTheKernel = 0;
    int* rgb;
    x -= 1;
    y -= 1;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            rgb = getPixel(x+i,y+j);
            if(rgb[0] == -404){
                delete[] rgb;
                continue;
            }
            totalSumOfTheKernel += m.Matrix[i][j];
            rSum += rgb[0]*m.Matrix[i][j];
            gSum += rgb[1]*m.Matrix[i][j];
            bSum += rgb[2]*m.Matrix[i][j];
            delete[] rgb;
        }
    }
    if(isEdgeDetection){
        totalSumOfTheKernel = 1;
    }
    rgb = new int[3];
    rgb[0] = rSum/totalSumOfTheKernel;
    rgb[1] = gSum/totalSumOfTheKernel;
    rgb[2] = bSum/totalSumOfTheKernel;     
    //cout << "RGB(" << rgb[0] << "," << rgb[1] << "," << rgb[2] << ")\n";      
    return rgb; 
}

//Metodos construtores e destrutores
image::image(){
    width = 50;
    height = 50;
    maxColorValue = 255;

    r = new int*[height];  
    g = new int*[height];
    b = new int*[height];     
    for(int i = 0; i < height; i++){
        r[i] = new int[width];
        g[i] = new int[width];
        b[i] = new int[width];
        for(int j = 0; j < width; j++){
            r[i][j] = maxColorValue;
            g[i][j] = maxColorValue;
            b[i][j] = maxColorValue;
        }
    }     
}
image::~image(){
    for(int i = 0; i < height; i++){
        delete[] r[i]; 
        delete[] g[i]; 
        delete[] b[i]; 
    }    
    delete[] r;
    delete[] g;
    delete[] b;
}
image::image(int imageWidth, int imageHeight, int rValue, int gValue, int bValue){
    width = imageWidth;
    height = imageHeight;
    maxColorValue = 255;
//Limita o numero entre 0 e maxValue;
    rValue = rValue%(maxColorValue+1);
    gValue = gValue%(maxColorValue+1);
    bValue = bValue%(maxColorValue+1);

    r = new int*[height];  
    g = new int*[height];
    b = new int*[height];     
    for(int i = 0; i < height; i++){
        r[i] = new int[width];
        g[i] = new int[width];
        b[i] = new int[width];
        for(int j = 0; j < width; j++){
            r[i][j] = rValue;
            g[i][j] = gValue;
            b[i][j] = bValue;
        }
    } 
}

//Metodo de copia
void image::operator=(const image& copyImage){
//Verifica se o arquivo é diferente do arquivo copiado;
    if(this != &copyImage){ 
        for(int i = 0; i < height; i++){
            delete[] r[i]; 
            delete[] g[i]; 
            delete[] b[i]; 
        }    
        delete[] r;
        delete[] g;
        delete[] b;

        width = copyImage.width;
        height = copyImage.height;
        maxColorValue = copyImage.maxColorValue;

        
        r = new int*[height];  
        g = new int*[height];
        b = new int*[height];     
        for(int i = 0; i < height; i++){
            r[i] = new int[width];
            g[i] = new int[width];
            b[i] = new int[width];
            for(int j = 0; j < width; j++){
                r[i][j] = copyImage.r[i][j];
                g[i][j] = copyImage.g[i][j];
                b[i][j] = copyImage.b[i][j];
            }
        }    
        return;
    }
    cout << "Erro: Objeto nao pode ser copiado para ele mesmo" << endl;
};

//Metodos Set e get

void image::putPixel(int x, int y,int rValue, int gValue, int bValue){
    if(x < 0 || x >= width){
        return;
    }
    if(y < 0 || y >= height){
        return;
    }
    r[y][x] = rValue;
    g[y][x] = gValue;
    b[y][x] = bValue;
}
int* image::getPixel(int x, int y){
    int *aux = new int[3];
    if(x < 0 || x >= width || y < 0 || y >= height){
        aux[0] = -404;
        aux[1] = -404;
        aux[2] = -404;
        return aux;
    }
    aux[0] = r[y][x];
    aux[1] = g[y][x];
    aux[2] = b[y][x];
    return aux;
}
int image::getWidth(){
    return width;
}
int image::getHeight(){
    return height;
}
int image::getMaxColor(){
    return maxColorValue;
}
//Metodos de Save e load

void image::saveImage(string imageName){
    ofstream outFile(imageName.append(".ppm"),ios::out);

    cout << "Salvando: " << imageName << endl;
    outFile << "P3" << endl;
    outFile << width << " " << height << endl;
    outFile << maxColorValue << endl;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            outFile << r[i][j] <<" "<< g[i][j] << " " << b[i][j] << " ";
        }
        outFile << endl;
    }
}
void image::loadImage(string imageName){
    ifstream inFile(imageName.append(".ppm"),ios::in);            
    string dump;
//Verifica a autenticidade do arquivo
    if(!inFile.good()){
        cout << "Erro: arquivo nao existe" << endl;
        return;
    }
    inFile >> dump;
    if(dump != "P3"){
        cout << "Erro: arquivo nao e P3" << endl;
        return;
    }
//Remove todos os antigos arrays antes de criar os novos;
    for(int i = 0; i < height; i++){
        delete[] r[i]; 
        delete[] g[i]; 
        delete[] b[i]; 
    }    
    delete[] r;
    delete[] g;
    delete[] b;

    cout << "Carregando : " << imageName << endl;
    inFile >> width;
    inFile >> height;
    inFile >> maxColorValue;
    
    r = new int*[height];  
    g = new int*[height];
    b = new int*[height];     
    for(int i = 0; i < height; i++){
        r[i] = new int[width];
        g[i] = new int[width];
        b[i] = new int[width];
        for(int j = 0; j < width; j++){
            inFile >> r[i][j];
            inFile >> g[i][j];
            inFile >> b[i][j];
        }
    }     

}

//Metodos de modificação da imagem

void image::invertColors(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            r[i][j] = maxColorValue - r[i][j];
            g[i][j] = maxColorValue - g[i][j];
            b[i][j] = maxColorValue - b[i][j];
        }
    }
}
void image::reflectX(){
    image aux;
    aux = *this;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            aux.putPixel(j,i,r[i][width - j -1],g[i][width - j-1],b[i][width - j-1]);
        }
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            putPixel(j,i,aux.r[i][j],aux.g[i][j],aux.b[i][j]);
        }
    }
}
void image::reflectY(){
    image aux;
    aux = *this;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            aux.putPixel(j,i,r[height - i -1][j],g[height - i -1][j],b[height - i -1][j]);
        }
        
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            putPixel(j,i,aux.r[i][j],aux.g[i][j],aux.b[i][j]);
        }
    }
}
void image::stampImage(image& stamp, int x, int y){
    for(int i = 0; i < stamp.height; i++){
        for(int j = 0; j < stamp.width; j++){
            putPixel((x+j)%width,(y+i)%height,stamp.r[i][j],stamp.g[i][j],stamp.b[i][j]);
        }
    }
}
void image::applyGausianBlur(int numberOfPasses){
    kernel GausianMatrix;
    image aux;
    int *rgb;
    aux = *this;
    GausianMatrix.Matrix[0][0] = 1;
    GausianMatrix.Matrix[1][0] = 2;
    GausianMatrix.Matrix[2][0] = 1;
    GausianMatrix.Matrix[0][1] = 2;
    GausianMatrix.Matrix[1][1] = 4;
    GausianMatrix.Matrix[2][1] = 2;
    GausianMatrix.Matrix[0][2] = 1;
    GausianMatrix.Matrix[1][2] = 2;
    GausianMatrix.Matrix[2][2] = 1;
    cout << "Aplicando Gausian Blur...\n";
    for(int w = 0; w < numberOfPasses; w++){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                rgb = aux.changeBasedOnKernel(j,i,GausianMatrix);
                putPixel(j,i,rgb[0],rgb[1],rgb[2]);
                delete[] rgb;
            }
        }
        aux = *this;
    }
}
void image::applyMedianBlur(int numberOfPasses){
    kernel GausianMatrix;
    image aux;
    int *rgb;
    aux = *this;
    GausianMatrix.Matrix[0][0] = 1;
    GausianMatrix.Matrix[1][0] = 1;
    GausianMatrix.Matrix[2][0] = 1;
    GausianMatrix.Matrix[0][1] = 1;
    GausianMatrix.Matrix[1][1] = 1;
    GausianMatrix.Matrix[2][1] = 1;
    GausianMatrix.Matrix[0][2] = 1;
    GausianMatrix.Matrix[1][2] = 1;
    GausianMatrix.Matrix[2][2] = 1;
    cout << "Aplicando Median Blur...\n";
    for(int w = 0; w < numberOfPasses; w++){
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                rgb = aux.changeBasedOnKernel(j,i,GausianMatrix);
                putPixel(j,i,rgb[0],rgb[1],rgb[2]);
                delete[] rgb;
            }
        }
        aux = *this;
    }
}
void image::applyGrayScale(){
    int *rgb = new int[3];
    int grayColor = 0;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            rgb = getPixel(j,i);
            //Usando o metodo de luminosidade
            grayColor = (0.299f*rgb[0])+(0.587f*rgb[1])+(0.114f*rgb[2]);
            putPixel(j,i,grayColor,grayColor,grayColor);
            delete[] rgb;
        }
    }
}
void image::applyStepTransformation(int StepValue){
    int *rgb = new int[3];
    applyGrayScale();
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            rgb = getPixel(j,i);
            if(rgb[0] <= StepValue){
                putPixel(j,i,0,0,0);
            }
            else{
                putPixel(j,i,maxColorValue,maxColorValue,maxColorValue);
            }
            delete[] rgb;
        }
    }
}
void image::applySobelEdgeDetection(bool saveSeparatedXYFiles){
    kernel gX;
    kernel gY;
    int *rgb;
    gX.Matrix[0][0] = -1;
    gX.Matrix[1][0] = -2;
    gX.Matrix[2][0] = -1;
    gX.Matrix[0][1] = 0;
    gX.Matrix[1][1] = 0;
    gX.Matrix[2][1] = 0;
    gX.Matrix[0][2] = 1;
    gX.Matrix[1][2] = 2;
    gX.Matrix[2][2] = 1;

    gY.Matrix[0][0] = -1;
    gY.Matrix[0][1] = -2;
    gY.Matrix[0][2] = -1;
    gY.Matrix[1][0] = 0;
    gY.Matrix[1][1] = 0;
    gY.Matrix[1][2] = 0;
    gY.Matrix[2][0] = 1;
    gY.Matrix[2][1] = 2;
    gY.Matrix[2][2] = 1;

    image gXResult;
    image gYResult;
    applyGrayScale();
    gXResult = *this;
    gYResult = *this;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

            rgb = changeBasedOnKernel(j,i,gX,true);
            if(rgb[0] < 0){
                rgb[0] = 0;
            }
            else if(rgb[0] > 255){
                rgb[0] = 255;
            }
            gXResult.putPixel(j,i,rgb[0],rgb[0],rgb[0]);
            delete[] rgb;
            
            rgb = changeBasedOnKernel(j,i,gY,true);
            if(rgb[0] < 0){
                rgb[0] = 0;
            }
            else if(rgb[0] > 255){
                rgb[0] = 255;
            }
            gYResult.putPixel(j,i,rgb[0],rgb[0],rgb[0]);
            delete[] rgb;
        }
    }
    if(saveSeparatedXYFiles){
        gYResult.saveImage("SobelY");
        gXResult.saveImage("SobelX");
    }
    int newGrayScale;
    float gYValue,gXValue;
    
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            rgb = gXResult.getPixel(j,i);
            gXValue = rgb[0];
            delete[] rgb;
            rgb = gYResult.getPixel(j,i);
            gYValue = rgb[0];
            delete[] rgb;
            newGrayScale = pow((pow(gXValue,2)+pow(gYValue,2)),0.5f);
            putPixel(j,i,newGrayScale,newGrayScale,newGrayScale);
        }
    }

}
void image::drawLine(int origX, int origY, int destX, int destY, color lineColor){
    
    int deltaX = abs(destX - origX);
    int deltaY = abs(destY - origY);
    int xDirection = origX < destX ? 1 : -1;
    int yDirection = origY < destY ? 1 : -1;
    int decision = (deltaY-deltaX)<<1;
    int x = origX, y = origY;

    if(deltaX>=deltaY){
        for(int i = 0; i <= deltaX; i++){
            putPixel(x,y,lineColor.r,lineColor.g,lineColor.b);
            if(decision > 0){
                decision = decision + (deltaY<<1) - (deltaX<<1);
                x += xDirection;
                y += yDirection;
            }
            else{
                decision = decision + (deltaY<<1);
                x += xDirection;
            }
        }
    }else{
        decision = (deltaX-deltaY)<<1;
        for(int i = 0; i <= deltaY; i++){
            putPixel(x,y,lineColor.r,lineColor.g,lineColor.b);
            if(decision > 0){
                decision = decision + (deltaX<<1) - (deltaY<<1);
                x += xDirection;
                y += yDirection;
            }
            else{
                decision = decision + (deltaX<<1);
                y += yDirection;
            }
        }
    }
}
