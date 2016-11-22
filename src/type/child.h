#ifndef LE_CHILD_H_
#define LE_CHILD_H_

#include <list>

namespace le
{



template<typename ParentType, typename ChildType>
class Parent
{
 public:
  typedef std::list<Child*> ChildContainer;
  typedef ChildContainer::iterator ChildIterator;
  
 public:
  Child* begin();
  Child* GetLastChild();

 private:
  std::list<Child*> childs_;
  
};

template<typename ParentType, typename ChildType>
class ChildNode
{
 public:
  ChildType* GetNextSibling();
  ChildType* GetPrevSibling();
  ParentType* GetParent();

 private:
  std::list<Child*>::iterator it_;
  ParentType* parent_;
  
};


template<typename ParentType, typename ChildType>
ChildType* ChildNode<ParentType,ChildType>::GetNextSibling()
{
  
  return nullptr;
}


template<typename ParentType, typename ChildType>
ChildType* ChildNode<ParentType,ChildType>::GetPrevSibling()
{
  return nullptr;
}


}

#endif /* LE_CHILD_H_ */
