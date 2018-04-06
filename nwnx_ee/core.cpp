#include "core.h"

#include <cmath>
#include <malloc.h>

namespace nwnx
{
namespace core
{
	HOOKS& get_hooks(hook::type h)
	{
		static std::unordered_map<int, HOOKS> all_hooks;
		return all_hooks[static_cast<int>(h)];
	}
	void run_hook_event(hook::type event)
	{
		for (auto& hook: get_hooks(event))
		{
			hook();
		}		
	}
	void register_hook(hook::type h, std::function<void()> HOOK)
	{
		get_hooks(h).push_back(HOOK);
	}
	REGISTERED_HOOK::REGISTERED_HOOK(hook::type h, std::function<void()> HOOK)
	{
		register_hook(h, HOOK);
	}

	void enable_write(unsigned long location)
	{
		char *page;
		page = (char *) location;
		page = (char *) (((int) page + PAGESIZE - 1) & ~(PAGESIZE - 1));
		page -= PAGESIZE;

		if (mprotect (page, PAGESIZE, PROT_WRITE | PROT_READ | PROT_EXEC))
			perror ("mprotect");
	}

	void hook_call(uint32_t from_addr, uint32_t to_func)
	{
		enable_write(from_addr);
		*(uint32_t*)(from_addr+1) = (to_func-(from_addr+5));
	}

	void hook_function(long from, long to, unsigned char* d_ret_code, long len)
	{
		unsigned char d_jmp_code[] = "\x68\x60\x70\x80\x90" /* push uint32_t 0x90807060 */
			"\xc3\x90\x90\x90\x90";//x00 /* ret , nop , nop */
		// enable write to code pages
		enable_write (from);
		// copy orig code stub to our "ret_code"
		len = len ? len : sizeof(d_jmp_code)-1; // - trailing 0x00
		memcpy ((void *) d_ret_code, (const void *) from, len);
		// make ret code
		*(long *)(d_jmp_code + 1) = from + len;
		memcpy ((char *) d_ret_code + len, (const void *) d_jmp_code, 6);
		// make hook code
		*(long *)(d_jmp_code + 1) = to;
		memcpy ((void *) from, (const void *) d_jmp_code, 6);
	}

	void hook_func(long from, long to, void*& from_org, long len)
	{
		from_org = malloc(0x20);
		hook_function(from, to, (unsigned char*)from_org, len);
	}

	void hook_func(long from, long to, long len)
	{
		hook_function(from, to, d_ret_code_nouse, len);
	}

	int run_script(CExoString* sname, int objid, int p3)
	{
		return ((int (*)(CVirtualMachine*, CExoString*, uint32_t, int))0x08261f94)(virtual_machine, sname, objid, p3);
	}
	int run_script(const std::string& sname, int objid, int p3)
	{
		CExoString script_exo_name(sname.c_str());
		return run_script(&script_exo_name, objid, 1);
	}
	int run_script(const std::string& sname, int objid)
	{
		return run_script(sname, objid, 1);
	}

	CVirtualMachine* virtual_machine = NULL;
	CNWRules* nwn_rules;
	CExoBase** p_exo_base = (CExoBase**)0x0832F1E4;
	CAppManager** p_app_manager = (CAppManager**)0x0832F1F4;
	CServerExoAppInternal* server_internal = NULL;
	CExoResMan* resman = NULL;
	CNWSModule* module = NULL;
	CTlkTable* talk_table = NULL;

	bool module_loaded = false;

	unsigned char d_ret_code_newvm[0x20];
	int (*VirtualMachineConstructor_Org)(CVirtualMachine*) = (int (*)(CVirtualMachine*))&d_ret_code_newvm;
	int VirtualMachineConstructor_HookProc(CVirtualMachine* me)
	{
		virtual_machine = me;
		return VirtualMachineConstructor_Org(me);
	}
	unsigned char d_ret_code_serverexoapp[0x20];
	void (*ServerExoAppConstructor_Org)(CServerExoApp*) = (void (*)(CServerExoApp*))&d_ret_code_serverexoapp;
	void ServerExoAppConstructor_HookProc(CServerExoApp* me)
	{
		ServerExoAppConstructor_Org(me);
		server_internal = me->srv_internal;
	}
	unsigned char d_ret_code_exoresman[0x20];
	void (*ExoResManConstructor_Org)(CExoResMan*) = (void (*)(CExoResMan*))&d_ret_code_exoresman;
	void ExoResManConstructor_HookProc(CExoResMan* me)
	{
		resman = me;
		(*p_exo_base)->exp_pack = 3;
		ExoResManConstructor_Org(me);
	}
	unsigned char d_ret_code_nwrules[0x20];
	void (*NWRulesConstructor_Org)(CNWRules*) = (void (*)(CNWRules*))&d_ret_code_nwrules;
	void NWRulesConstructor_HookProc(CNWRules* me)
	{
		nwn_rules = me;
		return NWRulesConstructor_Org(me);
	}
	unsigned char d_ret_code_newmodule[0x20];
	int (*ModuleConstructor_Org)(CNWSModule*, CExoString*, int, int) = (int (*)(CNWSModule*, CExoString*, int, int))&d_ret_code_newmodule;
	int ModuleConstructor_HookProc(CNWSModule* me, CExoString* name, int p3, int p4)
	{
		module = me;
		return ModuleConstructor_Org(me, name, p3, p4);
	}
	unsigned char d_ret_code_tlktable[0x20];
	void (*TlkTableConstructor_Org)(CTlkTable*) = (void (*)(CTlkTable*))&d_ret_code_tlktable;
	void TlkTableConstructor_HookProc(CTlkTable* me)
	{
		talk_table = me;
		return TlkTableConstructor_Org(me);
	}

