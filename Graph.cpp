// CSCI 311 - Spring 2023
// Project 3 - Graph cpp
// Author: Daniel Hawkins

#include <algorithm>
#include <iostream>
#include "Graph.h"
#include <queue>

using std::cout;
using std::queue;
using std::reverse;

/******************************************
 * Parametized Constructor                *
 * v - int - number of nodes in the graph *
 * return - none                          *
 ******************************************/
Graph::Graph(int v){
  nodes = {};
  adjMatrix.resize(v, vector<int>(v, 0));
}

/*******************************************************************
 * Prints an adjacency list (neighbors) for each node on the graph *
 * return - none                                                   *
 *******************************************************************/
void Graph::printAdjList(){
  for (int i = 0; i < nodes.size(); i++){
    cout << nodes[i]->id << ": ";

    for (int j = 0; j < nodes[i]->neighbors.size(); j++){
       cout << nodes[i]->neighbors[j]->id << " ";
    }
    
    cout << "\n";
  }
}

/******************************************************************************
 * Checks to see if a node is a neighbor of another node                      *
 * u - int - id of node that you want to check for if v is a neighbor of      *
 * v - int - id of node that you are checking to see if it is a neighbor of u *
 * return - bool - true if v is a neighbor of u, false if it is not           *
 ******************************************************************************/
bool Graph::isNeighbor(int u, int v){
  for (int i = 0; i < nodes[u]->neighbors.size(); i++){
    if (nodes[u]->neighbors[i]->id == v) {
      return true;
    }
  }

  return false;
}

/***************************************************************
 * Prepares the graph for a depth first search with DFSVisit() *
 * return - none                                               *
 ***************************************************************/
void Graph::DFS(){
  for (int i = 0; i < nodes.size(); i++){
    nodes[i]->visited = false;
    nodes[i]->predecessor = nullptr;
    nodes[i]->discovered = -1;
    nodes[i]->finished = -1;
  }

  int time = 0;

  for (int i = 0; i < nodes.size(); i++){
    if (nodes[i]->visited == false){
      time = DFSVisit(nodes[i]->id, time);
    }
  }
}

/****************************************
 * Runs a depth-first search of graph   *
 * s - int - starting node of search    *
 * time - int - starting time of search *
 * return - int - finish time of s      *
 ****************************************/
int Graph::DFSVisit(int s, int time){
  time++;
  nodes[s]->discovered = time;
  nodes[s]->visited = true;

  for (int i = 0; i < nodes[s]->neighbors.size(); i++){
    if (nodes[s]->neighbors[i]->visited == false){
      nodes[s]->neighbors[i]->predecessor = nodes[s];
      time = DFSVisit(nodes[s]->neighbors[i]->id, time);
    }
  }

  time++;
  nodes[s]->finished = time;
  return time;
}

/****************************************
 * Runs a breadth-first search of graph *
 * s - int - starting node of search    *
 * return - none                        *
 ****************************************/
void Graph::BFS(int s){
  for (int i = 0; i < nodes.size(); i++){
    nodes[i]->dist = INT_MAX;
    nodes[i]->visited = false;
    nodes[i]->predecessor = nullptr;
  }

  nodes[s]->dist = 0;
  nodes[s]->visited = true;
  queue<shared_ptr<Node>> workQ;
  workQ.push(nodes[s]);
  
  while (workQ.size() > 0){
    shared_ptr<Node> currentNode = workQ.front();
    workQ.pop();
    for (int i = 0; i < currentNode->neighbors.size(); i++){
      if (!currentNode->neighbors[i]->visited){
        currentNode->neighbors[i]->dist = currentNode->dist + 1;
        currentNode->neighbors[i]->visited = true;
        currentNode->neighbors[i]->predecessor = currentNode;
        workQ.push(currentNode->neighbors[i]);
      }
    }
  }
}

/********************************************************************************
 * Determines shortest path distances to all nodes from node s using BFS(int s) *
 * s - int - starting node of search                                            *
 * return - vector<int> - shortest distances of all nodes from node s           *
 ********************************************************************************/
vector<int> Graph::distancesFrom(int s){
  BFS(s);

  vector<int> distances;

  for (int i = 0; i < nodes.size(); i++){
    distances.push_back(nodes[i]->dist);
  }

  return distances;
}

/****************************************************************
 * Determines whether a graph is two colorable                  *
 * return - bool - true if graph is two-colorable, false if not *
 ****************************************************************/
