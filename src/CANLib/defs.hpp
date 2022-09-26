#pragma once

#if __linux__
#include <linux/can.h>
#include <unistd.h>
#else

#endif

enum class CanFormat { Standard, Extended };
enum class RetCode { Success, ReadErr, OpenErr, Timeout, SocketErr, WriteErr, InvalidParam };
