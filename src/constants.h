#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

#if defined(__DragonFly__)
  const QString ctn_PKG_BIN = QStringLiteral("/usr/local/sbin/pkg");
#else
  const QString ctn_PKG_BIN = QStringLiteral("/usr/pkg/bin/pkgin");
#endif

const QString ctn_OCTOPKG_DOAS = QStringLiteral("/usr/pkg/bin/qt-sudo");
const QString ctn_OCTOPKG_DOAS_PARAMS = QStringLiteral("-d");

#endif // CONSTANTS_H
