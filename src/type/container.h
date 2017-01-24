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
  
  typename std::list<NodeType*>::iterator GetNext() const;
  typename std::list<NodeType*>::iterator GetPrev() const;

  ContainerType* GetContainer() const { return container_; }
  void SetContainer(ContainerType* container) { container_ = container; }

  typename std::list<NodeType*>::iterator GetIterator() const { return iter_; }
  void SetIterator(typename std::list<NodeType*>::iterator iter) { iter_ = iter; }
  
 private:
  typename std::list<NodeType*>::iterator iter_;
  ContainerType* container_;
  
};

template<typename ContainerType, typename NodeType>
typename std::list<NodeType*>::iterator Node<ContainerType, NodeType>::GetNext() const
{
  auto tmp = iter_;
  return (++tmp);
}

template<typename ContainerType, typename NodeType>
typename std::list<NodeType*>::iterator Node<ContainerType, NodeType>::GetPrev() const
{
  auto tmp = iter_;
  return (--tmp);
}

template<typename ParentType, typename ChildType>
class Parent
{
 public:
  ChildType* GetFirstChild() const { return childs_.empty() ? nullptr : childs_.front(); }
  ChildType* GetLastChild() const { return childs_.empty() ? nullptr : childs_.back(); }
  int GetChildCount() const { return childs_.size(); }
  ChildType* GetChildAt(int index) const { return childs_[index]; }

  void AddChildAt(int index, ChildType* child, ParentType* parent) {
    if( child == nullptr )
      throw std::exception();
  
    childs_.emplace(childs_.begin() + index, child);
    child->SetParent(parent);
  }

  void AppendChild(ChildType* child, ParentType* parent)
  {
    AddChildAt(GetChildCount(), child, parent);
  }

  void RemoveChildAt(int index) { childs_.erase(childs_.begin() + index); }
  
 private:
  std::vector<ChildType*> childs_;
};

template<typename ParentType, typename ChildType>
class Child
{
 public:
  Child();
  int GetIndex(const ChildType* child) const;
  ParentType* GetParent() const { return parent_; }
  void SetParent(ParentType* parent) { parent_ = parent; }
  

  ChildType* GetNextSibling(const ChildType* child) const;
  ChildType* GetPrevSibling(const ChildType* child) const;
 private:
  ParentType* parent_;
};
template<typename ParentType, typename ChildType>
Child<ParentType,ChildType>::Child()
: parent_(nullptr)
{
}
template<typename ParentType, typename ChildType>
int Child<ParentType,ChildType>::GetIndex(const ChildType* child) const
{
  auto index = 0;
  for( ; index < GetParent()->GetChildCount() ; ++index )
    if( GetParent()->GetChildAt(index) == child )
      break;
  return index;
}

template<typename ParentType, typename ChildType>
ChildType* Child<ParentType,ChildType>::GetNextSibling(const ChildType* child) const
{
  auto parent = GetParent();
  auto child_count = parent->GetChildCount();
  if( parent->GetChildAt(child_count - 1) == child ) {
    return nullptr;
  } else {
    auto index = GetIndex(child);
    return parent->GetChildAt(index - 1);
  }
}

template<typename ParentType, typename ChildType>
ChildType* Child<ParentType,ChildType>::GetPrevSibling(const ChildType* child) const
{
  auto parent = GetParent();
  if( parent->GetChildAt(0) == child ) {
    return nullptr;
  } else {
    auto index = GetIndex(child);
    return parent->GetChildAt(index - 1);
  }
}

  

}

#endif /* LE_CONTAINER_H_ */
