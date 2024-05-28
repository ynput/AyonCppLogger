#ifndef AYONLOGGER_H
#define AYONLOGGER_H
#include "AyonCppApiCrossPlatformMacros.h"
#include "spdlog/async.h"
#include "spdlog/common.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <memory>
#include <optional>
#include <set>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>
/**
 * @class AyonLogger
 * @brief Simple Logger Class that wraps around spdlog in order to expose easy
 * logging functions \n AyonLogger::getInstance(log_File_path.json) init code \n
 *  automaticly logs to file and console
 */

class AyonLogger {
public:
  static AyonLogger &getInstance(const std::string &filepath) {
    static AyonLogger AyonLoggerInstance(filepath);
    return AyonLoggerInstance;
  };

  std::set<std::string>::iterator key(const std::string &key);

  bool regesterLoggingKey(const std::string &KeyName);

  bool unregisterLoggingKey(const std::string &KeyName);

  bool isKeyActive(const std::set<std::string>::iterator &logginIterator);

  template <typename... Args>
  void error(const std::set<std::string>::iterator &logginIterator,
             const std::string &format, const Args &...args) {
    if (logginIterator != EnabledLoggingKeys.end()) {
      log("error", format, args...);
    }
  };

  template <typename... Args>
  void error(const std::string &format, const Args &...args) {
    log("error", format, args...);
  };

  template <typename... Args>
  void info(const std::set<std::string>::iterator &logginIterator,
            const std::string &format, const Args &...args) {
    if (logginIterator != EnabledLoggingKeys.end()) {
      log("info", format, args...);
    }
  };

  template <typename... Args>
  void info(const std::string &format, const Args &...args) {
    log("info", format, args...);
  };

  template <typename... Args>
  void warn(const std::set<std::string>::iterator &logginIterator,
            const std::string &format, const Args &...args) {
    if (logginIterator != EnabledLoggingKeys.end()) {
      log("warn", format, args...);
    }
  };

  template <typename... Args>
  void warn(const std::string &format, const Args &...args) {
    log("warn", format, args...);
  };

  template <typename... Args>
  void critical(const std::set<std::string>::iterator &logginIterator,
                const std::string &format, const Args &...args) {
    if (logginIterator != EnabledLoggingKeys.end()) {
      log("critical", format, args...);
    }
  };

  template <typename... Args>
  void critical(const std::string &format, const Args &...args) {
    log("critical", format, args...);
  };

  void LogLevlInfo(const bool &alsoSetFileLogger = false);

  void LogLevlError(const bool &alsoSetFileLogger = false);

  void LogLevlWarn(const bool &alsoSetFileLogger = false);

  void LogLevlCritical(const bool &alsoSetFileLogger = false);

  void LogLevlOff(const bool &alsoSetFileLogger = false);

private:
  AyonLogger(const std::string &filepath);

  template <typename... Args>
  void log(const std::string &level, const std::string &massage,
           const Args &...args) {
    std::string formatted_message =
        fmt::vformat(massage, fmt::make_format_args(args...));

    if (enableFileLogging) {
      file_logger_->log(spdlog::level::from_str(level), formatted_message);
    }
    console_logger_->log(spdlog::level::from_str(level), formatted_message);
  };

  std::shared_ptr<spdlog::logger> console_logger_;
  std::shared_ptr<spdlog::logger> file_logger_;

  bool enableFileLogging;
  bool fileLoggerFilePathOverwrite;
  std::string fileLoggerFilePath;

  std::set<std::string> EnabledLoggingKeys;
};
#endif
