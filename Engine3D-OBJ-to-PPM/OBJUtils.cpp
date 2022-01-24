#include "OBJUtils.h"

void vertex::operator=(const vertex& copyVertex){
    if(this == &copyVertex){
        return;
    }
    x = copyVertex.x;
    y = copyVertex.y;
    z = copyVertex.z;
}


DotObjWaveFront::DotObjWaveFront(){
    
    scale = 1;
    faces.clear();
    vert.clear();
        
}

DotObjWaveFront::~DotObjWaveFront(){
    faces.clear();
    vert.clear();
}

int DotObjWaveFront::getScale(){
    return scale;
}

void DotObjWaveFront::setScale(int newScale){
    scale = newScale;
}


void DotObjWaveFront::loadOBJ(string fileName){
    if(fileName.find(".obj") == string::npos){
        fileName = fileName.append(".obj");
    }
    ifstream inFile(fileName,ios::in);
    string op, dump;
    vertex newVert;
    face newFace;
    
    if(!inFile.good()){
        cout << "Erro: arquivo nao existe" << endl;
        return;
    }
    
    cout << "Carregando: " << fileName << endl;
    
    while(!inFile.eof()){
        
        inFile >> op;
        if(op == "v"){
            inFile >> newVert.x;
            inFile >> newVert.y;
            inFile >> newVert.z;
            vert.push_back(newVert);
        }
        else if(op == "f"){
            inFile >> newFace.vertIndex[0];
            inFile >> newFace.vertIndex[1];
            inFile >> newFace.vertIndex[2];
            for(int i = 0; i < 3; i++){
                newFace.vertIndex[i]--;
            }
            faces.push_back(newFace);
        }
        else{
        }
        
    }
    inFile.close();
}

void DotObjWaveFront::saveOBJ(string fileName){
    ofstream outFile(fileName.append(".obj"),ios::out);

    cout << "Salvando: " << fileName << endl;
    for(unsigned int i = 0; i < vert.size(); i++){
        outFile << "v ";
        outFile << vert.at(i).x << " " << vert.at(i).y << " " << vert.at(i).z << endl;
    }
    for(unsigned int i = 0; i < faces.size(); i++){
        outFile << "f ";
        outFile << (faces.at(i).vertIndex[0]+1) << " " << (faces.at(i).vertIndex[1]+1) << " " << (faces.at(i).vertIndex[2]+1) << endl;
    }
    outFile.close();
}

vertex DotObjWaveFront::getVertexByIndex(unsigned int index){
    return vert.at(index);
}



int* DotObjWaveFront::getVertexFromFace(unsigned int faceIndex){
    int* aux;
    aux = new int[3];
    if(faces.size() <= faceIndex){
        cout << "Index fora de escopo";
        return nullptr;
    }
    aux[0] = faces.at(faceIndex).vertIndex[0]; 
    aux[1] = faces.at(faceIndex).vertIndex[1]; 
    aux[2] = faces.at(faceIndex).vertIndex[2]; 
    return aux;
}

int DotObjWaveFront::getNumberOfFaces(){
    return faces.size();
}
