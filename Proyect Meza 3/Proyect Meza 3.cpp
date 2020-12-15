// Proyect Meza 3.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
using namespace std;

class Grafo
{

   struct Nodo
   {
        int dato; //Informacion del nodo(value)
        bool visitado; //Saber si esta visitado o no (isvisited)
        vector<Nodo*> vecinos; //Vecinos del nodo (neighs)
        
        Nodo(int dato) //Inicializar el nodo(createNode)
        {
            this->dato = dato;
            visitado = false;
       
        }
   };

    int** matrizGrafo; //matrizAdyacencia
    vector <Nodo*> listaGrafo; //lista de adyacencia
    int numVertices; //Cantidad de vertices del grafo

    public:
        Grafo(int numVertices) //Inicializar matriz y lista 
        {
            this->numVertices = numVertices;
            matrizGrafo = new int* [numVertices];
            for (int i = 0; i < numVertices; i++)
            {
                matrizGrafo[i] = new int[numVertices];
                listaGrafo.push_back(new Nodo(i));
            }
            for (int i = 0; i < numVertices; i++)
            {
                for (int j = 0; j < numVertices; j++)
                    matrizGrafo[i][j] = 0;
            }
        }
        
        void addVecino(int vertice1, int vertice2) //Registro de adyacencias del grafo
        {
            matrizGrafo[vertice1 - 1][vertice2 - 1] = 1; //En la matriz
            listaGrafo.at(vertice1 - 1)->vecinos.push_back(listaGrafo.at(vertice2 - 1)); //En la lista
        }

        void verMatriz() //Muestra el grafo puesto en matriz
        {
            for (int i = -1; i < numVertices; i++)
            {
                for (int j = -1; j < numVertices; j++)
                {
                    if (i == -1 && j == -1) {
                        cout << "  ";
                    }
                    else if (i == -1) {
                        cout << j + 1 << " ";
                    }
                    else if (j == -1) {
                        cout << i + 1 << " ";
                    }
                    else {
                        cout << matrizGrafo[i][j] << " ";
                    }
                }
                cout << endl;
            }
        }
        void verLista() //Muestra el grafo puesto en lista
        {
            for (int i = 0; i < listaGrafo.size(); i++)
            {
                Nodo* verticeAct = listaGrafo.at(i);
                cout << verticeAct->dato << " ";
                for (int j = 0; j < verticeAct->vecinos.size(); j++)
                {
                    cout << verticeAct->vecinos.at(j)->dato << " ";
                }
                cout << endl;
            }
        }

        bool isBipartite_Matrix(int src) 
{ 
    //funcion para grafo bipartito
    int* colorArr= new int[numVertices]; 
    for (int i = 0; i < numVertices; ++i) 
        colorArr[i] = -1; 
  
    
    colorArr[src] = 1; 
  
    
    queue <int> q; 
    q.push(src); 
  
    while (!q.empty()) 
    { 
        
        int u = q.front(); 
        q.pop(); 
  
        
        if (matrizGrafo[u][u] == 1) 
        return false;  
  
       
        for (int v = 0; v < numVertices; ++v) 
        { 
            
            if (matrizGrafo[u][v] && colorArr[v] == -1) 
            { 
               
                colorArr[v] = 1 - colorArr[u]; 
                q.push(v); 
            } 
  
           
            else if (matrizGrafo[u][v] && colorArr[v] == colorArr[u]) 
                return false; 
        } 
    } 
    cout << "primer set de vertices" << endl;
  for (int i = 0; i < numVertices; i++)
  {
      if(colorArr[i] == 1){
          cout << i +1 << " ";
      }
  }
  cout << endl;
  cout << "segundo set de vertices" << endl;
  for (int i = 0; i < numVertices; i++)
  {
      if(colorArr[i] != 1){
          cout << i +1 << " ";
      }
  }
   cout << endl;
   
    return true; 
} 
  

};
//Funcion para crear un grafo
Grafo* Crear()
{
    //Codigo para saber cuantos vertices tiene el grafo
    int vertices = 0;
    Grafo* grafo;
    cout << "Creacion del grafo" << endl;
    cout << "Numero de vertices: ";
    cin >> vertices;
    grafo = new Grafo(vertices);
    //Codigo para registrar las adyacencias
    cout << "si deseas dejar de registrar presiona 0";
    while (true)
    {
        int vertice1 = 0, vertice2 = 0;
        system("CLS");
        cout << "Registro de adyacencias de los vertices\n";
        cout << "Del vertice: ";
        cin >> vertice1;
        if (vertice1 == 0)
            break;
        cout << "Al vertice: ";
        cin >> vertice2;
        
        if (grafo != NULL) {
            grafo->addVecino(vertice1, vertice2);
        }
       
    }
    system("CLS");
    return grafo;
}

