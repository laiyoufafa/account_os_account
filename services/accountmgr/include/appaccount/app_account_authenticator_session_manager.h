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

#ifndef OS_ACCOUNT_SERVICES_ACCOUNTMGR_INCLUDE_APPACCOUNT_APP_ACCOUNT_AUTHENTICATOR_SESSION_MANAGER_H
#define OS_ACCOUNT_SERVICES_ACCOUNTMGR_INCLUDE_APPACCOUNT_APP_ACCOUNT_AUTHENTICATOR_SESSION_MANAGER_H

#include "application_state_observer_stub.h"
#include "app_account_common.h"
#include "app_mgr_interface.h"
#include "app_mgr_proxy.h"
#include "iapp_account_authenticator_callback.h"
#include "iremote_object.h"
#include "singleton.h"
#include "want_params.h"

namespace OHOS {
namespace AccountSA {
class AppAccountAuthenticatorSession;
class AppAccountAuthenticatorSessionManager;

class SessionAppStateObserver : public AppExecFwk::ApplicationStateObserverStub {
public:
    explicit SessionAppStateObserver(AppAccountAuthenticatorSessionManager *sessionManager);
    virtual ~SessionAppStateObserver() = default;
    
    void OnAbilityStateChanged(const AppExecFwk::AbilityStateData &abilityStateData) override;
    void SetSessionManager(AppAccountAuthenticatorSessionManager *sessionManager);

private:
    AppAccountAuthenticatorSessionManager *sessionManager_;
};

class AppAccountAuthenticatorSessionManager : public DelayedSingleton<AppAccountAuthenticatorSessionManager> {
public:
    AppAccountAuthenticatorSessionManager();
    virtual ~AppAccountAuthenticatorSessionManager();

    ErrCode AddAccountImplicitly(const OAuthRequest &request);
    ErrCode Authenticate(const OAuthRequest &request);
    ErrCode GetAuthenticatorCallback(const OAuthRequest &request, sptr<IRemoteObject> &callback);
    void OnAbilityStateChanged(const AppExecFwk::AbilityStateData &abilityStateData);
    void Init();
    void CloseSession(const std::string &sessionId);
    ErrCode OpenSession(const std::string &action, const OAuthRequest &request);

private:
    std::mutex mutex_;
    sptr<AppExecFwk::IAppMgr> iAppMgr_;
    sptr<SessionAppStateObserver> appStateObserver_;
    std::map<std::string, std::shared_ptr<AppAccountAuthenticatorSession>> sessionMap_;
    std::map<std::string, std::set<std::string>> abilitySessions_;
    bool isInitialized_ = false;
};
}  // namespace AccountSA
}  // namespace OHOS

#endif  // OS_ACCOUNT_SERVICES_ACCOUNTMGR_INCLUDE_APPACCOUNT_APP_ACCOUNT_AUTHENTICATOR_SESSION_MANAGER_H
