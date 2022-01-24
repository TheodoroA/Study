#include "imageUtils.h"
#include "OBJUtils.h"

vertex rotate(vertex original, vertex rotationAngles){
    vertex newPosition;
    newPosition = original;
    vertex degreeToRadians;
    degreeToRadians.x = rotationAngles.x*0.0174532*0.5;
    degreeToRadians.y = rotationAngles.y*0.0174532*0.5;
    degreeToRadians.z = rotationAngles.z*0.0174532*0.5;

    //Rotação no eixo x;
    if(degreeToRadians.x != 0){
        newPosition.y = newPosition.y*cos(degreeToRadians.x) - newPosition.z*sin(degreeToRadians.x);
        newPosition.z = newPosition.y*sin(degreeToRadians.x) + newPosition.z*cos(degreeToRadians.x);
    }

    //Rotação no eixo y;
    if(degreeToRadians.y != 0){
        newPosition.z = newPosition.z*sin(degreeToRadians.y) - newPosition.x*cos(degreeToRadians.y);
        newPosition.x = newPosition.z*cos(degreeToRadians.y) + newPosition.x*sin(degreeToRadians.y);   
    }
    /*
    //Rotação no eixo z; Não funcionou do jeito esperado, deformada todos os pontos a um unico ponto 
    if(degreeToRadians.z != 0){
        newPosition.x = newPosition.x*cos(degreeToRadians.z) - newPosition.y*sin(degreeToRadians.z);
        newPosition.y = newPosition.x*sin(degreeToRadians.z) + newPosition.y*cos(degreeToRadians.z);
    }
    */
    return newPosition;
}


vertex prepareVertex(vertex original, int zNearPlane, int xCenter, int yCenter, int scale,vertex translation){

    //Calcula Projeção
    vertex projection;
    projection.z = original.z;

    const float perspectiveProportion = (zNearPlane + original.z);

    projection.x = xCenter + translation.x+scale*(original.x/perspectiveProportion);
    projection.y = yCenter + translation.y+scale*(original.y/perspectiveProportion);

    return projection;
}

bool calculateNormal(vertex vert1, vertex vert2, vertex vert3){
    vertex A;
    vertex B;
    A.x = vert2.x - vert1.x;
    A.y = vert2.y - vert1.y;
    A.z = vert2.z - vert1.z;
    B.x = vert3.x - vert1.x;
    B.y = vert3.y - vert1.y;
    B.z = vert3.z - vert1.z;

    float Z = (A.x * B.y) - (A.y * B.x);

    if(Z <= 0){
        return false;
    }else{
        return true;
    }
}

void projectToScreen(int zNearPlane, int xScreenSize, int yScreenSize, vertex translation, vertex rotation, 
DotObjWaveFront obj, color background, color foreground, string frameName){

    if(zNearPlane <= 1){
        zNearPlane = 2;
    }

    int xScreenCenter =((xScreenSize%2) == 0) ? xScreenSize/2 : xScreenSize/2 + 1;
    int yScreenCenter =((yScreenSize%2) == 0) ? yScreenSize/2 : yScreenSize/2 + 1;
    int scale = obj.getScale();
    int *aux, vertToInt[6];
    vertex v1,v2,v3;
    vertex v1ToS, v2ToS,v3ToS;
    image screen(xScreenSize,yScreenSize,background.r,background.g,background.b);

    for(int i = 0; i < obj.getNumberOfFaces(); i++){
        aux = obj.getVertexFromFace(i);
        v1 = obj.getVertexByIndex(aux[0]);
        v2 = obj.getVertexByIndex(aux[1]);
        v3 = obj.getVertexByIndex(aux[2]);

        v1 = rotate(v1,rotation);
        v2 = rotate(v2,rotation);
        v3 = rotate(v3,rotation);
        
        if(calculateNormal(v1,v2,v3)){
            continue;
        }

        v1ToS = prepareVertex(v1,zNearPlane,xScreenCenter,yScreenCenter, scale, translation);
        v2ToS = prepareVertex(v2,zNearPlane,xScreenCenter,yScreenCenter, scale, translation);
        v3ToS = prepareVertex(v3,zNearPlane,xScreenCenter,yScreenCenter, scale, translation);



        vertToInt[0] = v1ToS.x;
        vertToInt[1] = v1ToS.y;
        vertToInt[2] = v2ToS.x;
        vertToInt[3] = v2ToS.y;
        vertToInt[4] = v3ToS.x;
        vertToInt[5] = v3ToS.y;
 
 
        screen.drawLine(vertToInt[0],vertToInt[1],vertToInt[2],vertToInt[3],foreground);
        screen.drawLine(vertToInt[0],vertToInt[1],vertToInt[4],vertToInt[5],foreground);
        screen.drawLine(vertToInt[2],vertToInt[3],vertToInt[4],vertToInt[5],foreground);

        delete[] aux;
    }
    screen.saveImage(frameName);
}

