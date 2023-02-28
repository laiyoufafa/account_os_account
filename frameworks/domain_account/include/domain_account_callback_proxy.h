/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef OS_ACCOUNT_INTERFACES_INNERKITS_DOMAIN_ACCOUNT_INCLUDE_DOMAIN_ACCOUNT_CALLBACK_PROXY_H
#define OS_ACCOUNT_INTERFACES_INNERKITS_DOMAIN_ACCOUNT_INCLUDE_DOMAIN_ACCOUNT_CALLBACK_PROXY_H

#include "idomain_account_callback.h"
#include "iremote_proxy.h"

namespace OHOS {
namespace AccountSA {
class DomainAccountCallbackProxy : public IRemoteProxy<IDomainAccountCallback> {
public:
    explicit DomainAccountCallbackProxy(const sptr<IRemoteObject> &object);
    ~DomainAccountCallbackProxy();
    void OnResult(const int32_t errCode, Parcel &parcel) override;

private:
    ErrCode SendRequest(IDomainAccountCallback::Message code, MessageParcel &data);

private:
    static inline BrokerDelegator<DomainAccountCallbackProxy> delegator_;
};
}  // namespace AccountSA
}  // namespace OHOS
#endif  // OS_ACCOUNT_INTERFACES_INNERKITS_DOMAIN_ACCOUNT_INCLUDE_DOMAIN_ACCOUNT_CALLBACK_PROXY_H