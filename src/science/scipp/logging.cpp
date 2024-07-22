#include "science/scipp/logging.h"

#include <memory>

namespace science {

constexpr size_t kRotationMaxFileSize = 1024 * 1024 * 10;
const uint32_t kMaxBackupFiles = 5;

Logger* get_logger(std::string name, quill::LogLevel level) {
  Logger* log = quill::create_logger(name);
  log->set_log_level(level);
  return log;
}

void init_logging() {
  quill::Config cfg;

  std::string pattern = "%(time) | %(log_level) | %(logger) | %(message)";
  std::string pattern_ts = "%Y-%m-%d %H:%M:%S.%Qms";
  quill::Timezone tz = quill::Timezone::GmtTime;

  // Rotating file handler
  std::shared_ptr<quill::Handler> file_handler = quill::rotating_file_handler("logs/log.txt", []() {
    quill::RotatingFileHandlerConfig cfg;
    cfg.set_rotation_max_file_size(kRotationMaxFileSize);
    cfg.set_max_backup_files(kMaxBackupFiles);
    cfg.set_overwrite_rolled_files(true);
    return cfg;
  }());
  file_handler->set_log_level(quill::LogLevel::TraceL3);
  file_handler->set_pattern(pattern, pattern_ts, tz);
  cfg.default_handlers.emplace_back(file_handler);

  // Console handler
  quill::ConsoleColours colors;
  std::shared_ptr<quill::Handler> console_handler = quill::stdout_handler("stdout", colors);
  console_handler->set_log_level(quill::LogLevel::TraceL3);
  console_handler->set_pattern(pattern, pattern_ts, tz);
  cfg.default_handlers.emplace_back(console_handler);

  quill::configure(cfg);
  quill::start();

  quill::Logger* logger = quill::create_logger("logger", {file_handler, console_handler});
  logger->set_log_level(quill::LogLevel::TraceL3);
  logger->init_backtrace(2, quill::LogLevel::Critical);
}

}  // namespace science
