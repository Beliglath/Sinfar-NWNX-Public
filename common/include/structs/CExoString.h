#pragma once

#include <string>

struct CExoString_s 
{
	char* text;
	uint32_t len;
};

struct CExoString
{
	char* text;
	uint32_t len;
	CExoString() : text(NULL), len(0) {}
	CExoString(const CExoString& copy)
	{
		if (copy.text)
		{
			text = strdup(copy.text);
			len = strlen(copy.text);
		}
		else
		{
			text = NULL;
			len = 0;
		}
	}
	CExoString(CExoString&& move)
	{
		text = move.text;
		len = move.len;
		if (move.text)
		{
			move.text = NULL;
			move.len = 0;
		}
	}
    void operator=(const CExoString& assign)
    {
		if (text)
		{
			free(text);
		}
		if (assign.text)
		{
			text = strdup(assign.text);
			len = strlen(assign.text);
		}
		else
		{
			text = NULL;
			len = 0;
		}
    }
    void operator=(const char* assign)
    {
		if (text)
		{
			free(text);
		}
		if (assign)
		{
			text = strdup(assign);
			len = strlen(assign);
		}
		else
		{
			text = NULL;
			len = 0;
		}
    }
	bool operator==(const char* str)
	{
		if(text && str)
		{
			return strcmp(text, str) == 0;
		}
		else
		{
			return (!text || !*text) == (!str || !*str);
		}
	}
	bool operator==(const CExoString& other)
	{
		return *this == other.text;
	}
	std::string to_str() const
	{
		return std::string(text?text:"");
	}
	operator std::string() const
	{
		return to_str();
	}
	CExoString(const char* str)
	{
		if (str)
		{
			text = strdup(str);
			len = strlen(str);
		}
		else
		{
			text = NULL;
			len = 0;
		}
	}
	CExoString(const std::string& str) : CExoString(str.c_str()){}
	~CExoString()
	{
		if (text)
		{
			free(text);
			text = NULL;
			len = 0;
		}
	}
};

#ifndef __x86_64__
static_assert(sizeof(CExoString) == 0x8, "CExoString size is bad");
#endif