	unsigned char d_ret_code_nouse[0x20];
	int current_server_id = -1;
	const int sinfar_vault_id = 15;

	std::unordered_map<uint32_t, CGameObject*> cgoa;
	std::unordered_map<uint32_t, CGameObject*>::iterator cgoa_iter;
	unsigned char d_ret_code_goa_atpos[0x20];
	unsigned char d_ret_code_goa_charatpos[0x20];
	unsigned char d_ret_code_goa_external[0x20];
	unsigned char d_ret_code_goa_internal[0x20];
	unsigned char d_ret_code_delete[0x20];
	unsigned char d_ret_code_deleteget[0x20];
	unsigned char d_ret_code_get[0x20];
	uint32_t next_object_id = 0;
	uint32_t next_char_object_id = 0x7fffffff;
	int CGOA_AddObjectAtPos(void* array, uint32_t object_id, CGameObject* o)
	{
		if (o == (CGameObject*)OBJECT_INVALID)
		{
			fprintf(stderr, "CGOA_AddObjectAtPos: adding object invalid to game objects array\n");
		}
		else
		{
			if (object_id == OBJECT_INVALID) return CGOA_RET_BAD_ID;
			cgoa[object_id] = o;
		}
		return CGOA_RET_SUCCESS;
	}
	int CGOA_AddCharacterAtPos(void* array, uint32_t object_id, CGameObject* o)
	{
		fprintf(stderr, "CGOA_AddCharacterAtPos called but not implemented\n");
		fflush(stderr);
		return 0;
	}
	int CGOA_AddInternalObject(void* array, uint32_t* p_object_id, CGameObject* o, int isChar)
	{
		if (o == (CGameObject*)OBJECT_INVALID)
		{
			fprintf(stderr, "CGOA_AddInternalObject: adding object invalid to game objects array\n");
			*p_object_id = OBJECT_INVALID;
			return CGOA_RET_NULL_OBJECT;
		}

		if (o == NULL)
		{
			*p_object_id = OBJECT_INVALID;
			return CGOA_RET_NULL_OBJECT;
		}

		if (isChar)
		{
			*p_object_id = next_char_object_id;
			next_char_object_id--;
		}
		else
		{
			*p_object_id = next_object_id;
			next_object_id++;
		}
		cgoa[*p_object_id] = o;
		return CGOA_RET_SUCCESS;
	}
	int CGOA_AddExternalObject(void* array, uint32_t* p_object_id, CGameObject* o, int isChar)
	{
		fprintf(stderr, "CGOA_AddExternalObject called but not implemented\n");
		fflush(stderr);
		return 0;
	}
	int CGOA_Delete(void *array, uint32_t object_id)
	{
		if (object_id == OBJECT_INVALID) return CGOA_RET_BAD_ID;
		cgoa_iter = cgoa.find(object_id);
		if (cgoa_iter == cgoa.end()) return CGOA_RET_BAD_ID;
		cgoa.erase(cgoa_iter);
		return CGOA_RET_SUCCESS;
	}
	int CGOA_DeleteAndGet(void* array, uint32_t object_id, CGameObject** p_o)
	{
		if (object_id == OBJECT_INVALID)
		{
			*p_o = NULL;
			return CGOA_RET_BAD_ID;
		}
		cgoa_iter = cgoa.find(object_id);
		if (cgoa_iter == cgoa.end())
		{
			*p_o = NULL;
			return CGOA_RET_BAD_ID;
		}
		*p_o = cgoa_iter->second;
		cgoa.erase(cgoa_iter);
		return CGOA_RET_SUCCESS;
	}
	int CGOA_GetObject(void* array, uint32_t object_id, CGameObject** p_o)
	{
		if (object_id == OBJECT_INVALID)
		{
			*p_o = NULL;
			return CGOA_RET_BAD_ID;
		}
		cgoa_iter = cgoa.find(object_id);
		if (cgoa_iter == cgoa.end())
		{
			*p_o = NULL;
			return CGOA_RET_BAD_ID;
		}
		*p_o = cgoa_iter->second;
		return CGOA_RET_SUCCESS;
	}
	CGameObject* GetGameObject(uint32_t object_id)
	{
		if (object_id == OBJECT_INVALID) return NULL;
		cgoa_iter = cgoa.find(object_id);
		return cgoa_iter == cgoa.end() ? NULL : cgoa_iter->second;
	}
	CNWSObject* GetObjectById(uint32_t object_id)
	{
		CGameObject* o = GetGameObject(object_id);
		return (o ? o->vtable->AsNWSObject(o) : NULL);
	}
	CNWSStore* GetStoreById(uint32_t object_id)
	{
		CGameObject* o = GetGameObject(object_id);
		return (o ? o->vtable->AsNWSStore(o) : NULL);
	}
	CNWSItem* GetItemById(uint32_t object_id)
	{
		CGameObject* o = GetGameObject(object_id);
		return (o ? o->vtable->AsNWSItem(o) : NULL);
	}
	CNWSCreature* GetCreatureById(uint32_t object_id)
	{
		CGameObject* o = GetGameObject(object_id);
		return (o ? o->vtable->AsNWSCreature(o) : NULL);
	}
	CNWSArea* GetAreaById(uint32_t object_id)
	{
		CGameObject* o = GetGameObject(object_id);
		return (o ? o->vtable->AsNWSArea(o) : NULL);
	}
	CNWSDoor* GetDoorById(uint32_t object_id)
	{
		CGameObject* o = GetGameObject(object_id);
		return (o ? o->vtable->AsNWSDoor(o) : NULL);
	}
	CNWSTrigger* GetTriggerById(uint32_t object_id)
	{
		CGameObject* o = GetGameObject(object_id);
		return (o ? o->vtable->AsNWSTrigger(o) : NULL);
	}
	CNWSAreaOfEffectObject* GetAreaOfEffectObjectById(uint32_t object_id)
	{
		CGameObject* o = GetGameObject(object_id);
		return (o ? o->vtable->AsNWSAreaOfEffectObject(o) : NULL);
	}
	CNWSPlaceable* GetPlaceableById(uint32_t object_id)
	{
		CGameObject* o = GetGameObject(object_id);
		return (o ? o->vtable->AsNWSPlaceable(o) : NULL);
	}
	CNWSModule* get_module()
	{
		CGameObject* o = GetGameObject(0);
		return (o ? o->vtable->AsNWSModule(o) : NULL);
	}

