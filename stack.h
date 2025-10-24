#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : public std::vector<T> //using public bc i wanna use stuff from vector
{
public:
    Stack(){}

    ~Stack(){}

    bool empty() const{
      if(std::vector<T>::empty()){
        return true;
      }
      else{
        return false;
      }
    }

    size_t size() const{
      return std::vector<T>::size();
    }

    void push(const T& item){
      std::vector<T>::push_back(item);
    }

    void pop(){ // throws std::underflow_error if empty
      if(std::vector<T>::empty()){
        throw std::underflow_error("empty");
      }
      return std::vector<T>::pop_back();
    } 

    const T& top() const{
      if(std::vector<T>::empty()){
        throw std::underflow_error("empty");
      }
      return std::vector<T>::back();
    } // throws std::underflow_error if empty
    // Add other members only if necessary
};


#endif