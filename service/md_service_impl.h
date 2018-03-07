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

#ifndef SERVICE_MD_SERVICE_IMPL_H_
#define SERVICE_MD_SERVICE_IMPL_H_

#include "smack/md_service.h"
#include "service/socket_multicast.h"
#include "service/md_options.h"

namespace smack {

class MDServiceImpl :
      public SocketEvent,
      public MDService {
 public:
  MDServiceImpl(
      const rapidjson::Document& doc,
      MDServiceCallback* callback = 0);

  ~MDServiceImpl();

 private:
  virtual void on_receive_message(
      int id,
      const char* buff,
      unsigned int len);

 private:
  std::unique_ptr<MDOptions> options_;
  std::unique_ptr<SocketMulticast> multi_;
  MDServiceCallback* callback_;
};

}  // namespace smack

#endif  // SERVICE_MD_SERVICE_IMPL_H_
