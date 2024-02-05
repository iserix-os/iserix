/* SPDX-License-Identifier: GPL-2.0-only */
/* Copyright (c) 2024, VX/sys Contributors */
#include <stddef.h>
#include <string.h>
#include <sys/panic.h>
#include <sys/printf.h>
#include <sys/vmm.h>
#include <x86_64/cpu.h>
#include <x86_64/gdt.h>
#include <x86_64/idt.h>

#define IDT_SIZE 256

#define IDT_TRAP    (0x0F << 0)
#define IDT_INTR    (0x0E << 0)
#define IDT_RING_0  (0x00 << 5)
#define IDT_RING_3  (0x03 << 5)
#define IDT_PRESENT (0x01 << 7)

typedef struct idt_entry_s {
    uint16_t offset_0;
    uint16_t selector;
    uint8_t ist_off;
    uint8_t flags;
    uint16_t offset_1;
    uint32_t offset_2;
    uint32_t reserved;
} __packed idt_entry_t;

typedef struct idt_register_s {
    uint16_t size;
    uintptr_t offset;
} __packed idt_register_t;

static idt_entry_t idt[IDT_SIZE] = { 0 };
static idt_register_t idtr = { 0 };

/* $(TEMP_DIR)/x86_64.isr_stubs.S */
extern const uint64_t isr_stubs[IDT_SIZE];

void __used isr_handler(struct cpu_context *restrict ctx, uint64_t vector)
{
    panic("idt: isr_handler(%p, %02jX)", (void *)ctx, (uintmax_t)vector);
    UNREACHABLE();
}

static void init_idt(void)
{
    size_t i;
    idt_entry_t *entry;

    for(i = 0; i < IDT_SIZE; i++) {
        entry = &idt[i];

        memset(entry, 0, sizeof(idt_entry_t));

        entry->offset_0 = (isr_stubs[i] & 0x000000000000FFFF);
        entry->offset_1 = (isr_stubs[i] & 0x00000000FFFF0000) >> 16;
        entry->offset_2 = (isr_stubs[i] & 0xFFFFFFFF00000000) >> 32;
        entry->selector = GDT_SELECTOR(GDT_KERN_CODE_64, 0, 0);

        /* Interrupt vectors 0x00 to 0x1F are x86 exceptions */
        entry->flags |= ((i < 0x20) ? IDT_TRAP : IDT_INTR);

        entry->flags |= IDT_RING_0;
        entry->flags |= IDT_PRESENT;
    }

    idtr.size = (uint16_t)(sizeof(idt) - 1);
    idtr.offset = (uintptr_t)(&idt[0]);

    asm volatile("lidtq %0"::"m"(idtr));

    kprintf(KP_DEBUG, "idt: idtr.size=%zu", (size_t)idtr.size);
    kprintf(KP_DEBUG, "idt: idtr.offset=%p", (void *)idtr.offset);
}
core_initcall(idt, init_idt);
initcall_depend(idt, gdt);
initcall_depend(idt, vmm);
