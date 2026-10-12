#include "NPCAgent.h"
#include "Pathfinding.h"

#include <raylib.h>

NPCAgent::NPCAgent()
{
    m_position.x = 0.0f;
    m_position.y = 0.0f;
    m_currentIndex = 0;
    m_speed = 0.0f;
    m_currentNode = nullptr;
    m_path.clear();
    agentTexture = LoadTexture("ref/m8ra.png");
    flipAgentTexture = false;
}

NPCAgent::~NPCAgent()
{
    UnloadTexture(agentTexture);
    m_path.clear();
}

void NPCAgent::Update()
{
    if (m_path.empty()) return;
    if (m_currentIndex + 1 >= (int)m_path.size()) return;
    NodeSystem::Node* nextNode = m_path.at(m_currentIndex + 1);

    if (m_position.x < nextNode->position.x) { m_position.x++; if (flipAgentTexture) flipAgentTexture = false; }
    if (m_position.x > nextNode->position.x) { m_position.x--; if (!flipAgentTexture) flipAgentTexture = true; }
    if (m_position.y < nextNode->position.y) { m_position.y++; }
    if (m_position.y > nextNode->position.y) { m_position.y--; }

    if (m_position.x == nextNode->position.x && m_position.y == nextNode->position.y) {
        m_currentNode = nextNode;
        m_currentIndex++;
        if (m_currentNode == m_path.back())
        {
            m_position = m_path.back()->position;
            m_path.clear();
        }
    }
}

void NPCAgent::GoToNode(NodeSystem::Node* node)
{
    m_path = NodeMap::DijkstrasSearch(m_currentNode, node);
    m_currentIndex = 0;
}

void NPCAgent::SetNode(NodeSystem::Node* node)
{
    m_currentNode = node;
    if (node) m_position = node->position;
}

void NPCAgent::SetSpeed(float speed)
{
    m_speed = speed;
}

void NPCAgent::Draw()
{
    if (!flipAgentTexture)
    {
        DrawTexturePro(agentTexture,
            Rectangle{ 0.0f, 0.0f, (float)agentTexture.width, (float)agentTexture.height },
            Rectangle{ m_position.x, m_position.y, (float)agentTexture.width, (float)agentTexture.height },
            Vector2{ (float)agentTexture.width * .5f, (float)agentTexture.height - 16.f },
            0.0f, WHITE);
    }
    else
    {
        DrawTexturePro(agentTexture,
            Rectangle{ 0.0f, 0.0f, -(float)agentTexture.width, (float)agentTexture.height },
            Rectangle{ m_position.x, m_position.y, (float)agentTexture.width, (float)agentTexture.height },
            Vector2{ (float)agentTexture.width * .5f, (float)agentTexture.height - 16.f },
            0.0f, WHITE);
    }
}
