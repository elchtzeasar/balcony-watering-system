#ifndef CONFIGURATION_SRC_CONFIGURATIONFILE_H_
#define CONFIGURATION_SRC_CONFIGURATIONFILE_H_

#include <map>
#include <vector>
#include <yaml.h>
#include <iosfwd>

namespace balcony_watering_system {
namespace configuration {

class IConfiguration;
class IPumpConfiguration;
class ISoilMoistureSensorConfiguration;

class ConfigurationFile {
public:
  ConfigurationFile();
  virtual ~ConfigurationFile();

  ConfigurationFile& operator=(const ConfigurationFile&) = delete;
  ConfigurationFile& operator=(const ConfigurationFile&&) = delete;

  void parse();

  const std::vector<IPumpConfiguration const *> getPumpConfigurations() const;
  const std::vector<ISoilMoistureSensorConfiguration const *>
  getSoilMoistureSensorConfigurations() const;

private:
  enum class ParseState { NONE, EXPECTING_TYPE, TYPE_RECEIVED, EXPECTING_KEY, EXPECTING_VALUE };
  enum class ConsumeResult { PARSING_COMPLETE, SUCCESS, ERROR };
  ConsumeResult consume(ParseState& state, const yaml_event_t& event);

  static IConfiguration* createConfiguration(const std::string& type);

  IConfiguration* currentConfiguration;
  std::string currentKey;
  std::vector<IConfiguration*> configurations;

  friend std::ostream& operator<<(std::ostream& stream, const ParseState& state);
  friend std::ostream& operator<<(std::ostream& stream, const ConsumeResult& result);
};

} /* namespace configuration */
} /* namespace balcony_watering_system */

#endif /* CONFIGURATION_SRC_CONFIGURATIONFILE_H_ */

