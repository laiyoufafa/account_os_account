/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "domain_account_plugin_proxy.h"

#include "account_error_no.h"
#include "account_log_wrapper.h"

namespace OHOS {
namespace AccountSA {
DomainAccountPluginProxy::DomainAccountPluginProxy(const sptr<IRemoteObject> &object)
    : IRemoteProxy<IDomainAccountPlugin>(object)
{}

DomainAccountPluginProxy::~DomainAccountPluginProxy()
{}

ErrCode DomainAccountPluginProxy::SendRequest(
    IDomainAccountPlugin::Message code, MessageParcel &data, MessageParcel &reply)
{
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        ACCOUNT_LOGD("remote is nullptr, code = %{public}d", code);
        return ERR_ACCOUNT_COMMON_NULL_PTR_ERROR;
    }
    MessageOption option(MessageOption::TF_SYNC);
    ErrCode result = remote->SendRequest(static_cast<uint32_t>(code), data, reply, option);
    if (result != ERR_OK) {
        ACCOUNT_LOGE("failed to send request, result: %{public}d", result);
        return result;
    }
    if (!reply.ReadInt32(result)) {
        ACCOUNT_LOGE("failed to read result");
        return ERR_ACCOUNT_COMMON_READ_PARCEL_ERROR;
    }
    return result;
}

static ErrCode WriteCommonData(MessageParcel &data, const std::u16string &descriptor, const DomainAccountInfo &info)
{
    if (!data.WriteInterfaceToken(descriptor)) {
        ACCOUNT_LOGE("fail to write descriptor");
        return ERR_ACCOUNT_COMMON_WRITE_PARCEL_ERROR;
    }
    if (!data.WriteParcelable(&info)) {
        ACCOUNT_LOGE("fail to write name");
        return ERR_ACCOUNT_COMMON_WRITE_PARCEL_ERROR;
    }
    return ERR_OK;
}

ErrCode DomainAccountPluginProxy::AuthCommonInterface(const DomainAccountInfo &info,
    const std::vector<uint8_t> &authData, const sptr<IDomainAuthCallback> &callback, AuthMode authMode)
{
    MessageParcel data;
    ErrCode result = WriteCommonData(data, GetDescriptor(), info);
    if (result != ERR_OK) {
        return result;
    }
    if (!data.WriteUInt8Vector(authData)) {
        ACCOUNT_LOGE("failed to write authData");
        return ERR_ACCOUNT_COMMON_WRITE_PARCEL_ERROR;
    }
    if ((callback == nullptr) || (!data.WriteRemoteObject(callback->AsObject()))) {
        ACCOUNT_LOGE("failed to write callback");
        return ERR_ACCOUNT_COMMON_WRITE_PARCEL_ERROR;
    }
    if (!data.WriteInt32(static_cast<int32_t>(authMode))) {
        ACCOUNT_LOGE("failed to write authMode");
        return ERR_ACCOUNT_COMMON_WRITE_PARCEL_ERROR;
    }
    MessageParcel reply;
    return SendRequest(IDomainAccountPlugin::Message::DOMAIN_PLUGIN_AUTH, data, reply);
}

ErrCode DomainAccountPluginProxy::Auth(const DomainAccountInfo &info, const std::vector<uint8_t> &password,
    const sptr<IDomainAuthCallback> &callback)
{
    return AuthCommonInterface(info, password, callback, AUTH_WITH_CREDENTIAL_MODE);
}

ErrCode DomainAccountPluginProxy::AuthWithPopup(
    const DomainAccountInfo &info, const sptr<IDomainAuthCallback> &callback)
{
    return AuthCommonInterface(info, {}, callback, AUTH_WITH_POPUP_MODE);
}

ErrCode DomainAccountPluginProxy::AuthWithToken(const DomainAccountInfo &info, const std::vector<uint8_t> &token,
    const sptr<IDomainAuthCallback> &callback)
{
    return AuthCommonInterface(info, token, callback, AUTH_WITH_TOKEN_MODE);
}

ErrCode DomainAccountPluginProxy::GetAuthStatusInfo(
    const DomainAccountInfo &info, const sptr<IDomainAccountCallback> &callback)
{
    MessageParcel data;
    ErrCode result = WriteCommonData(data, GetDescriptor(), info);
    if (result != ERR_OK) {
        return result;
    }
    if ((callback == nullptr) || (!data.WriteRemoteObject(callback->AsObject()))) {
        ACCOUNT_LOGE("failed to write callback");
        return ERR_ACCOUNT_COMMON_WRITE_PARCEL_ERROR;
    }
    MessageParcel reply;
    return SendRequest(IDomainAccountPlugin::Message::DOMAIN_PLUGIN_GET_AUTH_STATUS_INFO, data, reply);
}
}  // namespace AccountSA
}  // namespace OHOS