	int (*SendServerToPlayerMessage)(CNWSMessage*, uint32_t, uint8_t, uint8_t, char*, uint32_t) = (int (*)(CNWSMessage*, uint32_t, uint8_t, uint8_t, char*, uint32_t))0x8076f10;
	int (*GetWriteMessage)(CNWSMessage*, char**, uint32_t*) = (int (*)(CNWSMessage*, char**, uint32_t*))0x80c2e54;
	void (*CreateWriteMessage)(CNWSMessage*, uint32_t, uint32_t, int) = (void (*)(CNWSMessage*, uint32_t, uint32_t, int))0x80c3aec;
	void (*WriteInt)(CNWMessage*, int, int) = (void (*)(CNWMessage*, int, int))0x080c3f00;
	void (*WriteFloat)(CNWMessage*, float, float, int) = (void (*)(CNWMessage*, float, float, int))0x080c40c8;
	void (*WriteCExoString)(CNWMessage*, CExoString, int) = (void (*)(CNWMessage*, CExoString, int))0x80c2d04;
	void (*WriteCExoLocString)(CNWSMessage*, CExoLocString*, uint8_t) = (void (*)(CNWSMessage*, CExoLocString*, uint8_t))0x08052480;
	void (*WriteChar)(CNWSMessage*, char, int) = (void (*)(CNWSMessage*, char, int))0x80c3cb4;
	void (*WriteObjectId)(CNWSMessage*, uint32_t) = (void (*)(CNWSMessage*, uint32_t))0x8052434;
	void (*WriteBool)(CNWSMessage*, bool) = (void (*)(CNWSMessage*, bool))0x80c3c08;
	void (*WriteWord)(CNWMessage*, uint16_t, int) = (void (*)(CNWMessage*, uint16_t, int))0x80c3d44;
	void (*WriteDWORD)(CNWSMessage*, uint32_t, int) = (void (*)(CNWSMessage*, uint32_t, int))0x80c3e74;
	void (*WriteResRef)(CNWMessage*, CResRef, int) = (void (*)(CNWMessage*, CResRef, int))0x80c2c74;
	void (*WriteByte)(CNWMessage*, uint8_t, int) = (void (*)(CNWMessage*, uint8_t, int))0x80c3c24;
	int (*ReadMessageOverflow)(CNWSMessage*, int) = (int (*)(CNWSMessage*, int))0x80c3a64;
	int (*ReadMessageUnderflow)(CNWSMessage*, int) = (int (*)(CNWSMessage*, int))0x80c3a8c;
	float (*ReadFloat)(CNWSMessage*, float, int) = (float (*)(CNWSMessage*, float, int))0x80c37fc;
	CExoString (*ReadExoString)(CNWSMessage*, int) = (CExoString (*)(CNWSMessage*, int))0x80c2954;
	int (*ReadInt)(CNWSMessage*, int) = (int (*)(CNWSMessage*, int))0x80c3710;
	uint32_t (*ReadObjectId)(CNWSMessage*) = (uint32_t (*)(CNWSMessage*))0x08052d84;
	void (*CExoLocString_Constructor)(CExoLocString*) = (void (*)(CExoLocString*))0x082c9eb8;
	void (*CExoLocString_Destructor)(CExoLocString*, int) = (void (*)(CExoLocString*, int))0x082c9f60;
    
