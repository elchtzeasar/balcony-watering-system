#ifndef ICONFIGURATION_H_
#define ICONFIGURATION_H_

#include <string>

namespace balcony_watering_system::configuration {

class IConfiguration {
public:
  virtual ~IConfiguration() = default;

  virtual void setField(const std::string& fieldName, const std::string& value) = 0;
};

}

#endif /* ICONFIGURATION_H_ */
