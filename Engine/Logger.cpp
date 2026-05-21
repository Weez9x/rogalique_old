#include "pch.h"
#include "Logger.h"
#include <iostream>

namespace EngineGame
{
	Logger* Logger::Instance()
	{
		static Logger instance;
		return &instance;
	}

	void Logger::AddSink(std::shared_ptr<LogSink> sink)
	{
		sinks.push_back(sink);
	}

	void Logger::Info(const std::string& message)
	{
		Log(LogLevel::Info, message);
	}

	void Logger::Warning(const std::string& message)
	{
		Log(LogLevel::Warning, message);
	}

	void Logger::Error(const std::string& message)
	{
		Log(LogLevel::Error, message);
	}

	void Logger::Log(LogLevel level, const std::string& message)
	{
		std::lock_guard<std::mutex> lock(mutex);

		const std::string formattedMessage = "[" + LevelToString(level) + "] " + message;

		for (auto& sink : sinks)
		{
			sink->Log(level, formattedMessage);
		}
	}

	std::string Logger::LevelToString(LogLevel level) const
	{
		switch (level)
		{
		case LogLevel::Info:
			return "INFO";
		case LogLevel::Warning:
			return "WARNING";
		case LogLevel::Error:
			return "ERROR";
		default:
			return "UNKNOWN";
		}
	}

	void ConsoleSink::Log(LogLevel level, const std::string& message)
	{
		std::cout << message << std::endl;
	}

	FileSink::FileSink(const std::string& filename)
	{
		file.open(filename, std::ios::app);
	}

	FileSink::~FileSink()
	{
		if (file.is_open())
		{
			file.close();
		}
	}

	void FileSink::Log(LogLevel level, const std::string& message)
	{
		if (file.is_open())
		{
			file << message << std::endl;
		}
	}
}