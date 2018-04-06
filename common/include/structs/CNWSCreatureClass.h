#pragma once

struct CNWSCreatureClass_s {
    CExoArrayList<uint32_t>     cl_spells_known[10];
    CExoArrayList<void*>        cl_spells_mem[10];      /* CNWSStats_Spell * */

    uint8_t                     cl_spells_bonus[10];
    uint8_t                     cl_spells_left[10];
    uint8_t                     cl_spells_max[10];

    uint8_t                     cl_class;
    uint8_t                     cl_level;

    uint8_t                     cl_negative_level;

    uint8_t                     cl_specialist;
    uint8_t                     cl_domain_1;
    uint8_t                     cl_domain_2;

    uint8_t                     unknown_2[4];
};
