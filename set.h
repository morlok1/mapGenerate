#ifndef SET_H
#define SET_H

#include "header.h"

class set : public QWidget
{
    Q_OBJECT

    QImage pic1;

    QGraphicsScene* scene;
    QGraphicsView* view;

    QPushButton* getImage1;
    QLineEdit* localAddress1;
    QGridLayout* grid;
    QPushButton* getStart;
    QLabel* info;

public:
    set();
    ~set();

public slots:

    void getFirstImage();
    void getImageSum();

    void createNewDote(double x, double y);
};

#endif // SET_H
