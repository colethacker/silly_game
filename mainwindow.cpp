#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickablelabel.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), findingMatch(false)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(100);
    connect(timer,SIGNAL(timeout()), this, SLOT(timerTick()));
    this->setupGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupGame()
{
    srand(time(NULL));
    int index;
    QString nextEmoji;
    QList<QString>* animalEmoji = new QList<QString>(std::initializer_list<QString>
                                                     {"🐺", "🐺"
                                                      ,"🦁", "🦁"
                                                      ,"🐯", "🐯"
                                                      ,"🦒", "🦒",
                                                      "🦊", "🦊",
                                                      "🦝", "🦝",
                                                      "🐷", "🐷",
                                                      "🐮","🐮" });

    for(auto button: this->findChildren<QPushButton*>())
    {
        button->setVisible(true);
        index = rand() % animalEmoji->count();
        nextEmoji = (*animalEmoji)[index];
        button->setText(nextEmoji);
        animalEmoji->removeAt(index);

        connect(button, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }
    timer->start();
    tenthsOfSecondsElapsed = 0;
    matchesFound = 0;
    delete animalEmoji;

}

void MainWindow::timerTick()
{
   tenthsOfSecondsElapsed++;
   ui->label->setText(QString::number(tenthsOfSecondsElapsed/10.0F, 'f', 1));
   if (matchesFound == 8)
   {
        timer->stop();
        ui->label->setText("Your time: "+ QString::number(tenthsOfSecondsElapsed/10.0F, 'f', 1)+ " seconds! Play again?");
        connect(ui->label, SIGNAL(clicked()), this, SLOT(setupClick()));
   }
}

void MainWindow::buttonClick()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if(findingMatch == false)
    {
        button->setVisible(false);
        lastEmjoiClicked = button;
        findingMatch = true;
    }

    else if(button->text() == lastEmjoiClicked->text())
    {
        button->setText("✅");
        lastEmjoiClicked->setVisible(true);
        lastEmjoiClicked->setText("✅");
        findingMatch = false;
        matchesFound++;
    }
    else
    {
        lastEmjoiClicked->setVisible(true);
        findingMatch = false;
    }
}

void MainWindow::setupClick()
{
   //disconnect(ui->label,SIGNAL(clicked()),this, SLOT(setupClick()));
    int index;
    QString nextEmoji;
    QList<QString>* animalEmoji = new QList<QString>(std::initializer_list<QString>
                                                     {"🐺", "🐺"
                                                      ,"🦁", "🦁"
                                                      ,"🐯", "🐯"
                                                      ,"🦒", "🦒",
                                                      "🦊", "🦊",
                                                      "🦝", "🦝",
                                                      "🐷", "🐷",
                                                      "🐮","🐮" });

    for(auto button: this->findChildren<QPushButton*>())
    {
        index = rand() % animalEmoji->count();
        nextEmoji = (*animalEmoji)[index];
        button->setText(nextEmoji);
        animalEmoji->removeAt(index);
    }
    timer->start();
    tenthsOfSecondsElapsed = 0;
    matchesFound = 0;

  delete animalEmoji;
}
