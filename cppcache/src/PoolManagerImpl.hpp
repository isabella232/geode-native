/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#ifndef GEODE_POOLMANAGERIMPL_H_
#define GEODE_POOLMANAGERIMPL_H_

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include <geode/HashMapOfPools.hpp>
#include <geode/Region.hpp>

#include "CacheImpl.hpp"

namespace apache {
namespace geode {
namespace client {

class Pool;
class PoolFactory;

class PoolManagerImpl {
 public:
  explicit PoolManagerImpl(CacheImpl* cache) : m_cache(cache) {}
  PoolManagerImpl(const PoolManagerImpl& copy) = default;
  ~PoolManagerImpl() = default;

  void removePool(const std::string& name);

  PoolFactory createFactory() const;

  void close(bool keepAlive);

  std::shared_ptr<Pool> find(const std::string& name) const;

  std::shared_ptr<Pool> find(std::shared_ptr<Region> region) const;

  const HashMapOfPools& getAll() const;

  void addPool(std::string name, const std::shared_ptr<Pool>& pool);

  const std::shared_ptr<Pool>& getDefaultPool() const;

 private:
  HashMapOfPools m_connectionPools;
  mutable std::recursive_mutex m_connectionPoolsLock;
  std::shared_ptr<Pool> m_defaultPool;
  CacheImpl* m_cache;
};

}  // namespace client
}  // namespace geode
}  // namespace apache

#endif  // GEODE_POOLMANAGERIMPL_H_
