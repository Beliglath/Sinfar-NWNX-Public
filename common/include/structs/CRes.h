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

#ifndef _NX_NWN_STRUCT_CRES_
#define _NX_NWN_STRUCT_CRES_

struct CRes_s;

struct CRes_vtable
{
	void* unk_0x0;
	void* unk_0x4;
	void (*Destructor)(CRes_s*, int); //0x8
	void* GetFixedResourceSize; //0xC
	void* GetFixedResourceDataOffset; //0x10
	int (*OnResourceFreed)(CRes_s*); //0x14
	int (*OnResourceServiced)(CRes_s*); //0x18
};

struct CRes_s {
	/* 0x0/0 */ unsigned short demands;
	/* 0x2/2 */ unsigned short requests;
	/* 0x4/4 */ unsigned int id;
	long unk4;				// 0x8
	char* data;			// 0xC
	void* entry_info; // 0x10
	unsigned int size;	// 0x14
	int owner_counter;			// 0x18
	char* has_low_buffer;				// 0x1C
	char* has_high_buffer;				// 0x20
	void* list_element;		// 0x24
	CRes_vtable* vtable;	// 0x28
};

#endif /* _NX_NWN_STRUCT_CRES_ */

/* vim: set sw=4: */
