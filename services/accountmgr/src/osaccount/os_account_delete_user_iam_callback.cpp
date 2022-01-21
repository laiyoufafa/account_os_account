/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
#include "os_account_delete_user_iam_callback.h"
#include "account_error_no.h"
#include "account_log_wrapper.h"
#include "os_account_manager.h"

namespace OHOS {
namespace AccountSA {
void OsAccountDeleteUserIamCallback::OnResult(int32_t result, UserIAM::UserIDM::RequestResult reqRet)
{
    ACCOUNT_LOGI("IAM OnResult callback! result %{public}d", result);
    isIamOnResultCallBack_ = true;
}

void OsAccountDeleteUserIamCallback::OnAcquireInfo(int32_t module, int32_t acquire,
    UserIAM::UserIDM::RequestResult reqRet)
{
    ACCOUNT_LOGI("IAM OnAcquireInfo callback! module %{public}d, acquire %{public}d.", module, acquire);
}
}  // namespace AccountSA
}  // namespace OHOS