// Copyright 2017 The Smack Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// -----------------------------------------------------------------------------
// File: [file_name]
// -----------------------------------------------------------------------------
//
// [file_descrition]
//
// Example:
//
//   ... ...
//
//

#ifndef SERVICE_MD_OPTIONS_H_
#define SERVICE_MD_OPTIONS_H_

#include <string>
#include "soil/json.h"

namespace smack {

class MDOptions {
 public:
  explicit MDOptions(const rapidjson::Document& doc);

  virtual ~MDOptions();

  std::string multi_ip;
  uint32_t multi_port;
  std::string local_ip;
};

}  // namespace smack

#endif  // SERVICE_MD_OPTIONS_H_
