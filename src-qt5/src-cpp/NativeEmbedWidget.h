//===========================================
//  Lumina-DE source code
//  Copyright (c) 2017, Ken Moore
//  Available under the 3-clause BSD license
//  See the LICENSE file for full details
//===========================================
//  This is a container object for embedding a native window into a QWidget
//    and maintaining a 1-to-1 mapping of sizing and other properties
//    while also providing compositing effects between the two windows
//===========================================
#ifndef _LUMINA_NATIVE_EMBED_WIDGET_H
#define _LUMINA_NATIVE_EMBED_WIDGET_H

#include "NativeWindow.h"
#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include <QShowEvent>
#include <QHideEvent>
#include <QPaintEvent>
#include <QMouseEvent>

class NativeEmbedWidget : public QWidget{
	Q_OBJECT
private:
	NativeWindow *WIN;
	QSize winSize;
	QImage winImage;
	bool paused, hasAlphaChannel;

private slots:
	//Simplification functions
	void syncWinSize(QSize sz = QSize());
	void syncWidgetSize(QSize sz);
	void hideWindow();
	void showWindow();
	QImage windowImage(QRect geom);

	void setWinUnpaused();

public:
	NativeEmbedWidget(QWidget *parent);

	bool embedWindow(NativeWindow *window);
	bool detachWindow();
	bool isEmbedded(); //status of the embed
	bool isPaused(){ return paused; }

public slots:
	void raiseWindow();
	void lowerWindow();

	//Pause/resume
	void pause();
	void resume();

	void resyncWindow();
	void repaintWindow();
	void reregisterEvents();

protected:
	void resizeEvent(QResizeEvent *ev);
	void showEvent(QShowEvent *ev);
	void hideEvent(QHideEvent *ev);
	void paintEvent(QPaintEvent *ev);
	void enterEvent(QEvent *ev);
	void leaveEvent(QEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
	void mousePressEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);
	//bool nativeEvent(const QByteArray &eventType, void *message, long *result);
};

#endif
