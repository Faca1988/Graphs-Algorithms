#include "libs.h"

using namespace std;

class Edge
{
private:
    string origin;     //Vértice origen
    string destination;    //Vértice destino
    int weight;       //peso entre el vértice origen y destino
public:
    Edge();
    Edge(string _origin, string _destination, int _weight);
    Edge(string _origin, string _destination);
    void SetEdge(string _origin, string _destination, int _weight);
    void SetOriginNode(string _origin); 
    string GetOriginNode(void); 
    void SetDestinationNode(string _destination);
    string GetDestinationNode(void);
    void SetNodes(string _origin, string _destination);
    void SetWeight(int _weight);
    int GetWeight(void);
    bool operator < ( const Edge& edge ) const
    {
        return weight < edge.weight;
    }
};
/***************************************************************************************
                                     DEFINICIONES
****************************************************************************************/
Edge::Edge()
{
    SetNodes(NULL, NULL);
    SetWeight( oo );
};

Edge::Edge(string _origin, string _destination, int _weight)
{
    SetEdge(_origin, _destination, _weight);
};

Edge::Edge(string _origin, string _destination)
{
    SetNodes(_origin, _destination);
    SetWeight( oo );
}

/*bool Edge::operator < ( const Edge& edge ) const
{
    return weight < edge.weight;
}*/

/*bool Edge::operator > ( const Edge& edge ) const
{
    return weight > edge.weight;
}*/

void Edge::SetOriginNode(string _origin) 
{
    origin = _origin;
};

string Edge::GetOriginNode(void) 
{
    return origin;
};

void Edge::SetDestinationNode(string _destination) 
{
    destination = _destination;
};

string Edge::GetDestinationNode(void) 
{
    return destination;
};

void Edge::SetNodes(string _origin, string _destination)
{
    SetOriginNode(_origin);
    SetDestinationNode(_destination);
};

void Edge::SetWeight(int _weight) 
{
    weight = _weight;
};

int Edge::GetWeight(void) 
{
    return weight;
};

void Edge::SetEdge(string _origin, string _destination, int _weight)
{
    SetNodes(_origin, _destination);
    SetWeight(_weight);
}