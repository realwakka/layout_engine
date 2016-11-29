#ifndef LE_CONTAINER_H_
#define LE_CONTAINER_H_

#include <list>

namespace le
{

template<typename Node>
class Container
{
 public:
  void InsertBefore(Node* new_node, Node* ref_node);
  
  Node* GetFirstNode();
  Node* GetLastNode();

 private:
  std::list<Node*> list_;
  
};

template<typename Node>
void Container<Node>::InsertBefore(Node* new_node, Node* ref_node)
{
  if( ref_node ) {
    auto it = list_.emplace_back(new_node);
  }
  else {
    auto it = std::find(list_.begin(), list_end(), new_node);
    it = list_.emplace(it,new_node);
    
  }
}

template<typename Node>
Node* Container<Node>::GetFirstNode()
{
  if( list_.empty() )
    return nullptr;
  else
    return list_.front();
}

template<typename Node>
Node* Container<Node>::GetLastNode()
{
  if( list_.empty() )
    return nullptr;
  else
    return list_.back();
}

template<typename Container>
class Node
{
 public:
  Node<Container>* GetNext() { return *(++iter_); }
  Node<Container>* GetPrev() { return *(--iter_); }

  Container* GetContainer() { return container; }
  
 private:
  std::list<Node*>::iterator iter_;
  Container* container_;
  
};

}

#endif /* LE_CONTAINER_H_ */
