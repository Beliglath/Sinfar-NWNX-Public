#pragma once

struct CNWSCombatAttackData_s {
    char unknown[0x38];
	int is_sneak; //0x38
	uint32_t unk_0x3c;
	uint32_t unk_0x40;
	uint32_t unk_0x44;
	uint32_t unk_0x48;
	uint32_t unk_0x4c;
    uint8_t attack_roll_result; //0x50
	uint8_t uint8_t_0x51; //0x51
	uint16_t attack_feat; //0x52
	uint16_t attack_special; //0x54
	uint16_t unknown_0x56;
	uint32_t unknown_0x58;
	uint32_t unknown_0x5c;
	uint32_t unknown_0x60;
	uint32_t attack_projectile; //0x64
	char unk_0x68[0x10];
	CExoArrayList<void*> attack_effects; //0x78
	CExoArrayList<void*> attack_spellscriptdata1; //0x84
	CExoArrayList<void*> attack_spellscriptdata2; //0x90
	CExoArrayList<void*> attack_messages; //0x9c
};
