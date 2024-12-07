#ifndef FILTRE_H_INCLUDED
#define FILTRE_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Filtre {
  vector<vector<float>>_action; //vecteur 2D contenant le filtre
  int _rayon; //rayon du filtre

public:
  Filtre(const vector<vector<float>>&, const int&); //constructeur du filtre
  Image application(Image&); //applique le filtre sur l'image
  int setPixel(vector<vector<int>>& vect, int x, int y); //modifie le pixel de coordonnées (x,y) et le retourne
};
#endif // FILTRE_H_INCLUDED
