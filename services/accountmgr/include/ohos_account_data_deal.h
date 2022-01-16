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

#ifndef BASE_ACCOUNT_INCLUDE_OHOS_ACCOUNT_DATA_DEAL_H
#define BASE_ACCOUNT_INCLUDE_OHOS_ACCOUNT_DATA_DEAL_H

#include <string>
#include <nlohmann/json.hpp>
#include "account_error_no.h"
#include "account_info.h"

namespace OHOS {
namespace AccountSA {
using json = nlohmann::json;

class OhosAccountDataDeal {
public:
    explicit OhosAccountDataDeal(const std::string &configFileDir);
    ErrCode Init(std::int32_t userId);
    ErrCode AccountInfoFromJson(AccountInfo &accountInfo, const std::int32_t userId) const;
    ErrCode AccountInfoToJson(const AccountInfo &accountInfo) const;
    ~OhosAccountDataDeal() {};

private:
    bool initOk_;
    std::string configFileDir_;
    void BuildJsonFileFromScratch(std::int32_t userId) const;
    void SaveAccountInfo(const AccountInfo &accountInfo) const;
};
}
}
#endif // BASE_ACCOUNT_INCLUDE_OHOS_ACCOUNT_DATA_DEAL_H
