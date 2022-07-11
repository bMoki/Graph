#include<iostream>
#include<vector>
#include<list>
#include<iterator>
#include <cstdio>
#include <cstdlib>

using namespace std;

class Aresta
{
    public:
        int verticeDestinoID;

    Aresta(){}
    Aresta(int destVID){
        verticeDestinoID = destVID;
    }

    void setVerticeDestinoID(int id){
        verticeDestinoID = id;
    }
    int getVerticeDestinoID(){
        return verticeDestinoID;
    }

};

class Vertice
{
   public:
       int vertice_id;

       list<Aresta> arestas;

       Vertice()
       {
        vertice_id = 0;
       }

       Vertice(int id){
        vertice_id = id;
       }

       int getVerticeID()
       {
           return vertice_id;
       }


       void setVerticeID(int id){
        vertice_id = id;
       }


       list<Aresta> getArestas()
       {
           return arestas;
       }

       void printArestas() {
            cout << "[";
            for (auto it = arestas.begin(); it != arestas.end(); it++) {
                cout << "(" << it -> getVerticeDestinoID() << "), ";
            }
            cout << "]";
            cout << endl;
        }
};

class Grafo
{
    public:
        vector<Vertice> vertices;

        Vertice getVertice(int vid){
            Vertice temp;
            for(int i=0;i<vertices.size();i++){
                temp = vertices.at(i);
                if(temp.getVerticeID() == vid){
                    return temp;
                }
            }
            return temp;
        }

        void addVertice(Vertice novoVertice)
        {
            bool check = verificaExistenciaVertice(novoVertice.getVerticeID());
            if(check == true)
            {
                cout<<"Um vertice com esse ID ja existe"<<endl;
            }
            else
            {
                vertices.push_back(novoVertice);
                cout<<"Vertice adicionado com sucesso!"<<endl;
            }
        }

        bool verificaExistenciaVertice(int vid)
        {
            for(int i=0;i<vertices.size();i++)
            {
                if(vertices.at(i).getVerticeID()==vid)
                {
                    return true;
                }
            }
            return false;
        }
        bool verificaExistenciaAresta(int verticePartida, int verticeDestino)
        {
            Vertice v = getVertice(verticePartida);
            list<Aresta> e;
            e = v.getArestas();
            for(auto it=e.begin();it != e.end(); it++){
                if(it -> getVerticeDestinoID()== verticeDestino){
                    return true;
                    break;
                }
            }
            return false;
        }

        void addAresta(int verticePartida, int verticeDestino)
        {
           bool check1 = verificaExistenciaVertice(verticePartida);
           bool check2 = verificaExistenciaVertice(verticeDestino);

           if((check1 && check2 == true))
           {
               bool check3 = verificaExistenciaAresta(verticePartida, verticeDestino);
               if(check3 == true)
               {
                   cout<< "Aresta entre "<< "(" << verticePartida << ") e ("<< verticeDestino << ") ja existe";
               }
               else
               {
                   for(int i=0; i < vertices.size(); i++){
                    if(vertices.at(i).getVerticeID()==verticePartida){
                        Aresta e(verticeDestino);
                        vertices.at(i).arestas.push_back(e);
                    }else if(vertices.at(i).getVerticeID()==verticeDestino){
                        Aresta e(verticePartida);
                        vertices.at(i).arestas.push_back(e);
                    }
                   }
                   cout<<"Aresta entre " << verticePartida << " e " << verticeDestino << " adicionada com sucesso!";
               }
           }
           else
           {
               cout<< "ID de vertice invalido.";
           }
        }

        void imprimeGrafo()
        {
            for(int i=0;i<vertices.size();i++)
            {
                Vertice temp;
                temp = vertices.at(i);
                cout<<" ("<<temp.getVerticeID()<<") --> ";
                temp.printArestas();
            }
        }

        void getTodosVizinhos(int vid)
        {
            cout << getVertice(vid).getVerticeID() << " --> ";
            for (int i = 0; i < vertices.size(); i++) {
              if (vertices.at(i).getVerticeID() == vid) {
                cout << "[";
                for (auto it = vertices.at(i).arestas.begin(); it != vertices.at(i).arestas.end(); it++) {
                  cout << "(" << it -> getVerticeDestinoID() << "), ";
                }
                cout << "]";

              }
            }

        }

        bool hamiltonianCycle( vector<bool> visited ,vector<int>& path, int v)
        {

            if (path.size() == vertices.size())
                for (auto it = vertices.at(v).arestas.begin(); it != vertices.at(v).arestas.end(); it++) {
                    if(it->getVerticeDestinoID() == vertices.at(0).getVerticeID()){
                        path.emplace_back(vertices.at(0).getVerticeID());
                        return true;
                    }
                    return false;
                }

            for (auto it = vertices.at(v).arestas.begin(); it != vertices.at(v).arestas.end(); it++) {
                for(int i=0;i<vertices.size();i++){
                    if (vertices.at(i).getVerticeID() == it->getVerticeDestinoID()) {

                        if (visited[i] == false)
                        {
                            visited[i] = true;
                            path.emplace_back(vertices.at(i).vertice_id);
                            if (hamiltonianCycle(visited,path, i))
                                return true;
                            visited[i] = false;
                            path.pop_back();
                        }
                    }
                }

            }
            return false;
        }

