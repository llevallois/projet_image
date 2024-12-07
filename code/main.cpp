#include <iostream>
#include "couleur.h"
#include <vector>
#include <fstream>
#include "filtre.h"
void mainTest();

using namespace std;

int main() {

    vector<vector<int>> rouge={{0,0,0,0},{0,0,255,255},{0,255,255,255},{255,255,255,255}};
    vector<vector<int>> vert={{0,0,255,255},{0,255,255,255},{255,255,255,0},{255,255,0,0}};
    vector<vector<int>> bleu={{255,255,0,0},{255,0,0,0},{0,0,0,0},{0,0,0,0}};


    vector<vector<int>> grayVect={{0,50,100,150},{50,100,150,200},{100,150,200,225},{150,200,225,255}};
    vector<vector<int>> grayVect2={ {0,50,100,50,0},
                                      {50,100,150,100,50},
                                      {100,150,200,150,100},
                                      {50,100,150,100,50},
                                      {0,50,100,50,0}};

    Image grayIm(grayVect,grayVect,grayVect);
    Image grayIm2(grayVect2,grayVect2,grayVect2);
    vector<vector<float>> g3={{1./16,1./8,1./16},{1./8,1./4,1./8},{1./16,1./8,1./16}};

    vector<vector<float>> g5={  {1./256,4./256,6./256,4./256,1./256},
                                  {4./256,16./256,24./256,16./256,4./256},
                                  {6./256,24./256,36./256,24./256,6./256},
                                  {4./256,16./256,24./256,16./256,4./256},
                                  {1./256,4./256,6./256,4./256,1./256},
                                  };
    Filtre flouG3(g3,1);
    Filtre flouG5(g5,2);

    Image c2(rouge,vert,bleu);
    ofstream output;
    int r,v,b;
    float val;
    int nb;

    Image c6=c2;
    Image c7=c6;
    Image c8;

    int choix=-1;
    while(choix!=QUIT){
        string fichier=fileName();
        string copieFile=fichier;
        c6=c2;
        choix=menu();

        output.open(fichier);
        switch(choix){
            case AFF:
                c7.display();
                break;

            case RED:
                c7=c6.composanteRouge();
                break;

            case DET:
                cout<<"Entrez 3 valeurs dans l'ordre rouge, vert, bleu"<<endl;
                cin>>r>>v>>b;
                if(c6.detection(r,v,b)) cout<<"Pixel trouve"<<endl;
                else cout<<"Pixel non présent dans l'image"<<endl;
                break;

            case GRAY:
                c7=c6.niveauxGris();
                break;

            case BNW:
                cout<<"Entrez le seuil"<<endl;
                cin>>nb;
                c7=c6.noirEtBlanc(nb);
                break;

            case LUMI:
                  cout<<"Souhaitez-vous augmenter ou diminuer la luminosite (1 pour augmenter, 2 pour diminuer)"<<endl;
                  cin>>nb;
                  while(nb !=1 && nb!=2){
                      cout<<"Choix invalide, veuillez reessayer : ";
                      cin>> nb;
                  }


              if(nb==1){
                  cout<<"Entrez la valeur d'augmentation de la luminosite (doit etre superieure a 1)"<<endl;
                  cin>>val;
                  c7=c6.luminosityUp(val);
              }
              else{
                  cout<<"Entrez la valeur de diminution de la luminosité (doit être inférieure à 1)"<<endl;
                  cin>>val;
                  c7=c6.luminosityDown(val);
              }
              break;

            case CONTR:
                cout<<"Souhaitez-vous augmenter ou diminuer le contraste (1 pour augmenter, 2 pour diminuer)"<<endl;
                cin>>nb;
                while(nb !=1 && nb!=2){
                    cout<<"Choix invalide, veuillez reessayer : ";
                    cin>> nb;
                }

              if(nb==1){
                  cout<<"Entrez la valeur d'augmentation du contraste (doit etre superieure a 1)"<<endl;
                  cin>>val;
                  c7=c6.contrasteUp(val);
              }

              else{
                  cout<<"Entrez la valeur de diminution du contraste (doit être inférieure à 1)"<<endl;
                  cin>>val;
                  c7=c6.contrasteDown(val);
              }
              break;


          case COP:
              for(int i = 0;i<4;i++){
                  copieFile.pop_back();
              }
              copieFile+="-copie.ppm";
              c8=c7.copie();
              break;

          case ROG:
              cout<<"Souhaitez-vous rogner l'image en haut, en bas, a droite ou a gauche ? (1 pour haut, 2 pour bas, 3 pour droite, 4 pour gauche)"<<endl;
              cin>>nb;
              while(nb!=1&&nb!=2&&nb!=3&&nb!=4){
                  cout<<"Choix invalide, veuillez reessayer : ";
                  cin>>nb;
              }

              switch(nb){

              case 1:
                  cout<<"Combien de lignes souhaitez-vous rogner du haut ?"<<endl;
                  cin>>nb;
                  c7=c6.rognerH(nb);
                  break;
              case 2:
                  cout<<"Combien de lignes souhaitez-vous rogner du bas ?"<<endl;
                  cin>>nb;
                  c7=c6.rognerH(nb);
                  break;
              case 3:
                  cout<<"Combien de colonnes souhaitez-vous rogner de la droite  ?"<<endl;
                  cin>>nb;
                  c7=c6.rognerH(nb);
                  break;
              case 4:
                  cout<<"Combien de colonnes souhaitez-vous rogner de la gauche ?"<<endl;
                  cin>>nb;
                  c7=c6.rognerH(nb);
                  break;
              }
              break;

              case ROT:
                  cout<<"Souhaitez-vous pivoter l'image vers la droite ou vers la gauche ? (1 pour droite, 2 pour gauche)"<<endl;
                  cin>>nb;
                  while(nb !=1 && nb!=2){
                      cout<<"Choix invalide, veuillez reessayer : ";
                      cin>> nb;
                  }

              if(nb==1){
                  c7=c6.rotationD();
              }
              else{
                  c7=c6.rotationG();
              }
              break;

              case SYM:
                  cout<<"Souhaitez-vous faire une symétrie verticale ou horizontale ? (1 pour verticale, 2 pour horizontal)"<<endl;
                  cin>>nb;
                  while(nb !=1 && nb!=2){
                      cout<<"Choix invalide, veuillez reessayer : ";
                      cin>> nb;
                  }

              if(nb==1){
                  c7=c6.retournementV();
              }
              else{
                  c7=c6.retournementH();
              }
              break;

              case AGR:
                 cout<<"Par combien souhaitez vous agrandir l'image ?";
                 cin>>nb;
                 c7=c6.agrandissement(nb);
                 break;


              case FLOU:
                  cout<<"Quel flou souhaitez-vous appliquer ? (1 pour un flou de rayon 1, 2 pour un flou de rayon 2)"<<endl;
                  cin>>nb;
                  while(nb !=1 && nb!=2){
                    cout<<"Choix invalide, veuillez reessayer : ";
                    cin>>nb;
                  }
                c7=c6.niveauxGris();
                if(nb==1){
                    c7=flouG3.application(c7);
                }
                else{
                    c7=flouG5.application(c7);
                }
              break;

                ///Ajout fonctionnalité
                //On rajoute la nouvelle fonctionnalité
              case BLANC:
                cout<<"Rentrez une valeur de rouge, de vert et de bleu:"<<endl;
                cin>>r>>v>>b;
                while(r<0 || r>255 || v<0 || v>255 || b<0 || b>255){
                    cout<<"Valeur incorrecte, réessayer."<<endl<<"Rentrez une valeur de rouge, de vert et de bleu:"<<endl;
                    cin>>r>>v>>b;
                }
                c7=c6.blanchirCouleur(r,v,b);
                break;

          case QUIT:
            cout<<"Au revoir !"<<endl;
              break;
          }
          if(choix!=QUIT) cout<<"Traitement effectue"<<endl<<endl;


        c7.writeFile(output);
        output.close();

    }
    //cout<<"\nTest :"<<endl;
    //mainTest();
}

