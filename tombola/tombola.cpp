#include "tombola.h"
#include "ui_tombola.h"

Tombola::Tombola(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tombola)
{
    ui->setupUi(this);

    setup_column(ui->column_1, 1);
    setup_column(ui->column_2, 2);
    setup_column(ui->column_3, 3);
    setup_column(ui->column_4, 4);
    setup_column(ui->column_5, 5);
    setup_column(ui->column_6, 6);
    setup_column(ui->column_7, 7);
    setup_column(ui->column_8, 8);
    setup_column(ui->column_9, 9);
    setup_column(ui->column_10, 10);
}

Tombola::~Tombola()
{
    delete ui;
}

void Tombola::setup_column(QVBoxLayout *column, int increment) {
    int count = 0;
    for(int i = 1; i < 10; i++) {
        set_horizontal_line(i, column);
        QLabel* l = create_label(count * 10 + increment);
        buttons.append(l);
        column->addWidget(l);
        count++;
    }
}

QLabel* Tombola::create_label(int number) {
    QLabel *button = new QLabel();
    button->setText(QString::number(number));
    button->setMinimumWidth(50);
    button->setMinimumHeight(50);
    button->setAlignment(Qt::AlignCenter);
    button->setObjectName(QString::number(number));
    button->setAttribute(Qt::WA_TranslucentBackground);
    button->setStyleSheet(
        "background-color: darkRed;"
        "border: 1px solid black;"
        "border-radius: 15px;"
        "color: lightGray; "
        "font-size: 70px;"
        "font: bold;"
        );
    return button;
}

void Tombola::set_horizontal_line(int i, QVBoxLayout* l) {
    if(i%3==1 && i != 1) {
        QWidget *horizontalLineWidget = new QWidget;
        horizontalLineWidget->setFixedHeight(2);
        horizontalLineWidget->setStyleSheet("background-color: black");
        l->addWidget(horizontalLineWidget);
    }
}

void Tombola::reset(){
    qDebug()  << "Press reset button";
    for(int y = 0; y < buttons.size(); y++) {
        buttons.at(y)->setAttribute(Qt::WA_TranslucentBackground);
        buttons.at(y)->setStyleSheet(
                    "background-color: darkRed;"
                    "border: 1px solid black;"
                    "border-radius: 15px;"
                    "color: lightGray; "
                    "font-size: 70px;"
                    "font: bold;"
                    );
        buttons.at(y)->update();
    }
    extracted.clear();
}

void Tombola::extract_number(){
    qDebug()  << "Press next number button";
    if(extracted.isEmpty()) {
        extracted = QList<int>();
    }
    if(extracted.size() >= 90) {
         qDebug()  << "no more value";
        return;
    }
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
    int i = ((qrand() % ((90 + 1) - 1)) + 1);
    while(extracted.contains(i)) {
        qDebug() << "Already present";
        i = ((qrand() % ((90 + 1) - 1)) + 1);
    }

    show_number_extracted(i);

    for(int y = 0; y < buttons.size(); y++) {
        if (QString::compare(buttons.at(y)->objectName(), QString::number(i), Qt::CaseInsensitive) == 0) {
            buttons.at(y)->setAttribute(Qt::WA_TranslucentBackground);
            buttons.at(y)->setStyleSheet(
                "background-color: darkRed;"
                "border: 1px solid black;"
                "border-radius: 15px;"
                "color: darkgreen;"
                "font-size: 70px;"
                "font: bold;"
                );
            buttons.at(y)->update();
            break;
        }
    }
    extracted.append(i);
    qDebug()  << extracted;
}

void Tombola::show_number_extracted(int number) {
    QFont font;
    font.setBold(true);
    font.setPixelSize(300);
    QMessageBox *mbox = new QMessageBox;
    mbox->setWindowTitle(tr("Estrazione"));
    mbox->setText(QString::number(number));
    mbox->setFont(font);
    mbox->setStandardButtons(0);
    mbox->show();
    QTimer::singleShot(3000, mbox, SLOT(hide()));

}
