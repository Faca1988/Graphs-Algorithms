#include "node.h"
#include "edge.h"

using namespace std;

#define NODEMETHOD true
#define EDGEMETHOD false

typedef vector<Node*> NodesList;
typedef vector<Edge*> EdgesList;

class Graph
{
private:
	void Initialize();
	void LoadNodes(void);
	void LoadEdges(void);

	NodesList rep; // representacion para NODEMETHOD
	EdgesList map; // representacion para EDGEMETHOD

	int nItems; // cantidad de items ingresados (nodos o aristas)
	
	int vertices; // son los nodos utilizados en el EDGEMETHOD
	
	bool graphMethod; // indicador del metodo usado: true->NODEMETHOD; false->EDGEMETHOD

public:
	Graph(bool _graphMethod); // constructor que genera la estructura segun el metodo utilizado
	Graph(void); // constructor que genera la estructura por defecto para trabajar en base a nodos (metodo)
	
	void Load (void);

	int GetSize();
	int GetTotalVortex(void);
	
	Node* GetNode(string nodeId); // retorna un nodo segun su string::id (NODEMETHOD)
	Node* GetNode(int nodeIndex); // retorna un nodo segun su int::index (NODEMETHOD)

	Edge* GetEdge(string vortexA, string vortexB);
	Edge* GetEdge(int positionInVector);

	EdgesList* GetGraph();
	NodesList* GetRepGraph();
};
/***************************************************************************************
                                     DEFINICIONES
****************************************************************************************/
Graph::Graph(bool _graphMethod)
{
	graphMethod = _graphMethod;
	Initialize();
};

Graph::Graph(void)
{
	graphMethod = NODEMETHOD;
	Initialize();
};

void Graph::Initialize()
{
	nItems = 0;
	vertices = 0;
};
	
void Graph::LoadNodes(void)
{
	// Ingresar la cantidad de nodos que va a tener el grafo
	cout << "Ingrese la cantidad de nodos del grafo:" << endl;
	cin >> nItems;

	// Creacion de nodos
	for(int nNode = 0; nNode < nItems; nNode++)
	{
		string nodeId;
		cout << "Ingrese el nombre del nodo " << nNode + 1 << ":" << endl;
		cin >> nodeId;
		Node* node = new Node(nodeId);
		rep.push_back(node);
	}

	// Carga de conecciones
	for(int nNode = 0; nNode < nItems; nNode++)
	{
		int nConnections;
		Node* currentNode = rep[nNode];
		cout << "Nodo " << currentNode->GetId() << endl;
		cout << "Ingrese la cantidad de conexiones:" << endl;
		cin >> nConnections;

		for(int i = 0; i < nConnections; i++)
		{
			string nodeId;
			cout << "Ingrese el nombre del nodo conectado " << i + 1 << ":" << endl;
			cin >> nodeId;
			int distanceFromNode;
			cout << "Ingrese la distancia al nodo conectado:" << endl;
			cin >> distanceFromNode;
			currentNode->AddConnection(nodeId, distanceFromNode);
		}
	}
};

void Graph::LoadEdges(void)
{
	cout << "Ingrese: numero_de_vertices [espacio] nro_de_aristas " << endl;
	cin >> vertices >> nItems;
	
	//Realizamos el ingreso del grafo, almacenando las aristas en un vector con los datos respectivos
    for( int nEdge = 0 ; nEdge < nItems ; nEdge++ )
    {
		string origen, destino;
		int peso;
        
		cout << endl << "Ingrese: Vertice Origen [espacio] Vertice Destino [espacio] peso" << endl; 
        cin >> origen >> destino >> peso;
		
		Edge* edge = new Edge(origen, destino, peso);
		map.push_back(edge);
    };
	cout << endl << endl;
};

void Graph::Load(void)
{
	if (graphMethod == NODEMETHOD)
	{
		LoadNodes();		
	}
	if (graphMethod == EDGEMETHOD)
	{
		LoadEdges();
	}
};

int Graph::GetSize()
{
	int length;
	if (graphMethod == NODEMETHOD)
	{
		length = (int) rep.size();	
	};

	if (graphMethod == EDGEMETHOD)
	{
		length = (int) map.size();
	};

	return length;	
}

int Graph::GetTotalVortex(void)
{
	return vertices;
};

Node* Graph::GetNode(string nodeId)
{
	Node* targetNode = nullptr;
	for(int i = 0; i < GetSize(); i++)
	{
		if(rep[i]->GetId() == nodeId)
		{
			targetNode = rep[i];
		}
	};
	return targetNode;
};

Node* Graph::GetNode(int nodeIndex)
{
	Node* targetNode = rep[nodeIndex];
	return targetNode;
};

Edge* Graph::GetEdge(string vortexA, string vortexB)
{
	Edge* targetEdge = nullptr;
	for (int i = 0; i < GetSize(); i++)
	{
		if( ( map[i]->GetOriginNode() == vortexA || map[i]->GetOriginNode() == vortexB ) &&
			(map[i]->GetDestinationNode() == vortexA || map[i]->GetDestinationNode() == vortexB) )
		{
			targetEdge = map[i];
			break;
		};
	};
	return targetEdge;
};

Edge* Graph::GetEdge(int positionInVector)
{
	Edge* targetEdge = map[positionInVector];
	return targetEdge;
};

EdgesList* Graph::GetGraph()
{
	return &map;	
};

NodesList* Graph::GetRepGraph()
{
	return &rep;		
};

