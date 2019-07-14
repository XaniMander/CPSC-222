#include "chain.h"
#include "chain_given.cpp"

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain(){
  Node* curr = head_->next;
  while (curr!=NULL) {
    delete curr->prev;
    curr->prev = NULL;
    curr = curr->next;
  }
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block & ndata){
    Node* insert = new Node(ndata);
    Node* temp = tail_->prev;
    temp->next = insert;
    insert->next = tail_;
}

/**
 * Modifies the Chain by moving a contiguous subset of len Nodes
 * dist nodes toward the end of the chain beginning from startPos
 * (maintaining the sentinel at the end). Their order is
 * not changed in the move. You may assume that the startPos and
 * len parameters are kind: startPos + len -1 <= . If there
 * are not enough nodes to shift by dist, just shift as many as
 * possible.
 */
void Chain::moveBack(int startPos, int len, int dist){
    Node* frontOfSub = walk(head_,startPos);
    Node* leftUnmoved = frontOfSub->prev;
    Node* backOfSub = walk(frontOfSub,len-1);
    Node* rightUnmoved = backOfSub->next;
    int moveable = size()-(startPos+len);
    if (moveable<dist) dist = moveable;
    Node* newFront = walk(backOfSub,dist);
    Node* newBack = newFront->next;
    leftUnmoved->next = rightUnmoved;
    rightUnmoved->prev = leftUnmoved;
    newFront->next = frontOfSub;
    frontOfSub->prev = newFront;
    newBack->prev = backOfSub;
    backOfSub->next = newBack;
}

/**
 * Rolls the current Chain by k nodes: removes the last
 * k nodes from the Chain and attaches them, in order, at
 * the start of the chain (maintaining the sentinel at the front).
 */
void Chain::roll(int k){
  int startPos = size()-k;
  if (startPos>0) {
    Node* newFront = head_->next;
    Node* newBack = walk(head_,startPos);
    Node* frontOfSub = newBack->next;
    Node* backOfSub = tail_->prev;
    head_->next = frontOfSub;
    frontOfSub->prev = head_;
    backOfSub->next = newFront;
    newFront->prev = backOfSub;
    newBack->next = tail_;
    tail_->prev = newBack;
  }
}

/**
 * Modifies the current chain by reversing the subchain
 * between pos1 and pos2, inclusive. The positions are
 * 1-based. You may assume that pos1 and pos2 are valid
 * locations in the Chain, and that pos2 >= pos1.
 */
void Chain::reverseSub(int pos1, int pos2){
    Node* leftSub = walk(head_,pos1);
    Node* rightSub = walk(head_,pos2);
    Node* outerLeft = leftSub->prev;
    Node* outerRight = rightSub->next;
    Node* prev = leftSub;
    Node* curr = leftSub->next;
    Node* next = curr->next;
    leftSub->prev = curr;
    leftSub->next = outerRight;
    while (prev!=rightSub) {
      curr->next = prev;
      curr->prev = next;
      prev = curr;
      curr = next;
      next = next->next;
    }
    prev->prev = outerLeft;
}

/*
* Modifies both the current and input chains by removing
* nodes from other, and interleaving them between the Nodes
* from the current Chain. The nodes from the other Chain
* should occupy the even locations in the result.
* of the resulting chain should be the sums of the s
* of current and the other. The other chain should have only
* two sentinels and no data nodes at the end of the operation.
* the weave fails and the original
* chains should be unchanged if block sizes are different.
* in that case, the result of the function should be:
* cout << "Block sizes differ." << endl;
*/
void Chain::weave(Chain & other) { // leaves other empty.
  if (height_!=other.height_ || width_!=other.width_) {
    cout << "Block sizes differ." << endl;
  } else {
    Node* currLeft = head_->next;
    Node* currRight = currLeft->next;
    Node* otherCurr = other.head_->next;
    while (currRight!=tail_) {
      Node* nextOther = otherCurr->next;
      currLeft->next = otherCurr;
      otherCurr->prev = currLeft;
      otherCurr->next = currRight;
      currRight->prev = otherCurr;
      otherCurr = nextOther;
      Node* nextCurr = currRight->next;
      currLeft = currRight;
      currRight = nextCurr;
    }
    currLeft->next = otherCurr;
    otherCurr->prev = currLeft;
    otherCurr->next = tail_;
  }
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
    Node* curr = head_;
    while (curr!=tail_) {
      curr = curr->next;
      delete curr->prev;
      curr->prev = NULL;
    }
    delete tail_;
    tail_ = NULL;
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const& other) {
    Node* curr = other.head_;
    while (curr->next!=other.tail_) {
      insertBack(curr->next->data);
    }
}
