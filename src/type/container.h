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
  typename std::list<NodeType*>::iterator InsertBefore(NodeType* new_node, typename std::list<NodeType*>::iterator iter);
  typename std::list<NodeType*>::iterator Append(NodeType* node);
  void Remove(typename std::list<NodeType*>::iterator iter);
  
  NodeType* GetFirstNode() const;
  NodeType* GetLastNode() const;
  
 private:
  std::list<NodeType*> list_;
  
};

template<typename NodeType>
typename std::list<NodeType*>::iterator Container<NodeType>::InsertBefore(NodeType* new_node, typename std::list<NodeType*>::iterator iter)
{
  return list_.emplace(iter, new_node);
}

template<typename NodeType>
typename std::list<NodeType*>::iterator Container<NodeType>::Append(NodeType* node)
{
  list_.emplace_back(node);
  return --list_.end();
}


// template<typename NodeType>
// void Container<NodeType>::InsertBefore(NodeType* new_node, NodeType* ref_node)
// {
//   if( ref_node == nullptr ) {
//     list_.emplace_back(new_node);
//   }
//   else {
//     auto it = ref_node->GetIterator();
//     it = list_.emplace(it,new_node);
    
//   }
// }

template<typename NodeType>
void Container<NodeType>::Remove(typename std::list<NodeType*>::iterator iter)
{
  list_.erase(iter);
}

template<typename NodeType>
NodeType* Container<NodeType>::GetFirstNode() const
{
  if( list_.empty() )
    return nullptr;
  else
    return list_.front();
}

template<typename NodeType>
NodeType* Container<NodeType>::GetLastNode() const
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
  Node() : container_(nullptr) {}
  virtual ~Node() {}
  
  typename std::list<NodeType*>::iterator GetNext();
  typename std::list<NodeType*>::iterator GetPrev();

  ContainerType* GetContainer() { return container_; }
  void SetContainer(ContainerType* container) { container_ = container; }

  typename std::list<NodeType*>::iterator GetIterator() const { return iter_; }
  void SetIterator(typename std::list<NodeType*>::iterator iter) { iter_ = iter; }
  
 private:
  typename std::list<NodeType*>::iterator iter_;
  ContainerType* container_;
  
};

template<typename ContainerType, typename NodeType>
typename std::list<NodeType*>::iterator Node<ContainerType, NodeType>::GetNext()
{
  auto tmp = iter_;
  return (++tmp);
}

template<typename ContainerType, typename NodeType>
typename std::list<NodeType*>::iterator Node<ContainerType, NodeType>::GetPrev()
{
  auto tmp = iter_;
  return (--tmp);
}





// template<typename Container, typename Node, typename NodeDelegate>
// class ContainerDelegate {
//  public:
//   void InsertBefore(NodeDelegate* new_delegate, NodeDelegate* ref_delegate);
//  private:
//   std::list<NodeDelegate*> list_;
//   Container* container_;
// };

// template<typename Container, typename Node, typename NodeDelegate>
// void ContainerDelegate::InsertBefore(NodeDelegate* new_delegate, NodeDelegate* ref_delegate)
// {
//   if( ref_delegate == nullptr ) {
//     list_.emplace_back(new_delegate);
//   } else {
//     auto it = list_.emplace(ref_delegate->GetIterator(), new_delegate);
//     new_delegate->SetIterator(it);
//     new_delegate->
//   }

// }

// template<typename Container, typename Node, typename ContainerDelegate>
// class NodeDelegate {
//  public:

  
//   typename std::list<NodeDelegate*>::iterator GetIterator() const { return iter_; }
//   void SetIterator(typename std::list<NodeDelegate*>::iterator iter) { iter_ = iter; }

//   void SetContainerDelegate(ContainerDelegate* container_delegate) { container_delegate_ = container_delegate; }
//   ContainerDelegate* GetContainerDelegate() const { return container_delegate_; }
  
//  private:
//   typename std::list<NodeDelegate*>::iterator iter_;
//   ContainerDelegate* container_delegate_;
//   Node* node_;
// };

}

#endif /* LE_CONTAINER_H_ */