int main()
{
    //Variables para el menú
    int opcion = 0, subOpcion = 0;
    bool menu = true, subMenu = true, registrar = true;
    //Grafo
    Grafo* grafo;
    //Código para registrar el grafo en la computadora
    grafo = Crear();
    grafo->verMatriz();
    cout << endl;
    grafo->verLista();
    system("pause");
    system("CLS");
    //Codigo para el menú con los ejercicios
    while (menu)
    {
        subMenu = true; subOpcion = 0; opcion = 0;
        cout << "Presiona el numero para acceder a los ejercicios:\n1 para grafos bipartitos\n2 para pareos en un grafo\n3 para grafos dirigidos"<<endl;
        cin >> opcion;
        system("CLS");
        switch (opcion)
        {
        case 1: //Grafos bipartitos
            while (subMenu)
            {
                cout << "Grafos Bipartitos"<<endl;
                cout << "Presiona el numero:\n1 para usar matriz de adyacencia\n2 para usar lista de adyacencia\nCualquier otro numero para salir del ejercicio"<<endl;
                cin >> subOpcion;
                system("CLS");
                switch (subOpcion)
                {
                case 1: //Usando matriz de adyacencia
                    cout << "Grafos Bipartitos con matriz" << endl;
                    if(!grafo->isBipartite_Matrix(0))
                    cout << "no es bipartito "<< endl;
                    break;
                case 2: //Usando lista de adyacencia
                    cout << "Grafos Bipartitos con lista" << endl;
                    break;
                default:
                    subMenu = false;
                    break;
                }
                system("pause");
                system("CLS");
            }
            break;
        case 2: //Pareo de grafos 
            while (subMenu)
            {
                cout << "Pareos de Grafos" << endl;
                cout << "Presiona el numero:\n1 para obtener un pareo del grafo\n2 para determinar si el grafo tiene pareos perfectos\n3 para pareos maximales" << endl;
                cout << "Cualquier otro numero para salir del ejercicio" << endl;
                cin >> subOpcion;
                system("CLS");
                switch (subOpcion)
                {
                case 1: //Pareo del grafo
                    cout << "Pareo del grafo" << endl;
                    break;
                case 2: //Pareo perfecto
                    cout << "Pareos perfectos" << endl;
                    break;
                case 3: //Pareo maximal
                    cout << "Pareos maximales" << endl;
                    break;
                default:
                    subMenu = false;
                    break;
                }
                system("pause");
                system("CLS");
            }
            break;
        case 3: //Grafos dirigidos
            while (subMenu)
            {
                cout << "Grafos dirigidos" << endl;
                cout << "Presiona el numero:\n1 para ver grafo dirigido en matriz\n2 para ver grafo dirigido en lista\n3 para ver BFS\n4 para ver DFS " << endl;
                cout << "Cualquier otro numero para salir del ejercicio" << endl;
                cin >> subOpcion;
                system("CLS");
                switch (subOpcion)
                {
                case 1: //Matriz de grafo dirigido
                    cout << "Matriz grafo dirigido" << endl;
                    break;
                case 2: //Lista de grafo dirigido
                    cout << "Lista grafo dirigido" << endl;
                    break;
                case 3: //BFS de grafo dirigido
                    cout << "BFS" << endl;
                    break;
                case 4: //DFS de grafo dirigido
                    cout << "DFS" << endl;
                    break;
                default:
                    subMenu = false;
                    break;
                }
                system("pause");
                system("CLS");
            }
            break;
        default:
            menu = false;
            break;
        }
    }
}
