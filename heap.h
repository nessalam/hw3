#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;
  int m_ary;
  PComparator comp;

  //helper func for returning arr index of the best child
  int getBestChild(int parent);
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c){
  m_ary = m;
  comp = c;
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap(){}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item){
  data.push_back(item);
  int index = data.size() - 1;

  //checking n swapping
  while(index > 0){
    int parent_index = (index - 1)/ m_ary;
    if(comp(data[index], data[parent_index])){
      //swapping w/ parent
      T temp = data[parent_index];
      data[parent_index] = data[index];
      data[index] = temp;
      index = parent_index;
    }
    else{
      break;
    }
  }
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const{
  return data.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const{
  return data.size();
}

template <typename T, typename PComparator>
int Heap<T, PComparator>::getBestChild(int parent){
  //finding first child's index
  int firstChild = parent * m_ary + 1;
  //check if the parent even has anyc hildren
  if(firstChild >= (int)data.size()){
    return -1; //no children
  }

  //start by assuming that the first child is the best
  int bestChild = firstChild;
  //look at the rest of the children
  for(int i = 1; i < m_ary; i++){
    int childIndex = firstChild + i;
    //make sure the index actually exists and if the child is better, update bestChild
    if(childIndex < (int)data.size() && comp(data[childIndex], data[bestChild])){
      bestChild = childIndex; 
    }
  }
  return bestChild;
}
// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("heap empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("heap empty");
  }
  //if theres only one element, just remove it
  if(data.size() == 1){
    data.pop_back();
    return;
  }

  //moving last element to root
  data[0] = data.back();
  data.pop_back();

  //keep swapping all the way to the end
  int curr = 0;
  while(true){
    int bestChild = getBestChild(curr);
    if(bestChild == -1){ //if no children exist, break
      break;
    }

    //if the best child is better than curr, swap
    if(comp(data[bestChild], data[curr])){
      T temp = data[curr];
      data[curr] = data[bestChild];
      data[bestChild] = temp;
      curr = bestChild;
    }
    else{
      break;
    }
  }
}

#endif

