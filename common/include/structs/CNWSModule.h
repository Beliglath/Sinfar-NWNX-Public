#pragma once

struct CNWSModule_s {
    uint32_t                    field_00;
    uint32_t                    field_04;
    uint32_t                    field_08;
    uint32_t                    field_0C;
    uint32_t                    field_10;
    uint32_t                    field_14;
    uint32_t                    field_18;
    uint32_t                    field_1C;
    uint32_t                    field_20;
    uint32_t                    field_24;
    uint32_t                    field_28;
    uint32_t                    field_2C;
    uint32_t                    field_30;
    uint32_t                    field_34;

    CExoArrayList<uint32_t>     mod_areas;

    uint32_t                    field_44;
    uint32_t                    field_48;
    uint32_t                    field_4C;
    uint32_t                    field_50;
    uint32_t                    field_54;
    uint32_t                    field_58;
    uint32_t                    field_5C;
    uint32_t                    field_60;
    uint32_t                    field_64;
    uint32_t                    field_68;
    uint32_t                    field_6C;
    uint32_t                    field_70;
    uint32_t                    field_74;
    uint32_t                    field_78;
    uint32_t                    field_7C;
    uint32_t                    field_80;
    uint32_t                    field_84;
    uint32_t                    field_88;
    uint32_t                    field_8C;
    uint32_t                    field_90;
    uint32_t                    field_94;
    uint32_t                    field_98;
    uint32_t                    field_9C;
    uint32_t                    field_A0;
    uint32_t                    field_A4;

    CNWSScriptVarTable          mod_vartable;
};
