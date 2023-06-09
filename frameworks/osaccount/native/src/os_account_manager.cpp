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
#include "os_account_manager.h"
#include "account_info.h"
#include "account_log_wrapper.h"
#include "os_account.h"
#include "singleton.h"

namespace OHOS {
namespace AccountSA {
ErrCode OsAccountManager::CreateOsAccount(
    const std::string &name, const OsAccountType &type, OsAccountInfo &osAccountInfo)
{
    return DelayedSingleton<OsAccount>::GetInstance()->CreateOsAccount(name, type, osAccountInfo);
}

ErrCode OsAccountManager::CreateOsAccountForDomain(
    const OsAccountType &type, const DomainAccountInfo &domainInfo, OsAccountInfo &osAccountInfo)
{
    return DelayedSingleton<OsAccount>::GetInstance()->CreateOsAccountForDomain(
        type, domainInfo, osAccountInfo);
}

ErrCode OsAccountManager::RemoveOsAccount(const int id)
{
    return DelayedSingleton<OsAccount>::GetInstance()->RemoveOsAccount(id);
}

ErrCode OsAccountManager::IsOsAccountExists(const int id, bool &isOsAccountExists)
{
    ACCOUNT_LOGI("OsAccountManager::IsOsAccountExists start");

    return DelayedSingleton<OsAccount>::GetInstance()->IsOsAccountExists(id, isOsAccountExists);
}

ErrCode OsAccountManager::IsOsAccountActived(const int id, bool &isOsAccountActived)
{
    ACCOUNT_LOGI("OsAccountManager::IsOsAccountActived start");

    return DelayedSingleton<OsAccount>::GetInstance()->IsOsAccountActived(id, isOsAccountActived);
}

ErrCode OsAccountManager::IsOsAccountConstraintEnable(
    const int id, const std::string &constraint, bool &isConstraintEnable)
{
    ACCOUNT_LOGI("OsAccountManager::IsOsAccountConstraintEnable start");

    return DelayedSingleton<OsAccount>::GetInstance()->IsOsAccountConstraintEnable(id, constraint, isConstraintEnable);
}

ErrCode OsAccountManager::IsOsAccountVerified(const int id, bool &isTestOsAccount)
{
    ACCOUNT_LOGI("OsAccountManager::IsOsAccountVerified start");

    return DelayedSingleton<OsAccount>::GetInstance()->IsOsAccountVerified(id, isTestOsAccount);
}

ErrCode OsAccountManager::GetCreatedOsAccountsCount(unsigned int &osAccountsCount)
{
    ACCOUNT_LOGI("OsAccountManager::GetCreatedOsAccountsCount start");

    return DelayedSingleton<OsAccount>::GetInstance()->GetCreatedOsAccountsCount(osAccountsCount);
}

ErrCode OsAccountManager::GetOsAccountLocalIdFromProcess(int &id)
{
    ACCOUNT_LOGI("OsAccountManager::GetOsAccountLocalIdFromProcess start");

    return DelayedSingleton<OsAccount>::GetInstance()->GetOsAccountLocalIdFromProcess(id);
}

ErrCode OsAccountManager::IsMainOsAccount(bool &isMainOsAccount)
{
    ACCOUNT_LOGI("OsAccountManager::IsMainOsAccount start");

    return DelayedSingleton<OsAccount>::GetInstance()->IsMainOsAccount(isMainOsAccount);
}

ErrCode OsAccountManager::GetOsAccountLocalIdFromUid(const int uid, int &id)
{
    if (uid < 0) {
        ACCOUNT_LOGE("invalid uid %{public}d.", uid);
        return ERR_OSACCOUNT_SERVICE_MANAGER_BAD_UID_ERROR;
    }
    id = uid / UID_TRANSFORM_DIVISOR;
    ACCOUNT_LOGI("uid %{public}d, os account id %{public}d.", uid, id);
    return ERR_OK;
}

ErrCode OsAccountManager::GetBundleIdFromUid(const int uid, int &bundleId)
{
    if (uid < 0) {
        ACCOUNT_LOGE("invalid uid %{public}d.", uid);
        return ERR_OSACCOUNT_SERVICE_MANAGER_BAD_UID_ERROR;
    }
    bundleId = uid % UID_TRANSFORM_DIVISOR;
    ACCOUNT_LOGI("uid %{public}d, get bundle id %{public}d.", uid, bundleId);
    return ERR_OK;
}

ErrCode OsAccountManager::GetOsAccountLocalIdFromDomain(const DomainAccountInfo &domainInfo, int &id)
{
    ACCOUNT_LOGI("OsAccountManager::GetOsAccountLocalIdFromDomain start");
    return DelayedSingleton<OsAccount>::GetInstance()->GetOsAccountLocalIdFromDomain(domainInfo, id);
}

ErrCode OsAccountManager::QueryMaxOsAccountNumber(int &maxOsAccountNumber)
{
    ACCOUNT_LOGI("OsAccountManager::QueryMaxOsAccountNumber start");

    return DelayedSingleton<OsAccount>::GetInstance()->QueryMaxOsAccountNumber(maxOsAccountNumber);
}

ErrCode OsAccountManager::GetOsAccountAllConstraints(const int id, std::vector<std::string> &constraints)
{
    ACCOUNT_LOGI("OsAccountManager::GetOsAccountAllConstraints start");

    return DelayedSingleton<OsAccount>::GetInstance()->GetOsAccountAllConstraints(id, constraints);
}

ErrCode OsAccountManager::QueryAllCreatedOsAccounts(std::vector<OsAccountInfo> &osAccountInfos)
{
    ACCOUNT_LOGI("OsAccountManager::QueryAllCreatedOsAccounts start");

    return DelayedSingleton<OsAccount>::GetInstance()->QueryAllCreatedOsAccounts(osAccountInfos);
}

ErrCode OsAccountManager::QueryCurrentOsAccount(OsAccountInfo &osAccountInfo)
{
    ACCOUNT_LOGI("OsAccountManager::QueryCurrentOsAccount start");

    return DelayedSingleton<OsAccount>::GetInstance()->QueryCurrentOsAccount(osAccountInfo);
}

ErrCode OsAccountManager::QueryOsAccountById(const int id, OsAccountInfo &osAccountInfo)
{
    ACCOUNT_LOGI("OsAccountManager::QueryOsAccountById start");

    return DelayedSingleton<OsAccount>::GetInstance()->QueryOsAccountById(id, osAccountInfo);
}

ErrCode OsAccountManager::GetOsAccountTypeFromProcess(OsAccountType &type)
{
    ACCOUNT_LOGI("OsAccountManager::GetOsAccountTypeFromProcess start");

    return DelayedSingleton<OsAccount>::GetInstance()->GetOsAccountTypeFromProcess(type);
}

ErrCode OsAccountManager::GetOsAccountProfilePhoto(const int id, std::string &photo)
{
    ACCOUNT_LOGI("OsAccountManager::GetOsAccountProfilePhoto start");

    return DelayedSingleton<OsAccount>::GetInstance()->GetOsAccountProfilePhoto(id, photo);
}

ErrCode OsAccountManager::IsMultiOsAccountEnable(bool &isMultiOsAccountEnable)
{
    ACCOUNT_LOGI("OsAccountManager::IsMultiOsAccountEnable start");

    return DelayedSingleton<OsAccount>::GetInstance()->IsMultiOsAccountEnable(isMultiOsAccountEnable);
}

ErrCode OsAccountManager::SetOsAccountName(const int id, const std::string &localName)
{
    ACCOUNT_LOGI("OsAccountManager::SetOsAccountName start");

    return DelayedSingleton<OsAccount>::GetInstance()->SetOsAccountName(id, localName);
}

ErrCode OsAccountManager::SetOsAccountConstraints(
    const int id, const std::vector<std::string> &constraints, const bool enable)
{
    ACCOUNT_LOGI("OsAccountManager::SetOsAccountConstraints start");

    return DelayedSingleton<OsAccount>::GetInstance()->SetOsAccountConstraints(id, constraints, enable);
}

ErrCode OsAccountManager::SetOsAccountProfilePhoto(const int id, const std::string &photo)
{
    ACCOUNT_LOGI("OsAccountManager::SetOsAccountProfilePhoto start");

    return DelayedSingleton<OsAccount>::GetInstance()->SetOsAccountProfilePhoto(id, photo);
}

ErrCode OsAccountManager::GetDistributedVirtualDeviceId(std::string &deviceId)
{
    ACCOUNT_LOGI("OsAccountManager::GetDistributedVirtualDeviceId start");

    return DelayedSingleton<OsAccount>::GetInstance()->GetDistributedVirtualDeviceId(deviceId);
}

ErrCode OsAccountManager::ActivateOsAccount(const int id)
{
    ACCOUNT_LOGI("OsAccountManager::ActivateOsAccount start");

    return DelayedSingleton<OsAccount>::GetInstance()->ActivateOsAccount(id);
}

ErrCode OsAccountManager::StartOsAccount(const int id)
{
    ACCOUNT_LOGI("OsAccountManager::StartOsAccount start");

    return DelayedSingleton<OsAccount>::GetInstance()->StartOsAccount(id);
}

ErrCode OsAccountManager::StopOsAccount(const int id)
{
    ACCOUNT_LOGI("OsAccountManager::StopOsAccount start");

    return DelayedSingleton<OsAccount>::GetInstance()->StopOsAccount(id);
}

ErrCode OsAccountManager::GetOsAccountLocalIdBySerialNumber(const int64_t serialNumber, int &id)
{
    ACCOUNT_LOGI("OsAccountManager::StartOsAccount start");

    return DelayedSingleton<OsAccount>::GetInstance()->GetOsAccountLocalIdBySerialNumber(serialNumber, id);
}

ErrCode OsAccountManager::GetSerialNumberByOsAccountLocalId(const int &id, int64_t &serialNumber)
{
    ACCOUNT_LOGI("OsAccountManager::StopOsAccount start");

    return DelayedSingleton<OsAccount>::GetInstance()->GetSerialNumberByOsAccountLocalId(id, serialNumber);
}

ErrCode OsAccountManager::SubscribeOsAccount(const std::shared_ptr<OsAccountSubscriber> &subscriber)
{
    ACCOUNT_LOGI("OsAccountManager::SubscribeOsAccount start");

    return DelayedSingleton<OsAccount>::GetInstance()->SubscribeOsAccount(subscriber);
}

ErrCode OsAccountManager::UnsubscribeOsAccount(const std::shared_ptr<OsAccountSubscriber> &subscriber)
{
    ACCOUNT_LOGI("OsAccountManager::UnsubscribeOsAccount start");

    return DelayedSingleton<OsAccount>::GetInstance()->UnsubscribeOsAccount(subscriber);
}
OS_ACCOUNT_SWITCH_MOD OsAccountManager::GetOsAccountSwitchMod()
{
    ACCOUNT_LOGI("OsAccountManager::GetOsAccountSwitchMod start");
    return DelayedSingleton<OsAccount>::GetInstance()->GetOsAccountSwitchMod();
}

ErrCode OsAccountManager::IsCurrentOsAccountVerified(bool &isVerified)
{
    ACCOUNT_LOGI("OsAccountManager::IsCurrentOsAccountVerified start");
    return DelayedSingleton<OsAccount>::GetInstance()->IsCurrentOsAccountVerified(isVerified);
}

ErrCode OsAccountManager::IsOsAccountCompleted(const int id, bool &isOsAccountCompleted)
{
    ACCOUNT_LOGI("OsAccountManager::IsOsAccountCompleted start");
    return DelayedSingleton<OsAccount>::GetInstance()->IsOsAccountCompleted(id, isOsAccountCompleted);
}

ErrCode OsAccountManager::SetCurrentOsAccountIsVerified(const bool isVerified)
{
    ACCOUNT_LOGI("OsAccountManager::SetCurrentOsAccountIsVerified start");
    return DelayedSingleton<OsAccount>::GetInstance()->SetCurrentOsAccountIsVerified(isVerified);
}

ErrCode OsAccountManager::SetOsAccountIsVerified(const int id, const bool isVerified)
{
    ACCOUNT_LOGI("OsAccountManager::SetOsAccountIsVerified start");
    return DelayedSingleton<OsAccount>::GetInstance()->SetOsAccountIsVerified(id, isVerified);
}

ErrCode OsAccountManager::GetCreatedOsAccountNumFromDatabase(const std::string& storeID, int &createdOsAccountNum)
{
    ACCOUNT_LOGI("OsAccountManager::GetCreatedOsAccountNumFromDatabase start");
    return DelayedSingleton<OsAccount>::GetInstance()->GetCreatedOsAccountNumFromDatabase(
        storeID, createdOsAccountNum);
}

ErrCode OsAccountManager::GetSerialNumberFromDatabase(const std::string& storeID, int64_t &serialNumber)
{
    ACCOUNT_LOGI("OsAccountManager::GetSerialNumberFromDatabase start");
    return DelayedSingleton<OsAccount>::GetInstance()->GetSerialNumberFromDatabase(storeID, serialNumber);
}

ErrCode OsAccountManager::GetMaxAllowCreateIdFromDatabase(const std::string& storeID, int &id)
{
    ACCOUNT_LOGI("OsAccountManager::GetMaxAllowCreateIdFromDatabase start");
    return DelayedSingleton<OsAccount>::GetInstance()->GetMaxAllowCreateIdFromDatabase(storeID, id);
}

ErrCode OsAccountManager::GetOsAccountFromDatabase(const std::string& storeID,
                                                   const int id,
                                                   OsAccountInfo &osAccountInfo)
{
    ACCOUNT_LOGI("OsAccountManager::GetOsAccountFromDatabase start");
    return DelayedSingleton<OsAccount>::GetInstance()->GetOsAccountFromDatabase(storeID, id, osAccountInfo);
}

ErrCode OsAccountManager::GetOsAccountListFromDatabase(const std::string& storeID,
                                                       std::vector<OsAccountInfo> &osAccountList)
{
    ACCOUNT_LOGI("OsAccountManager::GetOsAccountListFromDatabase start");
    return DelayedSingleton<OsAccount>::GetInstance()->GetOsAccountListFromDatabase(storeID, osAccountList);
}

ErrCode OsAccountManager::QueryActiveOsAccountIds(std::vector<int32_t>& ids)
{
    ACCOUNT_LOGI("OsAccountManager::QueryActiveOsAccountIds start");
    return DelayedSingleton<OsAccount>::GetInstance()->QueryActiveOsAccountIds(ids);
}
}  // namespace AccountSA
}  // namespace OHOS
