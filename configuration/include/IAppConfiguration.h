#ifndef CONFIGURATION_SRC_IAPPCONFIGURATION_H_
#define CONFIGURATION_SRC_IAPPCONFIGURATION_H_

#include <chrono>

namespace balcony_watering_system {
namespace configuration {

class IAppConfiguration {
public:
  virtual ~IAppConfiguration() = default;

  enum class Mode {
    NO_APP,
    TEXT_GUI,
    SINGLE_RUN,
  };
  virtual Mode getMode() const = 0;

  virtual const std::chrono::milliseconds& getCycleTime() const = 0;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_IAPPCONFIGURATION_H_ */
