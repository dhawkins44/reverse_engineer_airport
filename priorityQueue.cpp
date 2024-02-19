// CSCI 311 - Spring 2023
// Project 3 - Priority Queue cpp file
// Author: Daniel Hawkins

#include <math.h>
#include <utility>
#include "priorityQueue.h"

using std::swap;

/***********************
 * Default constructor *
 * return - none       *
 ***********************/
PriorityQueue::PriorityQueue(){}

/*******************************
 * Retrieves size of heap      *
 * return - int - size of heap *
 *******************************/
int PriorityQueue::size(){ return heap.size(); }

/********************************************************
 * Retrieves plane with lowest priority value           *
 * return - Airplane - plane with lowest priority value *
 ********************************************************/
shared_ptr<Node> PriorityQueue::peek(){ return heap[0]; }

/***********************************************************************
 * Checks whether priority queue is empty                              *
 * return - bool - true if priority queue is empty, false if it is not *
 ***********************************************************************/
bool PriorityQueue::empty(){
  if (heap.empty()){ return true; }
  return false;
}

/*********************************************************************
 * Adds airplane to the priority queue                               *
 * a - Airplane - Airplane that you are adding to the priority queue *
 * return - none                                                     *
 *********************************************************************/
void PriorityQueue::push(shared_ptr<Node> n){
  heap.push_back(n);
  int i = heap.size() - 1;

  while (i > 0 && heap[(i - 1) / 2]->dist > heap[i]->dist){
    swap(heap[i], heap[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

/****************************************************************************
 * Removes the plane with the lowest value priority from the priority queue *
 * return - Airplane - airplane that you removed from the priority queue    *
 ****************************************************************************/
shared_ptr<Node> PriorityQueue::pop(){
  shared_ptr<Node> n = heap[0];
  heap[0] = heap[heap.size() - 1];
  heap.pop_back();
 
  minHeapify(0, heap.size());

  return n;
}

/***************************************************************************
 * Rearranges values of heap to make sure that the heap remains a min heap *
 * when an index i may be out of order                                     *
 * i - int - index of value in heap that may be out of order               *
 * heapSize - int - size of heap                                           *
 * return - none                                                           *
 ***************************************************************************/
void PriorityQueue::minHeapify(int i, int heapSize){
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  int minI = i;
  if (left < heapSize && heap[left]->dist < heap[i]->dist){ minI = left; }
  if (right < heapSize && heap[right]->dist < heap[minI]->dist){ minI = right; }
  if (minI != i){
    swap(heap[i], heap[minI]);
    minHeapify(minI, heapSize);
  }
}
