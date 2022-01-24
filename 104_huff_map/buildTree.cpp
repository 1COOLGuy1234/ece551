#include "node.h"

void helper(priority_queue_t & minPQ) {
  Node * top_1 = minPQ.top();
  minPQ.pop();
  Node * top_2 = minPQ.top();
  minPQ.pop();
  Node * new_node = new Node(top_1, top_2);
  minPQ.push(new_node);
}


Node *  buildTree(uint64_t * counts) {
  // construct minPQ
  priority_queue_t pq;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) pq.push(new Node(i, counts[i]));
  }
  // remove the top 2 nodes
  while (pq.size() > 1) {
    helper(pq);
  }
  return pq.top();
}  