    void (*AddActionToFront)(CNWSObject*, uint32_t, uint16_t, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*,
        uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*) =
            (void (*)(CNWSObject*, uint32_t, uint16_t, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*,
        uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*))0x081ca5c0;
    void (*AddAction)(CNWSObject*, uint32_t, uint16_t, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*,
        uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*) =
            (void (*)(CNWSObject*, uint32_t, uint16_t, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*,
        uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*))0x081c9384;

	void (*AddLocString)(CExoLocString*, int, CExoString, uint8_t) = (void (*)(CExoLocString*, int, CExoString, uint8_t))0x082ca040;
	void (*ClearLocString)(CExoLocString*) = (void (*)(CExoLocString*))0x082ca0c0;
	int (*GetLevel)(CNWSCreatureStats*, int) = (int (*)(CNWSCreatureStats*, int))0x08163cc8;
    CNWSCombatAttackData* (*GetAttack)(CNWSCombatRound*, int) = (CNWSCombatAttackData* (*)(CNWSCombatRound*, int))0x080e522c;

	struct STR_RES
	{
		CExoString exo_string;
		CResRef resref;
		uint32_t unknown;
	};
	int (*GetTalkTableStr)(CTlkTable*, uint32_t, STR_RES*, int) = (int (*)(CTlkTable*, uint32_t, STR_RES*, int))0x82b4404;
	std::string get_string_by_str_ref(uint32_t strref)
	{
		STR_RES str_ref;
		str_ref.resref.value[0] = 0;
		GetTalkTableStr(talk_table, strref, &str_ref, 0);
		if (str_ref.exo_string.text)
		{
			std::string result(str_ref.exo_string.text);
			if (result == "Bad Strref") return "";
			return result;
		}
		else
		{
			return "";
		}
	}
	const char* get_first_loc_string(CExoLocString& loc_string)
	{
		CExoLinkedList* strings = loc_string.list;
		if (strings && strings->header)
		{
			CExoLinkedListNode* string_node = strings->header->first;
			while (string_node)
			{
				CExoLocStringElement* string_element = (CExoLocStringElement*)string_node->data;
				if (string_element->text.text && *(string_element->text.text))
				{
					return string_element->text.text;
				}
				string_node = string_node->next;
			}
		}
		return NULL;
	}
	std::string get_creature_final_name(CNWSCreature* creature)
	{
		if (creature->cre_display_name.text)
		{
			return creature->cre_display_name.text;
		}
		else
		{
			std::string final_name;
			//first name
			const char* firstname = get_first_loc_string(creature->cre_stats->cs_firstname);
			if (firstname)
			{
				final_name = firstname;
			}
			else if (creature->cre_stats->cs_firstname.strref != 0xFFFFFFFF)
			{
				final_name = get_string_by_str_ref(creature->cre_stats->cs_firstname.strref);
			}
			//last name
			const char* lastname = get_first_loc_string(creature->cre_stats->cs_lastname);
			if (lastname)
			{
				if (!final_name.empty()) final_name += " ";
				final_name += lastname;
			}
			else if (creature->cre_stats->cs_lastname.strref != 0xFFFFFFFF)
			{
				if (!final_name.empty()) final_name += " ";
				final_name += get_string_by_str_ref(creature->cre_stats->cs_lastname.strref);
			}
			return final_name;
		}
	}
    
    CNWBaseItem* (*GetBaseItem)(CNWRules*, int) = (CNWBaseItem* (*)(CNWRules*, int))0x080cba5c;
    CNWBaseItem* get_base_item(int baseitem)
    {
        return GetBaseItem(nwn_rules, baseitem);
    }

	CNWSMessage* get_nws_message()
	{
		return (*p_app_manager)->app_server->srv_internal->srv_client_messages;
	}
	CNWSItem* get_item_in_slot(CNWSInventory* inventory, uint32_t slot_flag)
	{
		if (slot_flag)
		{
			uint32_t array_slot = __builtin_ctz(slot_flag);
			if (array_slot > 17) return NULL;
			return GetItemById(inventory->inv_items[array_slot]);
		}
		return NULL;
	}

