/**
 * This file is part of the "libfnord" project
 *   Copyright (c) 2015 Paul Asmuth
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef _FNORD_LANGUAGE_H
#define _FNORD_LANGUAGE_H
#include "fnord-base/stdtypes.h"

namespace fnord {

/* ISO 639-1 */
enum class Language : uint16_t {
  EN = 1,
  DE = 2
};

Language languageFromString(const String& string);

} // namespace fnord

#endif
