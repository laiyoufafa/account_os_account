/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "account_log_wrapper.h"

#include "permission_kit.h"

using namespace OHOS::AccountSA;

namespace OHOS {
namespace Security {
namespace Permission {
int PermissionKit::VerifyPermission(const std::string &permissionName)
{
    ACCOUNT_LOGI("permissionName = %{public}s", permissionName.c_str());

    return PermissionState::PERMISSION_GRANTED;
}
}  // namespace Permission
}  // namespace Security
}  // namespace OHOS
