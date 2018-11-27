#include <algorithm>
#include "graph.h"
#include "unionFind.h"

#define MAX 1005  //maximo numero de vértices

class Kruskal
{
private:
    Graph* map;             // grafo original para resolver
    Graph* pMST;            // grafo resuelto se guarda en este ptr*
    int nVortices, nEdges;  // nro de vertices y de aristas
    int weight;             // peso de la arista actual
    int total;              // peso total del MST
    int nEdgesMST;         // Numero de Aristas del MST

public:
    Kruskal(Graph* mygraph);
    void resolve();
    void layout();

};

Kruskal::Kruskal(Graph* mygraph)
{
    map = mygraph;
    total = 0;
    nEdgesMST = 0;
    nEdges = map->GetSize();
    nVortices = map->GetTotalVortex();
};
void Kruskal::resolve()
{
    UnionFind<Edge , EdgesList> uf; 
    uf.Init( nVortices, (map->GetGraph()) );  // Inicializamos cada componente

    uf.Sort();                              // Ordenamos las aristas por su comparador

    uf.ShowItemsList();

}


void Kruskal::layout()
{
    //Si el MST encontrado no posee todos los vértices mostramos mensaje de error
    //Para saber si contiene o no todos los vértices basta con que el numero
    //de aristas sea igual al numero de vertices - 1
    if( nVortices - 1 != nEdgesMST )
    {
        puts("No existe MST valido para el grafo ingresado, el grafo debe ser conexo.");
        return;
    }

    puts( "-----El MST encontrado contiene las siguientes aristas-----");
    
    for( int i = 0 ; i < nEdgesMST ; ++i )
    {
        //( vertice u , vertice v ) : weight
        cout <<  "( " << pMST->GetEdge(i)->GetOriginNode() << " , " << pMST->GetEdge(i)->GetDestinationNode() << " ) : " << pMST->GetEdge(i)->GetWeight() << endl; 
    }

    printf( "El costo minimo de todas las aristas del MST es : %d\n" , total );
}