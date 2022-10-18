#include <QPushButton>
#include <QPaintEvent>
#include <QApplication>
#include <QPixmap>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMediaPlayer>
#include <QMediaContent>

#include <iostream>

class ImageButton : public QPushButton {
    Q_OBJECT
public:
    ImageButton() = default;
    ImageButton (QWidget* parent);
    void paintEvent(QPaintEvent* e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent* e) override;

public slots:
    void setUp();
    void setDown();

private:
    QPixmap mCurrentButtonPixmap;
    QPixmap mButtonDownPixmap;
    QPixmap mButtonUpPixmap;
    QMediaPlayer* player;
    QMediaContent clickSound;
};

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

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ImageButton redButton(nullptr);
    redButton.setFixedSize(200, 200);
    redButton.move(1000, 400);
    QObject::connect(&redButton, &QPushButton::clicked, [](){std::cout << "clicked\n";});
    redButton.show();

    return a.exec();
}
