// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef DEEPIN_INSTALLER_REBORN_PARTMAN_PARTITION_H
#define DEEPIN_INSTALLER_REBORN_PARTMAN_PARTITION_H

#include <QList>
#include <QStringList>

#include "partman/fs.h"
#include "partman/structs.h"

namespace partman {

enum class PartitionType {
  Primary,
  Logical,
  Extended,
  Unallocated,
};

enum class PartitionStatus {
  Real,
  New,
  Formatted,
};

class Partition {
 public:
  Partition();
  ~Partition();

  bool operator==(const Partition& other) const;

  QString device_path;
  QString path;
  QString uuid;
  QString label;
  QString part_label;  // Only some partition tables support part-label.
  int partition_number;
  PartitionType type;
  PartitionStatus status;
  FsType fs;
  OsType os;

  // sector size of the disk device needed for converting to/from sectors
  // and bytes
  qint64 sector_size;

  qint64 length;
  qint64 freespace;

  qint64 sector_start;
  qint64 sector_end;

  QString mount_point;

  // Returns actual partition size.
  // |length| is set only if this partition has a filesystem.
  qint64 getByteLength() const;

  // Returns a sector within this partition.
  // This method is only useful when calling ped_disk_get_partition_by_sector()
  qint64 getSector() const;

  // Returns length in sector.
  qint64 getSectorLength() const;
};

typedef QList<Partition> PartitionList;

}  // namespace partman

#endif  // DEEPIN_INSTALLER_REBORN_PARTMAN_PARTITION_H
