#include "imagebutton.h"

#include <QTimer>
#include <QPaintEvent>
#include <QPixmap>
#include <QPainter>

ImageButton::ImageButton(QWidget* parent) {
    setParent(parent);
    setToolTip("Click me!");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mButtonUpPixmap = QPixmap(":/UpButton.png");
    mButtonDownPixmap = QPixmap(":/DownButton.png");
    clickSound = QUrl("qrc:///click.mp3");
    mCurrentButtonPixmap = mButtonUpPixmap;
    setGeometry(mCurrentButtonPixmap.rect());
    player = new QMediaPlayer();
    player->setVolume(100);
    player->setMedia(clickSound);

    connect (this, &QPushButton::clicked, this, &ImageButton::setDown);
}

void ImageButton::paintEvent(QPaintEvent* e) {
    QPainter p(this);
    p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}

QSize ImageButton::sizeHint() const {
    return QSize(100, 100);
}

QSize ImageButton::minimumSizeHint() const {
    return sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent *e) {
    setDown();
}

void ImageButton::setDown() {
    player->stop();
    player->play();
    mCurrentButtonPixmap = mButtonDownPixmap;
    update();
    QTimer::singleShot(100, this, &ImageButton::setUp);
}

void ImageButton::setUp() {
    mCurrentButtonPixmap = mButtonUpPixmap;
    update();
}
