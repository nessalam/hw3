#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------





int main(int argc, char* argv[])
{
  if(argc < 2) {
      cout << "Please provide an input file" << endl;
      return 1;
  }

  // -----------------------------------------------
  // Feel free to update any code below this point
  // -----------------------------------------------
  Node* head = readList(argv[1]);
  cout << "Original list: ";
  print(head);
  cout << endl;

  // Test out your linked list code
  cout << "test 1: llpivot w/ pivot 10" << endl;
  Node* head1 = readList(argv[1]);
  Node* smaller1 = NULL;
  Node* larger1 = NULL;

  llpivot(head1, smaller1, larger1, 10);

  cout << "smaller than 10 list: ";
  print(smaller1);
  cout << "larger than 10 list: ";
  print(larger1);
  cout << "empty og list, should be empty if it worked lol";
  print(head1);

  dealloc(smaller1);
  dealloc(larger1);
  cout << endl;

  //test to remove even numbers
  cout << "test 2: using filter to remove even numbers" << endl;
  Node* head2 = readList(argv[1]);

  struct RemoveEven {
    bool operator()(int value){
      return (value%2==0);
    }
  };

  RemoveEven removeEven;
  Node* filtered1 = llfilter(head2, removeEven);
  cout << "og list: ";
  Node* temp1 = readList(argv[1]);
  print(temp1);
  dealloc(temp1);

  cout <<"after even numbers are removed:";
  print(filtered1);
  dealloc(filtered1);

  //testing an empty list
  Node* empty = NULL;
  Node* smallEmpty = NULL;
  Node* largeEmpty = NULL;

  llpivot(empty, smallEmpty, largeEmpty, 3);
  cout << "small empty list ";
  print(smallEmpty);
  cout << "large empty list ";
  print(largeEmpty);
  cout << "og empty list ";
  print(empty);

  //tsting singe eleemnt list
  Node* single = new Node(7, NULL);
  Node* smallSingle = NULL;
  Node* largeSingle = NULL;

  llpivot(single, smallSingle, largeSingle, 5);

  cout << "small single";
  print(smallSingle);
  cout << "small single";
  print(largeSingle);
  cout << "og single";
  print(single);

  dealloc(smallSingle);
  dealloc(largeSingle);
  cout << endl;

  return 0;
}
