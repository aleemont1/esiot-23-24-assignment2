#ifndef __ABSTRACT_BUTTON__
#define __ABSTRACT_BUTTON__

class AbstractButton {
 
public:
  AbstractButton();
  virtual bool isPressed() = 0;

  virtual void sync();
  long getLastSyncTime();

protected: 
  void updateSyncTime(long time);

private:
  long lastTimeSync;

};

#endif