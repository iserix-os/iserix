/* SPDX-License-Identifier: Zlib */
#include <arch/idt.h>
#include <arch/intreq.h>
#include <arch/limits.h>
#include <string.h>
#include <vex/errno.h>

static intreq_handler_t handlers[MAX_INTERRUPTS];

extern void x86_intreq_20(void);
extern void x86_intreq_21(void);
extern void x86_intreq_22(void);
extern void x86_intreq_23(void);
extern void x86_intreq_24(void);
extern void x86_intreq_25(void);
extern void x86_intreq_26(void);
extern void x86_intreq_27(void);
extern void x86_intreq_28(void);
extern void x86_intreq_29(void);
extern void x86_intreq_2A(void);
extern void x86_intreq_2B(void);
extern void x86_intreq_2C(void);
extern void x86_intreq_2D(void);
extern void x86_intreq_2E(void);
extern void x86_intreq_2F(void);
extern void x86_intreq_30(void);
extern void x86_intreq_31(void);
extern void x86_intreq_32(void);
extern void x86_intreq_33(void);
extern void x86_intreq_34(void);
extern void x86_intreq_35(void);
extern void x86_intreq_36(void);
extern void x86_intreq_37(void);
extern void x86_intreq_38(void);
extern void x86_intreq_39(void);
extern void x86_intreq_3A(void);
extern void x86_intreq_3B(void);
extern void x86_intreq_3C(void);
extern void x86_intreq_3D(void);
extern void x86_intreq_3E(void);
extern void x86_intreq_3F(void);
extern void x86_intreq_40(void);
extern void x86_intreq_41(void);
extern void x86_intreq_42(void);
extern void x86_intreq_43(void);
extern void x86_intreq_44(void);
extern void x86_intreq_45(void);
extern void x86_intreq_46(void);
extern void x86_intreq_47(void);
extern void x86_intreq_48(void);
extern void x86_intreq_49(void);
extern void x86_intreq_4A(void);
extern void x86_intreq_4B(void);
extern void x86_intreq_4C(void);
extern void x86_intreq_4D(void);
extern void x86_intreq_4E(void);
extern void x86_intreq_4F(void);
extern void x86_intreq_50(void);
extern void x86_intreq_51(void);
extern void x86_intreq_52(void);
extern void x86_intreq_53(void);
extern void x86_intreq_54(void);
extern void x86_intreq_55(void);
extern void x86_intreq_56(void);
extern void x86_intreq_57(void);
extern void x86_intreq_58(void);
extern void x86_intreq_59(void);
extern void x86_intreq_5A(void);
extern void x86_intreq_5B(void);
extern void x86_intreq_5C(void);
extern void x86_intreq_5D(void);
extern void x86_intreq_5E(void);
extern void x86_intreq_5F(void);
extern void x86_intreq_60(void);
extern void x86_intreq_61(void);
extern void x86_intreq_62(void);
extern void x86_intreq_63(void);
extern void x86_intreq_64(void);
extern void x86_intreq_65(void);
extern void x86_intreq_66(void);
extern void x86_intreq_67(void);
extern void x86_intreq_68(void);
extern void x86_intreq_69(void);
extern void x86_intreq_6A(void);
extern void x86_intreq_6B(void);
extern void x86_intreq_6C(void);
extern void x86_intreq_6D(void);
extern void x86_intreq_6E(void);
extern void x86_intreq_6F(void);
extern void x86_intreq_70(void);
extern void x86_intreq_71(void);
extern void x86_intreq_72(void);
extern void x86_intreq_73(void);
extern void x86_intreq_74(void);
extern void x86_intreq_75(void);
extern void x86_intreq_76(void);
extern void x86_intreq_77(void);
extern void x86_intreq_78(void);
extern void x86_intreq_79(void);
extern void x86_intreq_7A(void);
extern void x86_intreq_7B(void);
extern void x86_intreq_7C(void);
extern void x86_intreq_7D(void);
extern void x86_intreq_7E(void);
extern void x86_intreq_7F(void);
extern void x86_intreq_80(void);
extern void x86_intreq_81(void);
extern void x86_intreq_82(void);
extern void x86_intreq_83(void);
extern void x86_intreq_84(void);
extern void x86_intreq_85(void);
extern void x86_intreq_86(void);
extern void x86_intreq_87(void);
extern void x86_intreq_88(void);
extern void x86_intreq_89(void);
extern void x86_intreq_8A(void);
extern void x86_intreq_8B(void);
extern void x86_intreq_8C(void);
extern void x86_intreq_8D(void);
extern void x86_intreq_8E(void);
extern void x86_intreq_8F(void);
extern void x86_intreq_90(void);
extern void x86_intreq_91(void);
extern void x86_intreq_92(void);
extern void x86_intreq_93(void);
extern void x86_intreq_94(void);
extern void x86_intreq_95(void);
extern void x86_intreq_96(void);
extern void x86_intreq_97(void);
extern void x86_intreq_98(void);
extern void x86_intreq_99(void);
extern void x86_intreq_9A(void);
extern void x86_intreq_9B(void);
extern void x86_intreq_9C(void);
extern void x86_intreq_9D(void);
extern void x86_intreq_9E(void);
extern void x86_intreq_9F(void);
extern void x86_intreq_A0(void);
extern void x86_intreq_A1(void);
extern void x86_intreq_A2(void);
extern void x86_intreq_A3(void);
extern void x86_intreq_A4(void);
extern void x86_intreq_A5(void);
extern void x86_intreq_A6(void);
extern void x86_intreq_A7(void);
extern void x86_intreq_A8(void);
extern void x86_intreq_A9(void);
extern void x86_intreq_AA(void);
extern void x86_intreq_AB(void);
extern void x86_intreq_AC(void);
extern void x86_intreq_AD(void);
extern void x86_intreq_AE(void);
extern void x86_intreq_AF(void);
extern void x86_intreq_B0(void);
extern void x86_intreq_B1(void);
extern void x86_intreq_B2(void);
extern void x86_intreq_B3(void);
extern void x86_intreq_B4(void);
extern void x86_intreq_B5(void);
extern void x86_intreq_B6(void);
extern void x86_intreq_B7(void);
extern void x86_intreq_B8(void);
extern void x86_intreq_B9(void);
extern void x86_intreq_BA(void);
extern void x86_intreq_BB(void);
extern void x86_intreq_BC(void);
extern void x86_intreq_BD(void);
extern void x86_intreq_BE(void);
extern void x86_intreq_BF(void);
extern void x86_intreq_C0(void);
extern void x86_intreq_C1(void);
extern void x86_intreq_C2(void);
extern void x86_intreq_C3(void);
extern void x86_intreq_C4(void);
extern void x86_intreq_C5(void);
extern void x86_intreq_C6(void);
extern void x86_intreq_C7(void);
extern void x86_intreq_C8(void);
extern void x86_intreq_C9(void);
extern void x86_intreq_CA(void);
extern void x86_intreq_CB(void);
extern void x86_intreq_CC(void);
extern void x86_intreq_CD(void);
extern void x86_intreq_CE(void);
extern void x86_intreq_CF(void);
extern void x86_intreq_D0(void);
extern void x86_intreq_D1(void);
extern void x86_intreq_D2(void);
extern void x86_intreq_D3(void);
extern void x86_intreq_D4(void);
extern void x86_intreq_D5(void);
extern void x86_intreq_D6(void);
extern void x86_intreq_D7(void);
extern void x86_intreq_D8(void);
extern void x86_intreq_D9(void);
extern void x86_intreq_DA(void);
extern void x86_intreq_DB(void);
extern void x86_intreq_DC(void);
extern void x86_intreq_DD(void);
extern void x86_intreq_DE(void);
extern void x86_intreq_DF(void);
extern void x86_intreq_E0(void);
extern void x86_intreq_E1(void);
extern void x86_intreq_E2(void);
extern void x86_intreq_E3(void);
extern void x86_intreq_E4(void);
extern void x86_intreq_E5(void);
extern void x86_intreq_E6(void);
extern void x86_intreq_E7(void);
extern void x86_intreq_E8(void);
extern void x86_intreq_E9(void);
extern void x86_intreq_EA(void);
extern void x86_intreq_EB(void);
extern void x86_intreq_EC(void);
extern void x86_intreq_ED(void);
extern void x86_intreq_EE(void);
extern void x86_intreq_EF(void);
extern void x86_intreq_F0(void);
extern void x86_intreq_F1(void);
extern void x86_intreq_F2(void);
extern void x86_intreq_F3(void);
extern void x86_intreq_F4(void);
extern void x86_intreq_F5(void);
extern void x86_intreq_F6(void);
extern void x86_intreq_F7(void);
extern void x86_intreq_F8(void);
extern void x86_intreq_F9(void);
extern void x86_intreq_FA(void);
extern void x86_intreq_FB(void);
extern void x86_intreq_FC(void);
extern void x86_intreq_FD(void);
extern void x86_intreq_FE(void);
extern void x86_intreq_FF(void);

