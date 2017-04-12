#include "set.h"

set::set()
{
    grid = new QGridLayout(this);

    getImage1 = new QPushButton(this);
    getImage1->setText("Изображение #1");

    localAddress1 = new QLineEdit(this);
    localAddress1->setDisabled(true);

    getStart = new QPushButton(this);
    getStart->setText("Сложить");

    info = new QLabel(this);

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(this);

    view->setGeometry(0,0,400,400);
    view->setScene(scene);

    grid->addWidget(view,1,0,1,2);

    grid->addWidget(localAddress1,0,0);
    grid->addWidget(getImage1,0,1);

    grid->addWidget(getStart,2,0,1,2);
    grid->addWidget(info,3,0,1,2);

    setLayout(grid);

    QWidget::connect(getImage1, SIGNAL (clicked()), this, SLOT (getFirstImage()));
    QWidget::connect(getStart, SIGNAL (clicked()), this, SLOT (getImageSum()));
}

set::~set()
{

}

void set::getFirstImage()
{
    QString path =  QFileDialog::getOpenFileName(this,
                                                 QString::fromUtf8("Открыть файл"),
                                                 QDir::currentPath(),
                                                 "Images (*.png *.xpm *.jpg);;All files (*.*)");
    localAddress1->setText(path);
    pic1.load(path);
}

void set::getImageSum()
{
    uchar* data = new uchar[pic1.height()*pic1.width()];
    for (int i=0; i<pic1.width(); i++)
    {
        for (int j=0; j<pic1.height(); j++)
        {
            if (pic1.pixelColor(i,j).black() > 1)
            {
                createNewDote(i, j);
            }
        }
    }
    //picR = QImage(data, pic1.height(), pic2.width(), QImage::Format_ARGB32);
    //picR.save("result.png","PNG");
    info->setText(QString::number(pic1.height()) + "x" + QString::number(pic1.width()));
}

void set::createNewDote(double x, double y)
{
    int coeff = 2;
    QGraphicsRectItem* rect = new QGraphicsRectItem(QRectF(QPointF(coeff*x,coeff*y),QPointF(coeff*x+coeff,coeff*y+coeff)));
    scene->addItem(rect);
}

