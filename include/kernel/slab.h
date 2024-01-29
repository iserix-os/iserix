/* SPDX-License-Identifier: GPL-2.0-only */
/* Copyright (c) 2023, VX/sys Contributors */
#ifndef INCLUDE_KERNEL_SLAB_H
#define INCLUDE_KERNEL_SLAB_H
#include <kernel/initcall.h>
#include <stddef.h>

void *slab_alloc(size_t n);
void *slab_calloc(size_t count, size_t n);
void *slab_realloc(void *restrict ptr, size_t n);
void slab_free(void *restrict ptr);

initcall_extern(slab);

#endif /* INCLUDE_KERNEL_SLAB_H */
