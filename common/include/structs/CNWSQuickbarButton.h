#pragma once

struct CNWSQuickbarButton_s {
	uint32_t            qb_objid1;		/* 0x00 */
    uint32_t            qb_objid2;		/* 0x04 */

    uint8_t             qb_type;		/* 0x08 */
    uint8_t             qb_class;		/* 0x09 */

	char				qb_resref[17];	/* 0x0A */	// for stuff dragged from the creator
    
    CExoString			qb_label;		/* 0x1C */
    CExoString			qb_command;		/* 0x24 */

    CExoString          qb_label2;		/* 0x2C */	// for stuff dragged from the creator

    uint32_t            qb_id;			/* 0x34 */
    uint16_t            qb_metamagic;	/* 0x38 */
	
	uint16_t			qb_associate_type; /* 0x3A */

    uint32_t            qb_associate;		/* 0x3C */
};

#ifndef __x86_64__
static_assert(sizeof(CNWSQuickbarButton_s) == 0x40, "");
#endif
