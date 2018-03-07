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

#include "service/md_service_impl.h"
#include "soil/log.h"

namespace smack {

#define QUOTE_FLAG_SUMMARY 4

MDServiceImpl::MDServiceImpl(
    const rapidjson::Document& doc,
    MDServiceCallback* callback):
    callback_(callback) {
  SOIL_TRACE("MDServiceImpl::MDServiceImpl()");

  options_.reset(new MDOptions(doc));
  multi_.reset(new SocketMulticast());

  if (!multi_->sock_init(
          options_->multi_ip,
          options_->multi_port,
          options_->local_ip,
          0,
          this)) {
    throw std::runtime_error("init multi sock failed.");
  }
}

MDServiceImpl::~MDServiceImpl() {
  SOIL_TRACE("MDServiceImpl::~MDServiceImpl()");
  multi_->sock_close();
}

void MDServiceImpl::on_receive_message(
    int id,
    const char* buff,
    unsigned int len) {
  SOIL_TRACE("MDServiceImpl::on_receive_message()");
  SOIL_DEBUG("id: {}, msg len {}", id, len);

  if (!callback_)  {
    return;
  }

  if (len < sizeof(guava_udp_normal)) {
    return;
  }

  const guava_udp_normal* ptr_data =
      (const guava_udp_normal*)(buff);

  callback_->onReceiveNormal(ptr_data);
}

MDService* MDService::create(
    const rapidjson::Document& doc,
    MDServiceCallback* callback) {
  return new MDServiceImpl(doc, callback);
}

}  // namespace smack
