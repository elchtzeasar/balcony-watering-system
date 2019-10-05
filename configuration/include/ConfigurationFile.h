#ifndef CONFIGURATION_SRC_CONFIGURATIONFILE_H_
#define CONFIGURATION_SRC_CONFIGURATIONFILE_H_

#include <map>
#include <vector>
#include <yaml.h>
#include <iosfwd>

namespace balcony_watering_system {
namespace configuration {

class IADS1015Configuration;
class IConfiguration;
class IHumidityMeasurementConfiguration;
class IPumpConfiguration;
class ISimulationConfiguration;
class ISi7021SensorConfiguration;
class ISoilMoistureMeasurementConfiguration;
class ITemperatureMeasurementConfiguration;
class IVolumeMeasurementConfiguration;

class ConfigurationFile {
public:
  ConfigurationFile();
  virtual ~ConfigurationFile();

  ConfigurationFile& operator=(const ConfigurationFile&) = delete;
  ConfigurationFile& operator=(const ConfigurationFile&&) = delete;

  void parse();

  const std::vector<IHumidityMeasurementConfiguration const *> getHumidityMeasurementConfigurations() const;
  const std::vector<ISoilMoistureMeasurementConfiguration const *>
  getSoilMoistureMeasurementConfigurations() const;
  const std::vector<ITemperatureMeasurementConfiguration const *> getTemperatureMeasurementConfigurations() const;
  const std::vector<IVolumeMeasurementConfiguration const *> getVolumeMeasurementConfigurations() const;
  const std::vector<IPumpConfiguration const *> getPumpConfigurations() const;

  const std::vector<ISimulationConfiguration const *> getSimulationConfigurations() const;

  const std::vector<ISi7021SensorConfiguration const *> getSi7021SensorConfigurations() const;
  const std::vector<IADS1015Configuration const *> getADS1015Configurations() const;

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

