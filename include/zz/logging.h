#pragma once

#include "fileio.h"

#include <iostream>
#include <string>
#include <format>
#include <chrono>
#include <utility>

namespace zz::log
{
	enum e_logLevel
	{
		Info,
		Warning,
		Error,
		Debug
	};

	class Logger
	{
	public:
		Logger(const std::string& fileName, e_logLevel logLevel = Info)
			: m_logLevel(logLevel),
              m_fileIo(fileName)
		{
			
		}

		Logger(io::OFile&& fileIo, e_logLevel logLevel = Info)
			: m_logLevel(logLevel),
		      m_fileIo(std::move(fileIo))
		{
		}

		template <typename...Args>
		void Log(e_logLevel logLevel, std::string_view format, Args&&... args)
		{
			std::string consolePrefix;
			std::string filePrefix;

			const std::string time = GetCurrentDateTime();

			switch (logLevel)
			{
			case Info:
				consolePrefix = infoPrefixAnsi;
				filePrefix = infoPrefix;
				break;
			case Warning:
				consolePrefix = warnPrefixAnsi;
				filePrefix = warnPrefix;
				break;
			case Error:
				consolePrefix = errorPrefixAnsi;
				filePrefix = errorPrefix;
				break;
			case Debug:
				consolePrefix = debugPrefixAnsi;
				filePrefix = debugPrefix;
				break;
			}

			const std::string formatted = std::vformat(format, std::make_format_args(args...));

			const std::string consoleOutput = std::format("{} ({}): {}\n", consolePrefix, time, formatted);
			const std::string fileOutput = std::format("{} ({}): {}\n", filePrefix, time, formatted);

			m_fileIo.WriteLine(fileOutput);
			std::clog << consoleOutput;
		}

		template <e_logLevel logLevel, typename...Args>
		void Log(std::string format, Args... args)
		{
			if (m_logLevel >= logLevel)
				Log(logLevel, format, args...);
		}

	private:
		[[nodiscard]] std::string GetCurrentDateTime() const
		{
			const auto currentZone = std::chrono::current_zone();
			const auto time = currentZone->to_local(std::chrono::system_clock::now());

			return std::format("{:%Y-%m-%d %H:%M:%OS}", time);
		}

	private:
		const std::string infoPrefix = "[INFO]";
		const std::string warnPrefix = "[WARN]";
		const std::string errorPrefix = "[ERROR]";
		const std::string debugPrefix = "[DEBUG]";

		const std::string infoPrefixAnsi = "[\u001b[92mINFO\u001b[0m]";
		const std::string warnPrefixAnsi = "[\x1B[93mWARN\x1B[0m]";
		const std::string errorPrefixAnsi = "[\x1B[91mERROR\x1B[0m]";
		const std::string debugPrefixAnsi = "[\x1B[36mDEBUG\x1B[0m]";

		e_logLevel m_logLevel;
		io::OFile m_fileIo;
	};
}
