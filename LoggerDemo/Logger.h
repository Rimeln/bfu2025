#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <mutex>

class Logger {
public:
    enum class Level {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    static void init(bool logToFile = false, const std::string& filename = "app.log") {
        getInstance().m_logToFile = logToFile;
        getInstance().m_filename = filename;

        if (logToFile) {
            std::ofstream file(filename, std::ios::trunc);
            if (file.is_open()) {
                file.close();
            }
            log(Level::INFO, __FILE__, __LINE__, "Logger initialized to file: ", filename);
        } else {
            log(Level::INFO, __FILE__, __LINE__, "Logger initialized to console");
        }
    }

    template<typename... Args>
    static void debug(Args&&... args) {
        log(Level::DEBUG, __FILE__, __LINE__, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void info(Args&&... args) {
        log(Level::INFO, __FILE__, __LINE__, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void warning(Args&&... args) {
        log(Level::WARNING, __FILE__, __LINE__, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void error(Args&&... args) {
        log(Level::ERROR, __FILE__, __LINE__, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void fatal(Args&&... args) {
        log(Level::FATAL, __FILE__, __LINE__, std::forward<Args>(args)...);
    }

private:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    static std::mutex& getMutex() {
        static std::mutex mutex;
        return mutex;
    }

    Logger() : m_logToFile(false) {}
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    template<typename... Args>
    static void log(Level level, const char* file, int line, Args&&... args) {
        std::lock_guard<std::mutex> lock(getMutex());
        auto& instance = getInstance();

        std::stringstream ss;
        buildMessage(ss, std::forward<Args>(args)...);
        instance.writeLog(level, file, line, ss.str());
    }

    void writeLog(Level level, const char* file, int line, const std::string& message) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                      now.time_since_epoch()) % 1000;

        std::stringstream logEntry;
        logEntry << std::put_time(std::localtime(&time), "%H:%M:%S");
        logEntry << '.' << std::setfill('0') << std::setw(3) << ms.count();
        logEntry << " [" << levelToString(level) << "] ";
        logEntry << message;

        if (level == Level::ERROR || level == Level::FATAL) {
            logEntry << " [File: " << file << ", Line: " << line << "]";
        }

        std::string logStr = logEntry.str();

        std::cout << logStr << std::endl;

        if (m_logToFile && !m_filename.empty()) {
            std::ofstream file(m_filename, std::ios::app);
            if (file.is_open()) {
                file << logStr << std::endl;
                file.close();
            }
        }
    }

    static std::string levelToString(Level level) {
        switch (level) {
        case Level::DEBUG:   return "DEBUG";
        case Level::INFO:    return "INFO";
        case Level::WARNING: return "WARNING";
        case Level::ERROR:   return "ERROR";
        case Level::FATAL:   return "FATAL";
        default:             return "UNKNOWN";
        }
    }

    template<typename T, typename... Args>
    static void buildMessage(std::stringstream& ss, T&& first, Args&&... rest) {
        ss << std::forward<T>(first);
        buildMessage(ss, std::forward<Args>(rest)...);
    }

    static void buildMessage(std::stringstream& ss) {
    }

    bool m_logToFile;
    std::string m_filename;
};

#endif // LOGGER_H
