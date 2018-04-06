#pragma once

#include "CResRef.h"

struct CNWSCreatureStats_s {
    CExoArrayList<uint16_t>     cs_feats;               /* 0000 */
    CExoArrayList<void*>        cs_featuses;            /* 000C */         /* CNWSStats_FeatUses * */

    CExoArrayList<uint16_t>     cs_extra_feats;         /* 0000 */

    CNWSCreature               *cs_original;            /* 0024 */

    CExoArrayList<void*>        cs_levelstat;           /* 0028 */         /* CNWSStats_Level * */

    CExoLocString               cs_firstname;           /* 0034 */
    CExoLocString               cs_lastname;            /* 003C */

    CResRef                     cs_conv;            /* 0044 */
    uint32_t                    cs_conv_interruptable;  /* 0054 */

    CExoLocString               cs_desc_base;           /* 0058 */
    CExoLocString               cs_desc_override;       /* 0060 */

    int32_t                     cs_age;                 /* 0068 */
    uint32_t                    cs_gender;              /* 006C */
    uint32_t                    cs_xp;                  /* 0070 */
    uint32_t                    cs_is_pc;               /* 0074 */
    uint32_t                    cs_is_dm;               /* 0078 */

    uint32_t                    field_7C;
    uint32_t                    field_80;

    uint32_t                    cs_ai_disabled;         /* 0084 */

    uint32_t                    cs_dm_invisble;
    uint32_t                    cs_mclasslevupin;       /* 008C */

    uint32_t                    cs_faction_id;          /* 0090 */
    uint32_t                    cs_faction_orig;        /* 0094 */
    uint32_t                    cs_faction_predom;      /* 0098 */

    float                       cs_cr;                  /* 009C */

    uint8_t                     cs_starting_package;    /* 00A0 */
    uint8_t                     cs_classes_len;         /* 00A1 */
    uint8_t                     field_9A;
    uint8_t                     field_9B;

    CNWSCreatureClass           cs_classes[3];          /* 00A4 */

    uint16_t                    cs_race;                /* 03EC */
    uint16_t                    field_3EE;
    CExoString                  cs_subrace;             /* 03F0 */

    uint8_t                     cs_str;                 /* 03F8 */
    int8_t                      cs_str_mod;             /* 03F9 */
    uint8_t                     cs_dex;                 /* 03FA */
    int8_t                      cs_dex_mod;             /* 03FB */
    uint8_t                     cs_con;                 /* 03FC */
    int8_t                      cs_con_mod;             /* 03FD */
    uint8_t                     cs_int;                 /* 03FE */
    int8_t                      cs_int_mod;             /* 03FF */
    uint8_t                     cs_wis;                 /* 0400 */
    int8_t                      cs_wis_mod;             /* 0401 */
    uint8_t                     cs_cha;                 /* 0402 */
    int8_t                      cs_cha_mod;             /* 0403 */

    uint8_t                     cs_ac_natural_base;     /* 0404 */
    uint8_t                     cs_ac_armour_base;      /* 0405 */
    uint8_t                     cs_ac_shield_base;      /* 0406 */
    uint8_t                     cs_ac_armour_bonus;     /* 0407 */
    uint8_t                     cs_ac_armour_penalty;   /* 0408 */
    uint8_t                     cs_ac_deflection_bonus; /* 0409 */
    uint8_t                     cs_ac_deflection_penalty;
    uint8_t                     cs_ac_shield_bonus;     /* 040B */
    uint8_t                     cs_ac_shield_penalty;   /* 040C */
    uint8_t                     cs_ac_natural_bonus;    /* 040D */
    uint8_t                     cs_ac_natural_penalty;  /* 040E */
    uint8_t                     cs_ac_dodge_bonus;      /* 040F */
    uint8_t                     cs_ac_dodge_penalty;    /* 0410 */

    uint8_t                     cs_override_bab;        /* 0411 */

