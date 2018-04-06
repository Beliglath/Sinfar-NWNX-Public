#pragma once

struct CNWSPlayerStoreGUI
{
	void* unk_0x0;
};

struct CNWSPlayer_s {
    uint32_t            pl_id;

    uint32_t            field_04;
    uint32_t            field_08;
    CExoLinkedList*     pl_last_update_objects;
    CExoLinkedList*     pl_party_last_update_objects;
    uint32_t            field_14;
    uint32_t            field_18;
    uint32_t            field_1C;
    uint32_t            field_20;
    uint32_t            field_24;
    uint32_t            field_28;
    uint32_t            field_2C;
    uint32_t            pl_oid;
    uint32_t            field_34;
    uint32_t            field_38;
    uint32_t            field_3C;
    uint32_t            pl_pc_oid;
    uint32_t            field_44;
    uint32_t            field_48;
    uint32_t            field_4C;
    uint32_t            field_50;
    uint32_t            field_54;
    uint32_t            field_58;
    CNWSPlayerStoreGUI* pl_store_gui;
    uint32_t            field_60;
    uint32_t            field_64;
    uint32_t            field_68;
    CNWSPlayerLastUpdateObject* pl_last_update_object;
    uint32_t            field_70;

    uint8_t             pl_type; //0x74
    CResRef             pl_bicfile; //0x75
	uint8_t				unk_0x85[3];

    uint32_t            field_88;
	uint32_t            field_8c;
	uint32_t            field_90;
	uint32_t            field_94;
};
