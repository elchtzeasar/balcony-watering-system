/*
 *  Created on: Nov 25, 2019
 *      Author: peter
 */

#ifndef HARDWARE_SRC_OUTPUTPIN_H_
#define HARDWARE_SRC_OUTPUTPIN_H_

namespace balcony_watering_system {
namespace hardware {

class OutputPin {
public:
  OutputPin(int pin);

  void setup();

  void setValue(bool value) const;

private:
  const int pin;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_SRC_OUTPUTPIN_H_ */
