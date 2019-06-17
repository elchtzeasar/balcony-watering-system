#ifndef CONFIGURATION_SRC_PUMPCONFIGURATION_H_
#define CONFIGURATION_SRC_PUMPCONFIGURATION_H_

#include "IConfiguration.h"
#include "IPumpConfiguration.h"

namespace balcony_watering_system {
namespace configuration {

class PumpConfiguration : public IConfiguration, public IPumpConfiguration {
public:
  PumpConfiguration();
  virtual ~PumpConfiguration();

  virtual Type getType() const override;
  virtual void setField(const std::string& fieldName, const std::string& value) override;

  virtual const std::string& getName() const override;

private:
  std::string name;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_PUMPCONFIGURATION_H_ */
