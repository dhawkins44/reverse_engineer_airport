// CSCI 311 - Spring 2023
// Project 3 - Node cpp
// Author: Daniel Hawkins

#include "Node.h"
#include <limits.h>

/***********************
 * Default Constructor *
 * return - none       *
 ***********************/
Node::Node(){
  id = 0;
  idTwo = 0;
  dist = INT_MAX;
  discovered = -1;
  finished = -1;
  visited = false;
  isChgStation = false;
  color = "";
  predecessor = nullptr;
  neighbors = {};
}

/******************************
 * Parametized Constructor    *
 * i - int - id given to Node *
 * return - none              *
 ******************************/
Node::Node(int i){
  id = i;
  idTwo = 0;
  dist = INT_MAX;
  discovered = -1;
  finished = -1;
  visited = false;
  isChgStation = false;
  color = "";
  predecessor = nullptr;
  neighbors = {};
}