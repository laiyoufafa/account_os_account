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

#include "app_account_manager.h"

#include "account_log_wrapper.h"
#include "app_account.h"
#include "singleton.h"

namespace OHOS {
namespace AccountSA {
ErrCode AppAccountManager::AddAccount(const std::string &name, const std::string &extraInfo)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->AddAccount(name, extraInfo);
}

ErrCode AppAccountManager::AddAccountImplicitly(const std::string &owner, const std::string &authType,
    const AAFwk::Want &options, const sptr<IAppAccountAuthenticatorCallback> &callback)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->AddAccountImplicitly(
        owner, authType, options, callback);
}

ErrCode AppAccountManager::DeleteAccount(const std::string &name)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->DeleteAccount(name);
}

ErrCode AppAccountManager::GetAccountExtraInfo(const std::string &name, std::string &extraInfo)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->GetAccountExtraInfo(name, extraInfo);
}

ErrCode AppAccountManager::SetAccountExtraInfo(const std::string &name, const std::string &extraInfo)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->SetAccountExtraInfo(name, extraInfo);
}

ErrCode AppAccountManager::EnableAppAccess(const std::string &name, const std::string &authorizedApp)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->EnableAppAccess(name, authorizedApp);
}

ErrCode AppAccountManager::DisableAppAccess(const std::string &name, const std::string &authorizedApp)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->DisableAppAccess(name, authorizedApp);
}

ErrCode AppAccountManager::CheckAppAccountSyncEnable(const std::string &name, bool &syncEnable)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->CheckAppAccountSyncEnable(name, syncEnable);
}

ErrCode AppAccountManager::SetAppAccountSyncEnable(const std::string &name, const bool &syncEnable)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->SetAppAccountSyncEnable(name, syncEnable);
}

ErrCode AppAccountManager::GetAssociatedData(const std::string &name, const std::string &key, std::string &value)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->GetAssociatedData(name, key, value);
}

ErrCode AppAccountManager::SetAssociatedData(const std::string &name, const std::string &key, const std::string &value)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->SetAssociatedData(name, key, value);
}

ErrCode AppAccountManager::GetAccountCredential(
    const std::string &name, const std::string &credentialType, std::string &credential)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->GetAccountCredential(name, credentialType, credential);
}

ErrCode AppAccountManager::SetAccountCredential(
    const std::string &name, const std::string &credentialType, const std::string &credential)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->SetAccountCredential(name, credentialType, credential);
}

ErrCode AppAccountManager::Authenticate(const std::string &name, const std::string &owner,
    const std::string &authType, const AAFwk::Want &options, const sptr<IAppAccountAuthenticatorCallback> &callback)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->Authenticate(name, owner, authType, options, callback);
}

ErrCode AppAccountManager::GetOAuthToken(
    const std::string &name, const std::string &owner, const std::string &authType, std::string &token)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->GetOAuthToken(name, owner, authType, token);
}

ErrCode AppAccountManager::SetOAuthToken(
    const std::string &name, const std::string &authType, const std::string &token)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->SetOAuthToken(name, authType, token);
}

ErrCode AppAccountManager::DeleteOAuthToken(
    const std::string &name, const std::string &owner, const std::string &authType, const std::string &token)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->DeleteOAuthToken(name, owner, authType, token);
}

ErrCode AppAccountManager::SetOAuthTokenVisibility(
    const std::string &name, const std::string &authType, const std::string &bundleName, bool isVisible)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->SetOAuthTokenVisibility(
        name, authType, bundleName, isVisible);
}

ErrCode AppAccountManager::CheckOAuthTokenVisibility(
    const std::string &name, const std::string &authType, const std::string &bundleName, bool &isVisible)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->CheckOAuthTokenVisibility(
        name, authType, bundleName, isVisible);
}

ErrCode AppAccountManager::GetAuthenticatorInfo(const std::string &owner, AuthenticatorInfo &info)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->GetAuthenticatorInfo(owner, info);
}

ErrCode AppAccountManager::GetAllOAuthTokens(
    const std::string &name, const std::string &owner, std::vector<OAuthTokenInfo> &tokenInfos)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->GetAllOAuthTokens(name, owner, tokenInfos);
}

ErrCode AppAccountManager::GetOAuthList(
    const std::string &name, const std::string &authType, std::set<std::string> &oauthList)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->GetOAuthList(name, authType, oauthList);
}

ErrCode AppAccountManager::GetAuthenticatorCallback(const std::string &sessionId, sptr<IRemoteObject> &callback)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->GetAuthenticatorCallback(sessionId, callback);
}

ErrCode AppAccountManager::GetAllAccounts(const std::string &owner, std::vector<AppAccountInfo> &appAccounts)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->GetAllAccounts(owner, appAccounts);
}

ErrCode AppAccountManager::GetAllAccessibleAccounts(std::vector<AppAccountInfo> &appAccounts)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->GetAllAccessibleAccounts(appAccounts);
}

ErrCode AppAccountManager::SubscribeAppAccount(const std::shared_ptr<AppAccountSubscriber> &subscriber)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->SubscribeAppAccount(subscriber);
}

ErrCode AppAccountManager::UnsubscribeAppAccount(const std::shared_ptr<AppAccountSubscriber> &subscriber)
{
    ACCOUNT_LOGI("enter");

    return DelayedSingleton<AppAccount>::GetInstance()->UnsubscribeAppAccount(subscriber);
}
}  // namespace AccountSA
}  // namespace OHOS
