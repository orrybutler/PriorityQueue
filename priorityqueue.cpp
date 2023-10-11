#include <iostream>
#include "json.hpp"

#include "priorityqueue.h"

using namespace std;

PriorityQueue::PriorityQueue(std::size_t max_size) :
	nodes_(max_size + 1, KeyValuePair()),
	max_size_(max_size),
	size_(0) {
}

void PriorityQueue::insert(Key k) {
	insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
	// TODO: complete this function
    size_ = size_ + 1; // increase the size of the Priority Queue by 1
    size_t i = size_; // Set the size to a variable i
    if (size_ > max_size_) { // Check if size_ is greater than the manx size
        size_ = size_ - 1; // Decrement the size by 1 if the size is greater than the max size
        return; // exit funtion when size is greater than max size
    }
    nodes_[i] = kv; // set the KeyValuePair at i in nodes_ to the new KeyValue Pair
    heapifyUp(i); // Heap up the priority queue for the key of the passed KeyValuePair
}

KeyValuePair PriorityQueue::min() {
	// TODO: complete this function
    return nodes_[1]; // returns the munimum value of the Priority Queue
}

KeyValuePair PriorityQueue::removeMin() {
	// TODO: complete this function
    KeyValuePair removed_node; // Declare a variable KeyVariablePair removed_node
    removed_node = min(); // set removed_node equal to the first element in the queue
    nodes_[1] = nodes_[size_]; // set 1st element in Priority queue equal to the last element in the queue 
    removeNode(size_); // remove the node at the bottom of the priority queue
    size_ = size_ - 1; // decrement the size of the priority queue by 1
    heapifyDown(1); // Take the element from the top of the queue to where it belongs in the queue

    return removed_node; // return the node that was removed
}

bool PriorityQueue::isEmpty() const {
	// TODO: complete this function
    if (nodes_[1].first == 0) {// check if first spot in priority queue is equal to zero
        return true; //return true if is equal to zero
    }
    else {
        return false; // return false if is not equal to zero
    }
}

size_t PriorityQueue::size() const {
	// TODO: complete this function
    return size_; // return the size of the priority queue
}

nlohmann::json PriorityQueue::JSON() const {
	nlohmann::json result;
for (size_t i = 1; i <= size_; i++) {
      nlohmann::json node;
      KeyValuePair kv = nodes_[i];
      node["key"] = kv.first;
      node["value"] = kv.second;
      if (i != ROOT) {
          node["parent"] = std::to_string(i / 2);
      }
      if (2 * i <= size_) {
          node["leftChild"] = std::to_string(2 * i);
      }
      if (2 * i + 1 <= size_) {
          node["rightChild"] = std::to_string(2 * i + 1);
      }
      result[std::to_string(i)] = node;
  }
  result["metadata"]["max_size"] = max_size_;
  result["metadata"]["size"] = size_;
    return result;
}
void PriorityQueue::heapifyUp(size_t i) {
    while (getKey(i/2) > getKey(i)) { // Iterate while key at i/2 is greater than key at i
        if(i/2 == 0) { // check if i/2  is equal to zero
            return; // exit function when i/2 is equal to zero
        }
        swap(nodes_[i], nodes_[i/2]); // swap KeyValuePair at i with KeyValuePair at i/2
        i = i/2; // set i equal to i/2
    }
}

void PriorityQueue::heapifyDown(size_t i) {
    if (2*i > size_) { //check if 2*i is greater than the size of the priority queue
        return; //exit function when 2*i is greater than the size
    }
    if (getKey(i) > getKey(2*i + 1) || getKey(i) > getKey(2*i)) { //check if key at 2*i is less than key at i
        if (getKey(2 * i) < getKey(i)){  // check if key at 2*i is greater than key at i
            if ((getKey(2*i) > getKey(2 * i + 1)) && 2*i == size_) { // check if 2*i key is greater than 2*i + 1 key and check if 2*i  equal to size 
                swap(nodes_[i], nodes_[2*i]); // swap nodes at i and nodes at 2*i
                return heapifyDown(2*i); // reucurse on 2 * i
            }
        }if (getKey(2*i) > getKey(2*i + 1)) { // check if key at 2*i is greater than key at 2*i + 1
            swap(nodes_[i], nodes_[2*i + 1]); // swap nodes at i with nodes at 2*i + 1
            return heapifyDown(2*i + 1); // recurse on 2*i + 1
        }if (getKey(2*i) < getKey(2*i + 1)) { // check if key at 2*i is less than key at 2*i + 1
            swap(nodes_[i], nodes_[2*i]); // swap nodes at i with nodes at 2*i
            return heapifyDown(2*i); // recurse on 2* i
        }if ((getKey(2*i) == getKey(2*i + 1)) && 2*i < size_) {// check if 2 * i is equal to 2*i + 1 and 2*i is less than size
            swap(nodes_[i], nodes_[2*i]); // swap nodes at i with nodes at 2 * i the node on the left
            return heapifyDown(2*i); // recurse on 2 * i
        }
    }
}

void PriorityQueue::removeNode(size_t i) {
	// TODO: complete this function
    nodes_.erase(nodes_.begin() + i + 1); // delete then node that is a distance i from the beginning of the array
}

Key PriorityQueue::getKey(size_t i) {
	// TODO: complete this function
    KeyValuePair foundKey; // declare KeyValuePair found key
    foundKey = nodes_[i]; // set foundKey equal to the KeyValuePair at location i in the priority queue
    return foundKey.first; // return the key of the KVP
}