void defaultMain(){
    DotObjWaveFront Obj;
    Obj.loadOBJ("cara.obj"); 
    int* aux;
    Obj.setScale(300);
    vertex translation;
    translation.x = 0;
    translation.y = 0;
    vertex rotation;
    rotation.x = 0;
    rotation.y = 135;
    rotation.z = 0;

    

    color black;
    black.r = 0;
    black.g = 0;
    black.b = 0;

    color white;
    white.r = 255;
    white.g = 255;
    white.b  = 255;

    projectToScreen(1,600,600,translation,rotation,Obj,black,white,"Render3D");
}


int main(int argc, char *argv[]){
    if(argc <= 1){
        cout << "\n\t\tVocê não digitou nenhum arquivo!";
        cout << "\n\t\tExecução padrão está sendo feita \n\n";
        defaultMain();
        return 0;
    }

    DotObjWaveFront obj;
    obj.loadOBJ(argv[1]);
    
    vertex translation;
    translation.x = 0;
    translation.y = 0;
    vertex rotation;
    rotation.x = 0;
    rotation.y = 0;
    rotation.z = 0;

    color back;
    back.r = 0;
    back.g = 0;
    back.b = 0;

    color fore;
    fore.r = 255;
    fore.g = 255;
    fore.b  = 255;

    string fileName = "Render3D";
    obj.setScale(300);
    int x = 600, y = 600;
    int nearPlane = 1;
    int op;
    float scale;
        while (true){
        std::cout << "\n\n 0 - Renderizar \n 1 - Mudar Rotação\n 2 - Mudar Background Color\n 3 - Mudar Wireframe Color \n";
        cout << " 4- Mudar Translação\n 5 - Mudar Escala \n 6 - Mudar Resolução \n 7 - Mudar Nearfield\n 8 - Gerar arquivo de demonstração \n9- SAIR\n\n";
        cout << " Digite sua opcao: ";
        cin >> op;        
        cout << "\n\n\n\n\n";
        switch (op){
            case 0:
                projectToScreen(nearPlane,x,y,translation,rotation,obj,back,fore,fileName);
                break;
            case 1:
                cout << "Digite a rotação em graus do Objeto\n X= ";
                cin >> rotation.x;
                cout << "\n Y= ";
                cin >> rotation.y;
                break;
            case 2:
                cout << "Digite a nova cor do background de 0 a 255\n R= ";
                cin >> back.r;
                cout << "\n G= ";
                cin >> back.g;
                cout << "\n B= ";
                cin >> back.b;
                break;
            case 3:
                cout << "Digite a nova cor do objeto de 0 a 255\n R= ";
                cin >> fore.r;
                cout << "\n G= ";
                cin >> fore.g;
                cout << "\n B= ";
                cin >> fore.b;
                break;
            case 4:
                cout << "Digite a nova translação\n X= ";
                cin >> translation.x;
                cout << "\n Y= ";
                cin >> translation.y;
                break;
            case 5:
                cout << "Digite a nova escala: ";
                cin >> scale;
                obj.setScale(scale);
                break;
            case 6:
                cout << "Digite o novo tamanho de imagem\n X= ";
                cin >> x;
                cout << "\n Y= ";
                cin >> y;
                break;
            case 7:
                cout << "Digite a nova distancia focal: ";
                cin >> nearPlane;
                break;
            case 8:
                defaultMain();
                break;
            case 9:
                exit(0);
                break;   
            default:
                break;
        }
    }

    
}