#pragma once

#include <vector>
#include <functional>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <deque>
#include "include/NWNXLib.h"

#include <execinfo.h>

#ifndef PAGESIZE
#define PAGESIZE 4096
#endif

namespace nwnx
{
namespace core
{
    inline void print_backtrace()
    {
        void* stack[20];
        memset(&stack, 0, sizeof(stack));
        int stack_size = backtrace(stack, 20);
        char** str = backtrace_symbols(stack, stack_size);
        for (int i = 0; i < stack_size; i++)
                fprintf(stderr, "    %s\n", str[i]);
        free(str);
    }
    
	namespace hook
	{
		enum type
		{
			init,
			module_loading,
			module_loaded,
			ai_update,
			shutdown_server,
		};
	}
	typedef std::function<void()> HOOK;
	typedef std::vector<HOOK> HOOKS;
	HOOKS& get_hooks(hook::type h);
	void run_hook_event(hook::type event);
	void register_hook(hook::type h, std::function<void()> HOOK);
	struct REGISTERED_HOOK
	{
		REGISTERED_HOOK(hook::type h, std::function<void()> HOOK);
	};
	#define REGISTER_INIT(func) nwnx::core::REGISTERED_HOOK registered_hook_##FILE##LINE(nwnx::core::hook::init, func)
	
	extern CVirtualMachine* virtual_machine;
	extern CNWRules* nwn_rules;
	extern CExoBase** p_exo_base;
	extern CAppManager** p_app_manager;
	extern CServerExoAppInternal* server_internal;
	extern CExoResMan* resman;
	extern CNWSModule* module;
	extern CTlkTable* talk_table;

	extern bool module_loaded;

	void enable_write(unsigned long location);
	void hook_call(uint32_t from_addr, uint32_t to_func);
	void hook_function(long from, long to, unsigned char *d_ret_code, long len);
	void hook_func(long from, long to, void*& from_org, long len);
	int run_script(CExoString* sname, int objid, int p3);
	int run_script(const CExoString& sname, int objid, int p3);
	int run_script(const std::string& sname, int objid);

	int CGOA_GetObject(void* array, uint32_t object_id, CGameObject** p_o);
	int CGOA_AddInternalObject(void* array, uint32_t* p_object_id, CGameObject* o, int isChar);
	int CGOA_Delete(void *array, uint32_t object_id);
	CNWSPlayer* GetClientByGameObjectId_Unique_Hook(CServerExoApp* server, uint32_t object_id);
	CNWSPlayer* get_player_by_id(uint32_t pl_id);
	CNWSPlayer* get_player_by_game_object_id(uint32_t object_id);
	int64_t get_world_time(uint32_t* time_2880s, uint32_t* time_msec);

	extern unsigned char d_ret_code_nouse[0x20];
	extern int current_server_id;
	extern const int sinfar_vault_id;

	extern std::unordered_map<uint32_t, CGameObject*> cgoa;
	extern std::unordered_map<uint32_t, CGameObject*>::iterator cgoa_iter;
	CGameObject* GetGameObject(uint32_t object_id);
	CNWSObject* GetObjectById(uint32_t object_id);
	CNWSStore* GetStoreById(uint32_t object_id);
	CNWSItem* GetItemById(uint32_t object_id);
	CNWSCreature* GetCreatureById(uint32_t object_id);
	CNWSArea* GetAreaById(uint32_t object_id);
	CNWSDoor* GetDoorById(uint32_t object_id);
	CNWSTrigger* GetTriggerById(uint32_t object_id);
	CNWSAreaOfEffectObject* GetAreaOfEffectObjectById(uint32_t object_id);
	CNWSPlaceable* GetPlaceableById(uint32_t object_id);
	CNWSModule* get_module();