        void deletaAresta(int verticePartida, int verticeDestino)
        {
            bool check = verificaExistenciaAresta(verticePartida, verticeDestino);
            if (check == true) {
              for (int i = 0; i < vertices.size(); i++) {
                if (vertices.at(i).getVerticeID() == verticePartida) {
                  for (auto it = vertices.at(i).arestas.begin(); it != vertices.at(i).arestas.end(); it++) {
                    if (it -> getVerticeDestinoID() == verticeDestino) {
                      vertices.at(i).arestas.erase(it);
                      break;
                    }
                  }
                }

                if (vertices.at(i).getVerticeID() == verticeDestino) {

                  for (auto it = vertices.at(i).arestas.begin(); it != vertices.at(i).arestas.end(); it++) {
                    if (it -> getVerticeDestinoID() == verticePartida) {
                      vertices.at(i).arestas.erase(it);
                      break;
                    }
                  }
                }
              }
              cout << "Aresta entre " << verticePartida << " e " << verticeDestino << " deletada com sucesso." << endl;
            }
        }

         void deletaVertice(int vid)
         {
            int vIndex = 0;
            for (int i = 0; i < vertices.size(); i++) {
              if (vertices.at(i).getVerticeID() == vid) {
                vIndex = i;
              }else{
                cout<<"Vertice nao encontrado!"<<endl;
                return;
              }
            }
            for (int i = 0; i < vertices.size(); i++) {
              for (auto it = vertices.at(i).arestas.begin(); it != vertices.at(i).arestas.end(); it++) {
                if (it -> getVerticeDestinoID() == vid) {
                  vertices.at(i).arestas.erase(it);
                  break;
                }
              }

            }
            vertices.erase(vertices.begin() + vIndex);
            cout << "Vertice deletado com sucesso" << endl;
        }

};
int main(){
    int option=-1, id1, id2, w;
    Grafo g;
    Vertice v1;


    do{
        system("cls");
        cout <<"Selecione uma operacao: \n"<< endl;
        cout <<"1. Adiciona Vertice"<< endl;
        cout <<"2. Deletar Vertice"<< endl;
        cout <<"3. Adiciona Aresta"<< endl;
        cout <<"4. Deletar Aresta"<< endl;
        cout <<"5. Imprime todos vizinhos de um vertice"<< endl;
        cout <<"6. Imprime Grafo"<< endl;
        cout <<"7. Verifica se e hamiltoniano"<< endl;
        cout <<"0. Sair"<< endl;

        cin >> option;
        fflush(stdin);
        switch(option)
        {
            case 0:
            break;
            case 1:
                system("cls");
                cout <<"Operação Adicionar Vertice -"<< endl;
                cout<<"Digite o ID do vertice: ";
                cin>>id1;
                fflush(stdin);
                v1.setVerticeID(id1);
                g.addVertice(v1);
                getchar();

            break;
            case 2:
                system("cls");
                cout <<"Deletar Vertice-"<< endl;
                cout<<"Digite o ID do vertice: ";
                cin>>id1;
                fflush(stdin);
                g.deletaVertice(id1);
                getchar();
            break;
            case 3:
                system("cls");
                cout <<"Operação Adicionar Aresta-"<< endl;
                cout <<"Digite o ID do vertice de partida: ";
                cin >> id1;
                cout <<"Digite o ID do vertice de destino:";
                cin >> id2;
                fflush(stdin);
                g.addAresta(id1,id2);
                getchar();
            break;

            case 4:
                system("cls");
                cout <<"Deletar Aresta-"<< endl;
                cout <<"Digite o ID do vertice de partida: ";
                cin >> id1;
                cout <<"Digite o ID do vertice de destino:";
                cin >> id2;
                fflush(stdin);
                g.deletaAresta(id1,id2);
                getchar();
            break;
            case 5:
                system("cls");
                cout <<"Impreção de todos vizinhos de um vertice-"<< endl;

                cout << "Digite o ID de um vertice: ";
                cin >> id1;
                fflush(stdin);
                g.getTodosVizinhos(id1);
                getchar();
            break;
            case 6:
                system("cls");
                cout <<"Operação de impressão -"<< endl;
                g.imprimeGrafo();
                getchar();
            break;
            case 7:
            {
                system("cls");
                cout<<"Verifica se é hamiltoniano - "<<endl;

                vector<bool> visited(g.vertices.size(), false);
                visited[0] = true;
                vector<int> path;
                path.emplace_back(g.vertices.at(0).getVerticeID());

                if (g.hamiltonianCycle(visited, path, 0))
                {
                    cout<<"É hamiltoniano com o ciclo: "<<endl;
                    for (int i : path)
                        cout << i << "  ";

                }
                else{
                    cout << "Não é hamiltoniano" << endl;
                }
                getchar();
            break;
            }
            default:
                cout <<"Selecione uma opção valida"<< endl;
            break;
        }
        cout << endl;
    } while (option !=0);


    return 0;
    }
