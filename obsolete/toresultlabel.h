
/* BEGIN_COMMON_COPYRIGHT_HEADER
 *
 * TOra - An Oracle Toolkit for DBA's and developers
 * 
 * Shared/mixed copyright is held throughout files in this product
 * 
 * Portions Copyright (C) 2000-2001 Underscore AB
 * Portions Copyright (C) 2003-2005 Quest Software, Inc.
 * Portions Copyright (C) 2004-2013 Numerous Other Contributors
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;  only version 2 of
 * the License is valid for this program.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program as the file COPYING.txt; if not, please see
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 * 
 *      As a special exception, you have permission to link this program
 *      with the Oracle Client libraries and distribute executables, as long
 *      as you follow the requirements of the GNU GPL in regard to all of the
 *      software in the executable aside from Oracle client libraries.
 * 
 * All trademarks belong to their respective owners.
 *
 * END_COMMON_COPYRIGHT_HEADER */

#ifndef TORESULTLABEL_H
#define TORESULTLABEL_H

#include "config.h"
#include "toresult.h"

#include <qlabel.h>

class toEventQueryNew;
class toSQL;

/** This widget displays the result of a query where each item in the stream
 * is added to a label separated by an optional string.
 */

class toResultLabel : public QLabel, public toResult
{
    Q_OBJECT

    toEventQuery *Query;

    QStringList res;
    QString Separator;

public:
    /** Create the widget.
     * @param parent Parent widget.
     * @param name Name of widget.
     */
    toResultLabel(QWidget *parent, const char *name = NULL);
    /** Destruct object
     */
    ~toResultLabel();

    /** Reimplemented for internal reasons.
     */
    virtual void query(const QString &sql, const toQList &param);

    /** Handle any connection by default
     */
    virtual bool canHandle(const toConnection &)
    {
        return true;
    }

    /** Get separator string to use between result.
     */
    const QString &separator(void) const
    {
        return Separator;
    }
    /** Set separator string to use between result.
     */
    void setSeparator(const QString &sep)
    {
        Separator = sep;
    }

    // Why are these needed?
#if 1
    /** Set the SQL statement of this list
     * @param sql String containing statement.
     */
    void setSQL(const QString &sql)
    {
        toResult::setSQL(sql);
    }
    /** Set the SQL statement of this list. This will also affect @ref Name.
     * @param sql SQL containing statement.
     */
    void setSQL(const toSQL &sql)
    {
        toResult::setSQL(sql);
    }
    /** Set new SQL and run query.
     * @param sql New sql.
     * @see setSQL
     */
    void query(const QString &sql)
    {
        toResult::query(sql);
    }
    /** Set new SQL and run query.
     * @param sql New sql.
     * @see setSQL
     */
    void query(const toSQL &sql)
    {
        toResult::query(sql);
    }
    /** Set new SQL and run query.
     * @param sql New sql.
     * @see setSQL
     */
    void query(const toSQL &sql, toQList &par)
    {
        toResult::query(sql, par);
    }
#endif
public slots:
    /** Reimplemented for internal reasons.
     */
    virtual void refresh(void)
    {
        toResult::refresh();
    }
    /** Reimplemented for internal reasons.
     */
    virtual void executeWithParams(const QString &Param1)
    {
        toResult::executeWithParams(Param1);
    }
    /** Reimplemented For internal reasons.
     */
    virtual void executeWithParams(const QString &Param1, const QString &Param2)
    {
        toResult::executeWithParams(Param1, Param2);
    }
    /** Reimplemented for internal reasons.
     */
    virtual void executeWithParams(const QString &Param1, const QString &Param2, const QString &Param3)
    {
        toResult::executeWithParams(Param1, Param2, Param3);
    }
private slots:
    void poll(void);
    void queryDone(void);
};

#endif
