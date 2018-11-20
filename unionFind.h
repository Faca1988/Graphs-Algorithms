#include <stdio.h>
#include <iostream>
#include <cstring>
#include "edge.h"

#define MAX 1005

class UnionFind
{
	public:
		void MakeSet( int nItems);
		int Find(int item);
		void Union(int itemA, int itemB);
		bool SameComponent(int vortexA, int vortexB);

	private:
		int predecessor[MAX];
};

void UnionFind::MakeSet( int n )
{
    for( int i = 1 ; i <= n ; ++i ) UnionFind::predecessor[ i ] = i;
}

//Método para encontrar la raiz del vértice actual X
int UnionFind::Find( int x )
{
    return ( x == predecessor[ x ] ) ? x : predecessor[ x ] = Find( predecessor[ x ] );
}

//Método para unir 2 componentes conexas
void UnionFind::Union( int itemA , int itemB )
{
    predecessor[ Find(itemA) ] = Find(itemB);
}

//Método que me determina si 2 vértices estan o no en la misma componente conexa
bool UnionFind::SameComponent( Nodex* vortexA , Nodex* vortexB )
{
    return ( ( Find(vortexA) == Find(vortexB) ) ? true : false);    
}