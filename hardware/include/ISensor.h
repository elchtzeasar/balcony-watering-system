/*
 * ISensor.h
 *
 *  Created on: Aug 30, 2019
 *      Author: peter
 */

#ifndef HARDWARE_INCLUDE_ISENSOR_H_
#define HARDWARE_INCLUDE_ISENSOR_H_

#include <string>

namespace balcony_watering_system {
namespace hardware {

class ISensor {
public:
  virtual ~ISensor() = default;

  virtual const std::string& getName() const = 0;
};

} /* namespace hardware */
} /* namespace balcony_watering_system */

#endif /* HARDWARE_INCLUDE_ISENSOR_H_ */
