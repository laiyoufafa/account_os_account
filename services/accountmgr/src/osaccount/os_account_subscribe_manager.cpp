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

#include "account_log_wrapper.h"
#include "ios_account_event.h"
#include "os_account_subscribe_death_recipient.h"

#include "os_account_subscribe_manager.h"

namespace OHOS {
namespace AccountSA {
OsAccountSubscribeManager::OsAccountSubscribeManager()
    : subscribeDeathRecipient_(sptr<IRemoteObject::DeathRecipient>(new OsAccountSubscribeDeathRecipient()))
{}

OsAccountSubscribeManager::~OsAccountSubscribeManager()
{}

ErrCode OsAccountSubscribeManager::SubscribeOsAccount(
    const std::shared_ptr<OsAccountSubscribeInfo> &subscribeInfoPtr, const sptr<IRemoteObject> &eventListener)
{
    if (subscribeInfoPtr == nullptr) {
        ACCOUNT_LOGE("subscribeInfoPtr is nullptr");
        return ERR_APPACCOUNT_SERVICE_SUBSCRIBE_INFO_PTR_IS_NULLPTR;
    }

    if (eventListener == nullptr) {
        ACCOUNT_LOGE("eventListener is nullptr");
        return ERR_APPACCOUNT_SERVICE_EVENT_LISTENER_IS_NULLPTR;
    }
    auto subscribeRecordPtr = std::make_shared<OsSubscribeRecord>(subscribeInfoPtr, eventListener);
    if (subscribeRecordPtr == nullptr) {
        ACCOUNT_LOGE("subscribeRecordPtr is nullptr");
        return ERR_APPACCOUNT_SERVICE_SUBSCRIBE_RECORD_PTR_IS_NULLPTR;
    }
    if (subscribeDeathRecipient_ != nullptr) {
        eventListener->AddDeathRecipient(subscribeDeathRecipient_);
    }
    subscribeRecordPtr->subscribeInfoPtr_ = subscribeInfoPtr;
    subscribeRecordPtr->eventListener_ = eventListener;
    return InsertSubscribeRecord(subscribeRecordPtr);
}

ErrCode OsAccountSubscribeManager::UnsubscribeOsAccount(const sptr<IRemoteObject> &eventListener)
{
    if (eventListener == nullptr) {
        ACCOUNT_LOGE("eventListener is nullptr");
        return ERR_APPACCOUNT_SERVICE_EVENT_LISTENER_IS_NULLPTR;
    }

    if (subscribeDeathRecipient_ != nullptr) {
        eventListener->RemoveDeathRecipient(subscribeDeathRecipient_);
    }

    return RemoveSubscribeRecord(eventListener);
}

ErrCode OsAccountSubscribeManager::InsertSubscribeRecord(const OsSubscribeRecordPtr &subscribeRecordPtr)
{
    if (subscribeRecordPtr == nullptr) {
        ACCOUNT_LOGE("subscribeRecordPtr is nullptr");
        return ERR_APPACCOUNT_SERVICE_SUBSCRIBE_RECORD_PTR_IS_NULLPTR;
    }

    std::lock_guard<std::mutex> lock(subscribeRecordMutex_);

    subscribeRecords_.emplace_back(subscribeRecordPtr);

    return ERR_OK;
}

ErrCode OsAccountSubscribeManager::RemoveSubscribeRecord(const sptr<IRemoteObject> &eventListener)
{
    if (eventListener == nullptr) {
        ACCOUNT_LOGE("eventListener is nullptr");
        return ERR_APPACCOUNT_SERVICE_EVENT_LISTENER_IS_NULLPTR;
    }

    std::lock_guard<std::mutex> lock(subscribeRecordMutex_);

    for (auto it = subscribeRecords_.begin(); it != subscribeRecords_.end(); ++it) {
        if (eventListener == (*it)->eventListener_) {
            (*it)->eventListener_ = nullptr;
            subscribeRecords_.erase(it);
            break;
        }
    }

    return ERR_OK;
}

ErrCode OsAccountSubscribeManager::GetEventHandler(void)
{
    if (!handler_) {
        handler_ = std::make_shared<OHOS::AppExecFwk::EventHandler>(OHOS::AppExecFwk::EventRunner::Create());
        if (handler_ == nullptr) {
            ACCOUNT_LOGE("failed to create event handler");
            return ERR_OSACCOUNT_SERVICE_CREATE_EVENT_HANDLER;
        }
    }

    return ERR_OK;
}

ErrCode OsAccountSubscribeManager::PublicActivatedOsAccount(const int id)
{
    if (GetEventHandler() != ERR_OK) {
        ACCOUNT_LOGE("failed to get event handler");
        return ERR_OS_ACCOUNT_SERVICE_SUBSCRIBE_GET_EVENT_HANDLE_ERROR;
    }
    for (auto it = subscribeRecords_.begin(); it != subscribeRecords_.end(); ++it) {
        OS_ACCOUNT_SUBSCRIBE_TYPE osAccountSubscribeType;
        if ((*it)->subscribeInfoPtr_ == nullptr) {
            ACCOUNT_LOGI("OsAccountSubscribeManager PublicActivatedOsAccount subscribeInfoPtr_ is null");
        }
        (*it)->subscribeInfoPtr_->GetOsAccountSubscribeType(osAccountSubscribeType);
        if (osAccountSubscribeType == OS_ACCOUNT_SUBSCRIBE_TYPE::ACTIVED) {
            OHOS::AppExecFwk::InnerEvent::Callback callback =
                std::bind(&OsAccountSubscribeManager::OnAccountsChanged, this, (*it), id);
            if (handler_ == nullptr) {
                ACCOUNT_LOGI("OsAccountSubscribeManager PublicActivatedOsAccount handler_ is null");
            }
            handler_->PostTask(callback);
        }
    }
    return ERR_OK;
}

bool OsAccountSubscribeManager::OnAccountsChanged(const OsSubscribeRecordPtr &osSubscribeRecordPtr, const int id)
{
    auto osAccountEventProxy = iface_cast<IOsAccountEvent>(osSubscribeRecordPtr->eventListener_);
    if (osAccountEventProxy == nullptr) {
        ACCOUNT_LOGE("failed to get app account event proxy");
        return false;
    }
    if (GetEventHandler() != ERR_OK) {
        ACCOUNT_LOGE("failed to get event handler");
        return false;
    }
    osAccountEventProxy->OnAccountsChanged(id);
    return true;
}

ErrCode OsAccountSubscribeManager::PublicActivatingOsAccount(const int id)
{
    if (GetEventHandler() != ERR_OK) {
        ACCOUNT_LOGE("failed to get event handler");
        return ERR_OS_ACCOUNT_SERVICE_SUBSCRIBE_GET_EVENT_HANDLE_ERROR;
    }
    for (auto it = subscribeRecords_.begin(); it != subscribeRecords_.end(); ++it) {
        OS_ACCOUNT_SUBSCRIBE_TYPE osAccountSubscribeType;
        (*it)->subscribeInfoPtr_->GetOsAccountSubscribeType(osAccountSubscribeType);
        if (osAccountSubscribeType == OS_ACCOUNT_SUBSCRIBE_TYPE::ACTIVATING) {
            OHOS::AppExecFwk::InnerEvent::Callback callback =
                std::bind(&OsAccountSubscribeManager::OnAccountsChanged, this, (*it), id);

            handler_->PostTask(callback);
        }
    }
    return ERR_OK;
}
}  // namespace AccountSA
}  // namespace OHOS
