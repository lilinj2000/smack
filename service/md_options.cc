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

#include "service/md_options.h"

namespace smack {

using soil::json::get_item_value;

MDOptions::MDOptions(const rapidjson::Document& doc) {
  get_item_value(&multi_ip, doc, "/smack/multi_ip");
  get_item_value(&multi_port, doc, "/smack/multi_port");
  get_item_value(&local_ip, doc, "/smack/local_ip");

  return;
}

MDOptions::~MDOptions() {
}

}  // namespace smack
