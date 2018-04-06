#pragma once

struct CNWSItem_s {
    uint8_t                     it_color[6];            /* 0000 */
    uint8_t                     field_06;
    uint8_t                     field_07;

    uint32_t                    it_baseitem; //8

    uint32_t                    field_0C; //12

    CNWSObject                  obj; //0x10

    uint32_t                    field_1D4;              /* 01D4 */
    uint32_t                    field_1D8;              /* 01D8 */
    uint32_t                    field_1DC;              /* 01DC */
    uint32_t                    it_ac;                  /* 01E0 */

    uint8_t                     it_identified;          /* 01E4 */
    uint8_t                     field_1E5;
    uint8_t                     field_1E6;
    uint8_t                     field_1E7;

    uint32_t                    field_1E8;              /* 01E8 */
    uint32_t                    field_1EC;              /* 01EC */
    uint32_t                    field_1F0;              /* 01F0 */
    uint32_t                    field_1F4;              /* 01F4 */
    uint32_t                    field_1F8;              /* 01F8 */
    uint32_t                    field_1FC;              /* 01FC */
    uint32_t                    field_200;              /* 0200 */

    uint8_t                     it_charges;             /* 0204 */
    uint8_t                     field_205;
    uint8_t                     field_206;
    uint8_t                     field_207;

    uint32_t                    it_cost_ided;           /* 0208 */
    uint32_t                    it_cost_unided;         /* 020C */

    uint32_t                    it_cost_add;            /* 0210 */

    uint32_t                    field_214;              /* 0214 */

    uint8_t                     it_model[22];           /* 0218 */

    uint8_t                     field_22E;
    uint8_t                     field_22F;

    uint32_t                    field_230;              /* 0230 */
    uint32_t                    field_234;              /* 0234 */
    uint32_t                    field_238;              /* 0238 */
    uint32_t                    field_23C;              /* 023C */
    uint32_t                    field_240;              /* 0240 */
    uint32_t                    it_possessor;           /* 0244 */
    CItemRepository*            it_inventory;          /* 0248 */
    uint32_t                    field_24C;              /* 024C */
    uint32_t                    field_250;              /* 0250 */
    uint32_t                    field_254;              /* 0254 */
    uint32_t                    field_258;              /* 0258 */
    uint32_t                    field_25C;              /* 025C */
    uint32_t                    field_260;              /* 0260 */
    uint32_t                    field_264;              /* 0264 */
    uint32_t                    field_268;              /* 0268 */
    uint32_t                    field_26C;              /* 026C */
    uint32_t                    field_270;              /* 0270 */
    uint32_t                    field_274;              /* 0274 */
    uint32_t                    field_278;              /* 0278 */
    uint32_t                    field_27C;              /* 027C */
    uint32_t                    field_280;              /* 0280 */
    uint32_t                    field_284;              /* 0284 */

    uint8_t                     it_droppable;           /* 0288 */
    uint8_t                     field_289;
    uint8_t                     field_28A;
    uint8_t                     field_28B;

    uint32_t                    field_28C;              /* 028C */

    uint8_t                     it_pickpocketable;      /* 0290 */
    uint8_t                     field_290;
    uint8_t                     field_291;
    uint8_t                     field_292;

    uint32_t                    it_stack_size;              /* 0294 */

    uint8_t                     it_stolen;              /* 0298 */
    uint8_t                     field_299;
    uint8_t                     field_29A;
    uint8_t                     field_29B;

    uint32_t                    it_weight;              /* 029C */
	uint32_t                    field_2A0;
	uint32_t                    it_barterowner;
};

#ifndef __x86_64__
static_assert(sizeof(CNWSItem_s) == 0x2A8, "CNWSItem size is bad");
#endif
