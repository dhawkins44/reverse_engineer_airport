// CSCI 311 - Spring 2023
// Project 3
// Daniel Hawkins

#include <iostream>
#include <sstream>
#include <string>
#include "Graph.h"

using std::cin;
using std::cout;
using std::endl;
using std::make_shared;
using std::ostringstream;
using std::string;

string printPath(bool, Graph, vector<int>);
bool verifyPath(Graph, vector<int>, int, int);

int main(){
  int numNodes, numEdges, maxMiles, initChg, start, end, nodeName,
      hasChgStation, edgeStart, edgeEnd, distance, newGraphSize;
  shared_ptr<Node> startNode, endNode;
  vector<shared_ptr<Node>> relevantNodes;
  vector<int> path, tempPath;

  cin >> numNodes >> numEdges >> maxMiles >> initChg >> start >> end;

  Graph graph = Graph(numNodes);

  for (int i = 0; i < numNodes; i++){
    cin >> nodeName >> hasChgStation;
    shared_ptr<Node> temp = make_shared<Node>(nodeName);

    if (temp->id == start){
      startNode = temp;
    }

    if (temp->id == end){
      endNode = temp;
    }

    if (hasChgStation){
      temp->isChgStation = true;
      if (temp->id != start && temp->id != end){
        relevantNodes.push_back(temp);
      }
    }

    graph.nodes.push_back(temp);
  }

  relevantNodes.insert(relevantNodes.begin(), startNode);
  relevantNodes.push_back(endNode);

  for (int i = 0; i < numEdges; i++){
    cin >> edgeStart >> edgeEnd >> distance;

    graph.adjMatrix[edgeStart][edgeEnd] = distance;
    graph.adjMatrix[edgeEnd][edgeStart] = distance;
    graph.nodes[edgeStart]->neighbors.push_back(graph.nodes[edgeEnd]);
    graph.nodes[edgeEnd]->neighbors.push_back(graph.nodes[edgeStart]);
  }

  Graph newGraph = Graph(relevantNodes.size());

  for (int i = 0; i < relevantNodes.size(); i++){
    newGraph.nodes.push_back(make_shared<Node>(i));

    if (relevantNodes[i]->isChgStation){
      newGraph.nodes[i]->isChgStation = true;
    }
  }

  for (int i = 0; i < relevantNodes.size(); i++){
    graph.dijkstra(relevantNodes[i]->id);

    for (int j = 0; j < newGraph.nodes.size(); j++){
      if (relevantNodes[i]->id == start && !graph.nodes[start]->isChgStation){
        if (graph.nodes[relevantNodes[j]->id]->dist <= initChg){
          newGraph.adjMatrix[newGraph.nodes[i]->id][newGraph.nodes[j]->id] = graph.nodes[relevantNodes[j]->id]->dist;
          newGraph.adjMatrix[newGraph.nodes[j]->id][newGraph.nodes[i]->id] = graph.nodes[relevantNodes[j]->id]->dist;

          if (newGraph.nodes[i] != newGraph.nodes[j]){
            newGraph.nodes[i]->neighbors.push_back(newGraph.nodes[j]);
          }
        }
      } else if (graph.nodes[relevantNodes[j]->id]->dist <= maxMiles){
          newGraph.adjMatrix[newGraph.nodes[i]->id][newGraph.nodes[j]->id] = graph.nodes[relevantNodes[j]->id]->dist;
          newGraph.adjMatrix[newGraph.nodes[j]->id][newGraph.nodes[i]->id] = graph.nodes[relevantNodes[j]->id]->dist;
          
          if (newGraph.nodes[i] != newGraph.nodes[j]){
            newGraph.nodes[i]->neighbors.push_back(newGraph.nodes[j]);
          }
      }
    }
  }

  newGraph.dijkstra(newGraph.nodes.front()->id);

  // Change IDs on nodes to match original graph
  for (int i = 0; i < newGraph.nodes.size(); i++){
    newGraph.nodes[i]->id = relevantNodes[i]->id;
  }

  if (newGraph.nodes.back()->dist != INT_MAX && newGraph.nodes.front()->neighbors.size() != 0){
    path = newGraph.path(newGraph.nodes.back());
  }

  cout << printPath(verifyPath(newGraph, path, initChg, maxMiles), newGraph, path);
  
  return 0;
}

/************************************************************************
 * Prints result of verifyPath function and path of electric car        *
 * g - Graph - graph where path exists                                  *
 * v - bool - boolean representing if path is verified or not           *
 * path - vector<int> - vector containing the IDs of nodes in the order *
 * of the path                                                          *
 * return - string - string result of verifyPath function and path of   *
 * electric car                                                         *
 ************************************************************************/
string printPath(bool v, Graph g, vector<int> path){
  ostringstream out;

  if (v){
    out << "Verify Path: " << v << endl;
    out << g.nodes.back()->dist << ": ";

    for (int j = 0; j < path.size(); j++){
      out << path[j] << " ";
    }

    out << endl;
  } else {
    out << "No suitable path from " << g.nodes.front()->id << " to "
        << g.nodes.back()->id << " exists" << endl;
  }
  
  return out.str();
}

/************************************************************************
 * Determines if the electric car is able to complete path with charge  *
 * constraints                                                          *
 * g - Graph - Graph that contains path                                 *
 * path - vector<int> - vector containing the IDs of nodes in the order *
 * of the path                                                          *
 * i - int - initial charge of electric car                             *
 * c - maximum charge of electric car                                   *
 * return - bool - true if electric car is able to complete path, false *
 * otherwise                                                            *
 ************************************************************************/
bool verifyPath(Graph g, vector<int> path, int i, int c){
  if (path.empty()){
    return false;
  }

  for (int j = 0; j < path.size() - 1; j++){
    if (j == 0 && !g.nodes[0]->isChgStation){
      if (g.adjMatrix[j][j + 1] > i){
        return false;
      }
    } else if (g.adjMatrix[j][j + 1] > c){
      return false;
    }
  }

  return true;
}