#pragma once

#include "CExoArrayList.h"

struct CServerAIEventNode
{
	int64_t time;
	uint32_t obj_id;
	uint32_t obj_self_id;
	int event_type;
	void* event_data;
}; //size = 0x18

struct CExoAIObjectsArrayList
{
	uint32_t unknown;
	CExoArrayList<uint32_t> objects;
};

struct CServerAIMaster_s {
	CExoAIObjectsArrayList	 ai_objects[5];
	uint32_t unk_0x50;
	CExoLinkedList ai_pending_events; //0x54
};
