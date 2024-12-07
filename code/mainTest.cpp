#include <iostream>
#include "couleur.h"
#include <vector>
#include "filtre.h"

using namespace std;
void mainTest() {

    vector<vector<int>> rouge={{0,0,0,0},{0,0,255,255},{0,255,255,255},{255,255,255,255}};
  vector<vector<int>> vert={{0,0,255,255},{0,255,255,255},{255,255,255,0},{255,255,0,0}};
  vector<vector<int>> bleu={{255,255,0,0},{255,0,0,0},{0,0,0,0},{0,0,0,0}};
  Image c(rouge, vert, bleu);

    cout<<"---Test niveauGris---"<<endl;
    cout<<"- cas general (l'image devient grise)"<<endl;

  vector<vector<int>> rouge1={{85,85,85,85},{85,85,170,170},{85,170,170,85},{170,170,85,85}};
  vector<vector<int>> vert1={{85,85,85,85},{85,85,170,170},{85,170,170,85},{170,170,85,85}};
  vector<vector<int>> bleu1={{85,85,85,85},{85,85,170,170},{85,170,170,85},{170,170,85,85}};


    Image c1;
    Image c1a(rouge1, vert1, bleu1);
    c1=c.niveauxGris();
    if (c1.comparaison(c1a))
        cout<<"test passe !"<<endl;
    else
    {
        cout<<"test rate, resultat recu :"<<endl;
        c1.display();
        cout<<"resultat attendu :"<<endl;
        c1a.display();
    }



  cout<<"---Test rognerG---"<<endl;
  cout<<"- cas general (les deux premières colonnes ont ete enlevees)"<<endl;

  vector<vector<int>> rouge2={{0,0},{255,255},{255,255},{255,255}};
  vector<vector<int>> vert2={{255,255},{255,255},{255,0},{0,0}};
  vector<vector<int>> bleu2={{0,0},{0,0},{0,0},{
  0,0}};

    Image c2;
  Image c2a(rouge2, vert2, bleu2);

    c2=c.rognerG(2);
    if (c2.comparaison(c2a))
        cout<<"test passe !"<<endl;
    else
    {
        cout<<"test rate, resultat recu :"<<endl;
        c2.display();
        cout<<"resultat attendu :"<<endl;
        c2a.display();
    }

    cout<<"---Test rotationD---"<<endl;
      cout<<"- cas general (l'image a pivoté vers la droite)"<<endl;


  vector<vector<int>> rouge3={{255,0,0,0},{255,255,0,0},{255,255,255,0},{255,255,255,0}};
  vector<vector<int>> vert3={{255,255,0,0},{255,255,255,0},{0,255,255,255},{0,0,255,255}};
  vector<vector<int>> bleu3={{0,0,255,255},{0,0,0,255},{0,0,0,0},{0,0,0,0}};

    Image c3;
  Image c3a(rouge3, vert3, bleu3);
    c3=c.rotationD();
    if (c3.comparaison(c3a))
        cout<<"test passe !"<<endl;
    else
    {
        cout<<"test rate, resultat recu :"<<endl;
        c3.display();
        cout<<"resultat attendu :"<<endl;
        c3a.display();
    }


  cout<<"---Test retournementV---"<<endl;
  cout<<"- cas general (l'image est inversée verticalement)"<<endl;

  vector<vector<int>> rouge4={{255,255,255,255},{0,255,255,255},{0,0,255,255},{0,0,0,0}};
  vector<vector<int>> vert4={{255,255,0,0},{255,255,255,0},{0,255,255,255},{0,0,255,255}};
  vector<vector<int>> bleu4={{0,0,0,0},{0,0,0,0},{255,0,0,0},{255,255,0,0}};


    Image c4;
  Image c4a(rouge4,vert4,bleu4);
    c4=c.retournementV();
    if (c4.comparaison(c4a))
        cout<<"test passe !"<<endl;
    else
    {
        cout<<"test rate, resultat recu :"<<endl;
        c4.display();
        cout<<"resultat attendu :"<<endl;
        c4a.display();
    }
}
