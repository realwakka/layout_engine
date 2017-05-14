#ifndef LE_SET_RUN_PROP_COMMAND_H_
#define LE_SET_RUN_PROP_COMMAND_H_

#include <functional>
#include "controller/command/command.h"
#include "controller/command/split_run_command.h"

namespace le {

template<typename Setter, typename Getter, typename Value>
class SetRunPropCommand : public Command
{
 public:
  SetRunPropCommand(Character* begin, Character* end, Setter setter, Getter getter, Value value);
  virtual ~SetRunPropCommand() {}

  void Apply() override;
  void UnApply() override;
  void ReApply() override;

  std::string GetDecription() override { return "SetRunPropCommand"; }

 private:
  Character* begin_;
  Character* end_;

  SplitRunCommand split_begin_;
  SplitRunCommand split_end_;

  Setter setter_;
  Getter getter_;
  Value value_;

  std::vector<std::pair<Run*, Value>> value_list_;

};



template<typename Setter, typename Getter, typename Value>
SetRunPropCommand<Setter, Getter, Value>::SetRunPropCommand(Character* begin, Character *end, Setter setter, Getter getter, Value value)
    : begin_(begin),
      end_(end),
      split_begin_(begin),
      split_end_(end),
      value_(value),
      setter_(setter),
      getter_(getter)
{
}

template<typename Setter, typename Getter, typename Value>
void SetRunPropCommand<Setter, Getter, Value>::Apply()
{
  split_begin_.Apply();
  split_end_.Apply();

  auto begin_run = begin_->GetRun();
  auto end_run = end_->GetRun();

  value_list_.clear();
  for( auto run = begin_run ; run != end_run ; run = run->GetNextRun() ) {
    auto old_value = (run->GetRunProp().*(getter_))();
    value_list_.emplace_back(run, old_value);
    (run->GetRunProp().*(setter_))(value_ );
    run->UpdateGlyph();
  }
}

template<typename Setter, typename Getter, typename Value>
void SetRunPropCommand<Setter, Getter, Value>::UnApply()
{
  split_begin_.UnApply();
  split_end_.UnApply();

  value_list_.clear();
  for( auto&& pair : value_list_ ) {
    (pair.first->GetRunProp().*setter_)(pair.second);
  }
}

template<typename Setter, typename Getter, typename Value>
void SetRunPropCommand<Setter, Getter, Value>::ReApply()
{
  Apply();
}

namespace command_util {

template<typename Setter, typename Getter, typename Value>
SetRunPropCommand<Setter, Getter, Value>* CreateSetRunPropCommand(Character* begin, Character *end, Setter&& setter, Getter&& getter, Value&& value)
{
  return new SetRunPropCommand<Setter, Getter, Value>(begin, end, setter, getter, value);
}


}  // command_util


}  // le

#endif /* LE_SET_RUN_PROP_COMMAND_H_ */
