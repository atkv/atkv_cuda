/**
 ** This file is part of the atkv project.
 ** Copyright 2016 Anderson Tavares <nocturne.pe@gmail.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/
#ifndef AT_PQUEUE_H
#define AT_PQUEUE_H
#include <at/core/macro.h>
AT_BEGIN_DECLS
#include <stdint.h>
#include <at/core/optimization.h>
#include <at/core/queue.h>
/*=============================================================================
 STRUCTURE
 ============================================================================*/
#define AtPQueue(type) AtPQueue##type
#define at_pqueue_new(queue,optimization,policy) queue = _Generic((queue), \
  AtPQueueU64*: at_pqueueu64_new)(optimization, policy)

/**
 * @brief Priority Queue Structure
 */
typedef struct AtPQueueU64{
  AtQueueu64* pr;
  AtListU64*  v;
  uint64_t*         vp;
  uint64_t          cur_p;
  uint32_t          ne;
  uint32_t          np;
  AtOptimization    o;
  AtPolicy          po;
}AtPQueueU64;
/*=============================================================================
 PUBLIC API
 ============================================================================*/

/**
 * @brief at_pqueue_new
 * @param optimization
 * @return
 */
AtPQueueU64*
at_pqueueu64_new(AtOptimization o, AtPolicy po);

/**
 * @brief at_pqueue_new_prealloc
 * @param optimization
 * @param n_buckets
 * @param n_values
 * @return
 */
AtPQueueU64*
at_pqueueu64_new_prealloc(AtOptimization o, AtPolicy po, uint64_t np, uint64_t nv);

/**
 * @brief at_pqueue_add
 * @param queue
 * @param bucket
 * @param value
 */
void
at_pqueueu64_add(AtPQueueU64* q, uint64_t pr, uint64_t v);

/**
 * @brief at_pqueue_remove
 * @param queue
 * @return
 */
uint64_t
at_pqueueu64_remove(AtPQueueU64* q);

/**
 * @brief at_pqueueu64_remove_from
 * @param q
 * @param v
 */
void
at_pqueueu64_remove_from(AtPQueueU64* q, uint64_t v);

/**
 * @brief at_pqueueu64_is_empty
 * @param q
 * @return
 */
uint8_t
at_pqueueu64_is_empty(AtPQueueU64* q);

/**
 * @brief at_pqueueu64_has
 * @param q
 * @param pr
 * @param v
 * @return
 */
uint8_t
at_pqueueu64_has(AtPQueueU64* q, uint64_t v);

/**
 * @brief at_pqueue_destroy
 * @param queue_ptr
 */
void
at_pqueueu64_destroy(AtPQueueU64** qp);
AT_END_DECLS
#endif
