#pragma once

#if defined(__linux__)
#include <linux/can.h>
#include <unistd.h>
#else
#error "Cannot build backend if not on linux"
#endif

enum class CanFormat { Standard, Extended };
enum class RetCode { Success, ReadErr, OpenErr, Timeout, SocketErr, WriteErr, InvalidParam };
