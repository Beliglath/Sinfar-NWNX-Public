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

#ifndef _NX_NWN_STRUCT_CRESREF_
#define _NX_NWN_STRUCT_CRESREF_

class CResRef {
public:
	CResRef(const char* value)
	{
		if (value)
		{
			for (int i=0; i<16; i++)
			{
				if (value[i])
				{
					this->value[i] = tolower(value[i]);
				}
				else
				{
					this->value[i] = 0;
					break;
				}
			}
		}
		else
		{
			memset(this->value, 0, 16);
		}
	}
	CResRef()
	{
		memset(this->value, 0, 16);
	}
	std::string to_str()
	{
		char str_value[17];
		strncpy(str_value, value, 16);
		str_value[16] = 0;
		return str_value;
	}
	char value[16];
};

#endif /* _NX_NWN_STRUCT_CRESREF_ */

/* vim: set sw=4: */
