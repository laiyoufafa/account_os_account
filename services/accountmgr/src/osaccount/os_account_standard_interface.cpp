/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"){return ERR_OK;}
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
#include "os_account_standard_interface.h"

#include<thread>

#include "ability_manager_client.h"
#include "account_log_wrapper.h"
#include "bundle_mgr_interface.h"
#include "common_event_manager.h"
#include "common_event_support.h"
#include "datetime_ex.h"
#include "if_system_ability_manager.h"
#include "iservice_registry.h"
#include "istorage_manager.h"
#include "os_account_constants.h"
#include "os_account_stop_user_callback.h"
#include "storage_manager.h"
#include "storage_manager_proxy.h"
#include "system_ability_definition.h"
#include "want.h"

namespace OHOS {
namespace AccountSA {
ErrCode OsAccountStandardInterface::SendToAMSAccountStart(OsAccountInfo &osAccountInfo)
{
    ACCOUNT_LOGI("OsAccountStandardInterface SendToAMSAccountStart start");
    ErrCode code = AAFwk::AbilityManagerClient::GetInstance()->StartUser(osAccountInfo.GetLocalId());
    if (code != ERR_OK) {
        ACCOUNT_LOGE("failed to AbilityManagerClient start errcode is %{public}d", code);
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_AM_ACCOUNT_START_ERROR;
    }
    ACCOUNT_LOGI("send AM to start is ok");
    return ERR_OK;
}

ErrCode OsAccountStandardInterface::SendToAMSAccountStop(OsAccountInfo &osAccountInfo)
{
    ACCOUNT_LOGI("OsAccountStandardInterface SendToAMSAccountStop stop");
    sptr<OsAccountStopUserCallback> osAccountStopUserCallback = new OsAccountStopUserCallback();
    ErrCode code =
        AAFwk::AbilityManagerClient::GetInstance()->StopUser(osAccountInfo.GetLocalId(), osAccountStopUserCallback);
    if (code != ERR_OK) {
        ACCOUNT_LOGE("failed to AbilityManagerClient stop errcode is %{public}d", code);
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_AM_ACCOUNT_START_ERROR;
    }
    struct tm startTime = {0};
    struct tm nowTime = {0};
    OHOS::GetSystemCurrentTime(&startTime);
    OHOS::GetSystemCurrentTime(&nowTime);
    while (OHOS::GetSecondsBetween(startTime, nowTime) < Constants::TIME_WAIT_AM_TIME_OUT &&
           !osAccountStopUserCallback->isCallBackOk_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(Constants::WAIT_AM_TIME));
        OHOS::GetSystemCurrentTime(&nowTime);
    }
    if (!osAccountStopUserCallback->isReaturnOk_) {
        ACCOUNT_LOGE("failed to AbilityManagerClient stop in call back");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_AM_ACCOUNT_START_ERROR;
    }
    ACCOUNT_LOGI("send AM to stop is ok");
    return ERR_OK;
}

ErrCode OsAccountStandardInterface::SendToBMSAccountCreate(OsAccountInfo &osAccountInfo)
{
    ACCOUNT_LOGI("OsAccountStandardInterface SendToBMSAccountCreate start");
    sptr<ISystemAbilityManager> systemAbilityManager =
        SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (!systemAbilityManager) {
        ACCOUNT_LOGE("failed to get system ability mgr.");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_BM_ACCOUNT_CREATE_ERROR;
    }

    sptr<IRemoteObject> remoteObject = systemAbilityManager->GetSystemAbility(BUNDLE_MGR_SERVICE_SYS_ABILITY_ID);
    if (!remoteObject) {
        ACCOUNT_LOGE("failed to get bundle manager service.");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_BM_ACCOUNT_CREATE_ERROR;
    }

    auto bunduleMgrProxy = iface_cast<OHOS::AppExecFwk::IBundleMgr>(remoteObject);
    if (!bunduleMgrProxy) {
        ACCOUNT_LOGE("failed to get bunduleMgrProxy");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_BM_ACCOUNT_CREATE_ERROR;
    }
    auto bunduleUserMgrProxy = bunduleMgrProxy->GetBundleUserMgr();
    if (!bunduleUserMgrProxy) {
        ACCOUNT_LOGE("failed to get bunduleUserMgrProxy");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_BM_ACCOUNT_CREATE_ERROR;
    }
    bunduleUserMgrProxy->CreateNewUser(osAccountInfo.GetLocalId());
    ACCOUNT_LOGI("call bm to create user ok");
    return ERR_OK;
}

ErrCode OsAccountStandardInterface::SendToBMSAccountDelete(OsAccountInfo &osAccountInfo)
{
    ACCOUNT_LOGI("OsAccountStandardInterface SendToBMSAccountDelete start");
    sptr<ISystemAbilityManager> systemAbilityManager =
        SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (!systemAbilityManager) {
        ACCOUNT_LOGE("failed to get system ability mgr.");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_BM_ACCOUNT_DELETE_ERROR;
    }

    sptr<IRemoteObject> remoteObject = systemAbilityManager->GetSystemAbility(BUNDLE_MGR_SERVICE_SYS_ABILITY_ID);
    if (!remoteObject) {
        ACCOUNT_LOGE("failed to get bundle manager service.");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_BM_ACCOUNT_DELETE_ERROR;
    }

    auto bunduleMgrProxy = iface_cast<OHOS::AppExecFwk::IBundleMgr>(remoteObject);
    if (!bunduleMgrProxy) {
        ACCOUNT_LOGE("failed to get bunduleMgrProxy");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_BM_ACCOUNT_DELETE_ERROR;
    }
    auto bunduleUserMgrProxy = bunduleMgrProxy->GetBundleUserMgr();
    if (!bunduleUserMgrProxy) {
        ACCOUNT_LOGE("failed to get bunduleUserMgrProxy");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_BM_ACCOUNT_DELETE_ERROR;
    }
    bunduleUserMgrProxy->RemoveUser(osAccountInfo.GetLocalId());
    ACCOUNT_LOGI("call bm to remove user ok");
    return ERR_OK;
}

ErrCode OsAccountStandardInterface::SendToCESAccountCreate(OsAccountInfo &osAccountInfo)
{
    OHOS::AAFwk::Want want;
    want.SetAction(OHOS::EventFwk::CommonEventSupport::COMMON_EVENT_USER_ADDED);
    OHOS::EventFwk::CommonEventData data;
    data.SetCode(osAccountInfo.GetLocalId());
    data.SetWant(want);
    if (!OHOS::EventFwk::CommonEventManager::PublishCommonEvent(data)) {
        ACCOUNT_LOGE("SendToCESAccountCreate PublishCommonEvent failed!");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_CE_ACCOUNT_CREATE_ERROR;
    }
    ACCOUNT_LOGI("SendToCESAccountCreate PublishCommonEvent succeed!");
    return ERR_OK;
}

ErrCode OsAccountStandardInterface::SendToCESAccountDelete(OsAccountInfo &osAccountInfo)
{
    OHOS::AAFwk::Want want;
    want.SetAction(OHOS::EventFwk::CommonEventSupport::COMMON_EVENT_USER_REMOVED);
    OHOS::EventFwk::CommonEventData data;
    data.SetCode(osAccountInfo.GetLocalId());
    data.SetWant(want);
    if (!OHOS::EventFwk::CommonEventManager::PublishCommonEvent(data)) {
        ACCOUNT_LOGE("SendToCESAccountDelete PublishCommonEvent failed!");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_CE_ACCOUNT_DELETE_ERROR;
    }
    ACCOUNT_LOGI("SendToCESAccountDelete PublishCommonEvent succeed!");
    return ERR_OK;
}

ErrCode OsAccountStandardInterface::SendToCESAccountSwithced(OsAccountInfo &osAccountInfo)
{
    OHOS::AAFwk::Want want;
    want.SetAction(OHOS::EventFwk::CommonEventSupport::COMMON_EVENT_USER_SWITCHED);
    OHOS::EventFwk::CommonEventData data;
    data.SetCode(osAccountInfo.GetLocalId());
    data.SetWant(want);
    if (!OHOS::EventFwk::CommonEventManager::PublishCommonEvent(data)) {
        ACCOUNT_LOGE("SendToCESAccountSwithced PublishCommonEvent failed!");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_CE_ACCOUNT_SWITCHED_ERROR;
    }
    ACCOUNT_LOGI("SendToCESAccountSwithced PublishCommonEvent succeed!");
        return ERR_OK;
}

ErrCode OsAccountStandardInterface::SendToStorageAccountCreate(OsAccountInfo &osAccountInfo)
{
    ACCOUNT_LOGI("OsAccountStandardInterface SendToStorageAccountCreate start");
    auto systemAbilityManager = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (!systemAbilityManager) {
        ACCOUNT_LOGE("failed to get system ability mgr.");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_STORAGE_ACCOUNT_CREATE_ERROR;
    }
    auto remote = systemAbilityManager->GetSystemAbility(STORAGE_MANAGER_MANAGER_ID);
    if (!remote) {
        ACCOUNT_LOGE("failed to get STORAGE_MANAGER_MANAGER_ID service.");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_STORAGE_ACCOUNT_CREATE_ERROR;
    }
    auto proxy = iface_cast<StorageManager::IStorageManager>(remote);
    if (!proxy) {
        ACCOUNT_LOGE("failed to get STORAGE_MANAGER_MANAGER_ID proxy.");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_STORAGE_ACCOUNT_CREATE_ERROR;
    }
    int err = proxy->PrepareAddUser(osAccountInfo.GetLocalId());
    ACCOUNT_LOGI("PrepareAddUser code is %{public}d", err);
    ACCOUNT_LOGI("OsAccountStandardInterface PrepareAddUser succeed");
    return ERR_OK;
}

ErrCode OsAccountStandardInterface::SendToStorageAccountRemove(OsAccountInfo &osAccountInfo)
{
    ACCOUNT_LOGI("OsAccountStandardInterface SendToStorageAccountRemove start");
    auto systemAbilityManager = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (!systemAbilityManager) {
        ACCOUNT_LOGE("failed to get system ability mgr.");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_STORAGE_ACCOUNT_REMOVE_ERROR;
    }
    auto remote = systemAbilityManager->GetSystemAbility(STORAGE_MANAGER_MANAGER_ID);
    if (!remote) {
        ACCOUNT_LOGE("failed to get STORAGE_MANAGER_MANAGER_ID service.");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_STORAGE_ACCOUNT_REMOVE_ERROR;
    }
    auto proxy = iface_cast<StorageManager::IStorageManager>(remote);
    if (!proxy) {
        ACCOUNT_LOGE("failed to get STORAGE_MANAGER_MANAGER_ID proxy.");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_STORAGE_ACCOUNT_REMOVE_ERROR;
    }
    int err = proxy->RemoveUser(osAccountInfo.GetLocalId());
    ACCOUNT_LOGI("RemoveUser code is %{public}d", err);
    ACCOUNT_LOGI("OsAccountStandardInterface RemoveUser succeed");
    return ERR_OK;
}

ErrCode OsAccountStandardInterface::SendToStorageAccountStart(OsAccountInfo &osAccountInfo)
{
    ACCOUNT_LOGI("OsAccountStandardInterface SendToStorageAccountStart start");
    auto systemAbilityManager = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (!systemAbilityManager) {
        ACCOUNT_LOGE("failed to get system ability mgr.");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_STORAGE_ACCOUNT_START_ERROR;
    }
    auto remote = systemAbilityManager->GetSystemAbility(STORAGE_MANAGER_MANAGER_ID);
    if (!remote) {
        ACCOUNT_LOGE("failed to get STORAGE_MANAGER_MANAGER_ID service.");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_STORAGE_ACCOUNT_START_ERROR;
    }
    auto proxy = iface_cast<StorageManager::IStorageManager>(remote);
    if (!proxy) {
        ACCOUNT_LOGE("failed to get STORAGE_MANAGER_MANAGER_ID proxy.");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_STORAGE_ACCOUNT_START_ERROR;
    }
    int err = proxy->PrepareStartUser(osAccountInfo.GetLocalId());
    ACCOUNT_LOGI("PrepareStartUser code is %{public}d", err);
    ACCOUNT_LOGI("OsAccountStandardInterface PrepareStartUser succeed");
    return ERR_OK;
}

ErrCode OsAccountStandardInterface::SendToStorageAccountStop(OsAccountInfo &osAccountInfo)
{
    ACCOUNT_LOGI("OsAccountStandardInterface SendToStorageAccountStop start");
    auto systemAbilityManager = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (!systemAbilityManager) {
        ACCOUNT_LOGE("failed to get system ability mgr.");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_STORAGE_ACCOUNT_STOP_ERROR;
    }
    auto remote = systemAbilityManager->GetSystemAbility(STORAGE_MANAGER_MANAGER_ID);
    if (!remote) {
        ACCOUNT_LOGE("failed to get STORAGE_MANAGER_MANAGER_ID service.");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_STORAGE_ACCOUNT_STOP_ERROR;
    }
    auto proxy = iface_cast<StorageManager::IStorageManager>(remote);
    if (!proxy) {
        ACCOUNT_LOGE("failed to get STORAGE_MANAGER_MANAGER_ID proxy.");
        return ERR_OS_ACCOUNT_SERVICE_INTERFACE_TO_STORAGE_ACCOUNT_STOP_ERROR;
    }
    int err = proxy->StopUser(osAccountInfo.GetLocalId());
    ACCOUNT_LOGI("StopUser code is %{public}d", err);
    ACCOUNT_LOGI("OsAccountStandardInterface StopUser succeed");
    return ERR_OK;
}
}  // namespace AccountSA
}  // namespace OHOS
