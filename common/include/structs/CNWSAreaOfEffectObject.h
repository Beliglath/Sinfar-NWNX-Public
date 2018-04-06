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

#ifndef _NX_NWN_STRUCT_CNWSAREAOFEFFECTOBJECT_
#define _NX_NWN_STRUCT_CNWSAREAOFEFFECTOBJECT_

struct CNWSAreaOfEffectObject_s {
    CNWSObject                  obj;
	uint16_t                    field_1C6;
	uint16_t                    field_1C8;
    uint16_t                    field_1CA;
    uint32_t                    field_1CC;
    uint32_t                    aoe_spell_id;
    uint32_t                    field_1D4;
    uint32_t                    field_1D8;
    uint32_t                    field_1DC;
    uint32_t                    field_1E0;
    uint32_t                    field_1E4;
    uint32_t                    aoe_owner_id; //1e8
    uint32_t                    field_1EC;
    uint32_t                    field_1F0;
    uint32_t                    field_1F4;
    uint32_t                    aoe_spell_level; //1f8
};

#endif /* _NX_NWN_STRUCT_CNWSAREAOFEFFECTOBJECT_ */

/* vim: set sw=4: */
