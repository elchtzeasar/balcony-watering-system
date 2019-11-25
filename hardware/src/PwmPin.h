/*
 *  Created on: Nov 25, 2019
 *      Author: peter
 */

#ifndef HARDWARE_SRC_PWMPIN_H_
#define HARDWARE_SRC_PWMPIN_H_

namespace balcony_watering_system {
namespace hardware {

class PwmPin {
public:
  PwmPin(int pin);

  void setup();

  void setValue(float percentage) const;

private:
  const int pin;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_SRC_PWMPIN_H_ */
