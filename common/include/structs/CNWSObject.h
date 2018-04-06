#pragma once

struct CNWSObject_s {
    uint32_t            field_00;

    nwn_objid_t         obj_id;                         /* 0004 */
    uint8_t             obj_type;                       /* 0008 */

    uint8_t             field_09;
    uint8_t             field_0A;
    uint8_t             field_0B;

    CGameObject_VTable *obj_vtable;                     /* 000C */

    char               *obj_name;                   /* 0010 */
    uint32_t            field_14;

    uint16_t            field_18;
    uint16_t            obj_last_group_id;              /* 001A */

    CExoString          obj_tag;                        /* 001C */

    char               *obj_template;                   /* 0024 */

    uint32_t            field_28;
    uint32_t            field_2C;
    uint32_t            field_30;
    uint32_t            field_34;
    uint32_t            obj_conv_object_1;              /* 0038 */
    uint16_t            obj_portrait_id;                /* 003C */
    uint16_t            field_3E;
    CNWSDialog*         obj_dialog;              /* 0040 */
    uint32_t            field_44;
    uint32_t            field_48;
    uint32_t            field_4C;
    uint32_t            obj_conv_object_3;              /* 0050 */

    uint32_t            obj_conv_paused;                /* 0054 */
    uint32_t            obj_conv_owner;                 /* 0058 */
    uint32_t            obj_conv_animation;             /* 005C */

    int32_t             obj_ai_level;                   /* 0060 */
    uint32_t            obj_ai_lock;                    /* 0064 */

    CExoLinkedListNode *obj_ai_pos_list;                /* 0068 */

    uint8_t             field_6C;
    uint8_t             field_6D;
    uint8_t             field_6E;
    uint8_t             field_6F;

    nwn_objid_t         obj_action_target;              /* 0070 */
    uint32_t            field_74;

    uint32_t            obj_area_id;                    /* 0078 */

    Vector              obj_position;                   /* 007C */
    Vector              obj_orientation;                /* 0088 */

    uint32_t            field_94;
    uint32_t            field_98;

    uint32_t            obj_action_timer_day;           /* 009C */
    uint32_t            obj_action_timer_sec;           /* 00A0 */

    uint32_t            obj_last_anim_time_day;         /* 00A4 */
    uint32_t            obj_last_anim_time_sec;         /* 00A8 */
    uint32_t            field_AC;

    int32_t             obj_anim;                       /* 00B0 */
    float               obj_anim_speed;                 /* 00B4 */

    int32_t             obj_hp_cur;                     /* 00B8 */
    uint32_t            obj_hp_max;                     /* 00BC */
    uint32_t            obj_hp_temp;                    /* 00C0 */

    uint32_t            obj_is_commandable;             /* 00C4 */
    uint32_t            obj_is_destroyable;             /* 00C8 */
    uint32_t            obj_is_raisable;                /* 00CC */
    uint32_t            obj_is_dead_selectable;         /* 00D0 */
    uint32_t            obj_is_invulnerable;            /* 00D4 */

    CExoLinkedList      obj_actions;                    /* 00D8 */

    CNWSScriptVarTable  obj_vartable;                   /* 00DC */

    uint32_t            field_E4;
    uint32_t            field_E8;

    CGameEffect       **obj_effects;                    /* 00EC */
    uint32_t            obj_effects_len;                /* 00F0 */

    uint32_t            field_F4;

    CExoArrayList<void*> obj_visuals;                    /* 00F8 */
    nwn_objid_t        *obj_effect_target_list;         /* 0104 */
    uint32_t            obj_effect_target_len;          /* 0108 */

    uint32_t            field_10C;
    uint32_t            obj_pending_effect_removal;     /* 0110 */
    uint32_t            obj_saving_throw_spellid;       /* 0114 */

    int32_t             obj_custom_event_id;            /* 0118 */

    nwn_objid_t         obj_killer;                     /* 011C */
    nwn_objid_t         obj_last_hostile_actor;         /* 0120 */
    nwn_objid_t         obj_last_attacker;              /* 0124 */
    nwn_objid_t         obj_last_damager;               /* 0128 */
    nwn_objid_t         obj_last_disturbed;             /* 012C */

    int32_t            *obj_last_damage;                /* 0130 */

    uint16_t            obj_last_attack_type;           /* 0134 */
    uint8_t             obj_last_attack_mode;           /* 0136 */
    uint8_t             field_137;
    nwn_objid_t         obj_last_attack_weapon;         /* 0138 */

    nwn_objid_t         obj_inv_disturb_item;           /* 013C */
    int32_t             obj_inv_disturb_type;           /* 0140 */

    nwn_objid_t         obj_conv_last_speaker;          /* 0144 */
    uint32_t            obj_conv_private;               /* 0148 */
    uint32_t            obj_conv_play_hello;            /* 014C */
    CExoString         *obj_conv_last_resref;           /* 0150 */
    uint32_t            field_154;

    void               *obj_listen_expressions;         /* 0158 */

    uint32_t            field_15C;
    uint32_t            field_160;

    int32_t             obj_matched_position;           /* 0164 */
    uint32_t            obj_is_listening;               /* 0168 */

    void               *obj_matched_strings;            /* 016C */

    uint32_t            field_170;
    uint32_t            field_174;

    int8_t            *obj_damage_immunities;          /* 0178; actually int8_t internal to NWN */

    Vector              obj_last_spell_location;        /* 017C */
    nwn_objid_t         obj_last_spell_target;          /* 0188 */
    uint32_t            obj_last_spell_id;              /* 018C */
    uint8_t             obj_last_spell_domain_level;    /* 0190 */
    uint8_t             field_191;
    uint8_t             field_192;
    uint8_t             field_193;
    uint32_t            obj_last_spell_proj_time;       /* 0194 */
    uint32_t            obj_last_spell_cast;            /* 0198 */
    uint32_t            obj_last_spell_spontaneous;     /* 019C */
    uint8_t             obj_last_spell_multiclass;      /* 01A0 */
    uint8_t             obj_last_spell_metamagic;       /* 01A1 */
    uint8_t             field_1A2;
    uint8_t             field_1A3;
    uint32_t            obj_last_spell_castat_caster;   /* 01A4 */
    uint32_t            obj_last_spell_castat_id;       /* 01A8 */
    uint32_t            obj_last_spell_castat_harmful;  /* 01AC */
    uint16_t            obj_last_spell_feat;            /* 01B0 */
    uint16_t            field_1B2;

    CNWSAction         *obj_ai_action;                  /* 01B4 */
    uint32_t            obj_effect_index;               /* 01B8 */
    uint32_t            obj_effect_postprocess;         /* 01BC */

    uint32_t            obj_door_anim_played;           /* 01C0 */
};
