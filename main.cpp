/**********************************************
***Algoritmo: Minimum Spanning Tree - Kruskal
***Autor: Facundo N. Campos
***********************************************/
/*
EJEMPLO DE INPUT
5 6
1 2 2
1 5 3
2 3 1
3 4 5
3 5 2
4 5 4
RESULTADO: MST = 9 [(2,3),(1,2),(3,5),(4,5)]
*/
#include "kruskal.h"
//#include "dijkstra.h"

int main()
{
    /* *******************************************************************
                            ALGORITMO DE KRUSKAL
    *********************************************************************/
    
    Graph* graph = new Graph(EDGEMETHOD);
    graph->Load();

    Kruskal* kk = new Kruskal(graph);
    kk->resolve();
    kk->layout();

    /**********************************************************************/
    
    /* *******************************************************************
                            ALGORITMO DE DIJKSTRA
    *********************************************************************/
    
    /*Graph* mapa = new Graph(); // NODEMETHOD POR OMISION

    mapa->Load();

    Dijkstra* djk = new Dijkstra(mapa);

    string origen, destino;

    cout << "Ingrese: nodo_de_partida [espacio] nodo_de_llegada" << endl;
    cin >> origen >> destino;

    djk->ShowMinimalPath(origen, destino);*/

    /**********************************************************************/
    return 0;
};
