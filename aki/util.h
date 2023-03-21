#ifndef _AKI_UTIL_H_
#define _AKI_UTIL_H_

#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdint.h>

namespace aki {
    pid_t GetThreadId();
    uint32_t GetFiberId();
}

#endif