#ifndef DIALOG_WORLD_POINT_HPP
#define DIALOG_WORLD_POINT_HPP

#include <QDialog>
#include <opencv2/core/core.hpp>

namespace Ui {
    class DialogWorldPoint;
}

class DialogWorldPoint : public QDialog
{
    Q_OBJECT

    public:

        ~DialogWorldPoint();
        static cv::Point3f getWorldPoint(void);

private slots:
        void on_buttonBox_accepted();

private:
        Ui::DialogWorldPoint *ui;
        DialogWorldPoint();

protected:
        cv::Point3f worldPoint;


};

#endif // DIALOG_WORLD_POINT_HPP