	void DestroyTileset_HookProc(void* tileset)
	{
		return;
	}
	void DestroyResMan_HookProc()
	{
		return;
	}
	CNWSPlayer* get_player_by_id(uint32_t pl_id)
	{
		CExoLinkedListNode* player_list_node = server_internal->srv_client_list_1->header->first;
		while (player_list_node)
		{
			CNWSPlayer* player = (CNWSPlayer*)player_list_node->data;
			if (player->pl_id == pl_id) return player;
			player_list_node = player_list_node->next;
		}
		return NULL;
	}
	CNWSPlayer* get_player_by_game_object_id(uint32_t object_id)
	{
		if (object_id == OBJECT_INVALID) return NULL;
		CExoLinkedListNode* player_list_node = server_internal->srv_client_list_1->header->first;
		while (player_list_node)
		{
			CNWSPlayer* player = (CNWSPlayer*)player_list_node->data;
			if (player->pl_oid == object_id || player->pl_pc_oid == object_id) return player;
			player_list_node = player_list_node->next;
		}
		return NULL;
	}
	CNWSPlayer* GetPlayerByGameObjectId_HookProc(CServerExoApp* server, uint32_t object_id)
	{
		return get_player_by_game_object_id(object_id);
	}
	CNWSPlayer* GetClientByGameObjectId_Unique_Hook(CServerExoApp* server, uint32_t object_id)
	{
		if (object_id == OBJECT_INVALID) return NULL;
		CExoLinkedListNode* player_list_node = server_internal->srv_client_list_1->header->first;
		while (player_list_node)
		{
			CNWSPlayer* player = (CNWSPlayer*)player_list_node->data;
			if (player->pl_oid == object_id) return player;
			player_list_node = player_list_node->next;
		}
		return NULL;
	}
	uint32_t GetPlayerIdByGameObjectId_HookProc(CServerExoApp* server, uint32_t object_id)
	{
		CNWSPlayer* player = GetPlayerByGameObjectId_HookProc(server, object_id);
		if (player)
		{
			return player->pl_id;
		}
		else
		{
			return 0xfffffffe;
		}
	}
	CGameObject* GetGameObjectById_HookProc(CServerExoApp* server, uint32_t object_id)
	{
		if (object_id == OBJECT_INVALID) return NULL;
		cgoa_iter = cgoa.find(object_id);
		if (cgoa_iter == cgoa.end()) return NULL;
		return cgoa_iter->second;
	}
	CNWSCreature* GetCreatureById_HookProc(CServerExoApp* server, uint32_t object_id)
	{
		if (object_id == OBJECT_INVALID) return NULL;
		cgoa_iter = cgoa.find(object_id);
		if (cgoa_iter == cgoa.end()) return NULL;
		return cgoa_iter->second->vtable->AsNWSCreature(cgoa_iter->second);
	}
	CNWSItem* GetItemById_HookProc(CServerExoApp* server, uint32_t object_id)
	{
		if (object_id == OBJECT_INVALID) return NULL;
		cgoa_iter = cgoa.find(object_id);
		if (cgoa_iter == cgoa.end()) return NULL;
		return cgoa_iter->second->vtable->AsNWSItem(cgoa_iter->second);
	}
	CNWSArea* GetAreaById_HookProc(CServerExoApp* server, uint32_t object_id)
	{
		if (object_id == OBJECT_INVALID) return NULL;
		cgoa_iter = cgoa.find(object_id);
		if (cgoa_iter == cgoa.end()) return NULL;
		return cgoa_iter->second->vtable->AsNWSArea(cgoa_iter->second);
	}
	CGameObject* GetPlayerGameObject_HookProc(CNWSPlayer* player)
	{
		cgoa_iter = cgoa.find(player->pl_oid);
		if (cgoa_iter == cgoa.end())
		{
			if (player->pl_oid != player->pl_pc_oid)
			{
				player->pl_oid = player->pl_pc_oid;
				return GetPlayerGameObject_HookProc(player);
			}
			else
			{
				return NULL;
			}
		}
		return cgoa_iter->second;
	}
	CNWSArea* GetArea_HookProc(CNWSObject* object)
	{
		cgoa_iter = cgoa.find(object->obj_area_id);
		if (cgoa_iter == cgoa.end()) return NULL;
		return cgoa_iter->second->vtable->AsNWSArea(cgoa_iter->second);
	}

	void (*CNWSItem_Destructor)(CNWSItem*, int) = (void (*)(CNWSItem*, int))0x0819f0c0;

