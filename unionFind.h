#include <stdio.h>
#include <iostream>
#include <cstring>

#define MAX 1005

template<class Type, class TypeList>
class UnionFind
{
	public:
		void Init( int nItems, TypeList* itemsList);
		int FindRoot(int posItem);		
		void Union(int itemA, int itemB);
		bool SameComponent(int vortexA, int vortexB);
		void Sort();
		void ShowItemsList();

	private:
		int predecessor[MAX];			// guarda la pos. en la itemsList del antecesor. la pos. en este vector es la ref. al item referenciado en la itemsList en la misma pos. 
		vector<Type*> itemsList;	// guarda las dir. de mem. de los elementos del grafo pasado por referencia 
		int nItems;
};

template<class Type, class TypeList>
void UnionFind< Type, TypeList>::Init( int _nItems, TypeList* _itemsList )	// paso la cant de items por valor y el grafo con los items por referencia 
{
	nItems = _nItems;							// copio la cantidad de items en una var. propia
    itemsList = *_itemsList; 					// copio las dir. de mem. a mi lista de ptr*. Estos referencian a los elementos del grafo
	
	// inicializo las listas de elementos
	for( int i = 1 ; i <= nItems ; ++i ) 
	{
		predecessor[i] = i;						// guardo como antecesor la pos. del item actual de la itemsList (el antecesor del item actual es él mismo)
	};
};

//Método para encontrar la raiz del vértice actual en la pos. posItem
template<class Type, class TypeList>
int UnionFind<Type, TypeList>::FindRoot( int posItem ) // ej.: posItem = 3 ===> itemsList[3]
{
	/*
		RECURSIVIDAD. 
		si la pos. del item en la iL(itemsList) es el valor guardado en predecessor[posItem] quiere decir que ese elemento es la raiz,
		sino, guardo como antecesor del item indicado, el antecesor del item referenciado por predecessor[posItem] y asi sucesivamente...
	*/
    return ( posItem == predecessor[posItem] ) ? posItem : predecessor[posItem] = FindRoot( predecessor[posItem] );
};

//Método para unir 2 componentes conexas
template<class Type, class TypeList>
void UnionFind<Type, TypeList>::Union( int posItemA , int posItemB )
{
    /*
		A la pos. del elemento que es raiz del item A en la iL[posItemA] le asigno el valor donde se aloja la raiz del item B en iL[posItemB]
		convirtiendo la raiz del item B en la raiz del item A haciendo que pertenezcan a la misma componente conexa
	*/
	predecessor[ FindRoot( posItemA ) ] = FindRoot( posItemB );
};

//Método que me determina si 2 vértices estan o no en la misma componente conexa
template<class Type, class TypeList>
bool UnionFind<Type, TypeList>::SameComponent( int vortexA , int vortexB )
{
	// si la raiz de A es igual que la de B entoces estan en la misma componente, sino no.
    return ( ( FindRoot(vortexA) == FindRoot(vortexB) ) ? true : false); 
};

template <class Type, class TypeList>
void UnionFind<Type, TypeList>::Sort()
{
	cout << "SORT"<<endl;
	std::sort(itemsList[0], itemsList[nItems-1] );
};

template <class Type, class TypeList>
void UnionFind<Type, TypeList>::ShowItemsList()
{
	cout << "SHOW ITEMSLIST"<<endl;

	for(int i = 0; i < nItems; i++)
	{
		cout << itemsList[i]->GetOriginNode() <<" "<<itemsList[i]->GetWeight()<<endl;
	}
};