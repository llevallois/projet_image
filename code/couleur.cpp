#include <iostream>
#include <vector>
#include "couleur.h"
#include <fstream>

using namespace std;


Image::Image(const string &im){
    loadPicture(im, _rouge,_vert,_bleu);
    _longueur=_rouge.size();
    _largeur=_rouge[0].size();
}


Image::Image(const vector <vector<int>>& rouge, const vector <vector<int>>& vert, const vector <vector<int>>& bleu){

  _longueur=rouge.size();;
  _largeur=rouge[0].size();

  if(_longueur!=bleu.size() || _longueur!=vert.size() || vert.size()!=bleu.size()){
    throw(string("vecteur pas de même taille"));
  }
  else if(_largeur!=bleu[0].size() || _largeur!=vert[0].size() || vert[0].size()!=bleu[0].size()){
    throw(string("vecteur pas de même largeur"));
  }
  else{
     _rouge=rouge;
    _vert=vert;
    _bleu=bleu;
  }

}

/// Ajout de fonctionnalité :
Image Image::blanchirCouleur(int r, int v, int b) const {
    const float PROCHE = 0.01;
    float factBlanc;
    Image newIm; // On crée une nouvelle image et on la rend identique à l'image que l'on souhaite modifier
    newIm._rouge=_rouge;
    newIm._vert=_vert;
    newIm._bleu=_bleu;

    //On parcourt ses pixels
    for(int i=0; i<_largeur;i++){
        for(int j=0; j<_longueur;j++){

            //on calcule la valeur du pixel
            float r1 = 1.0 * (_rouge[i][j]-r)*(_rouge[i][j]-r);
            float v1 = 1.0 * (_vert[i][j]-v)*(_vert[i][j]-v);
            float b1 = 1.0 * (_bleu[i][j]-b)*(_bleu[i][j]-b);

            factBlanc =((r1+v1+b1)/(1.0 * (_rouge[i][j] * _rouge[i][j] + _vert[i][j]*_vert[i][j] + _bleu[i][j] *_bleu[i][j])));

            //si elle est proche
            if (factBlanc <= PROCHE){
                newIm._rouge[i][j]=255; // les pixels de la nouvelle image deviennent blanc
                newIm._vert[i][j] = 255;
                newIm._bleu[i][j] = 255;
            }
        }
    }

    return newIm;

}
/// FIN AJOUT DE FONCTIONNALITE


void Image::display() const
{

  for (int i =0; i<_rouge.size();i++)
  {
    for (int j=0;j<_rouge[i].size();j++)
      {
        cout<<" rgb ("<<i<<","<<j<<") = ("<<_rouge[i][j]<<","<<_vert[i][j]<<","<<_bleu[i][j]<<") | ";
      }
      cout<<endl;
    cout<<"------"<<endl;
  }
}

