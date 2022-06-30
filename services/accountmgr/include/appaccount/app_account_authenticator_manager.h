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

#ifndef OS_ACCOUNT_SERVICES_ACCOUNTMGR_INCLUDE_APPACCOUNT_APP_ACCOUNT_AUTHENTICATOR_MANAGER_H
#define OS_ACCOUNT_SERVICES_ACCOUNTMGR_INCLUDE_APPACCOUNT_APP_ACCOUNT_AUTHENTICATOR_MANAGER_H

#include "account_error_no.h"
#include "app_account_common.h"
#include "singleton.h"

namespace OHOS {
namespace AccountSA {
class AppAccountAuthenticatorManager : public DelayedSingleton<AppAccountAuthenticatorManager> {
public:
    AppAccountAuthenticatorManager();
    virtual ~AppAccountAuthenticatorManager();
    ErrCode GetAuthenticatorInfo(const std::string &owner, int32_t userId, AuthenticatorInfo &info);

private:
    void Init();

private:
    bool isInitialized_ = false;
};
}  // namespace AccountSA
}  // namespace OHOS

#endif  // OS_ACCOUNT_SERVICES_ACCOUNTMGR_INCLUDE_APPACCOUNT_APP_ACCOUNT_AUTHENTICATOR_MANAGER_H
