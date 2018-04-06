#pragma once

struct CDialogReply_s {
    uint32_t            anim_type; //0x0
    uint32_t            anim_loop; //0x4

    CExoLocString       text; //0x8
    CDialogNode        *nodes; //0x10
    uint32_t             nodes_len; //0x14

    char                script_conv[16]; //0x18

    uint32_t            delay; //0x28
    char                sound[16]; //0x2c

    uint32_t            quest; //0x3c
    uint32_t            quest_len; //0x40
    uint32_t            quest_entry;  //0x44
};