void __used x86_intreq_handler(struct interrupt_frame *restrict frame, uint64_t intvec)
{
    intreq_handler_t handler;

    if((intvec >= MIN_INTREQ_VEC) && (intvec < MAX_INTERRUPTS)) {
        if((handler = handlers[intvec - MIN_INTREQ_VEC]) == NULL)
            return;
        handler(frame);
    }
}

int set_intreq_handler(unsigned vector, intreq_handler_t handler)
{
    if(vector >= MAX_INTERRUPTS)
        return EINVAL;
    handlers[vector] = handler;
    return 0;
}

int unset_intreq_handler(unsigned vector)
{
    if(vector >= MAX_INTERRUPTS)
        return EINVAL;
    handlers[vector] = NULL;
    return 0;
}

void init_intreq(void)
{
    memset(handlers, 0, sizeof(handlers));

    set_idt_entry(0x20, 0, &x86_intreq_20);
    set_idt_entry(0x21, 0, &x86_intreq_21);
    set_idt_entry(0x22, 0, &x86_intreq_22);
    set_idt_entry(0x23, 0, &x86_intreq_23);
    set_idt_entry(0x24, 0, &x86_intreq_24);
    set_idt_entry(0x25, 0, &x86_intreq_25);
    set_idt_entry(0x26, 0, &x86_intreq_26);
    set_idt_entry(0x27, 0, &x86_intreq_27);
    set_idt_entry(0x28, 0, &x86_intreq_28);
    set_idt_entry(0x29, 0, &x86_intreq_29);
    set_idt_entry(0x2A, 0, &x86_intreq_2A);
    set_idt_entry(0x2B, 0, &x86_intreq_2B);
    set_idt_entry(0x2C, 0, &x86_intreq_2C);
    set_idt_entry(0x2D, 0, &x86_intreq_2D);
    set_idt_entry(0x2E, 0, &x86_intreq_2E);
    set_idt_entry(0x2F, 0, &x86_intreq_2F);
    set_idt_entry(0x30, 0, &x86_intreq_30);
    set_idt_entry(0x31, 0, &x86_intreq_31);
    set_idt_entry(0x32, 0, &x86_intreq_32);
    set_idt_entry(0x33, 0, &x86_intreq_33);
    set_idt_entry(0x34, 0, &x86_intreq_34);
    set_idt_entry(0x35, 0, &x86_intreq_35);
    set_idt_entry(0x36, 0, &x86_intreq_36);
    set_idt_entry(0x37, 0, &x86_intreq_37);
    set_idt_entry(0x38, 0, &x86_intreq_38);
    set_idt_entry(0x39, 0, &x86_intreq_39);
    set_idt_entry(0x3A, 0, &x86_intreq_3A);
    set_idt_entry(0x3B, 0, &x86_intreq_3B);
    set_idt_entry(0x3C, 0, &x86_intreq_3C);
    set_idt_entry(0x3D, 0, &x86_intreq_3D);
    set_idt_entry(0x3E, 0, &x86_intreq_3E);
    set_idt_entry(0x3F, 0, &x86_intreq_3F);
    set_idt_entry(0x40, 0, &x86_intreq_40);
    set_idt_entry(0x41, 0, &x86_intreq_41);
    set_idt_entry(0x42, 0, &x86_intreq_42);
    set_idt_entry(0x43, 0, &x86_intreq_43);
    set_idt_entry(0x44, 0, &x86_intreq_44);
    set_idt_entry(0x45, 0, &x86_intreq_45);
    set_idt_entry(0x46, 0, &x86_intreq_46);
    set_idt_entry(0x47, 0, &x86_intreq_47);
    set_idt_entry(0x48, 0, &x86_intreq_48);
    set_idt_entry(0x49, 0, &x86_intreq_49);
    set_idt_entry(0x4A, 0, &x86_intreq_4A);
    set_idt_entry(0x4B, 0, &x86_intreq_4B);
    set_idt_entry(0x4C, 0, &x86_intreq_4C);
    set_idt_entry(0x4D, 0, &x86_intreq_4D);
    set_idt_entry(0x4E, 0, &x86_intreq_4E);
    set_idt_entry(0x4F, 0, &x86_intreq_4F);
    set_idt_entry(0x50, 0, &x86_intreq_50);
    set_idt_entry(0x51, 0, &x86_intreq_51);
    set_idt_entry(0x52, 0, &x86_intreq_52);
    set_idt_entry(0x53, 0, &x86_intreq_53);
    set_idt_entry(0x54, 0, &x86_intreq_54);
    set_idt_entry(0x55, 0, &x86_intreq_55);
    set_idt_entry(0x56, 0, &x86_intreq_56);
    set_idt_entry(0x57, 0, &x86_intreq_57);
    set_idt_entry(0x58, 0, &x86_intreq_58);
    set_idt_entry(0x59, 0, &x86_intreq_59);
    set_idt_entry(0x5A, 0, &x86_intreq_5A);
    set_idt_entry(0x5B, 0, &x86_intreq_5B);
    set_idt_entry(0x5C, 0, &x86_intreq_5C);
    set_idt_entry(0x5D, 0, &x86_intreq_5D);
    set_idt_entry(0x5E, 0, &x86_intreq_5E);
    set_idt_entry(0x5F, 0, &x86_intreq_5F);
    set_idt_entry(0x60, 0, &x86_intreq_60);
    set_idt_entry(0x61, 0, &x86_intreq_61);
    set_idt_entry(0x62, 0, &x86_intreq_62);
    set_idt_entry(0x63, 0, &x86_intreq_63);
    set_idt_entry(0x64, 0, &x86_intreq_64);
    set_idt_entry(0x65, 0, &x86_intreq_65);
    set_idt_entry(0x66, 0, &x86_intreq_66);
    set_idt_entry(0x67, 0, &x86_intreq_67);
    set_idt_entry(0x68, 0, &x86_intreq_68);
    set_idt_entry(0x69, 0, &x86_intreq_69);
    set_idt_entry(0x6A, 0, &x86_intreq_6A);
    set_idt_entry(0x6B, 0, &x86_intreq_6B);
    set_idt_entry(0x6C, 0, &x86_intreq_6C);
    set_idt_entry(0x6D, 0, &x86_intreq_6D);
    set_idt_entry(0x6E, 0, &x86_intreq_6E);
    set_idt_entry(0x6F, 0, &x86_intreq_6F);
    set_idt_entry(0x70, 0, &x86_intreq_70);
    set_idt_entry(0x71, 0, &x86_intreq_71);
    set_idt_entry(0x72, 0, &x86_intreq_72);
    set_idt_entry(0x73, 0, &x86_intreq_73);
    set_idt_entry(0x74, 0, &x86_intreq_74);
    set_idt_entry(0x75, 0, &x86_intreq_75);
    set_idt_entry(0x76, 0, &x86_intreq_76);
    set_idt_entry(0x77, 0, &x86_intreq_77);
    set_idt_entry(0x78, 0, &x86_intreq_78);
    set_idt_entry(0x79, 0, &x86_intreq_79);
    set_idt_entry(0x7A, 0, &x86_intreq_7A);
    set_idt_entry(0x7B, 0, &x86_intreq_7B);
    set_idt_entry(0x7C, 0, &x86_intreq_7C);
    set_idt_entry(0x7D, 0, &x86_intreq_7D);
    set_idt_entry(0x7E, 0, &x86_intreq_7E);
    set_idt_entry(0x7F, 0, &x86_intreq_7F);
    set_idt_entry(0x80, 0, &x86_intreq_80);
    set_idt_entry(0x81, 0, &x86_intreq_81);
    set_idt_entry(0x82, 0, &x86_intreq_82);
    set_idt_entry(0x83, 0, &x86_intreq_83);
    set_idt_entry(0x84, 0, &x86_intreq_84);
    set_idt_entry(0x85, 0, &x86_intreq_85);
    set_idt_entry(0x86, 0, &x86_intreq_86);
    set_idt_entry(0x87, 0, &x86_intreq_87);
    set_idt_entry(0x88, 0, &x86_intreq_88);
    set_idt_entry(0x89, 0, &x86_intreq_89);
    set_idt_entry(0x8A, 0, &x86_intreq_8A);
    set_idt_entry(0x8B, 0, &x86_intreq_8B);
    set_idt_entry(0x8C, 0, &x86_intreq_8C);
    set_idt_entry(0x8D, 0, &x86_intreq_8D);
    set_idt_entry(0x8E, 0, &x86_intreq_8E);
    set_idt_entry(0x8F, 0, &x86_intreq_8F);
    set_idt_entry(0x90, 0, &x86_intreq_90);
    set_idt_entry(0x91, 0, &x86_intreq_91);
    set_idt_entry(0x92, 0, &x86_intreq_92);
    set_idt_entry(0x93, 0, &x86_intreq_93);
    set_idt_entry(0x94, 0, &x86_intreq_94);
    set_idt_entry(0x95, 0, &x86_intreq_95);
    set_idt_entry(0x96, 0, &x86_intreq_96);
    set_idt_entry(0x97, 0, &x86_intreq_97);
    set_idt_entry(0x98, 0, &x86_intreq_98);
    set_idt_entry(0x99, 0, &x86_intreq_99);
    set_idt_entry(0x9A, 0, &x86_intreq_9A);
    set_idt_entry(0x9B, 0, &x86_intreq_9B);
    set_idt_entry(0x9C, 0, &x86_intreq_9C);
    set_idt_entry(0x9D, 0, &x86_intreq_9D);
    set_idt_entry(0x9E, 0, &x86_intreq_9E);
    set_idt_entry(0x9F, 0, &x86_intreq_9F);
    set_idt_entry(0xA0, 0, &x86_intreq_A0);
    set_idt_entry(0xA1, 0, &x86_intreq_A1);
    set_idt_entry(0xA2, 0, &x86_intreq_A2);
    set_idt_entry(0xA3, 0, &x86_intreq_A3);
    set_idt_entry(0xA4, 0, &x86_intreq_A4);
    set_idt_entry(0xA5, 0, &x86_intreq_A5);
    set_idt_entry(0xA6, 0, &x86_intreq_A6);
    set_idt_entry(0xA7, 0, &x86_intreq_A7);
    set_idt_entry(0xA8, 0, &x86_intreq_A8);
    set_idt_entry(0xA9, 0, &x86_intreq_A9);
    set_idt_entry(0xAA, 0, &x86_intreq_AA);
    set_idt_entry(0xAB, 0, &x86_intreq_AB);
    set_idt_entry(0xAC, 0, &x86_intreq_AC);
    set_idt_entry(0xAD, 0, &x86_intreq_AD);
    set_idt_entry(0xAE, 0, &x86_intreq_AE);
    set_idt_entry(0xAF, 0, &x86_intreq_AF);
    set_idt_entry(0xB0, 0, &x86_intreq_B0);
    set_idt_entry(0xB1, 0, &x86_intreq_B1);
    set_idt_entry(0xB2, 0, &x86_intreq_B2);
    set_idt_entry(0xB3, 0, &x86_intreq_B3);
    set_idt_entry(0xB4, 0, &x86_intreq_B4);
    set_idt_entry(0xB5, 0, &x86_intreq_B5);
    set_idt_entry(0xB6, 0, &x86_intreq_B6);
    set_idt_entry(0xB7, 0, &x86_intreq_B7);
    set_idt_entry(0xB8, 0, &x86_intreq_B8);
    set_idt_entry(0xB9, 0, &x86_intreq_B9);
    set_idt_entry(0xBA, 0, &x86_intreq_BA);
    set_idt_entry(0xBB, 0, &x86_intreq_BB);
    set_idt_entry(0xBC, 0, &x86_intreq_BC);
    set_idt_entry(0xBD, 0, &x86_intreq_BD);
    set_idt_entry(0xBE, 0, &x86_intreq_BE);
    set_idt_entry(0xBF, 0, &x86_intreq_BF);
    set_idt_entry(0xC0, 0, &x86_intreq_C0);
    set_idt_entry(0xC1, 0, &x86_intreq_C1);
    set_idt_entry(0xC2, 0, &x86_intreq_C2);
    set_idt_entry(0xC3, 0, &x86_intreq_C3);
    set_idt_entry(0xC4, 0, &x86_intreq_C4);
    set_idt_entry(0xC5, 0, &x86_intreq_C5);
    set_idt_entry(0xC6, 0, &x86_intreq_C6);
    set_idt_entry(0xC7, 0, &x86_intreq_C7);
    set_idt_entry(0xC8, 0, &x86_intreq_C8);
    set_idt_entry(0xC9, 0, &x86_intreq_C9);
    set_idt_entry(0xCA, 0, &x86_intreq_CA);
    set_idt_entry(0xCB, 0, &x86_intreq_CB);
    set_idt_entry(0xCC, 0, &x86_intreq_CC);
    set_idt_entry(0xCD, 0, &x86_intreq_CD);
    set_idt_entry(0xCE, 0, &x86_intreq_CE);
    set_idt_entry(0xCF, 0, &x86_intreq_CF);
    set_idt_entry(0xD0, 0, &x86_intreq_D0);
    set_idt_entry(0xD1, 0, &x86_intreq_D1);
    set_idt_entry(0xD2, 0, &x86_intreq_D2);
    set_idt_entry(0xD3, 0, &x86_intreq_D3);
    set_idt_entry(0xD4, 0, &x86_intreq_D4);
    set_idt_entry(0xD5, 0, &x86_intreq_D5);
    set_idt_entry(0xD6, 0, &x86_intreq_D6);
    set_idt_entry(0xD7, 0, &x86_intreq_D7);
    set_idt_entry(0xD8, 0, &x86_intreq_D8);
    set_idt_entry(0xD9, 0, &x86_intreq_D9);
    set_idt_entry(0xDA, 0, &x86_intreq_DA);
    set_idt_entry(0xDB, 0, &x86_intreq_DB);
    set_idt_entry(0xDC, 0, &x86_intreq_DC);
    set_idt_entry(0xDD, 0, &x86_intreq_DD);
    set_idt_entry(0xDE, 0, &x86_intreq_DE);
    set_idt_entry(0xDF, 0, &x86_intreq_DF);
    set_idt_entry(0xE0, 0, &x86_intreq_E0);
    set_idt_entry(0xE1, 0, &x86_intreq_E1);
    set_idt_entry(0xE2, 0, &x86_intreq_E2);
    set_idt_entry(0xE3, 0, &x86_intreq_E3);
    set_idt_entry(0xE4, 0, &x86_intreq_E4);
    set_idt_entry(0xE5, 0, &x86_intreq_E5);
    set_idt_entry(0xE6, 0, &x86_intreq_E6);
    set_idt_entry(0xE7, 0, &x86_intreq_E7);
    set_idt_entry(0xE8, 0, &x86_intreq_E8);
    set_idt_entry(0xE9, 0, &x86_intreq_E9);
    set_idt_entry(0xEA, 0, &x86_intreq_EA);
    set_idt_entry(0xEB, 0, &x86_intreq_EB);
    set_idt_entry(0xEC, 0, &x86_intreq_EC);
    set_idt_entry(0xED, 0, &x86_intreq_ED);
    set_idt_entry(0xEE, 0, &x86_intreq_EE);
    set_idt_entry(0xEF, 0, &x86_intreq_EF);
    set_idt_entry(0xF0, 0, &x86_intreq_F0);
    set_idt_entry(0xF1, 0, &x86_intreq_F1);
    set_idt_entry(0xF2, 0, &x86_intreq_F2);
    set_idt_entry(0xF3, 0, &x86_intreq_F3);
    set_idt_entry(0xF4, 0, &x86_intreq_F4);
    set_idt_entry(0xF5, 0, &x86_intreq_F5);
    set_idt_entry(0xF6, 0, &x86_intreq_F6);
    set_idt_entry(0xF7, 0, &x86_intreq_F7);
    set_idt_entry(0xF8, 0, &x86_intreq_F8);
    set_idt_entry(0xF9, 0, &x86_intreq_F9);
    set_idt_entry(0xFA, 0, &x86_intreq_FA);
    set_idt_entry(0xFB, 0, &x86_intreq_FB);
    set_idt_entry(0xFC, 0, &x86_intreq_FC);
    set_idt_entry(0xFD, 0, &x86_intreq_FD);
    set_idt_entry(0xFE, 0, &x86_intreq_FE);
    set_idt_entry(0xFF, 0, &x86_intreq_FF);
}
