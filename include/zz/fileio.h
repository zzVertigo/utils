#pragma once

#include <fstream>
#include <format>
#include <chrono>
#include <type_traits>

namespace zz::io
{
	enum e_method
	{
		In = 1,
		Out = 2,
		InOut = In | Out
	};

	template<e_method IoKind>
	concept Input = static_cast<bool>(IoKind & In);

	template<e_method IoKind>
	concept Output = static_cast<bool>(IoKind & Out);

	namespace _detail
	{
		template<e_method IoKind>
		class FileIOImpl
		{
		public:
			using streamType =
				std::conditional_t<IoKind == In, std::ifstream,
				std::conditional_t<IoKind == Out, std::ofstream, std::fstream>>;

		public:
			FileIOImpl(streamType&& stream) noexcept
				: m_stream(std::move(stream))
			{

			}

			FileIOImpl(const std::string& fileName)
			{
				EnableStreamExceptions();
				m_stream.open(fileName.c_str());
			}

			std::string ReadLine()
				requires Input<IoKind>
			{
				std::string line{};

				EnableStreamExceptions();
				std::getline(m_stream, line);

				return line;
			}

			void WriteLine(std::string_view input)
				requires Output<IoKind>
			{
				EnableStreamExceptions();
				m_stream << input;
			}

			void Close()
			{
				EnableStreamExceptions();
				m_stream.close();
			}

		private:
			void EnableStreamExceptions()
			{
				m_stream.exceptions(streamType::badbit | streamType::failbit);
			}

		public:
			static constexpr e_method method = IoKind;

		private:
			streamType m_stream;
		};
	}

	using IFile = _detail::FileIOImpl<In>;
	using OFile = _detail::FileIOImpl<Out>;
	using File = _detail::FileIOImpl<InOut>;
}