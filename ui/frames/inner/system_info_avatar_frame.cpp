// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#include "ui/frames/inner/system_info_avatar_frame.h"

#include <QDebug>
#include <QFile>
#include <QHBoxLayout>
#include <QStringListModel>
#include <QVBoxLayout>

#include "base/file_util.h"
#include "service/settings_manager.h"
#include "service/settings_name.h"
#include "ui/delegates/avatar_list_delegate.h"
#include "ui/frames/consts.h"
#include "ui/views/pointer_list_view.h"
#include "ui/widgets/avatar_button.h"
#include "ui/widgets/comment_label_layout.h"
#include "ui/widgets/icon_button.h"
#include "ui/widgets/nav_button.h"
#include "ui/widgets/title_label.h"

namespace installer {

namespace {

// Check whether |avatar| is valid.
bool IsValidAvatar(const QString& avatar) {
  if (avatar.isEmpty()) {
    return false;
  }
  return QFile::exists(avatar);
}

}  // namespace

SystemInfoAvatarFrame::SystemInfoAvatarFrame(QWidget* parent)
  : QFrame(parent) {
  this->setObjectName("system_info_avatar_frame");

  this->initUI();
  this->initConnections();
}

void SystemInfoAvatarFrame::autoConf() {
  const QString avatar = GetDefaultAvatar();
  if (!IsValidAvatar(avatar)) {
    qWarning() << "autoConf() got invalid avatar: " << avatar;
    return;
  }

  emit this->avatarUpdated(avatar);
  WriteAvatar(avatar);
}

void SystemInfoAvatarFrame::updateTimezone(const QString& timezone) {
  timezone_button_->setText(timezone);
}

void SystemInfoAvatarFrame::initConnections() {
  connect(timezone_button_, &QPushButton::clicked,
          this, &SystemInfoAvatarFrame::timezoneClicked);

  // Return to previous page when chosen_avatar_button is clicked.
  connect(chosen_avatar_button_, &QPushButton::clicked,
          this, &SystemInfoAvatarFrame::finished);
  connect(list_view_, &QListView::pressed,
          this, &SystemInfoAvatarFrame::onListViewPressed);
}

void SystemInfoAvatarFrame::initUI() {
  timezone_button_ = new IconButton(":/images/timezone.png",
                                    ":/images/timezone.png",
                                    ":/images/timezone.png",
                                    128, 32, nullptr);
  TitleLabel* title_label = new TitleLabel(tr("User Avatar"));
  CommentLabelLayout* comment_layout = new CommentLabelLayout(
      tr("Select an avatar for your account"));
  chosen_avatar_button_ = new AvatarButton(GetDefaultAvatar());

  const QStringList avatars = GetAvatars();
  list_view_ = new PointerListView();
  QStringListModel* list_model = new QStringListModel(avatars);
  list_view_->setModel(list_model);
  AvatarListDelegate* list_delegate = new AvatarListDelegate();
  list_view_->setItemDelegate(list_delegate);
  QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  policy.setHorizontalStretch(10);
  policy.setVerticalStretch(10);
  list_view_->setSizePolicy(policy);
  list_view_->setContentsMargins(10, 10, 10, 10);
  list_view_->setSpacing(30);
  list_view_->setAcceptDrops(false);
  list_view_->setWrapping(true);
  list_view_->setUniformItemSizes(true);
  list_view_->setFlow(QListView::LeftToRight);
  list_view_->setViewMode(QListView::IconMode);
  list_view_->setFixedWidth(960);
  list_view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  list_view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  list_view_->setStyleSheet(ReadFile(":/styles/avatar_list_view.css"));;

  QVBoxLayout* layout = new QVBoxLayout();
  layout->setSpacing(kMainLayoutSpacing);
  layout->addWidget(timezone_button_, 0, Qt::AlignLeft);
  layout->addStretch(2);
  layout->addWidget(title_label, 0, Qt::AlignCenter);
  layout->addLayout(comment_layout);
  layout->addStretch(1);
  layout->addWidget(chosen_avatar_button_, 0, Qt::AlignCenter);
  layout->addStretch(1);
  layout->addWidget(list_view_, 0, Qt::AlignHCenter);
  layout->addStretch(3);

  this->setLayout(layout);
}

void SystemInfoAvatarFrame::onListViewPressed(const QModelIndex& index) {
  const QString avatar = index.model()->data(index).toString();
  chosen_avatar_button_->updateIcon(avatar);
  WriteAvatar(avatar);
  emit this->avatarUpdated(avatar);
  emit this->finished();
}

}  // namespace installer