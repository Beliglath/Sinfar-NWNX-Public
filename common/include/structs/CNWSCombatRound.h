/*
 *  NWNeXalt - Empty File
 *  (c) 2007 Doug Swarin (zac@intertex.net)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  $Id$
 *  $HeadURL$
 *
 */

#ifndef _NX_NWN_STRUCT_CNWSCOMBATROUND_
#define _NX_NWN_STRUCT_CNWSCOMBATROUND_

struct CNWSCombatRound_s {
    char unk_0x0[0x2114];
    uint8_t combat_current_attack; //0x2114
	uint8_t unk_0x2115;
	uint16_t unk_0x2116;
	char unk_0x2118[0x1c];
	uint32_t next_target_id; //0x2134
	char unk_0x2138[0x24];
	CNWSCreature* creature; //0x215c
};

#endif /* _NX_NWN_STRUCT_CNWSCOMBATROUND_ */

/* vim: set sw=4: */
