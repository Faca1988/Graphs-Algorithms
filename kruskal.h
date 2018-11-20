#include <algorithm>
#include "graph.h"

#define MAX 1005  //maximo numero de vértices

class Kruskal
{
private:
    Graph* map;
    Graph* pMST;
    int V, E;
    int weight;
    string origin;
    string destination;
    int total;          //weight total del MST
    int numAristas;     //Numero de Aristas del MST

public:
    Kruskal(Graph* mygraph);
    void resolve();
    void layout();

};

Kruskal::Kruskal(Graph* mygraph)
{
    map = mygraph;
    total = 0;
    numAristas = 0;
    E = map->GetSize();
    V = map->GetTotalVortex();
};
void Kruskal::resolve()
{
    
    //Inicializamos cada componente
    
    //Ordenamos las aristas por su comparador [PENDIENTE]

    for( int i = 0 ; i < E ; ++i )
    {   
        //Recorremos las aristas ya ordenadas por weight
        origin = map->GetEdge(i)->GetOriginNode(); //Vértice origin de la arista actual
        destination = map->GetEdge(i)->GetDestinationNode();  //Vértice destination de la arista actual
        weight = map->GetEdge(i)->GetWeight();        //weight de la arista actual

        //Verificamos si estan o no en la misma componente conexa
        if( origin != destination )
        {  //Evito ciclos
            total += weight;              //Incremento el weight total del MST
            pMST[numAristas++] = map[i];  //Agrego al MST la arista actual
           //Union de ambas componentes en una sola [PENDIENTE]
        }
    }
}


void Kruskal::layout()
{
    //Si el MST encontrado no posee todos los vértices mostramos mensaje de error
    //Para saber si contiene o no todos los vértices basta con que el numero
    //de aristas sea igual al numero de vertices - 1
    if( V - 1 != numAristas )
    {
        puts("No existe MST valido para el grafo ingresado, el grafo debe ser conexo.");
        return;
    }

    puts( "-----El MST encontrado contiene las siguientes aristas-----");
    
    for( int i = 0 ; i < numAristas ; ++i )
    {
        //( vertice u , vertice v ) : weight
        cout <<  "( " << pMST->GetEdge(i)->GetOriginNode() << " , " << pMST->GetEdge(i)->GetDestinationNode() << " ) : " << pMST->GetEdge(i)->GetWeight() << endl; 
    }

    printf( "El costo minimo de todas las aristas del MST es : %d\n" , total );
}