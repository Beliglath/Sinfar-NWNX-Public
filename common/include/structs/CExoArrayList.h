#pragma once

template<typename T> struct CExoArrayList {                                                         \
    T* data;                                                                      \
    uint32_t len;                                                                       \
    uint32_t alloc;
    CExoArrayList() : data(NULL), len(0), alloc(0)
    {
    }
	void empty()
	{
		free(data);
		data = NULL;
		alloc = 0;
		len = 0;
	}
    void add(const T& val)
    {
        if (len == alloc)
        {
            alloc += 10;
            data = static_cast<T*>(realloc(data, sizeof(T)*alloc));
        }
        data[len] = val;
        len++;
    }
    void delindex(uint32_t index)
    {
        memmove(data+index, data+index+1, sizeof(T) * (len - index - 1));
        len--;
    }
    bool contains(const T& val)
    {
        for (uint32_t i=0; i<len; i++)
        {
            if (data[i] == val) return true;
        }
        return false;
    }
    void delvalue(const T& val)
    {
        for (uint32_t i=0; i<len; i++)
        {
            if (data[i] == val)
            {
                delindex(i);
                return;
            }
        }
    }
    T& get(uint32_t index)
    {
        return data[index];
    }                                              \
};
