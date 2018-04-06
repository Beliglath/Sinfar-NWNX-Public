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

#ifndef _NX_NWN_STRUCT_CNWSSTORE_
#define _NX_NWN_STRUCT_CNWSSTORE_

struct CNWSStore_s {
    CNWSObject                  obj;
    uint32_t                    field_1C4;
    uint32_t                    field_1C8;
    uint32_t                    field_1CC;
    uint32_t                    field_1D0;
    CItemRepository*            st_page_1;
    CItemRepository*            st_page_2;
    CItemRepository*            st_page_3;
    CItemRepository*            st_page_4;
    CItemRepository*            st_page_5;
    uint32_t                    field_1E8;
    uint32_t                    field_1EC;
    uint32_t                    field_1F0;
    uint32_t                    field_1F4;
    uint32_t                    field_1F8;              /* 01F8 */
    uint32_t                    field_1FC;              /* 01FC */
    uint32_t                    field_200;              /* 0200 */
    uint32_t                    st_buy_stolen;          /* 0204 */
    uint32_t                    st_buy_stolen_mark_down;/* 0208 */
    uint32_t                    st_buy_mark_down;       /* 020C */
    uint32_t                    st_sell_mark_up;       	/* 0210 */
	uint32_t                    field_214; 
	uint32_t                    field_218; 
	uint32_t                    field_21C; 
	uint32_t                    field_220; 
	uint32_t                    field_224; 
	uint32_t                    field_228; 
	uint32_t                    field_22C; 
	uint32_t                    field_230; 
	uint32_t                    field_234; 
	uint32_t                    field_238; 
};

#endif /* _NX_NWN_STRUCT_CNWSSTORE_ */

/* vim: set sw=4: */
