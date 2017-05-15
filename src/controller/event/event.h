#ifndef LE_EVENT_H_
#define LE_EVENT_H_

namespace le {

enum EventFlags : int
{
  kNone                 = 0,       // Used to denote no flags explicitly

  // Universally applicable status bits.
  kIsSynthesized       = 1 << 0,

  // Modifier key state.
  kShiftDown           = 1 << 1,
  kControlDown         = 1 << 2,
  kAltDown             = 1 << 3,
  kCommandDown         = 1 << 4,  // GUI Key (e.g. Command on OS X
  // keyboards, Search on Chromebook
  // keyboards, Windows on MS-oriented
  // keyboards)
  kAltgrDown           = 1 << 5,
  kMod3Down            = 1 << 6,

  // Other keyboard state.
  kNumlockOn          = 1 << 7,
  kCapslockOn         = 1 << 8,
  kScrolllockOn       = 1 << 9,

  // Mouse buttons.
  kLeftMouseButton    = 1 << 10,
  kMiddleMouseButton  = 1 << 11,
  kRightMouseButton   = 1 << 12,
  kBackMouseButton    = 1 << 13,
  kForwardMouseButton = 1 << 14,
};


class Event
{
 public:
  Event();
  virtual ~Event();

  int GetFlags() const { return flags_; }
  void SetFlags(int flags) { flags_ = flags; }

  bool GetFlag(EventFlags flag) const { return (flags_ & flag); }
  void SetFlag(EventFlags flag, bool value);

 private:
  bool shift_down_;
  bool ctrl_down_;
  bool alt_down_;
  bool command_down_;

  int flags_;
  
};


}  // le

#endif /* LE_EVENT_H_ */
