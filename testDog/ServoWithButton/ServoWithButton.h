#ifndef _SERVOWITHBUTTON_H_
#define _SERVOWITHBUTTON_H_

class Leg{
  public:
  Leg(Servo primaryJoint, int pinPJ, Servo secondaryJoint, int pinSJ);
  void moveBy(int deg);
  void detachAll();
  void stopAll();
  private:
  Servo _primaryJoint;
  Servo _secondaryJoint;
};

#endif
