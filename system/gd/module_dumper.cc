/*
 * Copyright 2023 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define LOG_TAG "BtGdModule"

#include "module_dumper.h"

#include <sstream>

#include "dumpsys_data_generated.h"
#include "module.h"
#include "os/wakelock_manager.h"

using ::bluetooth::os::WakelockManager;

namespace bluetooth {

void ModuleDumper::DumpState(std::string* output, std::ostringstream& /*oss*/) const {
  log::assert_that(output != nullptr, "assert failed: output != nullptr");

  flatbuffers::FlatBufferBuilder builder(1024);
  auto title = builder.CreateString(title_);

  auto wakelock_offset = WakelockManager::Get().GetDumpsysData(&builder);

  std::queue<DumpsysDataFinisher> queue;
  for (auto it = module_registry_.start_order_.rbegin(); it != module_registry_.start_order_.rend();
       it++) {
    auto instance = module_registry_.started_modules_.find(*it);
    log::assert_that(instance != module_registry_.started_modules_.end(),
                     "assert failed: instance != module_registry_.started_modules_.end()");
    log::verbose("Starting dumpsys module:{}", instance->second->ToString());
    queue.push(instance->second->GetDumpsysData(&builder));
    log::verbose("Finished dumpsys module:{}", instance->second->ToString());
  }

  DumpsysDataBuilder data_builder(builder);
  data_builder.add_title(title);
  data_builder.add_wakelock_manager_data(wakelock_offset);

  while (!queue.empty()) {
    queue.front()(&data_builder);
    queue.pop();
  }

  builder.Finish(data_builder.Finish());
  *output = std::string(builder.GetBufferPointer(), builder.GetBufferPointer() + builder.GetSize());
}

}  // namespace bluetooth
