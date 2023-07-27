/**
 *
 * @file myopenglwidget.cpp
 *
 */
#include "myopenglwidget.h"

#include <unistd.h>

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    :QOpenGLWidget { parent }
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update())); // таймер для обновления
    timer->start(1); // скорость обновления
}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnableClientState(GL_VERTEX_ARRAY); // нужно для функции "glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);"
    glEnable(GL_POINT_SMOOTH); // нужно для "glDrawArrays(GL_POINTS, 0, 99);" Отрисовки рёбер
}

void MyOpenGLWidget::paintGL()
{
    glClearColor(normalize_0_1(r), normalize_0_1(g), normalize_0_1(b), a); // цвет фона

    // включение и выключение пунктирных линий
    if(LineStipple == 0)
        glEnable(GL_LINE_STIPPLE);
    else if(LineStipple == 1)
        glDisable(GL_LINE_STIPPLE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Resetear transformaciones
    glLoadIdentity();
    if(ProjectionType == 1)
        glOrtho(-2,2, -2,2, -5,100); // Прямая (Орографическая) проекция
    else if(ProjectionType == 0)
        glFrustum(-2,2, -2,2, -5,100); // Центральная (перспективная) проекция

    glRotated(xRot, 1, 0, 0);
    glRotated(yRot, 0, 1, 0);

    if ((x!=def_x)||(y!=def_y)||(z!=def_z)) {
        move_xyz(res, x-def_x, y-def_y , z-def_z);
        def_x=x;
        def_y=y;
        def_z=z;
    } // сдвиг по осям наш

    if (Rx != defRx) {
        rotation_x(res, ((Rx-defRx) * 2 * M_PI)/ 360);
        defRx=Rx;
    }
    if (Ry != defRy) {
        rotation_y(res, ((Ry-defRy) * 2 * M_PI)/ 360);
        defRy=Ry;
    }
    if (Rz != defRz) {
        rotation_z(res, ((Rz-defRz) * 2 * M_PI)/ 360);
        defRz=Rz;
    }
    if(autorotate != 0) rotation_y(res, 0.05);

    glLineStipple(1, 1); // пунктирные линии
    glColor3i(LineR, LineG, LineB); // цвет линиий (255, 255, 255) - белый
    glLineWidth(LineSize); // толщина линий

    // begin extern "C" -------------------------------------------------------------

    QByteArray ba = str.toLocal8Bit();
    char *c_str2 = ba.data();
    filename = c_str2;

    if(FOpen == 1) { // заполнение матриц
        deallocation(res);
        quantity(res, filename);
        if(allocation(res)) {
            record(res, filename);
            autoscale(res);
        } else {
            lbl_36->setText("Memory");
            lbl->setText("Error");
        }
        lbl_36->setText(QString::number(res->polygons.count_vertexes / 2));
        lbl->setText(QString::number(res->matrix_xyz.rows / 3));
        x = 0.0, y = 0.0, z = 0.0;
        def_x = 0.0, def_y = 0.0, def_z = 0.0;
        Rx = 0.0, Ry = 0.0, Rz = 0.0;
        defRx = 0.0, defRy = 0.0, defRz = 0.0;
        FOpen = 0;
    }
    // ------------------------------------------------------------------------------

    glVertexPointer(3, GL_DOUBLE, 0, res->matrix_xyz.matrix); //принимает вершины, нужно для следующей функции
    if (LineStipple != 2)
        glDrawElements(GL_LINES, res->polygons.count_vertexes, GL_UNSIGNED_INT, res->polygons.vertexes); // принимает индексы полигонов и отрисовывает линии по вершинам из функции выше


    if(PointType != 0) { // настройки отрисовки точек
        if(PointType == 2)
            glDisable(GL_POINT_SMOOTH);// при отключение точки будут квадратные
        else
            glEnable(GL_POINT_SMOOTH);
        glColor3i(PointR, PointG, PointB); // цвет точек (255, 255, 255) - белый
        glPointSize(PointSize); // толщена точек
        glDrawArrays(GL_POINTS, 0, res->matrix_xyz.rows/3); // отрисовка точек
    }


    if(xyz != 0) graficarLineas(); // вызов функции для отрисовки линий X, Y, Z
}


void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MyOpenGLWidget::graficarLineas(){ // функция для отрисовки линий X, Y, Z
    // X
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(20,0,0);
    // Y
    glBegin(GL_LINES);
    glColor3f(1,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,20,0);
    // Z
    glBegin(GL_LINES);
    glColor3f(0,1,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,20);
    glEnd();
}

double MyOpenGLWidget::normalize_0_1(double val) const { return (val - 1) / (255 - 1); }

void MyOpenGLWidget::mousePressEvent(QMouseEvent* mo) { mPos = mo->pos(); }

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent* mo) {
    int xRotTmp = xRot, yRotTmp = yRot;
    xRot = (1 / M_PI*(mo->pos().y() - mPos.y()));
    yRot = (1 / M_PI*(mo->pos().x() - mPos.x()));
    update();
}
