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

#include "app_account_authenticator_callback_proxy.h"

#include "account_error_no.h"
#include "account_log_wrapper.h"

namespace OHOS {
namespace AccountSA {
AppAccountAuthenticatorCallbackProxy::AppAccountAuthenticatorCallbackProxy(const sptr<IRemoteObject> &object)
    : IRemoteProxy<IAppAccountAuthenticatorCallback>(object)
{
    ACCOUNT_LOGI("enter");
}

AppAccountAuthenticatorCallbackProxy::~AppAccountAuthenticatorCallbackProxy()
{
    ACCOUNT_LOGI("enter");
}

void AppAccountAuthenticatorCallbackProxy::OnResult(int32_t resultCode, const AAFwk::Want &result)
{
    ACCOUNT_LOGI("enter");
    MessageParcel data;
    MessageParcel reply;

    if (!data.WriteInterfaceToken(GetDescriptor())) {
        ACCOUNT_LOGE("failed to write descriptor!");
        return;
    }

    if (!data.WriteInt32(resultCode)) {
        ACCOUNT_LOGE("failed to write resultCode");
        return;
    }
    if (!data.WriteParcelable(&result)) {
        ACCOUNT_LOGE("failed to write result");
        return;
    }
    SendRequest(IAppAccountAuthenticatorCallback::Message::ACCOUNT_RESULT, data, reply);
}

void AppAccountAuthenticatorCallbackProxy::OnRequestRedirected(AAFwk::Want &request)
{
    ACCOUNT_LOGI("enter");
    MessageParcel data;
    MessageParcel reply;

    if (!data.WriteInterfaceToken(GetDescriptor())) {
        ACCOUNT_LOGE("failed to write descriptor!");
        return;
    }

    if (!data.WriteParcelable(&request)) {
        ACCOUNT_LOGE("failed to write request");
        return;
    }
    SendRequest(IAppAccountAuthenticatorCallback::Message::ACCOUNT_REQUEST_REDIRECTED, data, reply);
}

ErrCode AppAccountAuthenticatorCallbackProxy::SendRequest(
    IAppAccountAuthenticatorCallback::Message code, MessageParcel &data, MessageParcel &reply)
{
    ACCOUNT_LOGI("enter");
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        ACCOUNT_LOGE("remote is nullptr, code = %{public}d", code);
        return ERR_APPACCOUNT_KIT_REMOTE_IS_NULLPTR;
    }
    MessageOption option(MessageOption::TF_SYNC);
    int32_t result = remote->SendRequest(static_cast<uint32_t>(code), data, reply, option);
    if (result != ERR_OK) {
        ACCOUNT_LOGE("failed to SendRequest, code = %{public}d, result = %{public}d", code, result);
        return ERR_APPACCOUNT_KIT_SEND_REQUEST;
    }
    return ERR_OK;
}
}  // namespace AccountSA
}  // namespace OHOS

