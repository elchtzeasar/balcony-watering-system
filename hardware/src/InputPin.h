/*
 *  Created on: Nov 25, 2019
 *      Author: peter
 */

#ifndef HARDWARE_SRC_INPUTPIN_H_
#define HARDWARE_SRC_INPUTPIN_H_

namespace balcony_watering_system {
namespace hardware {

class InputPin {
public:
  InputPin(int pin);

  void setup();

  bool getValue() const;

private:
  const int pin;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_SRC_INPUTPIN_H_ */
