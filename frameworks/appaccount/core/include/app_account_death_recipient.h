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

#ifndef APP_ACCOUNT_FRAMEWORKS_APPACCOUNT_CORE_INCLUDE_APP_ACCOUNT_DEATH_RECIPIENT_H
#define APP_ACCOUNT_FRAMEWORKS_APPACCOUNT_CORE_INCLUDE_APP_ACCOUNT_DEATH_RECIPIENT_H

#include "iremote_object.h"

namespace OHOS {
namespace AccountSA {
class AppAccountDeathRecipient : public IRemoteObject::DeathRecipient {
public:
    AppAccountDeathRecipient() = default;
    virtual ~AppAccountDeathRecipient() = default;

    virtual void OnRemoteDied(const wptr<IRemoteObject> &remote);
};
}  // namespace AccountSA
}  // namespace OHOS

#endif  // APP_ACCOUNT_FRAMEWORKS_APPACCOUNT_CORE_INCLUDE_APP_ACCOUNT_DEATH_RECIPIENT_H