	std::unordered_map<std::string, std::deque<uint32_t>> tags_map;
	bool safe_add_to_tags_map(const std::string& tag, uint32_t object_id)
	{
		if (tag.empty() || tag == "NULL")
		{
			return false;
		}
		CGameObject* o = GetGameObject(object_id);
		if (o)
		{
			if (o->type == 6 ||  //items
				(o->type == 9 && strncmp(tag.c_str(), "P_", 2) != 0)) //placeables
			{
				return false;
			}
		}

		tags_map[tag].push_front(object_id);
		return true;
	}
	void remove_object_from_tags_map(const std::string& tag, uint32_t object_id)
	{
		auto objects_with_tag_iter = tags_map.find(tag);
		if (objects_with_tag_iter != tags_map.end())
		{
			auto& objets_with_tag = objects_with_tag_iter->second;
			for (auto iter=objets_with_tag.begin(); iter!=objets_with_tag.end(); iter++)
			{
				if (*iter == object_id)
				{
					objets_with_tag.erase(iter);
					break;
				}
			}
			if (objets_with_tag.empty())
			{
				tags_map.erase(objects_with_tag_iter);
			}
		}
	}
	unsigned char d_ret_code_addlookup[0x20];
	int (*AddToLookupTable_Org)(CNWSModule*, CExoString*, uint32_t) = (int (*)(CNWSModule*, CExoString*, uint32_t))&d_ret_code_addlookup;
	int AddToLookupTable_HookProc(CNWSModule* module, CExoString* exo_tag, uint32_t object_id)
	{
		std::string tag;
		if (exo_tag->text)
		{
			tag = exo_tag->text;
			exo_tag->CExoString::~CExoString();
		}
		safe_add_to_tags_map(tag, object_id);
		return 1;
	}
	unsigned char d_ret_code_rmlookup[0x20];
	int (*RemoveFromLookupTable_Org)(CNWSModule*, CExoString*, uint32_t) = (int (*)(CNWSModule*, CExoString*, uint32_t))&d_ret_code_rmlookup;
	int RemoveFromLookupTable_HookProc(CNWSModule* module, CExoString* exo_tag, uint32_t object_id)
	{
		std::string tag;
		if (exo_tag->text)
		{
			tag = exo_tag->text;
			exo_tag->CExoString::~CExoString();
		}
		remove_object_from_tags_map(tag, object_id);
		return 1;
	}
	int RemoveItemFromLookupTable(CNWSModule* module, CExoString* exo_tag, uint32_t object_id)
	{
		exo_tag->CExoString::~CExoString();
		return 1;
	}
	int RemovePlaceableFromLookupTable(CNWSModule* module, CExoString* exo_tag, uint32_t object_id)
	{
		std::string tag;
		if (exo_tag->text)
		{
			tag = exo_tag->text;
			exo_tag->CExoString::~CExoString();
		}

		if (tag.empty() || tag == "NULL")
		{
			return 1;
		}

		remove_object_from_tags_map(tag, object_id);
		return 1;
	}
	uint32_t find_object_by_tag(const std::string& tag, uint32_t index)
	{
		auto objects_with_tag_iter = tags_map.find(tag);
		if (objects_with_tag_iter != tags_map.end())
		{
			auto& objets_with_tag = objects_with_tag_iter->second;
			if (index < objets_with_tag.size())
			{
				return objets_with_tag.at(index);
			}
		}
		return OBJECT_INVALID;
	}
	uint32_t FindObjectByTag_HookProc(CNWSModule* module, CExoString* exo_tag, uint32_t index)
	{
		return find_object_by_tag(exo_tag->to_str(), index);
	}
	uint32_t FindObjectByTagAndType_HookProc(CNWSModule* module, CExoString* exo_tag, int type, uint32_t index)
	{
		return find_object_by_tag(exo_tag->to_str(), index);
	}

