/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright (c), 2022, Kaneru Contributors */
#include <kaneru/debug.h>
#include <kaneru/errno.h>
#include <kaneru/initcall.h>
#include <kaneru/interrupt.h>
#include <kaneru/kprintf.h>
#include <kaneru/version.h>
#include <stddef.h>
#include <string.h>
#include <limine.h>

static void kmain(void) __noreturn;
static volatile struct limine_entry_point_request __used kmain_request = {
    .id = LIMINE_ENTRY_POINT_REQUEST,
    .revision = 0,
    .response = NULL,
    .entry = (limine_entry_point)(&kmain),
};

static void test_intr(void *restrict frame)
{
    struct x86_interrupt_frame *xframe = frame;
    kprintf(KP_EARLY, "interrupt test: int $%#02lX was issued", xframe->vector);
}

static void __noreturn kmain(void)
{
    int errnum;
    const struct initcall *ic;

    /* Print version */
    kprintf(KP_EARLY, "kmain: starting version %s", K_SEMVER);

    /* Initialize all the subsystems */
    for(ic = &__initcalls[0]; ic->func && ic->name[0]; ic++) {
        errnum = ic->func();
        if(errnum != 0) {
            if(errnum == -ENODEV)
                continue;
            panic("init %s: %s", ic->name, strerror(-errnum));
        }
    }

    /* test interrupts */
    intvec_t test_vec = alloc_interrupt(INTVEC_NULL);
    if(test_vec != INTVEC_NULL) {
        bind_interrupt_handler(test_vec, &test_intr);
        x86_map_interrupt(test_vec, 0x20, false);
        x86_map_interrupt(test_vec, 0x40, false);
        x86_map_interrupt(test_vec, 0x80, false);
        asm volatile("int $0x20");
        asm volatile("int $0x40");
        asm volatile("int $0x80");
    }

    panic("nothing to do");
}
