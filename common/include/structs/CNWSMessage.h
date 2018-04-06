#pragma once

struct CNWSMessage_s {
    char unk_0x0[0x24];
	uint8_t* msg_data; //0x24
	uint32_t msg_len; //0x28
	uint32_t msg_current_index; //0x2c
	uint32_t msg_data_2; //0x30
	uint32_t msg_len_2; //0x34
	uint32_t msg_current_index_2; //0x38
	uint32_t unk_0x3c;
	uint8_t unk_0x40;
	uint8_t unk_0x41;
	uint16_t unk_0x42;
	uint32_t unk_0x44;
	uint32_t unk_0x48;
	
	bool will_overflow(uint32_t rel_index, uint32_t read_size)
	{
		if (msg_current_index+rel_index+read_size > msg_len)
		{
			fprintf(stderr, "CNWSMessage overflow:%d+%d+%d vs %d\n", msg_current_index, rel_index, read_size, msg_len);
			return true;
		}
		return false;
	}
	uint32_t get_dword(uint32_t rel_index=0)
	{
		if (will_overflow(rel_index, 4)) return 0;
		return *(uint32_t*)(msg_data+msg_current_index+rel_index);		
	}
	uint32_t get_object(uint32_t rel_index=0)
	{
		if (will_overflow(rel_index, 4)) return OBJECT_INVALID;
		return ((*(uint32_t*)(msg_data+msg_current_index+rel_index))&0x7FFFFFFF);
	}
	float get_float(uint32_t rel_index=0)
	{
		if (will_overflow(rel_index, 4)) return 0;
		return *(float*)(msg_data+msg_current_index+rel_index);
	}
	CResRef get_resref(uint32_t rel_index=0)
	{
		if (will_overflow(rel_index, 4)) return CResRef();
		return CResRef((char*)msg_data+msg_current_index+rel_index);
	}
	uint8_t get_byte(uint32_t rel_index=0)
	{
		if (will_overflow(rel_index, 1)) return 0;
		return *(uint8_t*)(msg_data+msg_current_index+rel_index);	
	}
	std::string get_string(uint32_t rel_index=0)
	{
		uint8_t len = get_byte(rel_index);
		if (len == 0 || will_overflow(rel_index+1, len)) return "";
		return std::string((char*)msg_data+msg_current_index+rel_index+1, len);
	}
};