	CNWSScriptVarTable* GetGameObjectVarTable(CGameObject* o)
	{
		switch (o->type)
		{
			case OBJECT_TYPE_MODULE: return &(o->vtable->AsNWSModule(o)->mod_vartable);
			case OBJECT_TYPE_AREA: return &(o->vtable->AsNWSArea(o)->area_vartable);
			default: 
				CNWSObject* object = o->vtable->AsNWSObject(o);
				if (object)
				{
					return &(object->obj_vartable);
				}
				else
				{
					return NULL;
				}
		}
	}
	void** get_local_var(CNWSScriptVarTable* var_table, uint32_t var_type, const std::string& var_name)
	{
		uint32_t nVarCount = var_table->vt_len;
		for (uint32_t nVar=0; nVar<nVarCount; nVar++)
		{
			CScriptVariable* var = &(var_table->vt_list[nVar]);
			if (var->var_type == var_type)//int
			{
				if (var->var_name == var_name)
				{
					return (void**)&(var->var_value);
				}
			}
		}
		return NULL;
	}
	int get_local_int(CNWSScriptVarTable* var_table, const std::string& var_name)
	{
		int * result = (int*)get_local_var(var_table, VARTYPE_INT, var_name);
		return result ? *result : 0;
	}
	int get_local_int(CNWSObject* object, const std::string& var_name)
	{
		return get_local_int(&object->obj_vartable, var_name);
	}
	uint32_t get_local_object(CNWSScriptVarTable* var_table, const std::string& var_name)
	{
		uint32_t* result = (uint32_t*)get_local_var(var_table, VARTYPE_OBJECT, var_name);
		return result ? *result : OBJECT_INVALID;
	}
	uint32_t get_local_object(CNWSObject* object, const std::string& var_name)
	{
		return get_local_object(&object->obj_vartable, var_name);
	}
 	const char* get_local_string(CNWSScriptVarTable* var_table, const std::string& var_name)
	{
		CExoString** result = (CExoString**)get_local_var(var_table, VARTYPE_STRING, var_name);
		return result ? (*result)->text : NULL;
	}
	const char* get_local_string(CNWSObject* object, const std::string& var_name)
	{
		return get_local_string(&object->obj_vartable, var_name);
	}
	float get_local_float(CNWSScriptVarTable* var_table, const std::string& var_name)
	{
		float* result = (float*)get_local_var(var_table, VARTYPE_FLOAT, var_name);
		return result ? *result : 0;
	}
	float get_local_float(CNWSObject* object, const std::string& var_name)
	{
		return get_local_float(&object->obj_vartable, var_name);
	}
	int (*delete_local_var)(CNWSScriptVarTable*, int) = (int (*)(CNWSScriptVarTable*, int))0x81f4584;
	void (*SetLocalInt)(CNWSScriptVarTable*, CExoString*, int, int) = (void (*)(CNWSScriptVarTable*, CExoString*, int, int))0x081f3454;
	void (*SetLocalString)(CNWSScriptVarTable*, CExoString*, CExoString*) = (void (*)(CNWSScriptVarTable*, CExoString*, CExoString*))0x081f41b4;
	void set_local_int(CNWSScriptVarTable* table, const std::string& name, int value)
	{
		CExoString exo_var_name(name.c_str());
		SetLocalInt(table, &exo_var_name, value, 0);
	}
	void set_local_string(CNWSScriptVarTable* table, const std::string& name, const std::string& value)
	{
		CExoString exo_var_name(name.c_str());
		CExoString exo_var_value(value.c_str());
		SetLocalString(table, &exo_var_name, &exo_var_value);
	}
	void delete_local_var_by_name(CNWSScriptVarTable* var_table, const std::string& var_name, uint32_t var_type)
	{
		for (uint32_t var_index=0; var_index<var_table->vt_len; var_index++)
		{
			CScriptVariable* var = &(var_table->vt_list[var_index]);
			if (var->var_type == var_type && var->var_name == var_name.c_str())
			{
				delete_local_var(var_table, var_index);
				break;
			}
		}
	}
	void delete_local_string(CNWSScriptVarTable* var_table, const std::string& var_name)
	{
		delete_local_var_by_name(var_table, var_name, VARTYPE_STRING);
	}
	void delete_local_int(CNWSScriptVarTable* var_table, const std::string& var_name)
	{
		delete_local_var_by_name(var_table, var_name, VARTYPE_INT);
	}

	int has_feat(CNWSCreatureStats* stats, uint16_t feat_id)
	{
		uint16_t* cs_feats_data = stats->cs_feats.data;
		uint16_t* cs_feats_data_last = cs_feats_data + stats->cs_feats.len;
		while (cs_feats_data < cs_feats_data_last)
		{
			if (*cs_feats_data == feat_id) return true;
			cs_feats_data++;
		}
		cs_feats_data = stats->cs_extra_feats.data;
		cs_feats_data_last = cs_feats_data + stats->cs_extra_feats.len;
		while (cs_feats_data < cs_feats_data_last)
		{
			if (*cs_feats_data == feat_id) return true;
			cs_feats_data++;
		}
		return false;
	}

	int (*CWorldTimer__GetWorldTime)(CWorldTimer *, uint32_t *, uint32_t *) =
		(int (*)(CWorldTimer *, uint32_t *, uint32_t *))0x082416a4;
	int64_t get_world_time(uint32_t* time_2880s, uint32_t* time_msec)
	{
		int64_t ret;
		uint32_t a, b;

		if (time_2880s == NULL)
			time_2880s = &a;
		if (time_msec == NULL)
			time_msec = &b;

		CWorldTimer__GetWorldTime((*p_app_manager)->app_server->srv_internal->srv_time_world, time_2880s, time_msec);

		ret = *time_2880s;

		return ((ret * 2880000LL) + *time_msec);
	}

	bool validate_filename(const std::string& filename)
	{
		const char* temp = filename.c_str();
		while (*temp)
		{
			char c = *temp;
			if (c == '/' ||
				c == '\\' ||
				c == '|' ||
				c == '<' ||
				c == '>' ||
				c == ':' ||
				c == '?' ||
				c == '*' ||
				c == '"')
			{
				return false;
			}
			temp++;
		}
		return true;
	}
	
	float get_distance_between_points(Vector p1, Vector p2)
	{
		float dx = p1.x-p2.x;
		float dy = p1.y-p2.y;
		return std::abs(std::sqrt((dx * dx) + (dy * dy)));
	}

