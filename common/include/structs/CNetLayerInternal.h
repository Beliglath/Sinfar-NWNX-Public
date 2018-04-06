#pragma once

struct CNetLayerPlayerCDKeyInfo
{
	CExoString public_part;
	CExoString encoded;
};

struct PlayerInfo
{
	int is_connected;
	CExoString name; //0x4
	int language;
	int player_id; //0x10
	int is_player; //0x14
	int is_dm; //0x18
	int is_sysadmin; //0x1c
	CExoString unk_0x20;
	int unk_0x28;
	int unk_0x2c;
	int unk_0x30;
	int unk_0x34;
	CExoString challenge1;
	CExoString challenge2;
	CExoString challenge3;
	int connection_type;
	int localmode;
	CExoArrayList<CNetLayerPlayerCDKeyInfo> cdkeys; //0x58
	CExoString unk_0x64;
	int unk_0x6c;
	int unk_0x70;
	int expansion_pack;
};

struct CExoNetInternal_s
{
	uint32_t            field_00;
	uint32_t            field_04;
	int socket; //0x8
	char unk_0xc[0x30];
	void* addr_info; //0x3c
};

struct CExoNet_s
{
	CExoNetInternal* exo_net_internal;
};

struct CNetLayerWindow
{
	uint32_t unk_0x0;
	uint32_t unk_0x4;
	uint32_t unk_0x8;
	uint32_t unk_0xc;
	uint32_t connection_id; //0x10
	int addr_id; //0x14
	uint32_t unk_0x18;
	char unk_0x1c[0x900];
};

struct CNetLayerInternal_s {
    void* unknown;
	CExoNet* exo_net; //0x4
	uint32_t unk_0x8;
	CNetLayerWindow net_layer_windows[0x60];
	PlayerInfo players_info[0x60]; //0x36A8C
	char unk_0x3978C[0x407D0]; //0x3978C
	CExoString player_password; //0x79F5C
	CExoString dm_password; //0x79F64
};
