#ifndef IMAGEVIEWER_HPP
#define IMAGEVIEWER_HPP

#include <QWidget>

namespace Ui {
    class ImageViewer;
}

class ImageViewer : public QWidget
{
        Q_OBJECT

    public:
        explicit ImageViewer(QWidget *parent = 0);
        ~ImageViewer();

    private:
        Ui::ImageViewer *ui;
};

#endif // IMAGEVIEWER_HPP
