#pragma once

#include "core.h"

#include <map>
#include <vector>

namespace nwnx { namespace player {
	
extern const uint16_t ee_server_version;

struct PlayerExtraInfo
{
	PlayerExtraInfo();
	void reset();
	uint32_t game_version;
};
extern PlayerExtraInfo players_extra_info[0x60];

PlayerInfo* get_player_info(uint32_t player_id);
PlayerInfo* get_player_info(CNWSPlayer* player);

}
}
