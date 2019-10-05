#ifndef CONFIGURATION_SRC_IADS1015CONFIGURATION_H_
#define CONFIGURATION_SRC_IADS1015CONFIGURATION_H_

#include <string>

namespace balcony_watering_system {
namespace configuration {

class IADS1015Configuration {
public:
  virtual ~IADS1015Configuration() = default;

  virtual const std::string& getNamePrefix() const = 0;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_IADS1015CONFIGURATION_H_ */
