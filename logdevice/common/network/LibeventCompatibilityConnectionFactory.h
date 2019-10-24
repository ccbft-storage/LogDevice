/**
 * Copyright (c) 2017-present, Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */
#pragma once

#include "logdevice/common/ClientID.h"
#include "logdevice/common/NodeID.h"
#include "logdevice/common/ResourceBudget.h"
#include "logdevice/common/SocketTypes.h"
#include "logdevice/common/libevent/LibEventCompatibility.h"
#include "logdevice/common/network/IConnectionFactory.h"

namespace facebook { namespace logdevice {
class Connection;
class FlowGroup;
class SockAddr;
class SocketDependencies;
class LibeventCompatibilityConnectionFactory : public IConnectionFactory {
 public:
  explicit LibeventCompatibilityConnectionFactory(EvBase& base);

  std::unique_ptr<Connection>
  createConnection(NodeID node_id,
                   SocketType type,
                   ConnectionType connection_type,
                   FlowGroup& flow_group,
                   std::unique_ptr<SocketDependencies> deps) const override;

  std::unique_ptr<Connection>
  createConnection(int fd,
                   ClientID client_name,
                   const Sockaddr& client_address,
                   ResourceBudget::Token connection_token,
                   SocketType type,
                   ConnectionType conntype,
                   FlowGroup& flow_group,
                   std::unique_ptr<SocketDependencies> deps) const override;

 private:
  std::unique_ptr<IConnectionFactory> concrete_factory_;
};

}} // namespace facebook::logdevice
