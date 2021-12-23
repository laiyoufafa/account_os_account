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
#ifndef OS_ACCOUNT_SERVICES_ACCOUNTMGR_TEST_MOCK_OS_ACCOUNT_OS_ACCOUNT_STANDARD_INTERFACE_H
#define OS_ACCOUNT_SERVICES_ACCOUNTMGR_TEST_MOCK_OS_ACCOUNT_OS_ACCOUNT_STANDARD_INTERFACE_H
#include <vector>
#include "account_error_no.h"
#include "os_account_info.h"
namespace OHOS {
namespace AccountSA {
class OsAccountStandardInterface {
public:
    static ErrCode SendToAMSAccountStart(std::vector<OsAccountInfo> osAccountInfo);
    static ErrCode SendToAMSAccountStop(std::vector<OsAccountInfo> osAccountInfo);
    static ErrCode SendToBMSAccountCreate(std::vector<OsAccountInfo> osAccountInfo);
    static ErrCode SendToBMSAccountDelete(std::vector<OsAccountInfo> osAccountInfo);
    static ErrCode SendToCESAccountCreate(std::vector<OsAccountInfo> osAccountInfo);
    static ErrCode SendToCESAccountDelete(std::vector<OsAccountInfo> osAccountInfo);
    static ErrCode SendToCESAccountStart(std::vector<OsAccountInfo> osAccountInfo);
    static ErrCode SendToCESAccountStop(std::vector<OsAccountInfo> osAccountInfo);
    static ErrCode SetPhotoByPathAndByte(const std::string &path, std::string &byte, const std::string &photoType);
};
}  // namespace AccountSA
}  // namespace OHOS
#endif /* OS_ACCOUNT_SERVICES_ACCOUNTMGR_TEST_MOCK_OS_ACCOUNT_OS_ACCOUNT_STANDARD_INTERFACE_H */