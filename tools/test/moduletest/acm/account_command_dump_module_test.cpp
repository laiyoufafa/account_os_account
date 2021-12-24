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

#include <gtest/gtest.h>

#include "account_command.h"
#include "account_command_util.h"
#include "tool_system_test.h"

using namespace testing::ext;
using namespace OHOS;
using namespace OHOS::AAFwk;
using namespace OHOS::AccountSA;

namespace {
const std::string STRING_LOCAL_ACCOUNT_ID_INVALID = "local_account_id_invalid";
const std::string STRING_LOCAL_ACCOUNT_ID_INVALID_TWO = "1024";
}  // namespace

class AccountCommandDumpModuleTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    std::string cmd_ = "dump";
};

void AccountCommandDumpModuleTest::SetUpTestCase()
{}

void AccountCommandDumpModuleTest::TearDownTestCase()
{}

void AccountCommandDumpModuleTest::SetUp()
{}

void AccountCommandDumpModuleTest::TearDown()
{}

/**
 * @tc.name: Acm_Command_Dump_0100
 * @tc.desc: Verify the "acm dump -i <local-account-id>" command.
 * @tc.type: FUNC
 * @tc.require: SR000GGVFO
 */
HWTEST_F(AccountCommandDumpModuleTest, Acm_Command_Dump_0100, TestSize.Level1)
{
    std::string command = TOOL_NAME + " " + cmd_ + " -i " + STRING_LOCAL_ACCOUNT_ID_INVALID;
    GTEST_LOG_(INFO) << "command = " << command;

    std::string commandResult = ToolSystemTest::ExecuteCommand(command);
    EXPECT_EQ(commandResult, HELP_MSG_INVALID_ID_ARGUMENT + "\n");
}

/**
 * @tc.name: Acm_Command_Dump_0200
 * @tc.desc: Verify the "acm dump -i <local-account-id>" command.
 * @tc.type: FUNC
 * @tc.require: SR000GGVFO
 */
HWTEST_F(AccountCommandDumpModuleTest, Acm_Command_Dump_0200, TestSize.Level1)
{
    std::string command = TOOL_NAME + " " + cmd_ + " -i " + STRING_LOCAL_ACCOUNT_ID_INVALID_TWO;
    GTEST_LOG_(INFO) << "command = " << command;

    std::string commandResult = ToolSystemTest::ExecuteCommand(command);
    EXPECT_EQ(commandResult, STRING_DUMP_OS_ACCOUNT_NG + "\n");
}

/**
 * @tc.name: Acm_Command_Dump_0300
 * @tc.desc: Verify the "acm dump -i <local-account-id>" command.
 * @tc.type: FUNC
 * @tc.require: SR000GGVFO
 */
HWTEST_F(AccountCommandDumpModuleTest, Acm_Command_Dump_0300, TestSize.Level1)
{
    AccountCommandUtil::CreateOsAccount();

    AccountCommandUtil::DumpLastOsAccount();

    AccountCommandUtil::DeleteLastOsAccount();
}
