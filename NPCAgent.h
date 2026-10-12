#pragma once

#include <vector>
#include "raylib.h"
#include "Pathfinding.h"

class NPCAgent
{
public:
    NPCAgent();
    ~NPCAgent();

    void SetAgentTexture(Texture2D newTexture) { agentTexture = newTexture; }

    void Update();
    void GoToNode(NodeSystem::Node* node);
    void SetNode(NodeSystem::Node* node);
    void SetSpeed(float speed);
    void Draw();

private:
    Vector2 m_position;

    std::vector<NodeSystem::Node*> m_path;
    int m_currentIndex;
    NodeSystem::Node* m_currentNode;
    float m_speed;

    Texture2D agentTexture;
    bool flipAgentTexture;
};
