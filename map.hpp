#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "entities.hpp"
#include <map>



class Node {
public:
    std::unique_ptr<GameEntity> entity;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    Node* parent;

    Node(GameEntity* newEntity) : entity(newEntity), left(nullptr), right(nullptr), parent(nullptr) {}
};



class BSTMap {
private:
    std::unique_ptr<Node> root;
    std::map<int, Node*> nodeRegistry;

public:
    BSTMap() : root(nullptr) {}

    void registerNode(int id, Node* node) {
        if (node != nullptr) {
            nodeRegistry[id] = node;
        }
    }

    Node* getNodeById(int id) {
        if (nodeRegistry.find(id) != nodeRegistry.end()) {
            return nodeRegistry[id];
        }
        return nullptr;
    }

    // function declaration
    void populateMap();



    Node* getRoot() const {
        return root.get();
    }
};




void BSTMap::populateMap() {
    // Root Node - Monster 1, R1 open, R2 exit
    root = std::make_unique<Node>(new Monster("Monster1", 65, 1));
    registerNode(1, root.get());

    // Level 1
    Node* r1 = new Node(new RiverSpace(1)); // River 1
    root->left = std::unique_ptr<Node>(r1);
    registerNode(2, r1);

    Node* dBlue = new Node(new DeadEndSpace()); // Dead end with watcher
    root->right = std::unique_ptr<Node>(dBlue);
    registerNode(3, dBlue);

    // Level 2 under R1
    Node* f1Exit = new Node(new FogSpace()); // F1 exit
    r1->left = std::unique_ptr<Node>(f1Exit);
    registerNode(4, f1Exit);

    // Level 2 under F1 Exit
    Node* m2 = new Node(new Monster("Monster2", 40, 2)); // Monster 2, F3 exit, R2 open
    f1Exit->left = std::unique_ptr<Node>(m2);
    registerNode(5, m2);

    Node* specialR2 = new Node(new RiverSpace(2)); // Placeholder for R2
    f1Exit->right = std::unique_ptr<Node>(specialR2);
    registerNode(6, specialR2);

    // Level 3 under M2
    Node* c = new Node(new CliffSpace()); // Cliff
    m2->left = std::unique_ptr<Node>(c);
    registerNode(7, c);

    Node* f1Enter = new Node(new FogSpace()); // F1 enter
    m2->right = std::unique_ptr<Node>(f1Enter);
    registerNode(8, f1Enter);

    // Level 4 under Special R2
    Node* f4Exit = new Node(new FogSpace()); // F4 exit
    specialR2->right = std::unique_ptr<Node>(f4Exit);
    registerNode(9, f4Exit);

    // Level 5 under F4 Exit
    Node* blueSpace = new Node(new WatcherSpace()); // Blue space with watcher
    f4Exit->right = std::unique_ptr<Node>(blueSpace);
    registerNode(10, blueSpace);

    // Level 6 under Blue (F3 enter)
    Node* f3Enter = new Node(new FogSpace()); // F3 enter
    blueSpace->left = std::unique_ptr<Node>(f3Enter);
    registerNode(11, f3Enter);

    // Level 7 under F3 Enter (R3 exit, blue)
    Node* r3ExitBlue = new Node(new RiverSpace(3)); // R3 exit with blue space
    f3Enter->left = std::unique_ptr<Node>(r3ExitBlue);
    registerNode(12, r3ExitBlue);

    // Level 8 under R3 Exit Blue (C)
    Node* cliff2 = new Node(new CliffSpace()); // Another cliff
    r3ExitBlue->left = std::unique_ptr<Node>(cliff2);
    registerNode(13, cliff2);

    // Level 8 under R3 Exit Blue (F2 exit, blue)
    Node* f2ExitBlue = new Node(new FogSpace()); // F2 exit with blue space
    r3ExitBlue->right = std::unique_ptr<Node>(f2ExitBlue);
    registerNode(14, f2ExitBlue);

    // Further nodes to Boss
    Node* boss = new Node(new Monster("EndBoss", 50, 4)); // End boss
    f2ExitBlue->right = std::unique_ptr<Node>(boss);
    registerNode(15, boss);

}
