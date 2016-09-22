// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "partman/operation_delete.h"

namespace partman {

OperationDelete::OperationDelete(const Partition& partition_orig,
                                 const Partition& partition_new) {
  this->type = OperationType::Delete;
  this->partition_orig = partition_orig;
  this->partition_new = partition_new;
}

void OperationDelete::applyToVisual(PartitionList& partitions) const {
  substitute(partitions);
}

}  // namespace partman