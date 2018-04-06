#pragma once

struct CDialogSpeak_s {
    uint32_t* speaker;
    uint32_t speaker_len;
    CDialogReply info;
};

#ifndef __x86_64__
static_assert(sizeof(CDialogSpeak_s) == 80, "CDialogSpeak size is bad");
#endif