Image Image::composanteRouge()
{
  //cree une nouvelle image
  vector<vector<int>> r(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> v(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> b(_rouge.size(),vector<int>(_rouge[0].size()));

  //parcours les pixels de l'image
  for (int i = 0; i < _rouge.size(); i++) {
      for (int j = 0; j < _rouge[i].size(); j++)       {
      if (_rouge[i][j]>0)//si il y a du rouge qui compose le pixel il devient entièrement rouge
       {
        r[i][j]=255;
        v[i][j]=0;
        b[i][j]=0;
        }
      else{//sinon il deveint noir
        r[i][j]=0;
        v[i][j]=0;
        b[i][j]= 0;
      }

    }
  }

    return Image(r,v,b);//retourne l'image

}

bool Image::detection(const int& r, const int &v, const int& b)const
{//parcour les pixels de limage
  for (int i = 0; i < _rouge.size(); i++) {
    for (int j = 0; j < _rouge[i].size(); j++) {
      if (_rouge[i][j]==r && _vert[i][j]==v && _bleu[i][j]==b)//si les composant de couleurs d'un des pixels sont identique on retourne true
      {
        return true;
      }
    }
  }
  return false;//sinon le pixel n'est pas dans l'image
}

Image Image::niveauxGris()
{//on cree une nouvelle image
  vector<vector<int>> r(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> v(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> b(_rouge.size(),vector<int>(_rouge[0].size()));

  //on parcourt les pixels de l'image
  for (int i = 0; i < _rouge.size(); i++) {
      for (int j = 0; j < _rouge[i].size(); j++){
          r[i][j]=_rouge[i][j];
        v[i][j]=_vert[i][j];
        b[i][j]=_bleu[i][j];
//on calcule la moyenne des composant de couleurs et on l'assigne a la nouvelle image
        r[i][j]= (r[i][j]+v[i][j]+b[i][j])/3;
        v[i][j]=r[i][j];
        b[i][j]=r[i][j];

    }
  }

    return Image(r,v,b);//on retourne l'image

}

Image Image::noirEtBlanc(const int& seuil)
{//cree une nouvelle image
vector<vector<int>> r(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> v(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> b(_rouge.size(),vector<int>(_rouge[0].size()));

    Image c;
    c=this->niveauxGris();//on prend l'image en niveau de gris
  //on parcours les pixels de l'image
    for (int i = 0; i < _rouge.size(); i++) {
      for (int j = 0; j < _rouge[i].size(); j++)
      {
          if (c._rouge[i][j]<seuil)//si le pixel est au dessu du seuil il devient noir
          {
            r[i][j]=0;
            v[i][j]=0;
            b[i][j]= 0;
          }

        else//sinon il deveint blanc
        {
            r[i][j]=255;
            v[i][j]=255;
            b[i][j]= 255;
        }
      }
}
    return Image(r,v,b);//on retourne l'image

}

Image Image::luminosityUp(float& val)
{
    if (val<=1)//si la valeur est inférieur ou égale a 1 la fonction s'arrete
    {
        throw(string("la valeur doit être superieure à 1 !!"));
    }
  //on cree une nouvelle image
    vector<vector<int>> r(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> v(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> b(_rouge.size(),vector<int>(_rouge[0].size()));
//on parcour les pixels de l'image
  for (int i = 0; i < _rouge.size(); i++) {
      for (int j = 0; j < _rouge[i].size(); j++){
          r[i][j]=_rouge[i][j];//on assigne les composant de couleurs de l'image a la nouvelle image
        v[i][j]=_vert[i][j];
        b[i][j]=_bleu[i][j];

        if (r[i][j]*val>255)//si la valeur augmenté par le facteur est supérieur a 255 on assigne 255 a la nouvelle image
            r[i][j]=255;
        else//sinon on assigne la valeur augmenté par le facteur
        r[i][j]=r[i][j]*val;

        if (v[i][j]*val>255)v[i][j]=255;
        else v[i][j]=v[i][j]*val;

        if (b[i][j]*val>255)b[i][j]=255;
        else b[i][j]=b[i][j]*val;

        }
  }
    return Image(r,v,b);
}

Image Image::luminosityDown(float& val)
{
    if (val>=1)//si la valeur est supérieur ou égale a 1 la fonction s'arrete
    {
        throw(string("la valeur doit être superieure à 1 !!"));
    }
  //on cree une nouvelle image
    vector<vector<int>> r(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> v(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> b(_rouge.size(),vector<int>(_rouge[0].size()));

  for (int i = 0; i < _rouge.size(); i++) {
      for (int j = 0; j < _rouge[i].size(); j++){
        //on assigne les composant de couleurs de l'image a la nouvelle image
          r[i][j]=_rouge[i][j];
        v[i][j]=_vert[i][j];
        b[i][j]=_bleu[i][j];

        //si la valeur diminué par le facteur est inférieur a 0 on assigne 0 a la nouvelle image
        if (r[i][j]*val<0)r[i][j]=0;
        else r[i][j]=r[i][j]*val;
        //sinon on assigne la valeur diminué par le facteur
        if (v[i][j]*val<0)v[i][j]=0;
        else v[i][j]=v[i][j]*val;

        if (b[i][j]*val<0)b[i][j]=0;
        else b[i][j]=b[i][j]*val;

        }
  }
    return Image(r,v,b);//on retourne l'image
}

Image Image::contrasteUp(float& val)
{
    if (val<=1)//si la valeur est inférieur ou égale a 1 la fonction s'arrete
    {
        throw(string("la valeur doit être superieure à 1 !!"));
    }
  //on cree une nouvelle image
    vector<vector<int>> r(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> v(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> b(_rouge.size(),vector<int>(_rouge[0].size()));

  int dist;//on cree une variable qui va nous permettre de calculer la distance à 128

  //on parcour les pixels de l'image
  for (int i = 0; i < _rouge.size(); i++) {
      for (int j = 0; j < _rouge[i].size(); j++){
        //on assigne les composant de couleurs de l'image a la nouvelle image
          r[i][j]=_rouge[i][j];
        v[i][j]=_vert[i][j];
        b[i][j]=_bleu[i][j];

        dist = r[i][j]-128;//on calcule la distance à 128

        //si la distance est supérieur a la valeur multiplié par le facteur on assigne la valeur
        if (r[i][j]-dist+dist*2<0)r[i][j]=0;
           else if (r[i][j]-dist+dist*2>255)r[i][j]=255;
                else r[i][j]=r[i][j]-dist+dist*2;

        dist = v[i][j]-128;

        if (v[i][j]-dist+dist*2<0)v[i][j]=0;
            else if (v[i][j]-dist+dist*2>255)v[i][j]=255;
                else v[i][j]=v[i][j]-dist+dist*2;

        dist = b[i][j]-128;

        if (b[i][j]-dist+dist*2<0)b[i][j]=0;
            else if(b[i][j]-dist+dist*2>255)b[i][j]=255;
                else b[i][j]=b[i][j]-dist+dist*2;

        }
  }
    return Image(r,v,b);//on retourne l'image
}

Image Image::contrasteDown(float& val)
{
    if (val>=1)//si la valeur est supérieur ou égale a 1 la fonction s'arrete
    {
        throw(string("la valeur doit être infèrieur à 1 !!"));
    }
  //on cree une nouvelle image
    vector<vector<int>> r(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> v(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> b(_rouge.size(),vector<int>(_rouge[0].size()));

  int dist;//on cree une variable qui va nous permettre de calculer la distance à 128

  //on parcour les pixels de l'image
  for (int i = 0; i < _rouge.size(); i++) {
      for (int j = 0; j < _rouge[i].size(); j++){
        //on assigne les composant de couleurs de l'image a la nouvelle image
          r[i][j]=_rouge[i][j];
        v[i][j]=_vert[i][j];
        b[i][j]=_bleu[i][j];

        dist = r[i][j]-128;//on calcule la distance à 128

        //si la distance est inférieur a la valeur multiplié par le facteur on assigne la valeur
        if (r[i][j]-dist+dist*2<0)r[i][j]=0;
           else if (r[i][j]-dist+dist*2>255)r[i][j]=255;
                else r[i][j]=r[i][j]-dist+dist*2;

        dist = v[i][j]-128;

        if (v[i][j]-dist+dist*2<0)v[i][j]=0;
            else if (v[i][j]-dist+dist*2>255)v[i][j]=255;
                else v[i][j]=v[i][j]-dist+dist*2;

        dist = b[i][j]-128;

        if (b[i][j]-dist+dist*2<0)b[i][j]=0;
            else if(b[i][j]-dist+dist*2>255)b[i][j]=255;
                else b[i][j]=b[i][j]-dist+dist*2;

        }
  }
    return Image(r,v,b);//on retourne l'image
}


Image Image::rognerD(const int& nb)
{
  //on cree une nouvelle image avec moins de place à droite que l'oginale
     vector<vector<int>> r(_rouge.size(),vector<int>(_rouge[0].size()-nb));
  vector<vector<int>> v(_rouge.size(),vector<int>(_rouge[0].size()-nb));
  vector<vector<int>> b(_rouge.size(),vector<int>(_rouge[0].size()-nb));

  //on parcour les pixels de l'image rogner
  for (int i = 0; i < _rouge.size(); i++) {
      for (int j = 0; j < _rouge[i].size()-nb; j++){
        //on assigne les composant de couleurs de l'image a la nouvelle image
          r[i][j]=_rouge[i][j];
        v[i][j]=_vert[i][j];
        b[i][j]=_bleu[i][j];
        }
    }
    return Image(r,v,b);//on retourne l'image
}

Image Image::rognerG(const int& nb)
{
  //on cree une nouvelle image avec moins de place à gauche que l'oginale
     vector<vector<int>> r(_rouge.size(),vector<int>(_rouge[0].size()-nb));
  vector<vector<int>> v(_rouge.size(),vector<int>(_rouge[0].size()-nb));
  vector<vector<int>> b(_rouge.size(),vector<int>(_rouge[0].size()-nb));

  //on parcour les pixels de l'image rogner
  for (int i = 0; i < _rouge.size(); i++) {
      for (int j = nb; j < _rouge[i].size(); j++){
        //on assigne les composant de couleurs de l'image a la nouvelle image
          r[i][j-nb]=_rouge[i][j];
        v[i][j-nb]=_vert[i][j];
        b[i][j-nb]=_bleu[i][j];
        }
  }
    return Image(r,v,b);//on retourne l'image
}

Image Image::rognerH(const int& nb)
{//on cree une nouvelle image avec moins de place en haut que l'oginale
    vector<vector<int>> r(_rouge.size()-nb,vector<int>(_rouge[0].size()));
  vector<vector<int>> v(_rouge.size()-nb,vector<int>(_rouge[0].size()));
  vector<vector<int>> b(_rouge.size()-nb,vector<int>(_rouge[0].size()));

  //on parcour les pixels de l'image rogner
  for (int i = nb; i < _rouge.size(); i++) {
      for (int j = 0; j < _rouge[i].size(); j++){
        //on assigne les composant de couleurs de l'image a la nouvelle image
          r[i-nb][j]=_rouge[i][j];
        v[i-nb][j]=_vert[i][j];
        b[i-nb][j]=_bleu[i][j];
      }
  }
    return Image(r,v,b);//on retourne l'image
}

Image Image::rognerB(const int& nb)
{
  //on cree une nouvelle image avec moins de place en bas que l'oginale
     vector<vector<int>> r(_rouge.size()-nb,vector<int>(_rouge[0].size()));
  vector<vector<int>> v(_rouge.size()-nb,vector<int>(_rouge[0].size()));
  vector<vector<int>> b(_rouge.size()-nb,vector<int>(_rouge[0].size()));
//on parcour les pixels de l'image rogner
  for (int i = 0; i < _rouge.size()-nb; i++) {
      for (int j = 0; j < _rouge[i].size(); j++){
        //on assigne les composant de couleurs de l'image a la nouvelle image
          r[i][j]=_rouge[i][j];
        v[i][j]=_vert[i][j];
        b[i][j]=_bleu[i][j];
      }
  }
    return Image(r,v,b);//on retourne l'image
}

Image Image::rotationG()
{
  //si limage n'est pas carré la fonction s'arrete
    if(_rouge.size() !=_rouge[0].size()){
    throw(string("l'image n'est pas carré"));
  }
  else
  {
    //on cree une nouvelle image
     vector<vector<int>> r(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> v(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> b(_rouge.size(),vector<int>(_rouge[0].size()));

    //on parcour les pixels de l'image
  for (int i = 0; i < _rouge.size(); i++) {
      for (int j = 0; j < _rouge[i].size(); j++){
        //on assigne les composant de couleurs de l'image a la nouvelle image en les mettant à leur nouvelle position
        r[i][j]=_rouge[j][_rouge.size()-1-i];
        v[i][j]=_vert[j][_rouge.size()-1-i];
        b[i][j]=_bleu[j][_rouge.size()-1-i];

      }
  }
  return Image(r,v,b);//on retourne l'image
}

}

Image Image::rotationD()
{
  //si limage n'est pas carré la fonction s'arrete
    if(_rouge.size() !=_rouge[0].size()){
    throw(string("l'image n'est pas carré"));
  }
  else
  {
    //on cree une nouvelle image
     vector<vector<int>> r(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> v(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> b(_rouge.size(),vector<int>(_rouge[0].size()));
//on parcour les pixels de l'image
  for (int i = 0; i < _rouge.size(); i++) {
      for (int j = 0; j < _rouge[i].size(); j++){
        //on assigne les composant de couleurs de l'image a la nouvelle image en les mettant à leur nouvelle position
        r[i][j]=_rouge[_rouge.size()-1-j][i];
        v[i][j]=_vert[_rouge.size()-1-j][i];
        b[i][j]=_bleu[_rouge.size()-1-j][i];

      }
  }
  return Image(r,v,b);//on retourne l'image
}

}

Image Image::retournementH()
{
  //on cree une nouvelle image
    vector<vector<int>> r(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> v(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> b(_rouge.size(),vector<int>(_rouge[0].size()));
//on parcour les pixels de l'image
  for (int i = 0; i < _rouge.size(); i++) {
      for (int j = 0; j < _rouge[i].size(); j++){
        //on assigne les composant de couleurs de l'image a la nouvelle image en les mettais à leur nouvelle position
        r[i][j]=_rouge[i][_rouge.size()-1-j];
        v[i][j]=_vert[i][_rouge.size()-1-j];
        b[i][j]=_bleu[i][_rouge.size()-1-j];

      }
  }
  return Image(r,v,b);//on retourne l'image
}

Image Image::retournementV()
{
  //on cree une nouvelle image
    vector<vector<int>> r(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> v(_rouge.size(),vector<int>(_rouge[0].size()));
  vector<vector<int>> b(_rouge.size(),vector<int>(_rouge[0].size()));

  //on parcour les pixels de l'image
  for (int i = 0; i < _rouge.size(); i++) {
      for (int j = 0; j < _rouge[i].size(); j++){
        //on assigne les composant de couleurs de l'image a la nouvelle image en les mettan à leur nouvelle position
        r[i][j]=_rouge[_rouge.size()-1-i][j];
        v[i][j]=_vert[_rouge.size()-1-i][j];
        b[i][j]=_bleu[_rouge.size()-1-i][j];

      }
  }
  return Image(r,v,b);//on retourne l'image
}

Image Image::agrandissement(int nb)
{
  //si le facteur d'agrandissement est négatif ou égal à 1 la fonction renvoie l'image de base
    if (nb == 1 || nb==0)
    {
        return Image(_rouge,_vert,_bleu);
    }
  //on cree une nouvelle image avec des dimensions multiplier par le facteur d'agrandissement
    vector<vector<int>> r((_rouge.size()*nb),vector<int>((_rouge[0].size()*nb)));
  vector<vector<int>> v((_rouge.size()*nb),vector<int>((_rouge[0].size()*nb)));
  vector<vector<int>> b((_rouge.size()*nb),vector<int>((_rouge[0].size()*nb)));

  //on parcour les pixels de l'image
  for (int i = 0; i < r.size(); i++) {
      for (int j = 0; j < r[i].size(); j++){
        //on assigne les composant de couleurs à l'image en gardant les bon composant en divisant les variables i et j par le facteur d'agrandissement
        r[i][j]=_rouge[i/nb][j/nb];
        v[i][j]=_vert[i/nb][j/nb];
        b[i][j]=_bleu[i/nb][j/nb];
      }
  }

  return Image(r,v,b);//on retourne l'image
}







void Image::writeFile(ofstream& stream)const{
  stream<<"P3"<<endl; //on rajoute P3 au début du fichier pour que l'image ait bien le format .ppm
  stream<<_largeur<<endl; //on rajoute la largeur puis la longueur
  stream<<_longueur<<endl;
  stream<<"255"<<endl; //on rajoute 255 car c'est la valeur maximum que peut prendre un pixel
  for(int i=0;i<_rouge.size();i++){
    for(int j=0; j<_rouge[0].size();j++){
      stream<<_rouge[i][j]<<" "<<_vert[i][j]<<" "<<_bleu[i][j]<<endl; //on entre les valeurs des pixels un a à un
    }
  }
}


string fileName(){ //permet de nommer une image
    string fileN;
    string ext=".ppm"; //l'extension du fichier

    cout<<"Entrez le nom de l'image : ";
    cin>>fileN;

    if (!(fileN.find(ext) != string::npos)) { //si l'extension n'est pas dans le nom de l'image alors on la rajoute
        fileN+=ext;
    }
    return fileN;

}

int menu(){
  int	choice;

  //propose tous les choix possible à l'utilisateur
  cout << "\nEntrez " << endl
  << AFF << " pour afficher l'image " << endl
  << RED << " pour afficher les pixels ou la couleur rouge apparait  " << endl
  << DET << " pour detecter si une couleur apparait " << endl
  << GRAY << " pour afficher les niveaux de gris" << endl
  << BNW << " pour afficher le noir et blanc" << endl
  << LUMI << " pour modifier la luminosite de l'image" << endl
  << CONTR << " pour modifier le contraste de l'image" << endl
  << COP << " pour copier l'image" << endl
  << ROG << " pour rogner l'image" << endl
  << ROT << " pour pivoter l'image" << endl
  << SYM << " pour retourner l'image" << endl
  << AGR << " pour agrandir l'image" << endl
  << FLOU << " pour flouter l'image" << endl
  << BLANC << " pour blanchir l'image" <<endl
  << QUIT << " pour quitter le programme" << endl;
  cin >> choice;

    while (!validChoice(choice))
    {
        cout << choice << " is not a valid option, please enter again: " << endl;
        cin >> choice;
    }
    return choice;
}

bool validChoice(const int& choice) //vérifie  que l'utilisateur a rentré un choix valide pour le programme
{
    return (choice >= AFF && choice <= BLANC ||choice == QUIT);
}




Image Image::copie()const{ //copie l'image
    Image newImage;

  //récupère les valeurs de l'image et les affecte à la nouvelle
    newImage._rouge=_rouge;
    newImage._vert=_vert;
    newImage._bleu=_bleu;

    return newImage;
}










void loadPicture(const string &picture, vector<vector<int>> &red,
                                        vector<vector<int>> &green,
                                        vector <vector<int>> &blue)
{
    // Declaration des variables
    string line; // pour recuperer les lignes du fichier image au format .ppm, qui est code en ASCII.
    string format; //pour recuperer le format de l'image : celui-ci doit être de la forme P3
    string name; // au cas où l'utilisateur se trompe dans le nom de l'image a charger, on redemande le nom.
    int taille;
    vector <int> mypixels; // pour recuperer les donnees du fichier de maniere lineaire. On repartira ensuite ces donnees dans les tableaux correspondants
    ifstream entree; // Declaration d'un "flux" qui permettra ensuite de lire les donnees de l'image.
    int hauteur; // pour bien verifier que l'image est carree, et de taille respectant les conditions fixees par l'enonce
    // Initialisation des variables
    name = picture;
    // Permet d'ouvrir le fichier portant le nom picture
    // ouverture du fichier portant le nom picture
    entree.open(name);
    // On verifie que le fichier a bien ete ouvert. Si cela n'est pas le cas, on redemande un nom de fichier valide
    while (!entree){
        //cin.rdbuf(oldbuf);
        cerr << "Erreur! Impossible de lire de fichier " << name << " ! " << endl;
        cerr << "Redonnez le nom du fichier a ouvrir SVP. Attention ce fichier doit avoir un nom du type nom.ppm." << endl;
        cin >> name;
        entree.open(name); // relance
    }
    // Lecture du nombre definissant le format (ici P3)
    entree >> format;
    // on finit de lire la ligne (caractere d'espacement)
    getline(entree, line);
    // Lecture du commentaire
    getline(entree, line);
    //lecture des dimensions
    entree >> taille >> hauteur;
    getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
    // On verifie que l'image a une taille qui verifie bien les conditions requises par l'enonce.
    // Si cela n'est pas le cas, on redemande un fichier valide, et ce, tant que necessaire.
    while (format != "P3"){
        if (format != "P3"){
            cerr << "Erreur! L'image que vous nous avez donnee a un format ne verifiant pas les conditions requises." << endl;
            cerr << "L'image que vous nous avez donnee doit etre codee en ASCII et non en brut." << endl;
        }
  entree.close();
        // On va redemander un nom de fichier valide.
        do{
            cerr << "Veuillez redonner un nom de fichier qui respecte les conditions de format et de taille. Attention, ce nom doit etre de la forme nom.ppm." << endl;
            cin >> name;
            entree.open(name); // relance
        }while(!entree);
         // Lecture du nombre definissant le format (ici P3)
         entree >> format;
         getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
        // Lecture du commentaire
        getline(entree, line);
        //lecture des dimensions
        entree >> taille >> hauteur; // relance
        getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
    }
    //Lecture de la valeur max
    getline(entree, line);
    //Lecture des donnees et ecriture dans les tableaux :
    // Pour plus de simplicite, on stocke d'abord toutes les donnees dans mypixels
    // dans l'ordre de lecture puis ensuite on les repartira dans les differents tableaux.
    //Les donnees stockees dans mypixels sont de la forme RGB RGB RGB ....
    // Il faudra donc repartir les valeurs R correspondant a la composante rouge de l'image
    // dans le tableau red, de même pour G et B.
    int pix;
    mypixels.resize(3*taille*hauteur); // taille fixe : on alloue une fois pour toutes
    for (int i = 0; i < 3*taille*hauteur; i++){
      entree >> pix;
      mypixels[i]=pix;
    }
    // Remplissage des 3 tableaux : on repartit maintenant les valeurs dans les bonnes composantes
    // Comme dans mypixels, les donnees sont stockees de la maniere suivante : RGB RGB RGB, il faut mettre
    // les valeurs correspondant a la composante rouge dans red, ...
    // Ainsi, les valeurs de la composante rouge correspondent aux valeurs stockes aux indices
    // congrus a 0 mod 3 dans mypixels, que les valeurs de la composante verte correspond aux valeurs
    // stockes aux indices sont congrus a 1 mod 3, ...
     // les valeurs d'une ligne
    int val;
    red.resize(hauteur);
    green.resize(hauteur);
    blue.resize(hauteur);
    for (int i = 0; i < hauteur; i++){
      vector <int> ligneR(taille);
      vector <int> ligneB(taille);  // les lignes ont toutes la même taille
      vector <int> ligneG(taille);
      for (int j = 0; j < taille; j++){
            val =  mypixels[3*j + 3*taille*i];
            ligneR[j]=val;
            val = mypixels[3*j + 1 + 3*taille*i];
            ligneG[j]=val;
            val = mypixels[3*j + 2 + 3*taille*i];
            ligneB[j]=val;
        }
        red[i]=ligneR;
        green[i]=ligneG;
        blue[i]=ligneB;
    }
    // Informations a l'utilisateur pour dire que tout s'est bien passe
    cout << " L'image " << name << " a bien ete chargee dans les tableaux ." << endl;
     entree.close();
 }

vector<vector<int>> Image::getrouge()
{
    return _rouge;
}
  vector<vector<int>> Image::getvert()
  {
      return _vert;
  }
  vector<vector<int>> Image::getbleu()
  {
      return _bleu;
  }
  bool Image::comparaison (Image c)
  {
      return ((c.getrouge() == _rouge) && (c.getvert()==_vert )&& (c.getbleu()==_bleu) );
  }
