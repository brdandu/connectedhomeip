/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "AppOptions.h"

using chip::ArgParser::OptionDef;
using chip::ArgParser::OptionSet;
using chip::ArgParser::PrintArgError;

constexpr uint16_t kOptionInteractiveMode     = 0xFF02;
constexpr uint16_t kOptionInteractiveModePort = 0xFF03;

static bool gInteractiveMode = false;
static chip::Optional<uint16_t> gInteractiveModePort;

bool AppOptions::HandleOptions(const char * program, OptionSet * options, int identifier, const char * name, const char * value)
{
    bool retval = true;
    switch (identifier)
    {
    case kOptionInteractiveMode:
        gInteractiveMode = true;
        break;
    case kOptionInteractiveModePort:
        gInteractiveModePort = chip::MakeOptional(static_cast<uint16_t>(atoi(value)));
        break;
    default:
        PrintArgError("%s: INTERNAL ERROR: Unhandled option: %s\n", program, name);
        retval = false;
        break;
    }

    return retval;
}

OptionSet * AppOptions::GetOptions()
{
    static OptionDef optionsDef[] = {
        { "interactive", chip::ArgParser::kNoArgument, kOptionInteractiveMode },
        { "port", chip::ArgParser::kArgumentRequired, kOptionInteractiveModePort },
        {},
    };

    static OptionSet options = { AppOptions::HandleOptions, optionsDef, "PROGRAM OPTIONS",
                                 "  --interactive\n"
                                 "       Enable server interactive mode.\n"
                                 "  --port <port>\n"
                                 "       Specify the listening port for the server interactive mode.\n" };

    return &options;
}

bool AppOptions::GetInteractiveMode()
{
    return gInteractiveMode;
}

chip::Optional<uint16_t> AppOptions::GetInteractiveModePort()
{
    return gInteractiveModePort;
}
