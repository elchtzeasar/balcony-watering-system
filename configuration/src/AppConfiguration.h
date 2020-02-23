#ifndef CONFIGURATION_SRC_APPCONFIGURATION_H_
#define CONFIGURATION_SRC_APPCONFIGURATION_H_

#include "IConfiguration.h"
#include "IAppConfiguration.h"

#include "Logger.h"

namespace balcony_watering_system {
namespace configuration {

class AppConfiguration : public IConfiguration, public IAppConfiguration {
public:
  AppConfiguration();
  virtual ~AppConfiguration();

  virtual void setField(const std::string& fieldName, const std::string& value) override;

  virtual Mode getMode() const override;

  virtual const std::chrono::milliseconds& getCycleTime() const override;

private:
  Mode mode;

  std::chrono::milliseconds cycleTime;

  const platform::Logger logger;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_APPCONFIGURATION_H_ */
