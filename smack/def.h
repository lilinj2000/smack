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

#ifndef SMACK_DEF_H_
#define SMACK_DEF_H_

namespace smack {

#pragma pack(push, 1)

struct guava_udp_normal {
  unsigned int m_sequence;  //<会话编号
  char m_exchange_id;  //<市场  0 表示中金  1表示上期
  char m_channel_id;  //<通道编号
  char m_quote_flag;  //<行情标志  0 无time sale,无lev1,
  ///           1 有time sale,无lev1,
  ///           2 无time sale,有lev1,
  ///           3 有time sale,有lev1
  char m_symbol[8];  //<合约
  char m_update_time[9];  //<最后更新时间(秒)
  int m_millisecond;  //<最后更新时间(毫秒)

  double m_last_px;  //<最新价
  int m_last_share;  //<最新成交量
  double m_total_value;  //<成交金额
  double m_total_pos;  //<持仓量
  double m_bid_px;  //<最新买价
  int m_bid_share;  //<最新买量
  double m_ask_px;  //<最新卖价
  int m_ask_share;  //<最新卖量
};
#pragma pack(pop)

}  // namespace smack

#endif  // SMACK_DEF_H_
