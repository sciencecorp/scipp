#include "science/scipp/logging.h"

#include <memory>
#include "quill/Backend.h"
#include "quill/Frontend.h"
#include "quill/sinks/ConsoleSink.h"
#include "quill/sinks/RotatingFileSink.h"

namespace science {

constexpr size_t kRotationMaxFileSize = 1024 * 1024 * 10;
const uint32_t kMaxBackupFiles = 5;

Logger* get_logger(std::string name, quill::LogLevel level) {
  Logger* log = quill::Frontend::create_or_get_logger(name);
  log->set_log_level(level);
  return log;
}

void init_logging() {
  quill::BackendOptions opts;

  std::string pattern_str = "%(time) | %(log_level) | %(logger) | %(message)";
  std::string pattern_ts = "%Y-%m-%d %H:%M:%S.%Qms";
  auto pattern = quill::PatternFormatterOptions{pattern_str, pattern_ts,  quill::Timezone::GmtTime};

  // Rotating file handler
  auto file_handler = quill::Frontend::create_or_get_sink<quill::FileSink>(
    "logs/log.txt",
    []() {
      quill::RotatingFileSinkConfig cfg;
      cfg.set_open_mode('w');
      cfg.set_filename_append_option(quill::FilenameAppendOption::StartDateTime);
      cfg.set_overwrite_rolled_files(true);
      cfg.set_rotation_max_file_size(kRotationMaxFileSize);
      cfg.set_max_backup_files(kMaxBackupFiles);
      return cfg;
    }()
  );

  // Console handler
  auto console_handler = quill::Frontend::create_or_get_sink<quill::ConsoleSink>("console_sink_0", 
    []() {
      quill::ConsoleSinkConfig config;

      quill::ConsoleSinkConfig::Colours colours;

      config.set_colours(colours);
      return config;
    }()
  );

  quill::Backend::start(opts);

  quill::Logger* logger = quill::Frontend::create_or_get_logger("logger", {std::move(file_handler), std::move(console_handler)}, pattern);
  logger->set_log_level(quill::LogLevel::TraceL3);
  logger->init_backtrace(2, quill::LogLevel::Critical);
}

}  // namespace science
