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
            if (file.is_open())
                file.close();
        }
    }

    template<typename... Args>
    static void debug(Args&&... args) {
        log(Level::DEBUG, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void info(Args&&... args) {
        log(Level::INFO, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void warning(Args&&... args) {
        log(Level::WARNING, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void error(Args&&... args) {
        log(Level::ERROR, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void fatal(Args&&... args) {
        log(Level::FATAL, std::forward<Args>(args)...);
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

    template<typename... Args>
    static void log(Level level, Args&&... args) {
        std::lock_guard<std::mutex> lock(getMutex());
        auto& instance = getInstance();

        std::stringstream ss;
        buildMessage(ss, std::forward<Args>(args)...);

        instance.writeLog(level, ss.str());
    }

    void writeLog(Level level, const std::string& message) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        std::stringstream logEntry;
        logEntry << std::put_time(std::localtime(&time), "%H:%M:%S");
        logEntry << " [" << levelToString(level) << "] ";
        logEntry << message;

        std::string logStr = logEntry.str();

        std::cout << logStr << std::endl;

        if (m_logToFile && !m_filename.empty()) {
            std::ofstream file(m_filename, std::ios::app);
            if (file.is_open()) {
                file << logStr << std::endl;
            }
        }
    }

    static std::string levelToString(Level level) {
        switch (level) {
        case Level::DEBUG: return "DEBUG";
        case Level::INFO: return "INFO";
        case Level::WARNING: return "WARNING";
        case Level::ERROR: return "ERROR";
        case Level::FATAL: return "FATAL";
        }
        return "UNKNOWN";
    }

    template<typename T, typename... Args>
    static void buildMessage(std::stringstream& ss, T&& first, Args&&... rest) {
        ss << std::forward<T>(first);
        buildMessage(ss, std::forward<Args>(rest)...);
    }

    static void buildMessage(std::stringstream&) {}

    bool m_logToFile;
    std::string m_filename;
};

#endif