	void init()
	{
		hook_function(0x080b1a14, (unsigned long)ServerExoAppConstructor_HookProc, d_ret_code_serverexoapp, 14);
		hook_function(0x082aeca0, (unsigned long)ExoResManConstructor_HookProc, d_ret_code_exoresman, 14);
		hook_function(0x080c6188, (unsigned long)NWRulesConstructor_HookProc, d_ret_code_nwrules, 12);
		hook_function(0x082b6238, (unsigned long)TlkTableConstructor_HookProc, d_ret_code_tlktable, 13);
		hook_function(0x081b2dd0, (unsigned long)ModuleConstructor_HookProc, d_ret_code_newmodule, 12);
		hook_function(0x0825f150, (unsigned long)VirtualMachineConstructor_HookProc, d_ret_code_newvm, 12);

		//custom game object array system
		hook_function(0x080bad30, (unsigned long)CGOA_AddObjectAtPos, d_ret_code_goa_atpos, 12);
		hook_function(0x080bae78, (unsigned long)CGOA_AddCharacterAtPos, d_ret_code_goa_charatpos, 12);
		hook_function(0x080baf5c, (unsigned long)CGOA_AddExternalObject, d_ret_code_goa_external, 12);
		hook_function(0x080bb04c, (unsigned long)CGOA_AddInternalObject, d_ret_code_goa_internal, 12);
		hook_function(0x080bb200, (unsigned long)CGOA_Delete, d_ret_code_delete, 10);
		hook_function(0x080bb21c, (unsigned long)CGOA_DeleteAndGet, d_ret_code_deleteget, 12);
		hook_function(0x080bb2cc, (unsigned long)CGOA_GetObject, d_ret_code_get, 12);
		//speed up resets
		hook_function(0x082aeeb4, (unsigned long)DestroyResMan_HookProc, d_ret_code_nouse, 12);
		//the game object array system make this function crash, i dont understand why, but its useless anyway so i bypass it*/
		hook_function(0x808892c, (unsigned long)DestroyTileset_HookProc, d_ret_code_nouse, 12);

		//misc rewrite to optimize
		hook_func(0x08153bc4, (unsigned long)has_feat, 12);

		//rewrite the original get game object ID functions for better performance
		hook_function(0x080b24b8, (unsigned long)GetPlayerByGameObjectId_HookProc, d_ret_code_nouse, 12);
		hook_function(0x080b1ed0, (unsigned long)GetPlayerIdByGameObjectId_HookProc, d_ret_code_nouse, 12);
		hook_function(0x080b1d98, (unsigned long)GetGameObjectById_HookProc, d_ret_code_nouse, 12);
		hook_function(0x080b1de0, (unsigned long)GetCreatureById_HookProc, d_ret_code_nouse, 12);
		hook_function(0x080b1dc8, (unsigned long)GetItemById_HookProc, d_ret_code_nouse, 12);
		hook_function(0x080b1e10, (unsigned long)GetAreaById_HookProc, d_ret_code_nouse, 12);
		hook_function(0x0805e8b8, (unsigned long)GetPlayerGameObject_HookProc, d_ret_code_nouse, 9);
		hook_function(0x081d5028, (unsigned long)GetArea_HookProc, d_ret_code_nouse, 12);

		//Lookup Table (trying to improve performance)
		hook_function(0x081bead4, (unsigned long)AddToLookupTable_HookProc, d_ret_code_addlookup, 11);
		hook_function(0x081bec28, (unsigned long)RemoveFromLookupTable_HookProc, d_ret_code_rmlookup, 11);
		hook_call(0x0819f108, (uint32_t)RemoveItemFromLookupTable);
		hook_call(0x081dbeae, (uint32_t)RemovePlaceableFromLookupTable);
		hook_function(0x081bee08, (unsigned long)FindObjectByTag_HookProc, d_ret_code_nouse, 12);
		hook_function(0x081bef74, (unsigned long)FindObjectByTagAndType_HookProc, d_ret_code_nouse, 11);
	}
	REGISTER_INIT(init);

	unsigned char d_ret_code_moduleloaded[0x20];
	int (*module_loaded_org)(CNWSModule*) = (int (*)(CNWSModule*))&d_ret_code_moduleloaded;
	int module_loaded_hook(CNWSModule* module)
	{
		run_hook_event(hook::module_loading);

		int ret_val = module_loaded_org(module);

		module_loaded = true;

		printf("\n");
		
		run_hook_event(hook::module_loaded);

		run_script("mod_ev_preload", 0);

		return ret_val;
	}
	
	unsigned char d_ret_code_main[0x20];
	int (*main_org)(int, const char**) = (int (*)(int, const char**))&d_ret_code_main;
	int main_hook(int argc, const char** argv)
	{
		run_hook_event(hook::init);

		return main_org(argc, argv);
	}
	
	struct SINFARX 
	{
		SINFARX()
		{
			mallopt(M_CHECK_ACTION, 1);
            srand(time(NULL));

			//custom initialization
			hook_function(0x081b87b8, (unsigned long)module_loaded_hook, d_ret_code_moduleloaded, 12);
			hook_function(0x0804B270, (unsigned long)main_hook, d_ret_code_main, 12);
		}
	};
	SINFARX sinfarx; 
}
}
