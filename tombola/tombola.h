#ifndef TOMBOLA_H
#define TOMBOLA_H

#include <QMainWindow>
#include "QDebug"
#include "QTime"
#include <QtGui>
#include <QList>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include <QMessageBox>
#include <QTimer>
namespace Ui {
class Tombola;
}

class Tombola : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tombola(QWidget *parent = 0);
    QLabel *create_label(int number);
    void set_horizontal_line(int i, QVBoxLayout *l);
    void setup_column(QVBoxLayout *column, int increment);
    ~Tombola();

public slots:
    void extract_number();
    void reset();
private:
    Ui::Tombola *ui;
    QList<int> extracted;
    QList<QLabel*> buttons = QList<QLabel*>();
    void show_number_extracted(int number);
};

#endif // TOMBOLA_H
