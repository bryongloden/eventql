/**
 * Copyright (c) 2016 zScale Technology GmbH <legal@zscale.io>
 * Authors:
 *   - Paul Asmuth <paul@zscale.io>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License ("the license") as
 * published by the Free Software Foundation, either version 3 of the License,
 * or any later version.
 *
 * In accordance with Section 7(e) of the license, the licensing of the Program
 * under the license does not imply a trademark license. Therefore any rights,
 * title and interest in our trademarks remain entirely with us.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the license for more details.
 *
 * You can be released from the requirements of the license by purchasing a
 * commercial license. Buying such a license is mandatory as soon as you develop
 * commercial activities involving this program without disclosing the source
 * code of your own applications
 */
#pragma once
#include <zookeeper.h>
#include "eventql/eventql.h"
#include "eventql/config/config_directory.h"

namespace eventql {

class ZookeeperConfigDirectory : public ConfigDirectory {
public:

  ZookeeperConfigDirectory(
      const String& cluster_name,
      const String& zookeeper_addrs);

  ~ZookeeperConfigDirectory();

  ClusterConfig getClusterConfig() const override;

  void updateClusterConfig(ClusterConfig config) override;

  void setClusterConfigChangeCallback(
      Function<void (const ClusterConfig& cfg)> fn) override;

  RefPtr<NamespaceConfigRef> getNamespaceConfig(
      const String& customer_key) const override;

  void updateNamespaceConfig(NamespaceConfig config) override;

  void listNamespaces(
      Function<void (const NamespaceConfig& cfg)> fn) const override;

  void setNamespaceConfigChangeCallback(
      Function<void (const NamespaceConfig& cfg)> fn) override;

  TableDefinition getTableConfig(
      const String& db_namespace,
      const String& table_name) const override;

  void updateTableConfig(
      const TableDefinition& table,
      bool force = false) override;

  void listTables(
      Function<void (const TableDefinition& tbl)> fn) const override;

  void setTableConfigChangeCallback(
      Function<void (const TableDefinition& tbl)> fn) override;

  void start() override;
  void stop() override;

  /** don't call this! (can't be private b/c it needs to be called from c binding) */
  void handleZookeeperWatch(
      zhandle_t* zk,
      int type,
      int state,
      const char* path,
      void* ctx);

protected:

  enum class ZKState {
    INIT = 0,
    CONNECTING = 1,
    LOADING = 2,
    CONNECTED = 3,
    CONNECTION_LOST = 4,
    CLOSED = 5
  };

  String cluster_name_;
  String zookeeper_addrs_;
  size_t zookeeper_timeout_;
  ZKState state_;
  zhandle_t* zk_;
  std::mutex mutex_;
  std::condition_variable cv_;
};

} // namespace eventql
