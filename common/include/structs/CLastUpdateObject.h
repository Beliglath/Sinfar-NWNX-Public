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

#ifndef _NX_NWN_STRUCT_CLASTUPDATEOBJECT_
#define _NX_NWN_STRUCT_CLASTUPDATEOBJECT_

struct CLastUpdateObject_s {
    uint32_t            field_00;
    uint32_t            field_04;
    uint32_t            field_08;
    uint32_t     		field_0C;
    uint32_t            field_10;
    uint16_t            appearance;
	uint8_t             phenotype;
	uint8_t             field_17;
    uint32_t            field_18;
    uint32_t            field_1C;
    uint32_t            field_20;
    uint32_t            field_24;
    uint32_t            field_28;
    uint32_t            field_2C;
    uint32_t            field_30;
    uint32_t            field_34;
    uint32_t            field_38;
    uint32_t            field_3C;
    uint32_t            field_40;
    uint8_t             object_type;
    uint8_t             field_45;
    uint16_t            field_46;
    uint32_t            foot_step; //0x48
    uint32_t            object_id; //0x4c
	char				unk_0x50[0x5c];
	CExoLocString		firstname; //0xac
	CExoLocString		lastname; //0xb4
    uint32_t            field_bc;
    uint32_t            field_c0;
	CExoArrayList<void*> visuals; //0xC4
	char				unk_0xD0[0xa0];
};

#endif /* _NX_NWN_STRUCT_CLASTUPDATEOBJECT_ */

/* vim: set sw=4: */