bool Graph::isTwoColorable(){
   for (int i = 0; i < nodes.size(); i++){
    nodes[i]->dist = INT_MAX;
    nodes[i]->visited = false;
    nodes[i]->predecessor = nullptr;
  }

  nodes[0]->dist = 0;
  nodes[0]->visited = true;
  nodes[0]->color = "red";
  queue<shared_ptr<Node>> workQ;
  workQ.push(nodes[0]);
  
  while (workQ.size() > 0){
    shared_ptr<Node> currentNode = workQ.front();
    workQ.pop();
    for (int i = 0; i < currentNode->neighbors.size(); i++){
      if (currentNode->neighbors[i]->color == currentNode->color){
        return false;
      }

      if (!currentNode->neighbors[i]->visited){
        currentNode->neighbors[i]->dist = currentNode->dist + 1;
        currentNode->neighbors[i]->visited = true;
        currentNode->neighbors[i]->predecessor = currentNode;

        if (currentNode->color == "red"){
          currentNode->neighbors[i]->color = "blue";
        } else {
          currentNode->neighbors[i]->color = "red";
        }

        workQ.push(currentNode->neighbors[i]);
      }
    }
  }
  return true;
}

/************************************************************
 * Determines whether a graph is connected                  *
 * return - bool - true if graph is connected, false if not *
 ************************************************************/
bool Graph::isConnected(){
  BFS(0);

  for (shared_ptr<Node> n : nodes){
    if (!n->visited){
      return false;
    }
  }

  return true;
}

/***********************************************************
 * Determines whether a graph has a cycle                  *
 * return - bool - true if graph has a cycle, false if not *
 ***********************************************************/
bool Graph::hasCycle(){
  for (int i = 0; i < nodes.size(); i++){
    nodes[i]->dist = INT_MAX;
    nodes[i]->visited = false;
    nodes[i]->predecessor = nullptr;
  }

  nodes[0]->dist = 0;
  nodes[0]->visited = true;
  queue<shared_ptr<Node>> workQ;
  workQ.push(nodes[0]);
  
  while (workQ.size() > 0){
    shared_ptr<Node> currentNode = workQ.front();
    workQ.pop();
    for (int i = 0; i < currentNode->neighbors.size(); i++){
      if (!currentNode->neighbors[i]->visited){
        currentNode->neighbors[i]->dist = currentNode->dist + 1;
        currentNode->neighbors[i]->visited = true;
        currentNode->neighbors[i]->predecessor = currentNode;
        workQ.push(currentNode->neighbors[i]);
      } else if (currentNode->predecessor != currentNode->neighbors[i]){
        return true;
      }
    }
  }
  return false;
}

/********************************************************************
 * Determines whether a node v is reachable from u                  *
 * return - bool - true if node v is reachable from u, false if not *
 ********************************************************************/
bool Graph::isReachable(int u, int v){
  BFS(u);

  if (!nodes[v]->visited){
    return false;
  }

  return true;
}

/**********************************************************************
 * Determines the shortest path from a target node given a graph with *
 * non-negative edge weights                                          *
 * n - int - starting node                                            *
 * return - none                                                      *
 **********************************************************************/
void Graph::dijkstra(int n){
  for (int i = 0; i < nodes.size(); i++){
    nodes[i]->dist = INT_MAX;
    nodes[i]->predecessor = nullptr;
  }

  nodes[n]->dist = 0;
  PriorityQueue workQ = PriorityQueue();

  for (int i = 0; i < nodes.size(); i++){
    workQ.push(nodes[i]);
  }

  while (workQ.size() > 1){
    shared_ptr<Node> currentNode = workQ.pop();
    
    for (int i = 0; i < currentNode->neighbors.size(); i++){
      if (currentNode->neighbors[i]->dist > currentNode->dist + adjMatrix[currentNode->id][currentNode->neighbors[i]->id]){
        currentNode->neighbors[i]->dist = currentNode->dist + adjMatrix[currentNode->id][currentNode->neighbors[i]->id];
        currentNode->neighbors[i]->predecessor = currentNode;
        currentNode->neighbors[i]->visited = true;
        for (int j = (workQ.size() - 2) / 2; j > -1; j--){
          workQ.minHeapify(j, workQ.size());
        }
      }
    }
  }
}

/**************************************************************************
 * Creates vector of shortest path from a given end node                  *
 * shared_ptr<Node> - n - ending node of path                             *
 * return - vector<int> - vector of node IDs in order of nodes visited in *
 * shortest path                                                          *
 **************************************************************************/
vector<int> Graph::path(shared_ptr<Node> n){
  vector<int> path;

  path.push_back(n->id);

  while (n->predecessor != nullptr){
    n = n->predecessor;
    path.push_back(n->id);

    if (n == nodes[0]){
      break;
    }
  }

  reverse(path.begin(), path.end());

  return path;
}