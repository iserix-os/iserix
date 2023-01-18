/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright (c), 2022, KanOS Contributors */
#ifndef _INCLUDE_X86_SEGMENT_H__
#define _INCLUDE_X86_SEGMENT_H__
#include <kan/initcall.h>

#define SEGMENT_NULL 0
#define SEGMENT_KERN_CODE_16 1
#define SEGMENT_KERN_DATA_16 2
#define SEGMENT_KERN_CODE_32 3
#define SEGMENT_KERN_DATA_32 4
#define SEGMENT_KERN_CODE_64 5
#define SEGMENT_KERN_DATA_64 6
#define SEGMENT_USER_CODE_64 7
#define SEGMENT_USER_DATA_64 8
#define SEGMENT_SELECTOR(index, ldt, ring) (((ring) & 4) | (((ldt) & 1) << 2) | (index) << 3)

initcall_extern(x86_segment);

#endif /* _INCLUDE_X86_SEGMENT_H__ */
