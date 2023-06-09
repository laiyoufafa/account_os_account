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

#ifndef OS_ACCOUNT_INTERFACES_KITS_NAPI_APPACCOUNT_INCLUDE_NAPI_APP_ACCOUNT_H
#define OS_ACCOUNT_INTERFACES_KITS_NAPI_APPACCOUNT_INCLUDE_NAPI_APP_ACCOUNT_H

#include "napi/native_api.h"

namespace OHOS {
namespace AccountJsKit {
static thread_local napi_ref appAccountRef_ = nullptr;
class NapiAppAccount {
public:
    static napi_value Init(napi_env env, napi_value exports);

private:
    static napi_value CreateAppAccountManager(napi_env env, napi_callback_info cbInfo);
    static napi_value AddAccount(napi_env env, napi_callback_info cbInfo);
    static napi_value AddAccountImplicitly(napi_env env, napi_callback_info cbInfo);
    static napi_value DeleteAccount(napi_env env, napi_callback_info cbInfo);
    static napi_value DisableAppAccess(napi_env env, napi_callback_info cbInfo);
    static napi_value EnableAppAccess(napi_env env, napi_callback_info cbInfo);
    static napi_value CheckAppAccountSyncEnable(napi_env env, napi_callback_info cbInfo);
    static napi_value SetAccountCredential(napi_env env, napi_callback_info cbInfo);
    static napi_value SetAccountExtraInfo(napi_env env, napi_callback_info cbInfo);
    static napi_value SetAppAccountSyncEnable(napi_env env, napi_callback_info cbInfo);
    static napi_value SetAssociatedData(napi_env env, napi_callback_info cbInfo);
    static napi_value GetAllAccessibleAccounts(napi_env env, napi_callback_info cbInfo);
    static napi_value GetAllAccounts(napi_env env, napi_callback_info cbInfo);
    static napi_value GetAccountCredential(napi_env env, napi_callback_info cbInfo);
    static napi_value GetAccountExtraInfo(napi_env env, napi_callback_info cbInfo);
    static napi_value GetAssociatedData(napi_env env, napi_callback_info cbInfo);
    static napi_value Authenticate(napi_env env, napi_callback_info cbInfo);
    static napi_value GetOAuthToken(napi_env env, napi_callback_info cbInfo);
    static napi_value SetOAuthToken(napi_env env, napi_callback_info cbInfo);
    static napi_value DeleteOAuthToken(napi_env env, napi_callback_info cbInfo);
    static napi_value SetOAuthTokenVisibility(napi_env env, napi_callback_info cbInfo);
    static napi_value CheckOAuthTokenVisibility(napi_env env, napi_callback_info cbInfo);
    static napi_value GetAuthenticatorInfo(napi_env env, napi_callback_info cbinfo);
    static napi_value GetAllOAuthTokens(napi_env env, napi_callback_info cbInfo);
    static napi_value GetOAuthList(napi_env env, napi_callback_info cbInfo);
    static napi_value GetAuthenticatorCallback(napi_env env, napi_callback_info cbInfo);
    static napi_value Subscribe(napi_env env, napi_callback_info cbInfo);
    static napi_value Unsubscribe(napi_env env, napi_callback_info cbInfo);
    static napi_value JsConstructor(napi_env env, napi_callback_info cbinfo);
};
}  // namespace AccountJsKit
}  // namespace OHOS

#endif  // OS_ACCOUNT_INTERFACES_KITS_NAPI_APPACCOUNT_INCLUDE_NAPI_APP_ACCOUNT_H
