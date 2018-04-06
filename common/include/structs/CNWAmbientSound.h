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

#ifndef _NX_NWN_STRUCT_CNWAMBIENTSOUND_
#define _NX_NWN_STRUCT_CNWAMBIENTSOUND_

struct CNWAmbientSound_s {
    void               *unknown;

    uint32_t            enabled;

    uint32_t            music_delay;
    uint32_t            music_day;
    uint32_t            music_night;
    uint32_t            field_10;
    uint32_t            music_battle;
    uint32_t            field_18;

    uint32_t            ambient_day;
    uint32_t            ambient_night;
    uint8_t             ambient_day_volume;
    uint8_t             ambient_night_volume;

    uint8_t             field_26;
    uint8_t             field_27;
};

#endif /* _NX_NWN_STRUCT_CNWAMBIENTSOUND_ */

/* vim: set sw=4: */
