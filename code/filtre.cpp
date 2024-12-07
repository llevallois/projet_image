#include <iostream>
#include <vector>
#include "couleur.h"
#include <fstream>
#include "filtre.h"

Filtre::Filtre(const vector<vector<float>>& vect, const int& ray){
    _action=vect;
    _rayon=ray;
}



//applique le filtre à l'image
Image Filtre::application(Image& im){
    vector<vector<int>>vect=im.getrouge(); //le vecteur récupère les valeurs rouge de l'image
    vector<vector<int>>newVect=vect; //on copie le vecteur pour qu'il ait la bonne taille

    for(int x=0 ; x<vect.size() ; x++){
        for(int y=0 ; y<vect[x].size() ; y++){
            newVect[x][y]=setPixel(vect, x, y); //on attribue à chaque pixel une nouvelle valeur à l'aide des coordonnées actuelles de l'image
        }
    }

    Image retIm(newVect,newVect,newVect); //on crée la nouvelle image
    return retIm;
}

//renvoie la nouvelle valeur du pixel
int Filtre::setPixel(vector<vector<int>>& vect, int x, int y){
float result = 0;
    for(int i=0 ; i<_action.size() ; i++){
        for(int j = 0 ; j<_action[i].size() ; j++){
            if(x+i-_rayon>=0 && x+i-_rayon<vect.size() && y+j-_rayon>=0 && y+j-_rayon<vect.size()) //si la valeur n'est pas hors des bordures
             result += _action[i][j]*vect[x+i-_rayon][y+j-_rayon];//on multiplie la valeur du pixel par la valeur du filtre puis on l'ajoute au résultat
        }
    }
return result;
}
