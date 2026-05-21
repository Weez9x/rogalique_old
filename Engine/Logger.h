#pragma once

#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <fstream>

namespace EngineGame
{
	enum class LogLevel
	{
		Info,
		Warning,
		Error
	};

	class LogSink
	{
	public:
		virtual ~LogSink() = default;
		virtual void Log(LogLevel level, const std::string& message) = 0;
	};

	class ConsoleSink : public LogSink
	{
	public:
		void Log(LogLevel level, const std::string& message) override;
	};

	class FileSink : public LogSink
	{
	public:
		FileSink(const std::string& filename);
		~FileSink();

		void Log(LogLevel level, const std::string& message) override;

	private:
		std::ofstream file;
	};

	class Logger
	{
	public:
		static Logger* Instance();

		void AddSink(std::shared_ptr<LogSink> sink);

		void Info(const std::string& message);
		void Warning(const std::string& message);
		void Error(const std::string& message);

	private:
		Logger() = default;
		~Logger() = default;

		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

		void Log(LogLevel level, const std::string& message);
		std::string LevelToString(LogLevel level) const;

	private:
		std::vector<std::shared_ptr<LogSink>> sinks;
		std::mutex mutex;
	};
}