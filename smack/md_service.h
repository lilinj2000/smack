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

#ifndef SMACK_MD_SERVICE_H_
#define SMACK_MD_SERVICE_H_

#include <string>

#include "soil/json.h"
#include "smack/def.h"

namespace smack {

class MDServiceCallback {
 public:
  virtual void onReceiveNormal(const guava_udp_normal* data) = 0;

  virtual ~MDServiceCallback() {}
};

class MDService {
 public:
  virtual ~MDService() {
  }

  static MDService* create(
      const rapidjson::Document& doc,
      MDServiceCallback* callback);
};

}  // namespace smack

#endif  // SMACK_MD_SERVICE_H_
