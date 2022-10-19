#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaContent>

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

#endif // IMAGEBUTTON_H
