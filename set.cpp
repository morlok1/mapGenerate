#include "set.h"
#include <QApplication>
set::set()
{
    grid = new QGridLayout(this);

    localAddress = new QLineEdit(this);
    localAddress->setDisabled(true);

    getImage = new QPushButton(this);
    getImage->setText("Изображение");

    info = new QLabel(this);

    sensitivity = new QSlider(this);
    sensitivity->setValue(10);
    sensitivityValue = 10;
    sensitivity->setTickInterval(1);
    sensitivity->setTracking(true);
    sensitivity->setOrientation(Qt::Orientation::Horizontal);
    sensitivity->setMaximum(256);
    sensitivity->setMinimum(0);

    sensitivityText = new QLabel(this);
    sensitivityText->setText("Чувствительность: 10");
    sensitivityText->setAlignment(Qt::AlignCenter);
    sensitivityText->setMinimumWidth(120);
    sensitivityText->setMaximumWidth(120);

    permissionToDraw = new QCheckBox(this);
    permissionToDraw->setText("Да, я хочу отрисовать здесь карту");
    permissionToDraw->setChecked(true);

    getStart = new QPushButton(this);
    getStart->setText("Сгенерировать");



    scene = new QGraphicsScene(this);
    view = new QGraphicsView(this);

    view->setGeometry(0,0,400,400);
    view->setScene(scene);

    grid->addWidget(localAddress,0,0);
    grid->addWidget(getImage,0,1,1,2);
    grid->addWidget(sensitivityText,1,1);
    grid->addWidget(sensitivity,1,2);
    grid->addWidget(permissionToDraw,2,1,1,2);
    grid->addWidget(info,2,0);
    grid->addWidget(view,3,0,1,3);
    grid->addWidget(getStart,4,0,1,3);

    setLayout(grid);

    QWidget::connect(getImage, SIGNAL (clicked()), this, SLOT (getMapImage()));
    QWidget::connect(getStart, SIGNAL (clicked()), this, SLOT (getMapGenerate()));
    QWidget::connect(sensitivity, SIGNAL (valueChanged(int)), this, SLOT (setSensitivity()));
}

set::~set()
{

}

void set::getMapImage()
{
    QString path =  QFileDialog::getOpenFileName(this,
                                                 QString::fromUtf8("Открыть файл"),
                                                 QDir::currentPath(),
                                                 "Images (*.png *.jpg);;All files (*.*)");
    localAddress->setText(path);
    mapImage.load(path);
}

void set::getMapGenerate()
{
    //Чистим сцену
    scene->clear();
    //Этот результат мы выведем
    QString resInfo;

    //Открываем файл
    QFile file("map.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);


    //Начинаем обход изображения
    for (int i=0; i<mapImage.height(); i++)
    {
        for (int j=0; j<mapImage.width(); j++)
        {
            if (mapImage.pixelColor(j,i).black() >= sensitivityValue)
            {//Я, конечно, не расист, но... если пиксел не белый
                if (permissionToDraw->isChecked())
                    createNewDote(j, i);
                file.write("1");

            }
            else
                file.write("0");
            file.write(" ");
            //Выведем процесс, для красоты
            QCoreApplication::processEvents();
        }
        file.write("\r\n");
    }
    file.close();
    resInfo = "Сгенерирована карта размером " + QString::number(mapImage.height()) + "x" + QString::number(mapImage.width()) + " точек.";
    info->setText(resInfo);
}

void set::createNewDote(double x, double y)
{
    int coeff = 2;
    QGraphicsRectItem* rect = new QGraphicsRectItem(QRectF(QPointF(coeff*x,coeff*y),QPointF(coeff*x+coeff,coeff*y+coeff)));
    scene->addItem(rect);
}

void set::setSensitivity()
{
    sensitivityValue = sensitivity->value();
    if (sensitivityValue == 0) //Если все плохо
        sensitivityText->setText("You shall not pass");
    else if (sensitivityValue == 256)
        sensitivityText->setText("Халтурим ;)");
    else
        sensitivityText->setText("Чувствительность: " + QString::number(sensitivityValue));


}
