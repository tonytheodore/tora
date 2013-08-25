
/* BEGIN_COMMON_COPYRIGHT_HEADER
 *
 * TOra - An Oracle Toolkit for DBA's and developers
 *
 * Shared/mixed copyright is held throughout files in this product
 *
 * Portions Copyright (C) 2000-2001 Underscore AB
 * Portions Copyright (C) 2003-2005 Quest Software, Inc.
 * Portions Copyright (C) 2004-2009 Numerous Other Contributors
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 *      As a special exception, you have permission to link this program
 *      with the Oracle Client libraries and distribute executables, as long
 *      as you follow the requirements of the GNU GPL in regard to all of the
 *      software in the executable aside from Oracle client libraries.
 *
 *      Specifically you are not permitted to link this program with the
 *      Qt/UNIX, Qt/Windows or Qt Non Commercial products of TrollTech.
 *      And you are not permitted to distribute binaries compiled against
 *      these libraries.
 *
 *      You may link this product with any GPL'd Qt library.
 *
 * All trademarks belong to their respective owners.
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "core/toeditmenu.h"
#include "ts_log/ts_log_utils.h"

#include "icons/undo.xpm"
#include "icons/redo.xpm"
#include "icons/cut.xpm"
#include "icons/copy.xpm"
#include "icons/paste.xpm"
#include "icons/search.xpm"

#include <QtGui/QApplication>
#include <QtGui/QClipboard>
#include <QtCore/QMimeData>

toEditMenu::toEditMenu()
	: QMenu(tr("&Edit"), NULL)
	, toEditWidget::editHandler()
	, m_editWidget(NULL)
	, m_clipboardContent(false)
	, m_pasteSupported(false)
{
	QClipboard const *clipBoard = QApplication::clipboard();
	QMimeData const *mimeData = clipBoard->mimeData();
	connect(clipBoard, SIGNAL(dataChanged()), this, SLOT(clipBoardChanged()));

	m_clipboardContent = mimeData->hasText() && !clipBoard->text().isEmpty();

    undoAct = new QAction(QPixmap(const_cast<const char**>(undo_xpm)), tr("&Undo"), this);
    undoAct->setShortcut(QKeySequence::Undo);

    redoAct = new QAction(QPixmap(const_cast<const char**>(redo_xpm)), tr("&Redo"), this);
    redoAct->setShortcut(QKeySequence::Redo);

    cutAct = new QAction(QPixmap(const_cast<const char**>(cut_xpm)), tr("Cu&t"), this);
    cutAct->setShortcut(QKeySequence::Cut);
    cutAct->setToolTip(tr("Cut to clipboard"));

    copyAct = new QAction(QPixmap(const_cast<const char**>(copy_xpm)), tr("&Copy"), this);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setToolTip(tr("Copy to clipboard"));

    pasteAct = new QAction(QPixmap(const_cast<const char**>(paste_xpm)), tr("&Paste"), this);
    pasteAct->setShortcut(QKeySequence::Paste);
    pasteAct->setToolTip(tr("Paste from clipboard"));

    searchReplaceAct = new QAction(QPixmap(const_cast<const char**>(search_xpm)), tr("&Search && Replace..."), this);
    searchReplaceAct->setShortcut(QKeySequence::Find);
    searchReplaceAct->setToolTip(tr("Search & replace"));

    searchNextAct = new QAction(tr("Search &Next"), this);
    searchNextAct->setShortcut(QKeySequence::FindNext);

    selectAllAct = new QAction(tr("Select &All"), this);
    selectAllAct->setShortcut(QKeySequence::SelectAll);

#if 0
    // TODO: this part is waiting for QScintilla backend feature (yet unimplemented).
    selectBlockAct = new QAction(tr("Block Selection"), this);
    selectBlockAct->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_B);
    selectBlockAct->setCheckable(true);
#endif

    readAllAct = new QAction(tr("Read All &Items"), this);

    prefsAct = new QAction(tr("&Preferences..."), this);

    addAction(undoAct);
    addAction(redoAct);
    addSeparator();

    addAction(cutAct);
    addAction(copyAct);
    addAction(pasteAct);
    addSeparator();

    addAction(searchReplaceAct);
    addAction(searchNextAct);
    addAction(selectAllAct);
#if 0
// TODO: this part is waiting for QScintilla backend feature (yet unimplemented).
    addAction(selectBlockAct);
#endif
    addAction(readAllAct);
    addSeparator();

    addAction(prefsAct);

    disableAll();
}

void toEditMenu::receivedFocus(toEditWidget *widget)
{
	m_editWidget = widget;
	if(widget == NULL)
	{
		disableAll();
		return;
	}
	m_pasteSupported = widget->FlagSet.Paste;
    undoAct->setEnabled(widget->FlagSet.Undo);
    redoAct->setEnabled(widget->FlagSet.Redo);

    cutAct->setEnabled(widget->FlagSet.Cut);
    copyAct->setEnabled(widget->FlagSet.Copy);
    pasteAct->setEnabled(m_pasteSupported && m_clipboardContent);
    searchReplaceAct->setEnabled(widget->FlagSet.Search);
    searchNextAct->setEnabled(widget->FlagSet.Search);
    selectAllAct->setEnabled(widget->FlagSet.SelectAll);
#if 0 // TODO: this part is waiting for QScintilla backend feature (yet unimplemented).
    selectBlockAct->setEnabled(widget->FlagSet.SelectAll);
#endif
    readAllAct->setEnabled(widget->FlagSet.ReadAll);
}

void toEditMenu::lostFocus(toEditWidget *widget)
{
	////Q_ASSERT_X(widget == m_editWidget, (__HERE__).c_str(), "");
	disableAll();
	m_editWidget = NULL;
}

void toEditMenu::disableAll() {
	undoAct->setEnabled(false);
	redoAct->setEnabled(false);

	cutAct->setEnabled(false);
	copyAct->setEnabled(false);
	pasteAct->setEnabled(false);
	searchReplaceAct->setEnabled(false);
	searchNextAct->setEnabled(false);
	selectAllAct->setEnabled(false);
	readAllAct->setEnabled(false);
	m_pasteSupported = false;
}

toEditMenu::~toEditMenu()
{
	//TOTO CLEAN ALL
}

void toEditMenu::clipBoardChanged()
{
	QClipboard const *clipBoard = QApplication::clipboard();
	QMimeData const *mimeData = clipBoard->mimeData();
    pasteAct->setEnabled(m_pasteSupported && m_clipboardContent);
}