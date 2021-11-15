/* Copyright 2020 Unity-Drive Inc. All rights reserved */
/*     Author: ChengJie (chengjie@unity-drive.com)     */
#pragma once

#include <glog/logging.h>

namespace common {

#define LEFT_BRACKET "["
#define RIGHT_BRACKET "]"

#define MODULE_NAME " "

#define UDEBUG_MODULE(module) \
  VLOG(5) << LEFT_BRACKET << module << RIGHT_BRACKET << "[DEBUG] "
#define UDEBUG UDEBUG_MODULE(MODULE_NAME)
#define UINFO ULOG_MODULE(MODULE_NAME, INFO)
#define UWARN ULOG_MODULE(MODULE_NAME, WARN)
#define UERROR ULOG_MODULE(MODULE_NAME, ERROR)
#define UFATAL ULOG_MODULE(MODULE_NAME, FATAL)

#ifndef ULOG_MODULE_STREAM
#define ULOG_MODULE_STREAM(log_severity) ULOG_MODULE_STREAM_##log_severity
#endif

#ifndef ULOG_MODULE
#define ULOG_MODULE(module, log_severity) \
  ULOG_MODULE_STREAM(log_severity)(module)
#endif

#define ULOG_MODULE_STREAM_INFO(module)                         \
  google::LogMessage(__FILE__, __LINE__, google::INFO).stream() \
      << LEFT_BRACKET << module << RIGHT_BRACKET

#define ULOG_MODULE_STREAM_WARN(module)                            \
  google::LogMessage(__FILE__, __LINE__, google::WARNING).stream() \
      << LEFT_BRACKET << module << RIGHT_BRACKET

#define ULOG_MODULE_STREAM_ERROR(module)                         \
  google::LogMessage(__FILE__, __LINE__, google::ERROR).stream() \
      << LEFT_BRACKET << module << RIGHT_BRACKET

#define ULOG_MODULE_STREAM_FATAL(module)                         \
  google::LogMessage(__FILE__, __LINE__, google::FATAL).stream() \
      << LEFT_BRACKET << module << RIGHT_BRACKET

#define UINFO_IF(cond) ULOG_IF(INFO, cond, MODULE_NAME)
#define UWARN_IF(cond) ULOG_IF(WARN, cond, MODULE_NAME)
#define UERROR_IF(cond) ULOG_IF(ERROR, cond, MODULE_NAME)
#define UFATAL_IF(cond) ULOG_IF(FATAL, cond, MODULE_NAME)
#define ULOG_IF(severity, cond, module) \
  !(cond) ? (void)0                     \
          : google::LogMessageVoidify() & ULOG_MODULE(module, severity)

#define UCHECK(cond) CHECK(cond) << LEFT_BRACKET << MODULE_NAME << RIGHT_BRACKET

#define UINFO_EVERY(freq) \
  LOG_EVERY_N(INFO, freq) << LEFT_BRACKET << MODULE_NAME << RIGHT_BRACKET
#define UWARN_EVERY(freq) \
  LOG_EVERY_N(WARNING, freq) << LEFT_BRACKET << MODULE_NAME << RIGHT_BRACKET
#define UERROR_EVERY(freq) \
  LOG_EVERY_N(ERROR, freq) << LEFT_BRACKET << MODULE_NAME << RIGHT_BRACKET

#define ANSI_RED "\033[1m\x1b[31m"
#define ANSI_GREEN "\033[1m\x1b[32m"
#define ANSI_YELLOW "\033[1m\x1b[33m"
#define ANSI_BLUE "\033[1m\x1b[34m"
#define ANSI_MAGENTA "\033[1m\x1b[35m"
#define ANSI_CYAN "\033[1m\x1b[36m"
#define ANSI_RESET "\x1b[0m"

#ifndef UCOLOR
#define UCOLOR(color, message) \
  LOG(INFO) << "\n" << color << message << ANSI_RESET << " "
#endif

#ifndef DCOLOR
#define DCOLOR(color, message) \
  VLOG(4) << "\n" << color << message << ANSI_RESET << " "
#endif

#ifndef UCOLOR_EVERY
#define UCOLOR_EVERY(freq, color, message) \
  LOG_EVERY_N(INFO, freq) << color << message << ANSI_RESET
#endif

#define UYELLOW(message) UCOLOR(ANSI_YELLOW, message)
#define URED(message) UCOLOR(ANSI_RED, message)
#define UGREEN(message) UCOLOR(ANSI_GREEN, message)
#define UBLUE(message) UCOLOR(ANSI_BLUE, message)
#define UMAGENTA(message) UCOLOR(ANSI_MAGENTA, message)
#define UCYAN(message) UCOLOR(ANSI_CYAN, message)

#define DYELLOW(message) DCOLOR(ANSI_YELLOW, message)
#define DRED(message) DCOLOR(ANSI_RED, message)
#define DGREEN(message) DCOLOR(ANSI_GREEN, message)
#define DBLUE(message) DCOLOR(ANSI_BLUE, message)
#define DMAGENTA(message) DCOLOR(ANSI_MAGENTA, message)
#define DCYAN(message) DCOLOR(ANSI_CYAN, message)

#define DTIME DBLUE("[Time]")

#define URED_EVERY(freq, message) UCOLOR_EVERY(freq, ANSI_RED, message)

}  // namespace common
