#ifndef CONFIGURATION_SRC_ADS1015CONFIGURATION_H_
#define CONFIGURATION_SRC_ADS1015CONFIGURATION_H_

#include "IConfiguration.h"
#include "IADS1015Configuration.h"

namespace balcony_watering_system {
namespace configuration {

class ADS1015Configuration : public IConfiguration, public IADS1015Configuration {
public:
  ADS1015Configuration();
  virtual ~ADS1015Configuration();

  virtual void setField(const std::string& fieldName, const std::string& value) override;

  virtual const std::string& getNamePrefix() const override;

private:
  std::string namePrefix;
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_ADS1015CONFIGURATION_H_ */
