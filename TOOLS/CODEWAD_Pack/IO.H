#pragma once

#include <iostream>
#include <fstream>

#ifdef _DEBUG
	#include <assert.h>
#endif

namespace IO
{
	struct StreamReader
	{
		StreamReader(const char* filePath)
		{
			if (m_isOpen)
			{
				close();
			}
			open(filePath);
		}

		StreamReader::~StreamReader()
		{
			if (m_stream.is_open())
			{
				m_stream.close();
			}
		}

		void open(const char* filePath)
		{
			m_stream.open(filePath, std::ios::binary);
			m_isOpen = m_stream.is_open();

			if (m_isOpen)
			{
				m_stream.seekg(0, SEEK_END);
				m_length = tell();
				m_stream.seekg(0, SEEK_SET);
			}
		}

		template <typename T>
		void read(T& input, unsigned long length = 0)
		{
#ifdef _DEBUG
			assert(m_isOpen);
#endif

			if (!length)
			{
				m_stream.read(reinterpret_cast<char*>(&input), sizeof(T));
				m_pos += sizeof(T);
			}
			else
			{
				m_stream.read(reinterpret_cast<char*>(&input), length);
				m_pos += length;
			}
		}

		void readRaw(char* input, unsigned long length = 0)
		{
			m_stream.read(input, length);
			m_pos += length;
		}

		void readString(std::string& string)
		{
			char c = -1;
			while (c != 0)
			{
				read(c);
				string += c;
			}
		}

		std::streampos tell()
		{
			if (m_stream.is_open())
			{
				return m_stream.tellg();
			}

			return std::streampos(-1);
		}

		std::streampos length()
		{
			if (m_stream.is_open())
			{
				return m_length;
			}

			return std::streampos(-1);
		}

		void seek(const unsigned int& pos)
		{
			if (m_stream.is_open())
			{
				m_pos = pos;
				m_stream.seekg(m_pos, SEEK_SET);
			}
		}

		void close()
		{
			if (m_isOpen)
			{
				m_stream.close();
				m_isOpen = false;
			}
		}

		bool m_isOpen;
		std::ifstream m_stream;
		std::streampos m_length;
		std::streampos m_pos;
	};

	struct StreamWriter
	{
		StreamWriter(const char* filePath)
		{
			open(filePath);
		}

		StreamWriter::~StreamWriter()
		{
			if (m_stream.is_open())
			{
				m_stream.close();
			}
		}

		void open(const char* filePath)
		{
			if (m_isOpen)
			{
				close();
			}
			m_stream.open(filePath, std::ios::binary);
			m_isOpen = m_stream.is_open();
		}

		template <typename T>
		void write(T& input, unsigned long length = 0)
		{
#ifdef _DEBUG
			assert(m_isOpen);
#endif

			if (!length)
			{
				m_stream.write(reinterpret_cast<char*>(&input), sizeof(T));
				m_pos += sizeof(T);
			}
			else
			{
				m_stream.write(reinterpret_cast<char*>(input), length);
				m_pos += length;
			}
		}

		void readRaw(char* input, unsigned long length = 0)
		{
			m_stream.write(input, length);
			m_pos += length;
		}

		std::streampos tell()
		{
			if (m_stream.is_open())
			{
				return m_stream.tellp();
			}

			return std::streampos(-1);
		}

		void seek(const unsigned int& pos)
		{
			if (m_stream.is_open())
			{
				m_pos = pos;
				m_stream.seekp(m_pos, SEEK_SET);
			}
		}

		void close()
		{
			if (m_isOpen)
			{
				m_stream.close();
				m_isOpen = false;
			}
		}

		bool m_isOpen;
		std::ofstream m_stream;
		std::streampos m_pos;
	};
}
