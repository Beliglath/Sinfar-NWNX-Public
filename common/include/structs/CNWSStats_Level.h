#pragma once

struct CNWSStats_Level_s {
    CExoArrayList<uint32_t>     ls_spells_known[10];

    uint32_t                    unknown_1[30];

    CExoArrayList<uint16_t>     ls_featlist;

    uint8_t                    *ls_skilllist;
    uint8_t                     ls_skillpoints;

    uint8_t                     unknown_2;

    uint8_t                     ls_ability;
    uint8_t                     ls_hp;

    uint8_t                     ls_class;
};
