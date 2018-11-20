#include "graph.h"

using namespace std;

class Dijkstra
{
private:
    Graph* g;

    bool ExistSomeNodeWithoutPermanentWeight();
    Node* GetNodeWithLessTemporalWeight();
    void SetTemporalWeights(Node* currentNode);
    NodesList GetMinimalPath(Node* originNode, Node* destinationNode);
    void RenderMinimalPath(NodesList minimalPath);

public:
    Dijkstra(Graph* _g)
    { 
        g = _g; 
    }

    void ShowMinimalPath(string originNodeID, string destinationNodeID);
};

/***************************************************************************************
                                     DEFINICIONES
****************************************************************************************/
bool Dijkstra::ExistSomeNodeWithoutPermanentWeight()
{
    // Busca la existencia de algún nodo con peso permanente
    for (int i = 0; i < g->GetSize(); i++)
    {
        // Define el nodo a evaluar
        Node* node = g->GetNode(i);
        if (node->permanentWeight == INF)
        {
            // El nodo tiene peso permanente
            return true;
        }
    }
    // No encontró ningún nodo sin peso permanente
    return false;
};

Node* Dijkstra::GetNodeWithLessTemporalWeight()
{
    Node* targetNode;
    int targetIndex = 0;
    // Inicializa la variable con un valor muy alto para que el primer nodo 
    // que cumpla con las condiciones la actualice con su peso
    int minorTemporalWeight = 9999;
    // Busca la posición del nodo con el menor peso actual entre todos los nodos del grafo,
    // omitiendo los nodos con pesos permanentes y los nodos con pesos temporales infinitos
    for (int i = 0; i < g->GetSize(); i++)
    {
        // Define el nodo a evaluar
        Node* node = g->GetNode(i);
        // Si no tiene peso permanente
        if (node->permanentWeight == INF)
        {
            // Si tiene peso temporal
            if (node->temporalWeight != INF)
            {
                // Si su peso temporal es menor que el actual menor
                if (node->temporalWeight < minorTemporalWeight)
                {
                    minorTemporalWeight = node->temporalWeight;
                    targetIndex = i;
                }
            }
        }
    }
    targetNode = g->GetNode(targetIndex);
    return targetNode;
};

void Dijkstra::SetTemporalWeights(Node* currentNode)
{
    // Obtiene la cantidad de conecciones que tiene el nodo actual
    int connectionsCounter = (int) currentNode->connections.size();    
    for (int i = 0; i < connectionsCounter; i++)
    {
        // Obtiene la distancia con el nodo
        int connectionDistance =  currentNode->connections[i].distance;
        // Obtiene el nodo de la conexión
        string connectionNodeId = currentNode->connections[i].nodeId;
        Node* connectedNode = g->GetNode(connectionNodeId);
        // Si no tiene peso permanente
        if (connectedNode->permanentWeight == INF)
        {
            // Calcula el peso acumulado
            int accumulatedWeight = currentNode->permanentWeight + connectionDistance;
            // Si no tiene peso temporal
            if (connectedNode->temporalWeight == INF)
            {
                // Asigna el peso acumulado
                connectedNode->temporalWeight = accumulatedWeight;
            }
            else
            {
                // Asigna el menor entre el peso temporal que tiene y el peso acumulado
                connectedNode->temporalWeight = accumulatedWeight < connectedNode->temporalWeight ? accumulatedWeight : connectedNode->temporalWeight;
            }
        }
    }
};

NodesList Dijkstra::GetMinimalPath(Node* originNode, Node* destinationNode)
{
    NodesList minimalPath;
    Node* currentNode = destinationNode;        
    while (currentNode != originNode) 
    {
        // Obtiene la cantidad de conecciones que tiene el nodo actual
        int connectionsCounter = (int) currentNode->connections.size();
        // Busca cual es el nodo previo que corresponde al camino mínimo
        // El peso permanente del nodo actual menos la distancia con el 
        // nodo previo tiene que ser igual al peso permanente del nodo previo
        for (int i = 0; i < connectionsCounter; i++)
        {
            // Obtiene la distancia con el nodo
            int connectionDistance =  currentNode->connections[i].distance;
            // Obtiene el nodo de la conexión
            string connectionNodeId = currentNode->connections[i].nodeId;
            Node* connectedNode = g->GetNode(connectionNodeId);
            if ((currentNode->permanentWeight - connectionDistance) == connectedNode->permanentWeight)
            {
                // Agrega el nodo actual con su conexión a la lista de camino mínimo
                Node* minimalPathNode = new Node(currentNode->GetId());
                minimalPathNode->AddConnection(connectionNodeId, connectionDistance);
                minimalPath.push_back(minimalPathNode);
                // Establece el nodo conectado como el actual para continuar con la evaluación
                currentNode = connectedNode;
                if (currentNode == originNode)
                {
                    // Crea un nuevo nodo con el nombre del nodo actual
                    Node* minimalPathNode = new Node(currentNode->GetId());
                    // Carga el nuevo nodo a la lista de nodos del camino mínimo
                    // No se agrega conexión ya que es el nodo origen
                    minimalPath.push_back(minimalPathNode);
                }
                break;
            }
        }
    }
    return minimalPath;
};

void Dijkstra::RenderMinimalPath(NodesList minimalPath)
{
    int totalDistance = 0;
    int nodesCounter = minimalPath.size();
    cout << endl << endl << "----------------" << "CAMINO MINIMO" << "----------------" << endl << endl;
    for (int i = nodesCounter - 1; i >= 0; i--)
    {
        if (i == nodesCounter - 1)
        {
            cout << "NODO " << minimalPath[i]->GetId();
        }
        else
        {
            int nodeDistance = minimalPath[i]->connections[0].distance;
            totalDistance += nodeDistance;
            cout << " - distancia " << nodeDistance << " - " << "NODO " << minimalPath[i]->GetId();
        }
    }
    cout << endl << endl << "---------------------------------------------" << endl;
    cout << endl << "Cantidad de nodos: " << nodesCounter << endl;
    cout << endl << "Distancia total: " << totalDistance << endl;
    cout << endl << "---------------------------------------------" << endl << endl;
};

void Dijkstra::ShowMinimalPath(string originNodeID, string destinationNodeID)
{
    // Inicializa el nodo actual 
    Node* currentNode = nullptr;
    // Define el nodo origen
    Node* originNode = g->GetNode(originNodeID);
    // Define el nodo destino
    Node* destinationNode = g->GetNode(destinationNodeID);
    // Completa los pesos permanentes de todos los nodos
    while (ExistSomeNodeWithoutPermanentWeight())
    {
        // Define el nodo actual y le establece el peso permanente
        if (currentNode == nullptr)
        {
            // Establece como nodo actual el nodo origen
            currentNode = originNode;
            // Define el peso permanente del nodo actual como 0 por ser el primero
            currentNode->permanentWeight = 0;
        }
        else
        {
            // Busca el nodo con el menor peso temporal para convertirlo en el nodo actual
            currentNode = GetNodeWithLessTemporalWeight();
            // Define el peso permanente del nodo actual
            currentNode->permanentWeight = currentNode->temporalWeight;                
        };
        // Define y/o actualiza los pesos temporales de todas los nodos conectados al nodo actual (que no tengan peso permanente)
        SetTemporalWeights(currentNode);
    }
    // Crea una lista de nodos para el camino mínimo y la completa con los nodos correctos
    NodesList minimalPath = GetMinimalPath(originNode, destinationNode);
    RenderMinimalPath(minimalPath);
};