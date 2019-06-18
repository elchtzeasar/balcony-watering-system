#include "ConfigurationFile.h"

#include "IConfiguration.h"
#include "PumpConfiguration.h"
#include "SimulationConfiguration.h"
#include "SoilMoistureMeasurementConfiguration.h"

#include <cassert>
#include <iostream>
#include <stdio.h>

namespace balcony_watering_system {
namespace configuration {

using ::std::string;
using ::std::vector;

std::ostream& operator<<(std::ostream& stream, const ConfigurationFile::ParseState& state);
std::ostream& operator<<(std::ostream& stream, const ConfigurationFile::ConsumeResult& result);
std::ostream& operator<<(std::ostream& stream, const yaml_event_t& event);

ConfigurationFile::ConfigurationFile() :
    currentConfiguration(nullptr),
    configurations() {
}

ConfigurationFile::~ConfigurationFile() {
}

void ConfigurationFile::parse() {
  yaml_parser_t parser;
  yaml_event_t event;

  auto configurationFile = fopen("config.yaml", "r");

  yaml_parser_initialize(&parser);
  yaml_parser_set_input_file(&parser, configurationFile);

  ParseState state = ParseState::NONE;
  ConsumeResult consumeResult;
  do {
    if (!yaml_parser_parse(&parser, &event)) {
      throw "parsing failed";
    }
    consumeResult = consume(state, event);

    yaml_event_delete(&event);
  } while (consumeResult == ConsumeResult::SUCCESS);
}

const vector<IPumpConfiguration const *> ConfigurationFile::getPumpConfigurations() const {
  vector<IPumpConfiguration const *> result;

  for (const auto configuration : configurations) {
    auto specializedConfiguration = dynamic_cast<IPumpConfiguration const*>(configuration);

    if (specializedConfiguration) {
      result.push_back(specializedConfiguration);
    }
  }

  return result;
}

const vector<ISoilMoistureMeasurementConfiguration const *> ConfigurationFile::getSoilMoistureMeasurementConfigurations() const {
  vector<ISoilMoistureMeasurementConfiguration const *> result;

  for (const auto configuration : configurations) {
    auto specializedConfiguration = dynamic_cast<ISoilMoistureMeasurementConfiguration const*>(configuration);

    if (specializedConfiguration) {
      result.push_back(specializedConfiguration);
    }
  }

  return result;
}

const vector<ISimulationConfiguration const *> ConfigurationFile::getSimulationConfigurations() const {
  vector<ISimulationConfiguration const *> result;

  for (const auto configuration : configurations) {
    auto specializedConfiguration = dynamic_cast<ISimulationConfiguration const*>(configuration);

    if (specializedConfiguration) {
      result.push_back(specializedConfiguration);
    }
  }

  return result;
}

ConfigurationFile::ConsumeResult ConfigurationFile::consume(
    ParseState& state, const yaml_event_t& event) {
  ConsumeResult result;

  switch (event.type) {
  case YAML_NO_EVENT:
  case YAML_STREAM_START_EVENT:
  case YAML_DOCUMENT_START_EVENT:
    result = ConsumeResult::SUCCESS;
    break;
  case YAML_STREAM_END_EVENT:
  case YAML_DOCUMENT_END_EVENT:
    result = ConsumeResult::PARSING_COMPLETE;
    break;
  case YAML_ALIAS_EVENT:
    assert(false && "TBI");
    break;
  case YAML_SCALAR_EVENT: {
    if (state == ParseState::EXPECTING_TYPE) {
      auto type = reinterpret_cast<const char*>(event.data.scalar.value);
      currentConfiguration = createConfiguration(type);
      state = ParseState::TYPE_RECEIVED;
    }
    else if (state == ParseState::EXPECTING_KEY) {
      currentKey = reinterpret_cast<const char*>(event.data.scalar.value);
      state = ParseState::EXPECTING_VALUE;
    }
    else if (state == ParseState::EXPECTING_VALUE) {
      const char* currentValue = reinterpret_cast<const char*>(event.data.scalar.value);

      assert(currentConfiguration != nullptr);
      currentConfiguration->setField(currentKey, currentValue);
      state = ParseState::EXPECTING_KEY;
    }
    else {
      assert(false && "wrong state");
    }
    result = ConsumeResult::SUCCESS;
  } break;
  case YAML_SEQUENCE_START_EVENT:
    result = ConsumeResult::SUCCESS;
    break;
  case YAML_SEQUENCE_END_EVENT:
    result = ConsumeResult::SUCCESS;
    break;
  case YAML_MAPPING_START_EVENT:
    if (state == ParseState::NONE) {
      state = ParseState::EXPECTING_TYPE;
    }
    else if (state == ParseState::TYPE_RECEIVED) {
      state = ParseState::EXPECTING_KEY;
    }
    result = ConsumeResult::SUCCESS;
    break;
  case YAML_MAPPING_END_EVENT:
    if (state == ParseState::EXPECTING_KEY) {
      state = ParseState::EXPECTING_TYPE;
      configurations.push_back(currentConfiguration);
      currentConfiguration = nullptr;
    }
    else if (state == ParseState::EXPECTING_TYPE) {
      state = ParseState::NONE;
    }
    result = ConsumeResult::SUCCESS;
    break;
  }

  return result;
}

IConfiguration* ConfigurationFile::createConfiguration(const string& type) {
  if (type == "SoilMoistureMeasurement") {
    return new SoilMoistureMeasurementConfiguration();
  }
  else if (type == "Pump") {
    return new PumpConfiguration();
  }
  else if (type == "Simulation") {
    return new SimulationConfiguration();
  }
  assert(false && "unknown type");
  return nullptr;
}

std::ostream& operator<<(std::ostream& stream, const ConfigurationFile::ParseState& state) {
  switch (state) {
  case ConfigurationFile::ParseState::NONE: stream << "NONE"; break;
  case ConfigurationFile::ParseState::EXPECTING_TYPE: stream << "EXPECTING_TYPE"; break;
  case ConfigurationFile::ParseState::TYPE_RECEIVED: stream << "TYPE_RECEIVED"; break;
  case ConfigurationFile::ParseState::EXPECTING_KEY: stream << "EXPECTING_KEY"; break;
  case ConfigurationFile::ParseState::EXPECTING_VALUE: stream << "EXPECTING_VALUE"; break;
  default: assert(false && "unknown state"); break;
  }

  return stream;
}

std::ostream& operator<<(std::ostream& stream, const ConfigurationFile::ConsumeResult& state) {
  switch (state) {
  case ConfigurationFile::ConsumeResult::PARSING_COMPLETE: stream << "PARSING_COMPLETE"; break;
  case ConfigurationFile::ConsumeResult::SUCCESS: stream << "SUCCESS"; break;
  case ConfigurationFile::ConsumeResult::ERROR: stream << "ERROR"; break;
  default: assert(false && "unknown result"); break;
  }

  return stream;
}

std::ostream& operator<<(std::ostream& stream, const yaml_event_t& event) {
  switch (event.type) {
  case YAML_NO_EVENT: stream << "STREAM_START_EVENT"; break;
  case YAML_STREAM_START_EVENT: stream << "STREAM_START_EVENT"; break;
  case YAML_DOCUMENT_START_EVENT: stream << "DOCUMENT_START_EVENT"; break;
  case YAML_STREAM_END_EVENT: stream << "STREAM_END_EVENT"; break;
  case YAML_DOCUMENT_END_EVENT: stream << "DOCUMENT_END_EVENT"; break;
  case YAML_ALIAS_EVENT: stream << "ALIAS_EVENT"; break;
  case YAML_SCALAR_EVENT: stream << "SCALAR_EVENT"; break;
  case YAML_SEQUENCE_START_EVENT: stream << "SEQUENCE_START_EVENT"; break;
  case YAML_SEQUENCE_END_EVENT: stream << "SEQUENCE_END_EVENT"; break;
  case YAML_MAPPING_START_EVENT: stream << "MAPPING_START_EVENT"; break;
  case YAML_MAPPING_END_EVENT: stream << "MAPPING_END_EVENT"; break;
  default: assert(false && "unknown");
  }

  return stream;
}

} /* namespace configuration */
} /* namespace balcony_watering_system */
