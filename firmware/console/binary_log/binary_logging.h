/**
 * @file binary_logging.h
 */

#pragma once

#include "buffered_writer.h"

int getSdCardFieldsCount();

void writeSdLogLine(Writer& buffer);
#if EFI_UNIT_TEST
void resetFileLogging();
#endif // EFI_UNIT_TEST
