#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const vector<vector<int>>constRouge={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
const vector<vector<int>>constVert={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
const vector<vector<int>>constBleu={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
const int   AFF=1, RED=2, DET=3, GRAY=4, BNW=5,
            LUMI=6, CONTR=7, COP=8, ROG=9, ROT=10,
            SYM=11, AGR=12, FLOU=13, BLANC = 14, QUIT=999;


class Image {
  vector<vector<int>> _rouge;//vecteur 2d contenant les valeurs de rouge
  vector<vector<int>> _vert;//vecteur 2d contenant les valeurs de vert
  vector<vector<int>> _bleu;//vecteur 2d contenant les valeurs de bleu
  int _longueur;//longeur de l'image
  int _largeur;//largeur de l'image

public:
Image(const string&);
  Image(const vector<vector<int>>& rouge=constRouge, const vector<vector<int>>& vert=constVert,
        const vector<vector<int>>& bleu=constBleu);
  void display() const;
  Image composanteRouge();//crée une image au même composant de rouge partout
  bool detection(const int& r, const int& v, const int& b)const;//retourne vrai si il y a un pixel de cette couleur dans l'image
  Image niveauxGris();//créé une nouvelle image à partir de l’image cible dont chaque pixel est gris
  void writeFile(ofstream&) const;//écris dans l'image dans le fichier

Image noirEtBlanc(const int& seuil);//créé une nouvelle image à partir de l’image cible en noir et blanc
Image luminosityUp(float& val);//créé une nouvelle image à partir de l’image cible avec la luminosité augmenter
Image luminosityDown(float& val);//créé une nouvelle image à partir de l’image cible avec la luminosité diminuer
Image contrasteUp(float& val);//créé une nouvelle image à partir de l’image cible avec le contraste augmenter
Image contrasteDown(float& val);//créé une nouvelle image à partir de l’image cible avec le contraste diminuer

Image rognerD(const int& nb);//rogne l'image vers la droite
Image rognerG(const int& nb);//rogne l'image vers la gauche
Image rognerH(const int& nb);//rognge l'image vers le haut
Image rognerB(const int& nb);//rognge l'image vers le bas
Image rotationD();//tourne l'image vers la droite
Image rotationG();//tourne l'image vers la gauche
Image retournementH();//retourne l'image horizontalement
Image retournementV();//retourne l'image verticalement
Image agrandissement(int nb);//agrandis l'image

vector<vector<int>> getrouge();
vector<vector<int>> getvert();
vector<vector<int>> getbleu();
bool comparaison (Image c);

Image copie()const; //copie de l'image


/// Ajout de fonctionnalité
//Si la couleur fournie est proche de la couleur du pixel il devient blanc
Image blanchirCouleur(int r, int v, int b) const;
};


string fileName(); //entre le nom du fichier
int menu(); //affiche le menu et retourne le choix de l'utilisateur
bool validChoice(const int&); //vérifie que le choix de l'utilisateur est valide

void loadPicture(const string &picture, vector<vector<int>> &red, vector<vector<int>> &green, vector<vector<int>>&blue);
