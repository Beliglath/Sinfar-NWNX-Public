#pragma once

struct CNWSDialog_s {
    uint32_t             entries_len;
    CDialogSpeak       *entries;

    uint32_t             replies_len;
    CDialogReply   *replies;

    uint32_t             starts_len;
    CDialogNode        *starts;

    char                script_end[16];
    char                script_abort[16];

    uint32_t           *parties;

    uint32_t            field_3C;
    uint32_t            field_40;

    uint32_t            current_node;

    uint32_t            field_48;

    uint32_t            lang;
    uint32_t            oid_with;
    uint32_t            oid_self;

    uint32_t            field_58;
    uint32_t            field_5C;
    uint32_t            field_60;
    uint32_t            dlg_private;

    uint32_t            oid_self_2; //0x68
    uint32_t            prevent_zoom; //0x6c
	uint32_t			unk_0x70;
	uint32_t			unk_0x74;
};

#ifndef __x86_64__
static_assert(sizeof(CNWSDialog_s) == 0x78, "");
#endif

