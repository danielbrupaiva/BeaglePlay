#pragma once

#include <iostream>
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"

#define PRINT(x) std::cout << x << std::endl;

namespace Core {
class Logger : public std::enable_shared_from_this<Logger> {
    std::string m_logger_name;
    std::string m_filename;
    std::shared_ptr<spdlog::logger> m_logger;
    spdlog::level::level_enum m_log_level;

public:
    explicit Logger(const std::string_view _logger_name, spdlog::level::level_enum _log_level = spdlog::level::info)
        : m_logger_name{_logger_name}, m_log_level{_log_level} {
        m_logger = spdlog::stdout_color_mt(m_logger_name);
        m_logger->set_level(m_log_level);
    };

    explicit Logger(const std::string_view _logger_name, const std::string_view _filename,
                    spdlog::level::level_enum _log_level = spdlog::level::info)
        : m_logger_name{_logger_name}, m_filename{_filename}, m_log_level{_log_level} {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(m_filename);
        m_logger = std::make_shared<spdlog::logger>(m_logger_name,
                                                    spdlog::sinks_init_list{console_sink, file_sink});
        m_logger->set_level(m_log_level);
    };

    ~Logger() {
        spdlog::drop_all();
    };

    static std::shared_ptr<Logger>
    create(const std::string_view _logger_name, spdlog::level::level_enum _log_level) {
        return std::make_shared<Logger>(_logger_name, _log_level);
    };

    static std::shared_ptr<Logger> create(const std::string_view _logger_name, const std::string_view _filename,
                                          spdlog::level::level_enum _log_level) {
        return std::make_shared<Logger>(_logger_name, _filename, _log_level);
    };

    std::shared_ptr<Logger> get() {
        return shared_from_this();
    };

    inline void set_log_level(spdlog::level::level_enum _level) { m_logger->set_level(_level); };
    /* Logger message*/
    template <typename... Args>
    inline void trace(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        m_logger->trace(fmt, std::forward<Args>(args)...);
    };
    template <typename... Args>
    inline void debug(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        m_logger->debug(fmt, std::forward<Args>(args)...);
    };
    template <typename... Args>
    inline void info(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        m_logger->info(fmt, std::forward<Args>(args)...);
    };
    template <typename... Args>
    inline void warn(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        m_logger->warn(fmt, std::forward<Args>(args)...);
    };
    template <typename... Args>
    inline void error(spdlog::format_string_t<Args...> fmt, Args &&...args) {
           m_logger->error(fmt, std::forward<Args>(args)...);
    };
    template <typename... Args>
    inline void critical(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        m_logger->critical(fmt, std::forward<Args>(args)...);
    };
    /* Getters and Setters */
    inline std::string get_logger_name() const { return m_logger_name; }
    inline void set_logger_name(std::string_view _logger_name) { m_logger_name = _logger_name; };
    inline std::string get_filename() const { return m_filename; }
    inline void set_filename(std::string_view _filename) { m_filename = _filename; };
};
};//Core namespace
inline Core::Logger logger{"App", spdlog::level::debug};