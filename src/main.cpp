/*
* This file is part of OctoPkg, an open-source GUI for pkgng.
* Copyright (C) 2015 Alexandre Albuquerque Arnt
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*/

#include "mainwindow.h"
#include "argumentlist.h"
#include "strconstants.h"
#include "unixcommand.h"
#include "constants.h"
#include <iostream>

#include "QtSolutions/qtsingleapplication.h"
#include <QMessageBox>
//#include <QTranslator>
#include <QResource>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

  ArgumentList *argList = new ArgumentList(argc, argv);
  QString packagesToInstall;
  QtSingleApplication app( StrConstants::getApplicationName(), argc, argv );

  if (app.isRunning())
  {    
    app.sendMessage("RAISE");
    delete argList;
    return 0;
  }

  if(!QFile::exists("/bin/sh"))
  {
    QMessageBox::critical( 0, StrConstants::getApplicationName(), StrConstants::getErrorNoSHFound());
    delete argList;
    return 1;
  }

  bool doas = (QFile::exists(QStringLiteral("/usr/pkg/bin/doas")) &&
    QFile::exists(QStringLiteral("/usr/pkg/etc/doas.conf")));
  bool sudo = QFile::exists(QStringLiteral("/usr/pkg/bin/sudo"));

  if (!doas && !sudo)
  {
    QMessageBox::critical( 0, StrConstants::getApplicationName(), StrConstants::getErrorNoDoasSudoFound());
    delete argList;
    return 1;
  }

  if(!QFile::exists(ctn_OCTOPKG_DOAS))
  {
    QMessageBox::critical( 0, StrConstants::getApplicationName(), StrConstants::getOctoPKGDoasNotFound());
    delete argList;
    return 1;
  }

  //This sends a message just to enable the socket-based QtSingleApplication engine
  app.sendMessage("RAISE");

  /*QTranslator appTranslator;
  appTranslator.load(":/resources/translations/octopkg_" +
                     QLocale::system().name());
  app.installTranslator(&appTranslator);*/

  if (argList->getSwitch("-help")){
    std::cout << StrConstants::getApplicationCliHelp().toLatin1().data() << std::endl;
    delete argList;
    return(0);
  }
  else if (argList->getSwitch("-version")){
    std::cout << "\n" << StrConstants::getApplicationName().toLatin1().data() <<
                 " " << StrConstants::getApplicationVersion().toLatin1().data() << "\n" << std::endl;
    delete argList;
    return(0);
  }

  if (UnixCommand::isRootRunning()){
    QMessageBox::critical( 0, StrConstants::getApplicationName(), StrConstants::getErrorRunningWithRoot());
    delete argList;
    return (-2);
  }

  MainWindow w;
  app.setActivationWindow(&w);
  app.setQuitOnLastWindowClosed(false);

  if (argList->getSwitch("-d"))
  {
    //If user chooses to switch debug info on...
    w.turnDebugInfoOn();
  }

  if (!packagesToInstall.isEmpty())
  {
    QStringList packagesToInstallList =
      packagesToInstall.split(",", Qt::SkipEmptyParts);
    w.setPackagesToInstallList(packagesToInstallList);
  }

  w.show();
  QResource::registerResource("./resources.qrc");

  return app.exec();
}
