//===========================================
//  Lumina Desktop source code
//  Copyright (c) 2017, Ken Moore
//  Available under the 3-clause BSD license
//  See the LICENSE file for full details
//===========================================
#ifndef _LUMINA_PDF_VIEWER_MAIN_WINDOW_H
#define _LUMINA_PDF_VIEWER_MAIN_WINDOW_H

#include <QPrintPreviewWidget>
#include <QPrintDialog>
#include <QPrinter>
#include <QMainWindow>
#include <QProgressBar>
#include <QLabel>
#include <QKeyEvent>
#include <QDebug>
#include <QWheelEvent>
#include <QApplication>
#include <QMenu>

#include <poppler/qt5/poppler-qt5.h>
#include "PresentationLabel.h"
#include "propDialog.h"
#include "PrintWidget.h"

namespace Ui{
	class MainUI;
};

class MainUI : public QMainWindow{
	Q_OBJECT
public:
	MainUI();
	~MainUI();

	void loadFile(QString path);

private:
	Poppler::Document *DOC;
	PrintWidget *WIDGET;
	Ui::MainUI *ui;
	PropDialog *PROPDIALOG;
	QPrintDialog *PrintDLG;
	QString lastdir;
	bool matchCase;
	QMap<Poppler::TextBox*, int> results;
	int currentHighlight;

	//Other Interface elements
	QProgressBar *progress;
	QAction *progAct; //action associated with the progressbar
	QTimer *clockTimer;
	QMenu *contextMenu;
	//QFrame *frame_presenter;
	QLabel *label_clock, *label_page;
	QAction *clockAct, *pageAct;

	//PDF Page Loading cache variables
	QHash<int, QImage> loadingHash;
	int numPages;

	void loadPage(int num, Poppler::Document *doc, MainUI *obj, QSize dpi, QSizeF page);

	//Functions/variables for the presentation mode
	PresentationLabel *presentationLabel;
	QScreen *getScreen(bool current, bool &cancelled);
	int CurrentPage;
	void startPresentation(bool atStart);
	void ShowPage(int page);
	void endPresentation();

private slots:
	void startLoadingPages();
	void slotPageLoaded(int);

	//Simplification routines
	void nextPage(){ ShowPage( WIDGET->currentPage()+1 ); } //currentPage() starts at 1 rather than 0
	void prevPage(){ ShowPage( WIDGET->currentPage()-1 ); } //currentPage() starts at 1 rather than 0
	void firstPage(){ ShowPage(1); }
	void lastPage(){ ShowPage(numPages); }
	void startPresentationHere(){ startPresentation(false); }
	void startPresentationBeginning(){ startPresentation(true); }
	void closePresentation(){ endPresentation(); }

	void showInformation();
	void find(QString text, bool forward);
	void enableFind();
	void showBookmarks();

	void paintToPrinter(QPrinter *PRINTER);

	//Button Slots
	void OpenNewFile();

	//Other interface slots
	void updateClock();
	void updatePageNumber();
	void showContextMenu(const QPoint&){ contextMenu->popup(QCursor::pos()); }
	void updateContextMenu();

	void setScroll(bool);
	void rotate(bool);


signals:
	void PageLoaded(int);

protected:
	void keyPressEvent(QKeyEvent*);
	void wheelEvent(QWheelEvent*);
	void resizeEvent(QResizeEvent*);
	void closeEvent(QCloseEvent *ev){
	  endPresentation();
	  QMainWindow::closeEvent(ev);
	}
};
#endif
