#ifndef LE_SET_PROP_COMMAND_H_
#define LE_SET_PROP_COMMAND_H_

namespace le {

template<typename Setter, typename Getter, typename Value>
class SetPropCommand
{
 public:
  SetPropCommand(Character* begin, Character *end, Setter setter, Value value);
  virtual ~SetPropCommand();
  
 private:
  Character* begin_;
  Character* end_;

  Setter setter_;
  Value value_;

  Character* fixed_begin_;
  Character* fixed_end_;
  std::vector<Run*> run_list_;
};



template<typename Setter, typename Getter, typename Value>
SetPropCommand::SetPropCommand(Character* begin, Character *end, Setter setter, Value value)
    : begin_(begin),
      end_(end),
      setter_(setter),
      value_(value)
{
  fixed_begin_ = begin;
  while( true ) {
    auto next = fixed_begin_->GetPrevRunCharacter();
    if( next )
      fixed_begin_ = next;
  }

  fixed_end_ = end;
  while( true ) {
    auto next = fixed_end_->GetNextRunCharacter();
    if( next )
      fixed_end_ = next;
  }

  
}
template<typename Setter, typename Getter, typename Value>
void SetRunPropCommand::Apply()
{
  auto front_splitted = begin_->GetRun()->Split(begin_);
  if( front_splitted ) {

  } else {
    
  }

  auto back_splitted = begin_->GetRun()->Split(end_);
}


}  // le

#endif /* LE_SET_PROP_COMMAND_H_ */
