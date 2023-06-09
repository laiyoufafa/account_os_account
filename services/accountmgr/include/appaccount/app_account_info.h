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

#ifndef OS_ACCOUNT_SERVICES_ACCOUNTMGR_INCLUDE_APPACCOUNT_APP_ACCOUNT_INFO_H
#define OS_ACCOUNT_SERVICES_ACCOUNTMGR_INCLUDE_APPACCOUNT_APP_ACCOUNT_INFO_H

#include <set>

#include "account_error_no.h"
#include "iaccount_info.h"
#include "app_account_constants.h"
#include "parcel.h"

namespace OHOS {
namespace AccountSA {
struct OAuthTokenInfo {
    std::string authType;
    std::string token;
    std::set<std::string> authList;
};

class AppAccountInfo : public IAccountInfo, public Parcelable {
public:
    AppAccountInfo();
    explicit AppAccountInfo(const std::string &name, const std::string &owner);
    virtual ~AppAccountInfo() = default;

    ErrCode GetOwner(std::string &owner);
    ErrCode SetOwner(const std::string &owner);

    ErrCode GetName(std::string &name) const;
    ErrCode SetName(const std::string &name);

    ErrCode GetExtraInfo(std::string &extraInfo) const;
    ErrCode SetExtraInfo(const std::string &extraInfo);

    ErrCode EnableAppAccess(const std::string &authorizedApp);
    ErrCode DisableAppAccess(const std::string &authorizedApp);

    ErrCode GetAuthorizedApps(std::set<std::string> &apps) const;
    ErrCode SetAuthorizedApps(const std::set<std::string> &apps);

    ErrCode GetSyncEnable(bool &syncEnable) const;
    ErrCode SetSyncEnable(const bool &syncEnable);

    ErrCode GetAssociatedData(const std::string &key, std::string &value) const;
    ErrCode SetAssociatedData(const std::string &key, const std::string &value);

    ErrCode GetAccountCredential(const std::string &credentialType, std::string &credential) const;
    ErrCode SetAccountCredential(const std::string &credentialType, const std::string &credential);

    ErrCode GetOAuthToken(const std::string &authType, std::string &token) const;
    ErrCode SetOAuthToken(const std::string &authType, const std::string &token);
    ErrCode DeleteOAuthToken(const std::string &authType, const std::string &token);
    ErrCode SetOAuthTokenVisibility(const std::string &authType, const std::string &bundleName, bool isVisible);
    ErrCode CheckOAuthTokenVisibility(
        const std::string &authType, const std::string &bundleName, bool &isVisible) const;
    ErrCode GetAllOAuthTokens(std::vector<OAuthTokenInfo> &tokenInfos) const;
    ErrCode GetOAuthList(const std::string &authType, std::set<std::string> &oauthList) const;

    bool Marshalling(Parcel &parcel) const override;
    static AppAccountInfo *Unmarshalling(Parcel &parcel);

    Json ToJson() const override;
    void FromJson(const Json &jsonObject) override;
    std::string ToString() const override;
    std::string GetPrimeKey() const override;

private:
    void ParseTokenInfosFromJson(const Json &jsonObject);
    bool ReadFromParcel(Parcel &parcel);

    bool WriteStringSet(const std::set<std::string> &stringSet, Parcel &data) const;
    bool ReadStringSet(std::set<std::string> &stringSet, Parcel &data);
    bool WriteStringMap(const std::map<std::string, std::string> &stringSet, Parcel &data) const;
    bool ReadStringMap(std::map<std::string, std::string> &stringMap, Parcel &data);
    bool WriteTokenInfos(const std::map<std::string, OAuthTokenInfo> &tokenInfos, Parcel &data) const;
    bool ReadTokenInfos(std::map<std::string, OAuthTokenInfo> &tokenInfos, Parcel &data);

private:
    std::string owner_;
    std::string name_;
    std::string extraInfo_;
    std::set<std::string> authorizedApps_;
    bool syncEnable_ = false;
    std::string associatedData_;
    std::string accountCredential_;
    std::map<std::string, OAuthTokenInfo> oauthTokens_;
};
}  // namespace AccountSA
}  // namespace OHOS

#endif  // OS_ACCOUNT_SERVICES_ACCOUNTMGR_INCLUDE_APPACCOUNT_APP_ACCOUNT_INFO_H