	extern int (*SendServerToPlayerMessage)(CNWSMessage*, uint32_t, uint8_t, uint8_t, char*, uint32_t);
	extern int (*GetWriteMessage)(CNWSMessage*, char**, uint32_t*);
	extern void (*CreateWriteMessage)(CNWSMessage*, uint32_t, uint32_t, int);
	extern void (*WriteInt)(CNWMessage*, int, int);
	extern void (*WriteFloat)(CNWMessage*, float, float, int);
	extern void (*WriteCExoString)(CNWMessage*, CExoString, int);
	extern void (*WriteCExoLocString)(CNWSMessage*, CExoLocString*, uint8_t);
	extern void (*WriteChar)(CNWSMessage*, char, int);
	extern void (*WriteObjectId)(CNWSMessage*, uint32_t);
	extern void (*WriteBool)(CNWSMessage*, bool);
	extern void (*WriteWord)(CNWMessage*, uint16_t, int);
	extern void (*WriteDWORD)(CNWSMessage*, uint32_t, int);
	extern void (*WriteResRef)(CNWMessage*, CResRef, int);
	extern void (*WriteByte)(CNWMessage*, uint8_t, int);
	extern int (*ReadMessageOverflow)(CNWSMessage*, int);
	extern int (*ReadMessageUnderflow)(CNWSMessage*, int);
	extern float (*ReadFloat)(CNWSMessage*, float, int);
	extern CExoString (*ReadExoString)(CNWSMessage*, int);
	extern int (*ReadInt)(CNWSMessage*, int);
	extern uint32_t (*ReadObjectId)(CNWSMessage*);
	extern void (*CExoLocString_Constructor)(CExoLocString*);
	extern void (*CExoLocString_Destructor)(CExoLocString*, int);
    
    extern void (*AddActionToFront)(CNWSObject*, uint32_t, uint16_t, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*,
        uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*);
    extern void (*AddAction)(CNWSObject*, uint32_t, uint16_t, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*,
        uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*, uint32_t, void*);

	extern void (*AddLocString)(CExoLocString*, int, CExoString, uint8_t);
	extern void (*ClearLocString)(CExoLocString*);
	extern int (*GetLevel)(CNWSCreatureStats*, int);
    extern CNWSCombatAttackData* (*GetAttack)(CNWSCombatRound*, int);

	std::string get_string_by_str_ref(uint32_t strref);
	const char* get_first_loc_string(CExoLocString& loc_string);
	std::string get_creature_final_name(CNWSCreature* creature);

    CNWBaseItem* get_base_item(int baseitem);
	CNWSMessage* get_nws_message();
	CNWSItem* get_item_in_slot(CNWSInventory* inventory, uint32_t slot_flag);

	extern void (*CNWSItem_Destructor)(CNWSItem*, int);

	extern std::unordered_map<std::string, std::deque<uint32_t>> tags_map;
	bool safe_add_to_tags_map(const std::string& tag, uint32_t object_id);
	void remove_object_from_tags_map(const std::string& tag, uint32_t object_id);
	uint32_t find_object_by_tag(const std::string& tag, uint32_t index);

	int has_feat(CNWSCreatureStats* stats, uint16_t feat_id);

	CNWSScriptVarTable* GetGameObjectVarTable(CGameObject* o);
	int get_local_int(CNWSScriptVarTable* var_table, const std::string& var_name);
	int get_local_int(CNWSObject* object, const std::string& var_name);
	uint32_t get_local_object(CNWSScriptVarTable* var_table, const std::string& var_name);
	uint32_t get_local_object(CNWSObject* object, const std::string& var_name);
	const char* get_local_string(CNWSScriptVarTable* var_table, const std::string& var_name);
	const char* get_local_string(CNWSObject* object, const std::string& var_name);
	float get_local_float(CNWSScriptVarTable* var_table, const std::string& var_name);
	float get_local_float(CNWSObject* object, const std::string& var_name);
	void set_local_int(CNWSScriptVarTable* table, const std::string& name, int value);
	void set_local_string(CNWSScriptVarTable* table, const std::string& name, const std::string& value);
	void delete_local_string(CNWSScriptVarTable* var_table, const std::string& var_name);
	void delete_local_int(CNWSScriptVarTable* var_table, const std::string& var_name);
	extern int (*delete_local_var)(CNWSScriptVarTable*, int);

	bool validate_filename(const std::string& filename);
	float get_distance_between_points(Vector p1, Vector p2);
}
}
