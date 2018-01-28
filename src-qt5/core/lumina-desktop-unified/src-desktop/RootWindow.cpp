//===========================================
//  Lumina-desktop source code
//  Copyright (c) 2017, Ken Moore
//  Available under the 3-clause BSD license
//  See the LICENSE file for full details
//===========================================
#include "RootWindow.h"
#include "QMLImageProvider.h"
#include <QQmlImageProviderBase>

RootWindow::RootWindow() : QObject(){
  root_win = QWindow::fromWinId( QX11Info::appRootWindow() ); //
  root_view = new QQuickView(root_win); //make it a child of the root window
  root_obj = RootDesktopObject::instance();
  syncRootSize();
  connect(root_win, SIGNAL(widthChanged(int)), this, SLOT(syncRootSize()) );
  connect(root_win, SIGNAL(heightChanged(int)),this, SLOT(syncRootSize()) );
  //Now setup the QQuickView
  root_view->setResizeMode(QQuickView::SizeRootObjectToView);
  root_view->engine()->rootContext()->setContextProperty("RootObject", root_obj);
  root_view->engine()->addImageProvider("native_window", new QMLImageProvider(QQmlImageProviderBase::Image) );
  //root_view->engine()->addImageProvider("native_window_icon", new QMLImageProvider(QQmlImageProviderBase::Pixmap) );
  RootDesktopObject::RegisterType(); //make sure object classes are registered with the QML subsystems
}

RootWindow::~RootWindow(){
  root_view->deleteLater();
  root_obj->deleteLater();
}

void RootWindow::start(){
  root_view->setSource(QUrl("qrc:///qml/RootDesktop.qml"));
  root_win->show();
  root_view->show();
}

void RootWindow::syncRootSize(){
  //qDebug() << "Sync Root Size:" << root_win->width() << root_win->height() << root_view->geometry();
  QList<QScreen*> screens = QApplication::screens();
  QRect unif;
  for(int i=0; i<screens.length(); i++){ unif = unif.united(screens[i]->geometry()); }
  if(unif.width() != root_view->width() || unif.height() != root_view->height()){
    root_view->setGeometry(0, 0, unif.width(), unif.height() );
    emit RootResized(root_view->geometry());
  }
  root_obj->updateScreens();
  //qDebug() << " - after:" << root_view->geometry();
}
