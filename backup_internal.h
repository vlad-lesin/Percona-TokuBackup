/* -*- mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*- */
// vim: ft=cpp:expandtab:ts=8:sw=4:softtabstop=4:

#ifndef BACKUP_INTERNAL_H
#define BACKUP_INTERNAL_H

#ident "Copyright (c) 2012-2013 Tokutek Inc.  All rights reserved."
#ident "$Id: backup.h 54696 2013-03-25 20:59:02Z bkuszmaul $"

#include "backup.h"
#include "sys/types.h"

unsigned long get_throttle(void);
// Effect: Callback used during a backup session to get current throttle level.

void create_subdirectories(const char*);

char *malloc_snprintf(size_t size, const char *format, ...) __attribute__((format (printf, 2, 3)));
// Effect: Return a malloced string of the given size containing the results of doing snprintf(string,size,format,...)
//  No errors occur if the size isn't big enough, instead a properly null-terminated string of at most size is returned without overflowing any buffers.

#endif // end of header guardian.
