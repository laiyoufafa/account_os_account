/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
 */
#include "hitrace_adapter.h"
#ifdef HAS_HITRACE_PART
#include "hitrace_meter.h"
#endif // HAS_HITRACE_PART

namespace OHOS {
namespace AccountSA {
void InitHiTrace()
{
#ifdef HAS_HITRACE_PART
    UpdateTraceLabel();
#endif // HAS_HITRACE_PART
}

void StartSyncTrace(const std::string& value)
{
#ifdef HAS_HITRACE_PART
    StartTrace(HITRACE_TAG_ACCOUNT_MANAGER, value);
#else // HAS_HITRACE_PART
    (void)value;
#endif // HAS_HITRACE_PART
}

void EndSyncTrace()
{
#ifdef HAS_HITRACE_PART
    FinishTrace(HITRACE_TAG_ACCOUNT_MANAGER);
#endif // HAS_HITRACE_PART
}

void ValueTrace(const std::string& name, int64_t count)
{
#ifdef HAS_HITRACE_PART
    CountTrace(HITRACE_TAG_ACCOUNT_MANAGER, name, count);
#else // HAS_HITRACE_PART
    (void)name;
    (void)count;
#endif // HAS_HITRACE_PART
}
} // AccountSA
} // OHOS
