#pragma once

#include "core.h"

namespace nwnx { namespace core {
	
class CBNMessage
{
private:
	uint8_t* data;
	uint32_t len;
public:
	CBNMessage(uint8_t* data, uint32_t len) : data(data), len(len)
	{
		this->data += 4;
		this->len -= 4;
	}

	template<typename T> T read_num()
	{
		if (len < sizeof(T))
		{
			return 0;
		}
		else
		{
			T result = *(T*)data;
			data += sizeof(T);
			len -= sizeof(T);
			return result;
		}
	}
	
	template<typename T> T* read_vec(uint8_t size)
	{
		if (size == 0) return NULL;
		uint32_t read_size = sizeof(T)*size;
		if (len < read_size)
		{
			return NULL;
		}
		else
		{
			T* result = (T*)data;
			data += read_size;
			len -= read_size;
			return result;
		}
	}
	
	uint8_t read_byte()
	{
		return read_num<uint8_t>();
	}
	uint16_t read_word()
	{
		return read_num<uint16_t>();
	}
	uint32_t read_dword()
	{
		return read_num<uint32_t>();
	}
	std::string read_string()
	{
		uint8_t size = read_byte();
		if (size == 0) return "";
		char* data = read_vec<char>(size);
		if (data)
		{
			return std::string(data, size);
		}
		else
		{
			return "";
		}
	}
};

}
}