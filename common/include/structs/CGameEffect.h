#pragma once

struct CGameEffect_EXTRA
{
	std::string xdata;
	std::string tag;
};

struct CGameEffect_s {

	CGameEffect_s() = delete; 
	CGameEffect_s(int unk)
	{
		((void (*)(CGameEffect_s*, int))0x0817DC70)(this, unk);
		this->extra = NULL;
		
	}
	~CGameEffect_s()
	{
		((void (*)(CGameEffect_s*, int))0x0817dfdc)(this, 2);
	}
	
    uint32_t            eff_id;                 /* 00 */

    uint32_t            eff_id_part2;           /* 04 */

    uint16_t            eff_type;               /* 08 */
    uint16_t            eff_dursubtype;         /* 0A */

    float               eff_duration;           /* 0C */

    uint32_t            eff_expire_day;         /* 10 */
    uint32_t            eff_expire_time;        /* 14 */

    nwn_objid_t         eff_creator;            /* 18 */
    int32_t             eff_spellid;            /* 1C */

    uint32_t            eff_is_exposed;         /* 20 */
    uint32_t            eff_is_iconshown;       /* 24 */

    uint32_t            eff_caster_level;       /* 28 */

    uint32_t            eff_link_id1;           /* 2C */
    uint32_t            eff_link_id2;           /* 30 */

    uint32_t            eff_num_integers;       /* 34 */
    int32_t            *eff_integers;           /* 38 */

    float               eff_floats[4];          /* 3C */
    CExoString_s eff_strings[6];         		/* 4c */
    nwn_objid_t         eff_objects[4];         /* 7c */

    uint32_t            eff_skiponload;         /* 9c */
	
	CGameEffect_EXTRA* extra; //0x90
};

#ifndef __x86_64__
static_assert(sizeof(CGameEffect_s) == 0x94, "CGameEffect_s size is bad");
#endif
