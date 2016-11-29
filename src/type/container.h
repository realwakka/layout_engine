#ifndef LE_CONTAINER_H_
#define LE_CONTAINER_H_

#include <list>
#include <algorithm>

namespace le
{

template<typename NodeType>
class Container
{
 public:
  void InsertBefore(NodeType* new_node, NodeType* ref_node);
  
  NodeType* GetFirstNode();
  NodeType* GetLastNode();
  
 private:
  std::list<NodeType*> list_;
  
};

template<typename NodeType>
void Container<NodeType>::InsertBefore(NodeType* new_node, NodeType* ref_node)
{
  if( ref_node ) {
    list_.emplace_back(new_node);
  }
  else {
    auto it = ref_node->GetIterator();
    //auto it = std::find(list_.begin(), list_.end(), new_node);
    it = list_.emplace(it,new_node);
    
  }
}

template<typename NodeType>
NodeType* Container<NodeType>::GetFirstNode()
{
  if( list_.empty() )
    return nullptr;
  else
    return list_.front();
}

template<typename NodeType>
NodeType* Container<NodeType>::GetLastNode()
{
  if( list_.empty() )
    return nullptr;
  else
    return list_.back();
}

template<typename ContainerType, typename NodeType>
class Node
{
 public:
  NodeType* GetNext() { return *(++iter_); }
  NodeType* GetPrev() { return *(--iter_); }

  ContainerType* GetContainer() { return container_; }
  void SetContainer(ContainerType* container) { container_ = container; }

  typename std::list<NodeType*>::iterator GetIterator() const { return iter_; }
  void GetIterator(typename std::list<NodeType*>::iterator iter) { iter_ = iter; }
  
 private:
  typename std::list<NodeType*>::iterator iter_;
  ContainerType* container_;
  
};

}

#endif /* LE_CONTAINER_H_ */
