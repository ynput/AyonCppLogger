#include "AyonLogger.h"
#include "AyonCppApiCrossPlatformMacros.h"
#include "spdlog/async.h"
#include "spdlog/common.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <cstdlib>
#include <filesystem>
#include <memory>
#include <set>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>

std::set<std::string>::iterator AyonLogger::key(const std::string &key) {
  return EnabledLoggingKeys.find(key);
};

bool AyonLogger::regesterLoggingKey(const std::string &KeyName) {
  std::pair<std::set<std::string>::iterator, bool> insertion =
      EnabledLoggingKeys.insert(KeyName);
  if (insertion.second) {
    return true;
  }
  return false;
}

bool AyonLogger::unregisterLoggingKey(const std::string &KeyName) {
  std::set<std::string>::iterator it = EnabledLoggingKeys.find(KeyName);
  if (it != EnabledLoggingKeys.end()) {
    EnabledLoggingKeys.erase(it);
    return true;
  }
  return false;
}

bool AyonLogger::isKeyActive(
    const std::set<std::string>::iterator &logginIterator) {
  if (logginIterator != EnabledLoggingKeys.end()) {
    return true;
  }
  return false;
};

void AyonLogger::LogLevlInfo(const bool &alsoSetFileLogger) {
  if (alsoSetFileLogger) {
    file_logger_->set_level(spdlog::level::info);
  }
  console_logger_->set_level(spdlog::level::info);
}

void AyonLogger::LogLevlError(const bool &alsoSetFileLogger) {
  if (alsoSetFileLogger) {
    file_logger_->set_level(spdlog::level::err);
  }
  console_logger_->set_level(spdlog::level::err);
}

void AyonLogger::LogLevlWarn(const bool &alsoSetFileLogger) {
  if (alsoSetFileLogger) {
    file_logger_->set_level(spdlog::level::warn);
  }
  console_logger_->set_level(spdlog::level::warn);
}

void AyonLogger::LogLevlCritical(const bool &alsoSetFileLogger) {
  if (alsoSetFileLogger) {
    file_logger_->set_level(spdlog::level::critical);
  }
  console_logger_->set_level(spdlog::level::critical);
}

void AyonLogger::LogLevlOff(const bool &alsoSetFileLogger) {
  if (alsoSetFileLogger) {
    file_logger_->set_level(spdlog::level::off);
  }
  console_logger_->set_level(spdlog::level::off);
}

AyonLogger::AyonLogger(const std::string &filepath) {
  // Initialize console logger
  console_logger_ = spdlog::stdout_color_mt("console");
  console_logger_->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");

  char *envVarFileLoggingPath = std::getenv("AYONLOGGERFILEPOS");

  if (envVarFileLoggingPath != nullptr) {
    fileLoggerFilePath =
        std::string(std::filesystem::absolute(
                        std::string(envVarFileLoggingPath) + "/logFile.json")
                        .string());
    fileLoggerFilePathOverwrite = true;
  }

  char *envVarFileLogging = std::getenv("AYONLOGGERFILELOGGING");

  if (envVarFileLogging != nullptr) {
    switch (envVarFileLogging[1]) {
    case 'F':
      enableFileLogging = false;
      break;
    default:
      enableFileLogging = true;
      file_logger_ = spdlog::basic_logger_mt<spdlog::async_factory>(
          "fileLogger", fileLoggerFilePathOverwrite ? fileLoggerFilePath.c_str()
                                                    : filepath.c_str());
      file_logger_->set_pattern(
          "{\"timestamp\":\"%Y-%m-%d %H:%M:%S.%e\",\"level\":\"%l\",\"Thread "
          "Id\":\"%t\",\"Process Id\":\"%P\",\"message\":\"%v\"}");
      break;
    }
  }

  char *envVarLogLvl = std::getenv("AYONLOGGERLOGLVL");

  if (envVarLogLvl != nullptr) {
    switch (envVarLogLvl[0]) {
    case 'I':
      if (enableFileLogging) {
        file_logger_->set_level(spdlog::level::info);
      }
      console_logger_->set_level(spdlog::level::info);
      break;
    case 'E':
      if (enableFileLogging) {
        file_logger_->set_level(spdlog::level::err);
      }
      console_logger_->set_level(spdlog::level::err);
      break;
    case 'W':
      if (enableFileLogging) {
        file_logger_->set_level(spdlog::level::warn);
      }
      console_logger_->set_level(spdlog::level::warn);
      break;
    case 'C':
      if (enableFileLogging) {
        file_logger_->set_level(spdlog::level::critical);
      }
      console_logger_->set_level(spdlog::level::critical);
      break;
    case 'O':
      if (enableFileLogging) {
        file_logger_->set_level(spdlog::level::off);
      }
      console_logger_->set_level(spdlog::level::off);
      break;
    default:
      break;
    }
  }

  const char *envVarLoggingKeys = std::getenv("AYON_LOGGIN_LOGGIN_KEYS");
  if (envVarLoggingKeys != nullptr) {
    std::string envVarString(envVarLoggingKeys);
    std::string token;
    std::istringstream tokenStream(envVarString);
    while (std::getline(tokenStream, token, '/')) {
      EnabledLoggingKeys.insert(token);
    }
  }
}
