#pragma once

struct CExoLinkedListHeader {
    CExoLinkedListNode         *first;
    CExoLinkedListNode         *last;
    uint32_t                    len;
};
