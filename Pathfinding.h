#pragma once

#include <raylib.h>
#include <string>
#include <cmath>
#include <vector>
#include "Tilemap.h"

namespace NodeSystem
{
    struct Node;

    struct Edge {
        Node* target;
        float cost;
        Edge() { target = nullptr; cost = 0; }
        Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}
    };

    struct Node {

        Vector2 position;
        std::vector<Edge> connections;
        float gScore;
        Node* previous;
        int nodeID;

        Node() { gScore = 0; previous = nullptr; position = { 0,0 }; nodeID = 0; }
        Node(float x, float y) { position.x = x; position.y = y; gScore = 0; nodeID = 0; previous = nullptr; }
        ~Node() { connections.clear(); }

        void SetPosition(float x, float y) { position.x = x; position.y = y; }

        void ConnectTo(Node* other, float cost) { connections.push_back(Edge(other, cost)); }
    };
}

class NodeMap
{
public:
    int m_width, m_height;
    float m_cellSize;

    NodeSystem::Node** m_nodes;
    NodeMap() { m_width = 0; m_height = 0; m_cellSize = 0; m_nodes = nullptr; }
    ~NodeMap();
    void Initialise(std::vector<std::string> asciiMap, int cellSize);

    void Initialise(Tilemap* tileMap, int cellSize);

    NodeSystem::Node* GetNode(int x, int y) const { if (x < 0 || y < 0 || x >= m_width || y >= m_height) return nullptr; return m_nodes[x + m_width * y]; }
    NodeSystem::Node* GetClosestNode(Vector2 worldPos);

    void Draw();
    static void DrawPath(std::vector<NodeSystem::Node*> nodeMapPath, Color lineColor, float lineThickness);

    static std::vector<NodeSystem::Node*> DijkstrasSearch(NodeSystem::Node* startNode, NodeSystem::Node* endNode);
    static std::vector<NodeSystem::Node*> AStarSearch(NodeSystem::Node* startNode, NodeSystem::Node* endNode);

    static float EuclideanDistance(Vector2 pos1, Vector2 pos2);
};

// NPCAgent moved to its own files (NPCAgent.h / NPCAgent.cpp)
