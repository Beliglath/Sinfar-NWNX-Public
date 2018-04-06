#include "player.h"

using namespace nwnx::core;
using namespace nwnx::player;

uint32_t last_player_to_server_id = 0;
unsigned char d_ret_code_handleplayertoservmsg[0x20];
int (*HanldePlayertoServerMessage_Org)(CNWSMessage*, uint32_t, uint8_t*, uint32_t) = (int (*)(CNWSMessage*, uint32_t, uint8_t*, uint32_t))&d_ret_code_handleplayertoservmsg;
int HanldePlayertoServerMessage_Hook(CNWSMessage* msg, uint32_t player_id, uint8_t* data, uint32_t data_size)
{
	last_player_to_server_id = player_id;
	return HanldePlayertoServerMessage_Org(msg, player_id, data, data_size);
}

CNWSPlayer* sending_obj_update_player = NULL;
unsigned char d_ret_code_upateclientgo[0x20];
int (*UpdateClientGameObjectsForPlayer_Org)(CServerExoAppInternal*, CNWSPlayer*, int, unsigned long long) = (int (*)(CServerExoAppInternal*, CNWSPlayer*, int, unsigned long long))&d_ret_code_upateclientgo;
int UpdateClientGameObjectsForPlayer_Hook(CServerExoAppInternal* server_internal, CNWSPlayer* player, int p3, unsigned long long p4)
{
	return UpdateClientGameObjectsForPlayer_Org(server_internal, player, p3, p4);
}

CNWSPlayer* sending_client_area_player = NULL;
unsigned char d_ret_code_sa[0x20];
void (*SendServerToPlayerArea_ClientArea_Org)(CNWSMessage*, CNWSPlayer*, CNWSArea*, float, float, float, const Vector*, int32_t) =
	(void (*)(CNWSMessage*, CNWSPlayer*, CNWSArea*, float, float, float, const Vector*, int32_t))&d_ret_code_sa;
void SendServerToPlayerArea_ClientArea_HookProc(CNWSMessage* msg, CNWSPlayer* player, CNWSArea* area,
	float f1, float f2, float f3, const Vector* v, int32_t i)
{
	sending_client_area_player = player;

	return SendServerToPlayerArea_ClientArea_Org(msg, player, area, f1, f2, f3, v, i);
}

void OnWritePlcAppearance_AddBool(CNWSMessage* msg, bool value)
{
	WriteBool(msg, value);
	if (players_extra_info[sending_obj_update_player->pl_id].game_version > 8109)
	{
		WriteBool(msg, 0);
	}		
}


float OnDriveControl_ReadObjId(CNWSMessage* msg, float p2, int p3)
{
	float result = ReadFloat(msg, p2, p3);
	if (players_extra_info[last_player_to_server_id].game_version > 8109)
	{
		ReadObjectId(msg);
	}
	return result;
}

unsigned char d_ret_cdoe_additemapprtomsg[0x20];
int (*AddItemAppearanceToMessage_Org)(CNWSMessage*, CNWSItem*) = (int (*)(CNWSMessage*, CNWSItem*))&d_ret_cdoe_additemapprtomsg;
void AddItemAppearanceToMessage_Hook(CNWSMessage* message, CNWSItem* item)
{
	AddItemAppearanceToMessage_Org(message, item);
	if (players_extra_info[sending_obj_update_player->pl_id].game_version >= 8150 && get_base_item(item->it_baseitem)->ModelType == 3)
	{
		for (uint32_t i=0; i<ITEM_APPR_ARMOR_NUM_MODELS; i++)
		{
			for (uint32_t j=0; j<6; j++)
			{
				WriteByte((CNWMessage*)message, 0xFF, 8);
			}
		}
	}
}

void OnAddActiveItemProperty_WriteLastBool(CNWSMessage* msg, bool value)
{
	WriteBool(msg, value);
	if (players_extra_info[sending_obj_update_player->pl_id].game_version >= 8150)
	{
		WriteBool(msg, 0);
	}	
}

uint32_t sending_server_status_player_id = 0;
int (*SendServerToPlayerServerStatus_Status_Org)(CNWSMessage*, uint32_t);
int SendServerToPlayerServerStatus_Status_Hook(CNWSMessage* msg, uint32_t player_id)
{
	sending_server_status_player_id = player_id;
	return SendServerToPlayerServerStatus_Status_Org(msg, player_id);
}
void OnSendServerStatus_WriteServerModeStr(CNWMessage* message, CExoString* exo_string, int num_bits)
{
	WriteCExoString(message, *exo_string, num_bits);
	exo_string->CExoString::~CExoString();
	
	if (players_extra_info[sending_server_status_player_id].game_version >= 8166)
	{
		WriteCExoString(message, "", 0x20);
		WriteCExoString(message, "", 0x20);
		WriteByte(message, 0, 0x8);
	}		
}

void OnPackArea_WriteExoLocString(CNWSMessage* msg, CExoLocString* loc_str, unsigned char p3)
{
	if (players_extra_info[sending_client_area_player->pl_id].game_version >= 8166)
	{
		WriteBool(msg, 0); //will write loc string
	}
	WriteCExoLocString(msg, loc_str, p3);
	//WriteCExoString((CNWMessage*)msg, "", 0x20);
}

/*void OnWriteItemUpdate_WriteExoLocString(CNWSMessage* msg, CExoLocString* loc_str, unsigned char p3)
{
	WriteCExoLocString(msg, loc_str, p3);
	if (players_extra_info[WriteGameObjectUpdate_UpdateObject_player->pl_id].game_version >= 8166)
	{
		if ((WriteGameObjectUpdate_UpdateObject_player_flags & 0x40) && WriteGameObjectUpdate_UpdateObject_object->obj_type == OBJECT_TYPE_CREATURE)
		{
			WriteBool(msg, 0); //lootable?
		}
	}
}*/

namespace nwnx {
	void init()
	{
		hook_function(0x08196544, (long)HanldePlayertoServerMessage_Hook, d_ret_code_handleplayertoservmsg, 12);
		hook_function(0x080a4a70, (unsigned long)UpdateClientGameObjectsForPlayer_Hook, d_ret_code_upateclientgo, 12);
		hook_function(0x0806504c, (unsigned long)SendServerToPlayerArea_ClientArea_HookProc, d_ret_code_sa, 12);
		
		hook_call(0x08061EE4, (long)OnWritePlcAppearance_AddBool);
		
		hook_call(0x0818F8E7, (long)OnDriveControl_ReadObjId);
		
		hook_function(0x080621B8, (long)AddItemAppearanceToMessage_Hook, d_ret_cdoe_additemapprtomsg, 12);

		hook_call(0x08062072, (long)OnAddActiveItemProperty_WriteLastBool);
		
		hook_func(0x08077a98, (long)SendServerToPlayerServerStatus_Status_Hook, (void*&)SendServerToPlayerServerStatus_Status_Org, 9);
		hook_call(0x08077BCF, (long)OnSendServerStatus_WriteServerModeStr);
		
		hook_call(0x080D0FBC, (long)OnPackArea_WriteExoLocString);
		
		//hook_call(0x08072DCE, (long)OnWriteItemUpdate_WriteExoLocString);
		
		enable_write(0x0830ED43);
		strcpy((char*)0x0830ED43, std::to_string(ee_server_version).c_str());
	}
	REGISTER_INIT(init);
}
