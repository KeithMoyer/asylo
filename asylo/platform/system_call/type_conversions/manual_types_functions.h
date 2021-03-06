/*
 *
 * Copyright 2019 Asylo authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef ASYLO_PLATFORM_SYSTEM_CALL_TYPE_CONVERSIONS_MANUAL_TYPES_FUNCTIONS_H_
#define ASYLO_PLATFORM_SYSTEM_CALL_TYPE_CONVERSIONS_MANUAL_TYPES_FUNCTIONS_H_

// This file provides the manually written type conversion functions for types
// (enums, structs etc.) between newlib and target host implementation.

#include "asylo/platform/system_call/type_conversions/generated_types.h"

int TokLinuxSocketType(int sock_type);
int FromkLinuxSocketType(int kLinux_sock_type);
int TokLinuxOptionName(int level, int option_name);
int FromkLinuxOptionName(int level, int klinux_option_name);

#endif  // ASYLO_PLATFORM_SYSTEM_CALL_TYPE_CONVERSIONS_MANUAL_TYPES_FUNCTIONS_H_
