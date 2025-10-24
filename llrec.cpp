#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
  //base case
  if(head == NULL){
    smaller = NULL;
    larger = NULL;
    return;
  }

  //saving next node so we can process the current one
  Node* nextNode = head->next; 

  //head recursion on the rest of the list
  llpivot(nextNode, smaller, larger, pivot);

  //processing curr node
  if(head->val <= pivot){ //smaller lsit first
    head->next = smaller;
    smaller = head;
  }
  else{ //large list
    head->next = larger;
    larger = head;
  }

  head = NULL; //set to null after moving all nodes
}