    uint8_t                     field_40A;
    uint8_t                     field_40B;
    uint32_t                    field_40C;
    uint32_t                    field_410;
    uint32_t                    field_414;
    uint32_t                    field_418;
    uint32_t                    field_41C;

    CCombatInformation         *cs_combat_info;         /* 0428 */

    uint32_t                    field_424;
    uint32_t                    field_428;
    uint32_t                    field_42C;
    uint32_t                    field_430;

    CExoArrayList<CNWSStats_SpecAbil>* cs_specabil;            /* 043C */

	uint16_t effects_ptr[0x1b];/* 0440 */

    uint16_t                    cs_skill_points;        /* 0476 */
    uint8_t                    *cs_skills;              /* 0478 */

    uint8_t                     field_479;
    uint8_t                     field_47A;

    CResRef                  cs_portrait;        /* 047E */

    uint8_t                     cs_al_goodevil;         /* 048E */
    uint8_t                     field_487;
    uint8_t                     cs_al_lawchaos;         /* 0490 */
    uint8_t                     field_489;

    uint8_t                     cs_color_skin;          /* 0492 */
    uint8_t                     cs_color_hair;          /* 0493 */
    uint8_t                     cs_color_tattoo_1;      /* 0494 */
    uint8_t                     cs_color_tattoo_2;      /* 0495 */

    uint16_t                    cs_appearance;          /* 0496 */

    uint8_t                     cs_phenotype;           /* 0498 */
    uint8_t                     cs_appearance_head;     /* 0499 */

    uint8_t                     cs_bodypart_rfoot;      /* 049A */
    uint8_t                     cs_bodypart_lfoot;      /* 049B */
    uint8_t                     cs_bodypart_rshin;      /* 049C */
    uint8_t                     cs_bodypart_lshin;      /* 049D */
    uint8_t                     cs_bodypart_lthigh;     /* 049E */
    uint8_t                     cs_bodypart_rthigh;     /* 049F */
    uint8_t                     cs_bodypart_pelvis;     /* 04A0 */
    uint8_t                     cs_bodypart_torso;      /* 04A1 */
    uint8_t                     cs_bodypart_belt;       /* 04A2 */
    uint8_t                     cs_bodypart_neck;       /* 04A3 */
    uint8_t                     cs_bodypart_rfarm;      /* 04A4 */
    uint8_t                     cs_bodypart_lfarm;      /* 04A5 */
    uint8_t                     cs_bodypart_rbicep;     /* 04A6 */
    uint8_t                     cs_bodypart_lbicep;     /* 04A7 */
    uint8_t                     cs_bodypart_rshoul;     /* 04A8 */
    uint8_t                     cs_bodypart_lshoul;     /* 04A9 */
    uint8_t                     cs_bodypart_rhand;      /* 04AA */
    uint8_t                     cs_bodypart_lhand;      /* 04AB */

    uint8_t                     field_4A4_old;
    uint8_t                     cs_tail_old;            /* 04AD */
    uint8_t                     cs_wings_old;           /* 04AE */
    uint8_t                     field_4A7_old;

    uint32_t                    cs_tail;                /* 04B0 */
    uint32_t                    cs_wings;               /* 04B4 */

    uint32_t                    cs_movement_rate;       /* 04B8 */

    uint32_t                    field_4AC;
    uint32_t                    field_4B0;

    int8_t                      cs_save_fort;           /* 04C4 */
    int8_t                      cs_save_will;           /* 04C5 */
    int8_t                      cs_save_reflex;         /* 04C6 */

    uint8_t                     field_4B7;

    uint32_t                    cs_acomp_type;          /* 04C8 */
    uint32_t                    cs_famil_type;          /* 04CC */

    CExoString                  cs_acomp_name;          /* 04D0 */
    CExoString                  cs_famil_name;          /* 04D8 */

    char                       *cs_deity;               /* 04E0 */
};
