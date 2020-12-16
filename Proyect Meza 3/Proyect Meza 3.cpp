// Proyect Meza 3.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <tuple>
#include <queue>
#include <algorithm>

using namespace std;
//Hola
struct Nodo
{
    int dato; //Informacion del nodo(value)
    bool visitado; //Saber si esta visitado o no (isvisited)
    vector<Nodo*> vecinos; //Vecinos del nodo (neighs)
    Nodo* padre;
    Nodo(int dato) //Inicializar el nodo(createNode) //Constructor
    {
        this->dato = dato;
        visitado = false;

    }
};

bool compararNodos(Nodo* a, Nodo* b) { return (a->vecinos.size() < b->vecinos.size()); }

class Grafo
{
    public:
        int** matrizGrafo; //matrizAdyacencia
        vector <Nodo*> listaGrafo; //lista de adyacencia
        vector <tuple<int, int>> aristasDFS;
        int numVertices; //Cantidad de vertices del grafo
        vector<int> recorridoDFS;
        vector<int> recorridoBFS;
        bool dirigido;

        Grafo(int numVertices, bool dirigido) //Inicializar matriz y lista //Constructor
        {
            this->dirigido = dirigido;
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
            if (dirigido)
            {
                matrizGrafo[vertice1 - 1][vertice2 - 1] = 1; //En la matriz
                listaGrafo.at(vertice1 - 1)->vecinos.push_back(listaGrafo.at(vertice2 - 1)); //En la lista
            }
            else {
                matrizGrafo[vertice1 - 1][vertice2 - 1] = 1; //En la matriz
                matrizGrafo[vertice2 - 1][vertice1 - 1] = 1; 
                listaGrafo.at(vertice1 - 1)->vecinos.push_back(listaGrafo.at(vertice2 - 1)); //En la lista
                listaGrafo.at(vertice2 - 1)->vecinos.push_back(listaGrafo.at(vertice1 - 1)); 
            }
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
                cout << (verticeAct->dato + 1) << " ";
                for (int j = 0; j < verticeAct->vecinos.size(); j++)
                {
                    cout << (verticeAct->vecinos.at(j)->dato + 1) << " ";
                }
                cout << endl;
            }
        }
        void pareoMaximal() {
            LimpiarVisitados();
            vector<Nodo*> nodos = listaGrafo;
            sort(nodos.begin(), nodos.end(), compararNodos);
            for (int i = 0; i < nodos.size(); i++) {
                Nodo* temp = nodos.at(i);
                if (!temp->visitado) {
                    for (int j = 0; j < temp->vecinos.size(); j++) {
                        if (!temp->vecinos.at(j)->visitado) {
                            temp->vecinos.at(j)->visitado = true;
                            temp->visitado = true;
                            cout << temp->dato << "-" << temp->vecinos.at(j)->dato << endl;
                            break;
                        }
                    }
                }
            }
            LimpiarVisitados();
        }
        void DFS(Nodo* vertice, int vuelta)
        {
            vertice->visitado = true;
            recorridoDFS.push_back((vertice->dato + 1));
            for (int i = 0; i < vertice->vecinos.size(); i++)
            {
                Nodo* vecino = vertice->vecinos.at(i);
                if (!vecino -> visitado)
                {
                    cout << (vertice->dato + 1) << "-" << (vecino->dato + 1) << " ";
                    DFS(vecino, vuelta);
                }
            }
        }
        void BFS(Nodo* vertice)
        {
            queue <Nodo*> cola;
            cola.push(vertice);
            vertice->visitado = true;
            while (cola.size() > 0)
            {
                Nodo* aux = cola.front();
                cola.pop();
                cout << (aux->dato + 1) << " expande a: ";
                recorridoBFS.push_back((aux->dato + 1));
                for (int i = 0; i < aux->vecinos.size(); i++)
                {
                    Nodo* vecino = aux->vecinos.at(i);
                    if (!vecino->visitado)
                    {
                        cola.push(vecino);
                        vecino->visitado = true;
                        vecino->padre = aux;
                        cout << (vecino->dato + 1) << " ";
                    }
                }
                cout << endl;
            }
        }
        bool isBipartite_Matrix(int src) //funcion para grafo bipartito
        { 
            
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
                if(colorArr[i] == 1)
                {
                    cout << i +1 << " ";
                }
            }
            cout << endl;
            cout << "segundo set de vertices" << endl;
            for (int i = 0; i < numVertices; i++)
            {
                if(colorArr[i] != 1)
                {
                  cout << i +1 << " ";
                } 
            }
            cout << endl;
        return true; 
        }   
        void LimpiarVisitados()
        {
            for (int i = 0; i < listaGrafo.size(); i++)
            {
                listaGrafo.at(i)->visitado = false;
            }
        }
};
//Funcion para crear un grafo
Grafo* Crear()
{
    //Codigo para saber cuantos vertices tiene el grafo
    int vertices = 0;
    int dirigido = 0;
    Grafo* grafo;
    cout << "Creacion del grafo" << endl;
    cout << "Numero de vertices: ";
    cin >> vertices;
    cout <<"Presiona 1 si tu grafo es dirigido cualquier otro numero si no lo es\n(Esto afecta la manera en como se almacena el grafo): ";
    cin >> dirigido;
    if (dirigido == 1)
        grafo = new Grafo(vertices, true);
    else
        grafo = new Grafo(vertices, false);
    //Codigo para registrar las adyacencias
    while (true)
    {
        int vertice1 = 0, vertice2 = 0;
        system("CLS");
        cout << "Registro de adyacencias de los vertices\n";
        cout << "si deseas dejar de registrar pon 0 en \"Del vertice:\"\n";
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
    cout << "Matriz de Adyacencia" << endl;
    grafo->verMatriz();
    cout << endl << "Lista de Adyacencia" << endl;
    grafo->verLista();
    cout << endl;
    system("Pause");
    system("CLS");
    return grafo;
}

int main()
{
    //Variables para el menú
    int opcion = 0, subOpcion = 0;
    bool menu = true, subMenu = true, registrar = true;
    //Grafo
    Grafo* grafo = nullptr;
    //Código para registrar el grafo en la computadora
    //grafo = Crear();
    //grafo->verMatriz();
    //cout << endl;
    //grafo->verLista();
    //system("pause");
    //system("CLS");
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
                if (grafo == NULL)
                    grafo = Crear();
                cout << "Grafos Bipartitos"<<endl;
                cout << "Presiona el numero:\n1 para usar matriz de adyacencia\n2 para usar lista de adyacencia\nCualquier otro numero para salir del ejercicio"<<endl;
                cin >> subOpcion;
                system("CLS");
                switch (subOpcion)
                {
                case 1: //Usando matriz de adyacencia
                    cout << "Grafo Bipartitos con matriz" << endl;
                    if(!grafo->isBipartite_Matrix(0))
                        cout << "no es bipartito "<< endl;
                    system("pause");
                    break;
                case 2: //Usando lista de adyacencia
                    cout << "Grafos Bipartitos con lista" << endl;
                    system("pause");
                    break;
                default:
                    subMenu = false;
                    break;
                }
                system("CLS");
            }
            //delete grafo;
            grafo = NULL;
            break;
        case 2: //Pareo de grafos 
            while (subMenu)
            {
                if (grafo == NULL)
                    grafo = Crear();
                cout << "Pareos de Grafos" << endl;
                cout << "Presiona el numero:\n1 para obtener un pareo del grafo\n2 para determinar si el grafo tiene pareos perfectos\n3 para pareos maximales" << endl;
                cout << "Cualquier otro numero para salir del ejercicio" << endl;
                cin >> subOpcion;
                system("CLS");
                switch (subOpcion)
                {
                case 1: //Pareo del grafo
                    cout << "Pareo del grafo" << endl;
                    system("pause");
                    break;
                case 2: //Pareo perfecto
                    cout << "Pareos perfectos" << endl;
                    system("pause");
                    break;
                case 3: //Pareo maximal
                    cout << "Pareos maximales" << endl;
                    grafo->pareoMaximal();
                    system("pause");
                    break;
                default:
                    subMenu = false;
                    break;
                }
                system("CLS");
            }
            delete grafo;
            grafo = NULL;
            break;
        case 3: //Grafos dirigidos
            while (subMenu)
            {
                if (grafo == NULL)
                {
                    grafo = Crear();
                    while (!grafo->dirigido)
                    {
                        system("CLS");
                        cout << "El grafo registrado no es dirigido\nPor favor registra un grafo dirigido\n";
                        system("PAUSE");
                        system("CLS");
                        delete grafo;
                        grafo = NULL;
                        grafo = Crear();
                    }
                }
                    
                cout << "Grafos dirigidos" << endl;
                cout << "Presiona el numero:\n1 para ver grafo dirigido en matriz\n2 para ver grafo dirigido en lista\n3 para ver BFS\n4 para ver DFS " << endl;
                cout << "Cualquier otro numero para salir del ejercicio" << endl;
                cin >> subOpcion;
                system("CLS");
                switch (subOpcion)
                {
                case 1: //Matriz de grafo dirigido
                    cout << "Matriz grafo dirigido" << endl;
                    grafo->verMatriz();
                    system("pause");
                    break;
                case 2: //Lista de grafo dirigido
                    cout << "Lista grafo dirigido" << endl;
                    grafo->verLista();
                    system("pause");
                    break;
                case 3: //BFS de grafo dirigido
                {
                    grafo->LimpiarVisitados();
                    cout << "BFS" << endl;
                    grafo->BFS(grafo->listaGrafo.at(0));
                    cout << endl << "Recorrido BFS desde " << (grafo->listaGrafo.at(0)->dato + 1) << endl;
                    for (int i = 0; i < grafo->recorridoBFS.size(); i++)
                    {
                        if (i != (grafo->recorridoBFS.size() - 1))
                            cout << grafo->recorridoBFS.at(i) << "-";
                        else
                            cout << grafo->recorridoBFS.at(i) << endl;
                    }
                    grafo->recorridoBFS.clear();
                    system("pause");
                }
                    break;
                case 4: //DFS de grafo dirigido
                {
                    grafo->LimpiarVisitados();
                    cout << "DFS" << endl;
                    Nodo* verticeInicio = grafo->listaGrafo.at(0);
                    cout << "Aristas que conforman el arbol abarcador" << endl;
                    grafo->DFS(verticeInicio, 1);
                    cout << endl << "Recorrido DFS desde " << (verticeInicio->dato + 1) << endl;
                    for (int i = 0; i < grafo->recorridoDFS.size(); i++)
                    {
                        if (i != (grafo->recorridoDFS.size() - 1))
                            cout << grafo->recorridoDFS.at(i) << "-";
                        else
                            cout << grafo->recorridoDFS.at(i) << endl;
                    }
                    grafo->recorridoDFS.clear();
                    system("pause");
                }
                    break;
                default:
                    subMenu = false;
                    break;
                }
                system("CLS");
            }
            delete grafo;
            grafo = NULL;
            break;
        default:
            menu = false;
            break;
        }
    }
}
