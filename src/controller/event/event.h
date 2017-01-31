#ifndef LE_EVENT_H_
#define LE_EVENT_H_

namespace le {

class Event
{
 public:
  Event() {}
  virtual ~Event() {}

  bool GetShiftDown() const { return shift_down_; }
  void SetShiftDown(bool shift_down) { shift_down_ = shift_down; }

  bool GetCtrlDown() const { return ctrl_down_; }
  void SetCtrlDown(bool ctrl_down) { ctrl_down_ = ctrl_down; }

  bool GetAltDown() const { return alt_down_; }
  void SetAltDown(bool alt_down) { alt_down_ = alt_down; }

  bool GetCommandDown() const { return command_down_; }
  void SetCommandDown(bool command_down) { command_down_ = command_down; }


 private:
  bool shift_down_;
  bool ctrl_down_;
  bool alt_down_;
  bool command_down_;
  
};


}  // le

#endif /* LE_EVENT_H_ */
