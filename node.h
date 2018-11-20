#include "libs.h"

using namespace std;

struct Connection
{
   string nodeId;
   int distance;
};

typedef vector<Connection> ConnectionsList;

class Node
{
private:
    string id;

public:
    ConnectionsList connections;
    int temporalWeight;  
    int permanentWeight;

    Node(string _id)
    {
    	id = _id;
    	temporalWeight = INF;
        permanentWeight = INF;
    }

    void AddConnection(string _nodeId, int _distance)
    {
        Connection newConnection;
        newConnection.nodeId = _nodeId;
        newConnection.distance = _distance;
        connections.push_back(newConnection);
    }

    string GetId()
    {
        return id;
    }
};