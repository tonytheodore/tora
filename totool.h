/****************************************************************************
 *
 * TOra - An Oracle Toolkit for DBA's and developers
 * Copyright (C) 2000 GlobeCom AB
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 *      As a special exception, you have permission to link this program
 *      with the Qt and Oracle Client libraries and distribute executables,
 *      as long as you follow the requirements of the GNU GPL in regard to
 *      all of the software in the executable aside from Qt and Oracle client
 *      libraries.
 *
 ****************************************************************************/


#ifndef __TOTOOL_H
#define __TOTOOL_H

#include <map>
#include <qstring.h>
#include <qpopupmenu.h>
#include <qobject.h>

#include "otlv32.h"

class toConnection;

class toSettingTab {
public:
  toSettingTab()
  { }
  virtual void saveSetting(void) = NULL;
};

class toTool : public QObject {
  Q_OBJECT
private:
  QString Name;
  QString Key;
  int Priority;
  static map<QString,toTool *> *Tools;
  static map<QString,QString> *Configuration;
  QPixmap *ButtonPicture;

  static void loadConfig(void);
protected:
  virtual char **pictureXPM(void);
public:
  toTool(int priority,const char *name);
  ~toTool();

  QString name() const
  { return Name; }
  int priority() const
  { return Priority; }
  static map<QString,toTool *> &tools(void)
  { return *Tools; }
  virtual const QPixmap *toolbarImage();
  virtual const char *menuItem()
  { return NULL; }
  virtual const char *toolbarTip()
  { return menuItem(); }
  virtual QWidget *toolWindow(QWidget *parent,toConnection &connection) = NULL;

  // These should not be used by the actual tools
  static void saveConfig(void);
  static const QString &globalConfig(const QString &tag,const QString &def);
  static void globalSetConfig(const QString &tag,const QString &value);

  // This should be used by the tool
  const QString &config(const QString &tag,const QString &def);
  void setConfig(const QString &tag,const QString &value);
  
  // The returned widget should also be derived from toSettingTab
  virtual QWidget *configurationTab(QWidget *parent)
  { return NULL; }
public slots:
  void createWindow(void);
};

#endif
