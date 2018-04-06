#include "player.h"
#include "BNMessage.h"
#include <regex>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace nwnx::core;

namespace nwnx { namespace player {

const uint16_t ee_server_version = 8166;

PlayerInfo* get_player_info(uint32_t player_id)
{
	if (player_id < 0x60)
	{
		return &server_internal->srv_network->net_internal->players_info[player_id];
	}
	return NULL;
}
PlayerInfo* get_player_info(CNWSPlayer* player)
{
	if (server_internal->srv_network)
	{
		return get_player_info(player->pl_id);
	}
	return NULL;
}

PlayerExtraInfo::PlayerExtraInfo()
{
	reset();
}
void PlayerExtraInfo::reset()
{
	game_version = 0;
}
PlayerExtraInfo players_extra_info[0x60];

void (*SetCDKeyArrayListSize)(CExoArrayList<CNetLayerPlayerCDKeyInfo>*, uint32_t) = (void (*)(CExoArrayList<CNetLayerPlayerCDKeyInfo>*, uint32_t))0x82ACED8;
void reset_player_info(CNetLayerInternal* net_layer_internal, uint32_t player_id)
{
	players_extra_info[player_id].reset();
	PlayerInfo* player_info = &net_layer_internal->players_info[player_id];
	player_info->is_connected = 0;
	player_info->name = NULL;
	player_info->language = 0;
	player_info->player_id = -1;
	player_info->is_player = 0;
	player_info->is_dm = 0;
	player_info->is_sysadmin = 0;
	player_info->unk_0x20 = NULL;
	player_info->unk_0x28 = 0;
	player_info->unk_0x2c = 0;
	player_info->unk_0x30 = 0;
	player_info->unk_0x34 = 0;
	player_info->challenge1 = NULL;
	player_info->challenge2 = NULL;
	player_info->challenge3 = NULL;
	player_info->connection_type = 0;
	player_info->localmode = 0;
	SetCDKeyArrayListSize(&player_info->cdkeys, 0);
	player_info->unk_0x64 = NULL;
	player_info->unk_0x6c = 0;
	player_info->unk_0x70 = 0;
	player_info->expansion_pack = 0;
}

void (*PlayerListChange)(CServerExoAppInternal*, uint32_t, int, int) = (void (*)(CServerExoAppInternal*, uint32_t, int, int))0x080a1d18;
void (*ShutdownNetLayerWindow)(CNetLayerWindow*) = (void (*)(CNetLayerWindow*))0x829E4CC;
void (*SendBNDPMessage)(CNetLayerInternal*, uint32_t, uint32_t) = (void (*)(CNetLayerInternal*, uint32_t, uint32_t))0x082aa1f4;
int disconnect_player(CNetLayerInternal* net_layer_internal, uint32_t player_id, uint32_t str_resref, bool send_bndp)
{
	if (player_id >= 0x60) return 0;
	PlayerListChange(server_internal, player_id, 0, 0);
	if (send_bndp) SendBNDPMessage(net_layer_internal, player_id, str_resref);
	ShutdownNetLayerWindow(&net_layer_internal->net_layer_windows[player_id]);
	reset_player_info(net_layer_internal, player_id);
	return 1;
}
int DisconnectPlayer_HookProc(CNetLayerInternal* net_layer_internal, uint32_t player_id, uint32_t str_resref, int send_bndp, int p5)
{
	return disconnect_player(net_layer_internal, player_id, str_resref, send_bndp);
}

bool is_player_name_valid(const std::string& player_name)
{
	uint32_t player_name_len = player_name.length();
	if (player_name_len < 1 || player_name_len > 64)
	{
		return false;
	}
	if (player_name == "." || player_name == "..")
	{
		return false;
	}
	const char* player_name_c_str = player_name.c_str();
	for (uint32_t i=0; i<player_name_len; i++)
	{
		char c = player_name_c_str[i];
		if (c == '/' ||
			c == '\\' ||
			c == '|' ||
			c == '<' ||
			c == '>' ||
			c == ':' ||
			c == '?' ||
			c == '*' ||
			c == '~' ||
			c == '"')
		{
			return false;
		}
	}	
	return true;
}
bool validate_player_name(std::string& player_name)
{
	return true;
}
bool is_player_name_banned(const std::string& player_name)
{
	return false;
}
std::regex cdkey_regex = std::regex("^[A-Z0-9]{8}$", std::regex_constants::extended);
bool is_cdkey_valid(const std::string& player_name, const std::string& cdkey)
{
	if (cdkey.length() != 8 || !std::regex_match(cdkey, cdkey_regex, std::regex_constants::match_any))
	{
		fprintf(stderr, "Connection refused (%s) for using a bad CDKey (%s)\n", player_name.c_str(), cdkey.c_str());
		return false;
	}
	return true;
}
bool is_cdkey_banned(const std::string& player_name, const std::string& cdkey)
{
	return false;
}
bool is_ip_address_banned(const std::string& player_name, const std::string& ip_address)
{
	return false;
}
bool is_player_login_authorized(const std::string& player_name, const std::string& cdkey)
{
	return true;
}
int (*GetPlayerAddressData)(CNetLayerInternal*, uint32_t, uint32_t*, uint32_t**, uint32_t**, uint32_t*) = (int (*)(CNetLayerInternal*, uint32_t, uint32_t*, uint32_t**, uint32_t**, uint32_t*))0x082ac0cc;
uint32_t (*SetNetworkAddressData)(CNetLayerInternal*, uint32_t, uint32_t*, uint32_t*, uint32_t) = (uint32_t (*)(CNetLayerInternal*, uint32_t, uint32_t*, uint32_t*, uint32_t))0x082AC178;
int assign_connection_addr_id(CNetLayerInternal* net_layer_internal, uint32_t connection_id)
{
	uint32_t ip;
	uint32_t port;
	uint32_t addr_data1[4];
	uint32_t* p_addr_data1 = &addr_data1[0];
	uint32_t addr_data2[4];
	uint32_t* p_addr_data2 = &addr_data2[0];
	GetPlayerAddressData(net_layer_internal, connection_id, &ip, &p_addr_data1, &p_addr_data2, &port);
	int result = SetNetworkAddressData(net_layer_internal, ip, p_addr_data1, p_addr_data2, port);
	if (result == -1)
	{
		fprintf(stderr, "failed to SetNetworkAddressData: %x:%d\n", ip, port);
	}
	return result;
}

uint32_t player_id_by_connection_id(CNetLayerInternal* net_layer_internal, uint32_t connection_id)
{
	for (uint32_t player_id = 0; player_id<0x60; player_id++)
	{
		if (net_layer_internal->net_layer_windows[player_id].connection_id == connection_id)
		{
			return player_id;
		}
	}
	return -1;
}

int (*SendBNVRMessage)(CNetLayerInternal*, uint32_t, uint8_t) = (int (*)(CNetLayerInternal*, uint32_t, uint8_t))0x082a673c;
void (*SetPlayerConnected)(CNetLayerInternal*, uint32_t) = (void (*)(CNetLayerInternal*, uint32_t))0x082a9d88;
int (*EncryptString)(char**, uint32_t*, CExoString*) = (int (*)(char**, uint32_t*, CExoString*))0x082C91D4;
std::string encrypt_string(const std::string& str)
{
	CExoString result;
	CExoString exo_str = str;
	EncryptString(&result.text, &result.len, &exo_str);
	return result;
}
int HandleBNVSMessage_HookProc(CNetLayerInternal* net_layer_internal, uint32_t connection_id, uint8_t* data, uint32_t data_len)
{	
	CBNMessage bnmsg(data, data_len);
	uint8_t msg_unk1 = bnmsg.read_byte();
	if (msg_unk1 != 'V' && msg_unk1 != 'P')
	{
		fprintf(stderr, "msg_unk1 = %d\n", msg_unk1);
	}
	uint8_t msg_unk2 = bnmsg.read_byte();
	if (msg_unk2 != 3 && msg_unk2 != 1)
	{
		fprintf(stderr, "msg_unk2 = %d\n", msg_unk2);
	}
	std::string msg_cdkey1 = bnmsg.read_string();
	std::string msg_cdkey2 = bnmsg.read_string();
	std::string msg_cdkey3 = bnmsg.read_string();
	std::string msg_unk3 = bnmsg.read_string();
	std::string msg_password = bnmsg.read_string();
	
	uint32_t player_id = player_id_by_connection_id(net_layer_internal, connection_id);
	if (player_id < 0x60)
	{
		CNetLayerWindow* net_layer_window = &net_layer_internal->net_layer_windows[player_id];
		PlayerInfo* player_info = get_player_info(player_id);
		uint32_t response = 0;
		if ((player_info->connection_type & 0x20) && 
			msg_password != encrypt_string(net_layer_internal->dm_password.to_str()+player_info->challenge1.to_str()))
		{
			response = 3; //CNetLayer::CONNECT_ERR_PASSWORD_INCORRECT
		}
		else if (!(player_info->connection_type & 0x20) &&
				net_layer_internal->player_password.text && 
				*net_layer_internal->player_password.text &&
				msg_password != encrypt_string(net_layer_internal->player_password.to_str()+player_info->challenge1.to_str()))
		{
			response = 3; //CNetLayer::CONNECT_ERR_PASSWORD_INCORRECT
		}
		else
		{
			response = 0;
		}
		SendBNVRMessage(net_layer_internal, net_layer_window->addr_id, response);
		if (response == 0)
		{
			SetPlayerConnected(net_layer_internal, player_id);
		}
	}
	else
	{
		int addr_id = assign_connection_addr_id(net_layer_internal, connection_id);
		if (addr_id == -1) return 0;
		SendBNVRMessage(net_layer_internal, addr_id, 0x11/* master server not responding */);
	}
	return 1;
}

void (*AddPlayerInfoCDKey)(PlayerInfo*, const CExoString&, const CExoString&) = (void (*)(PlayerInfo*, const CExoString&, const CExoString&))0x0829fb8c;
int (*SetSlidingWindow)(CNetLayerInternal*, uint32_t, uint32_t, uint32_t*) = (int (*)(CNetLayerInternal*, uint32_t, uint32_t, uint32_t*))0x082a177c;
int (*SendBNCRMessage)(CNetLayerInternal*, uint32_t, uint8_t, uint32_t) = (int (*)(CNetLayerInternal*, uint32_t, uint8_t, uint32_t))0x082A3208;
int HandleBNCSMessage_HookProc(CNetLayerInternal* net_layer_internal, uint32_t connection_id, uint8_t* data, uint32_t data_len)
{
	uint32_t already_connected_player_id = player_id_by_connection_id(net_layer_internal, connection_id);
	if (already_connected_player_id < 0x60)
	{
		disconnect_player(net_layer_internal, already_connected_player_id, 0, false);
	}
	
	int addr_id = assign_connection_addr_id(net_layer_internal, connection_id);
	if (addr_id == -1) return 0;
	
	std::string ip = inet_ntoa(((struct sockaddr_in*)net_layer_internal->exo_net->exo_net_internal->addr_info)[addr_id].sin_addr);
	
	CBNMessage bnmsg(data, data_len);
	/*uint16_t msg_port = */bnmsg.read_word();
	uint8_t msg_connecttype = bnmsg.read_byte();
	uint32_t msg_version = bnmsg.read_dword();
	uint16_t msg_exppack = bnmsg.read_word();
	uint8_t msg_lang = bnmsg.read_byte();
	/*uint32_t msg_tickcount = */bnmsg.read_dword();
	std::string msg_account = bnmsg.read_string();
	std::string msg_cdkey = bnmsg.read_string();

	uint32_t response = 0;
		
	CExoLinkedListNode* player_list_node = server_internal->srv_client_list_1->header->first;
	while (player_list_node)
	{
		CNWSPlayer* player = (CNWSPlayer*)player_list_node->data;
		if (net_layer_internal->players_info[player->pl_id].name == msg_account)
		{
			response = 6; //CNetLayer::CONNECT_ERR_PLAYER_NAME_IN_USE
			break;
		}
		player_list_node = player_list_node->next;
	}
	
	if (msg_version != 8109 && msg_version != ee_server_version)
	{
		response = 2; //CNetLayer::CONNECT_ERR_SERVER_VERSIONMISMATCH
	}
	/*else if (msg_exppack < 3)
	{
		response = 11; //CNetLayer::CONNECT_ERR_EXPANSION_PACK_WRONG 
	}*/
	else if (msg_connecttype != 0x10 /*CNetLayer::CONNECTTYPE_PLAYER*/ && 
		msg_connecttype != 0x20 /*CNetLayer::CONNECTTYPE_GAMEMASTER*/)
	{
		response = 14; //CNetLayer::CONNECT_ERR_ADMIN_CONNECTION_REFUSED
	}
	else if (!is_player_name_valid(msg_account) || !validate_player_name(msg_account))
	{
		response = 8; //CNetLayer::CONNECT_ERR_PLAYER_NAME_REFUSED
	}
	else if (is_player_name_banned(msg_account))
	{
		response = 10; //CNetLayer::CONNECT_ERR_BANNED
	}
	else if (!is_cdkey_valid(msg_account, msg_cdkey))
	{
		response = 12; //CNetLayer::CONNECT_ERR_CDKEY_UNAUTHORIZED
	}
	else if (is_cdkey_banned(msg_account, msg_cdkey))
	{
		response = 10; //CNetLayer::CONNECT_ERR_BANNED		
	}
	else if (is_ip_address_banned(msg_account, ip))
	{
		response = 10; //CNetLayer::CONNECT_ERR_BANNED			
	}
	else if (!is_player_login_authorized(msg_account, msg_cdkey))
	{
		response = 17; //CNetLayer::CONNECT_ERR_LOGIN_DENIED_MASTERSERVER_NOT_RESPONDING
	}
	
	if (response == 0)
	{
		uint32_t player_id = 0;
		if (SetSlidingWindow(net_layer_internal, addr_id, connection_id, &player_id))
		{
			PlayerExtraInfo* player_extra_info = &players_extra_info[player_id];
			player_extra_info->game_version = msg_version;
			PlayerInfo* player_info = &net_layer_internal->players_info[player_id];
			player_info->is_connected = 1;
			player_info->language = msg_lang;
			player_info->name = msg_account;
			player_info->player_id = player_id;
			player_info->expansion_pack = msg_exppack;
			player_info->connection_type = msg_connecttype;
			AddPlayerInfoCDKey(player_info, msg_cdkey, "");
			SendBNCRMessage(net_layer_internal, addr_id, 0, player_id);
			return 1;
		}
		else
		{
			response = 5; //server full
		}
	}
	if (response != 0)
	{
		SendBNCRMessage(net_layer_internal, addr_id, response, 0);
	}
	return 1;
}

void init()
{
	hook_function(0x082a4a54, (long)HandleBNVSMessage_HookProc, d_ret_code_nouse, 12);
	hook_function(0x082a1e38, (long)HandleBNCSMessage_HookProc, d_ret_code_nouse, 12);
}
REGISTER_INIT(init);

}
}
