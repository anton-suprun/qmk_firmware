// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#ifdef __cplusplus
// Older QMK test helpers rely on a transitive include absent in current libc++.
#    include <sstream>
#endif
#include "test_common.h"
#include "../../users/nerf_caffeine/config.h"
