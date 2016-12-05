#include <QSqlDatabase>
#include <string>

#include "player.hpp"

class DAOWrapper
{
    public:
        DAOWrapper(QString host, QString user,
                   QString pass, QString db, int port);
        DAOWrapper(cv::FileNode node);
        ~DAOWrapper();

        void persistPlayer(Player& player);

    private:
        QSqlDatabase db;
};
