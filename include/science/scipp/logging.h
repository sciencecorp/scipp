#pragma once

#include <string>

#include "quill/Logger.h"
#include "quill/LogMacros.h"

namespace science {

#ifndef NDEBUG
static const quill::LogLevel kDefaultLogLevel = quill::LogLevel::TraceL3;
#else
static const quill::LogLevel kDefaultLogLevel = quill::LogLevel::Info;
#endif

using Logger = quill::Logger;

/**
 * @brief Get a logger object with the given name
 * 
 * @param name
 * @param level 
 * @return Logger* 
 */
Logger* get_logger(std::string name, quill::LogLevel level = kDefaultLogLevel);

/**
 * @brief Initialize logging with the default log level
 * 
 * This function should be called once at the beginning of the program.
 */
void init_logging();

}  // namespace science
