#ifndef SET_H
#define SET_H

#include "header.h"

class set : public QWidget
{
    Q_OBJECT

    //Данные
    QImage mapImage;
    int sensitivityValue;

    //Сцена
    QGraphicsScene* scene;
    QGraphicsView* view;

    //Интерфейс
    QGridLayout* grid;

    QLineEdit* localAddress;
    QPushButton* getImage;
    QSlider* sensitivity;
    QLabel* sensitivityText;
    QCheckBox* permissionToDraw;
    QLabel* info;
    QPushButton* getStart;


public:
    set();
    ~set();

public slots:

    void getMapImage();
    void getMapGenerate();

    void createNewDote(double x, double y);

    void setSensitivity();
};

#endif // SET_H
