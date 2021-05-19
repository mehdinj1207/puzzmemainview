
#include "PuzzleMainView.h"
#include "ui_PuzzleMainView.h"
#include <ctime>
#include <QPrinter>
#include <QDialog>
#include <QPrintDialog>
#include <QMessageBox>
#include <QFileDialog>

PuzzleMainView::PuzzleMainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PuzzleMainView)
{
    ui->setupUi(this);
    this->createGame(4);
    scene->resetColorToWhite();
    scene->plotBoard();
    scene->resetSceneRect();
    setResultText("Welcome to takuzu");

    ui->comboBoxLevel->addItem("Easy");
    ui->comboBoxLevel->addItem("Medium");
    ui->comboBoxLevel->addItem("Hard");

    //PuzzleBook *book = new PuzzleBook();
    //book->saveNewGame(puzzle);
}

PuzzleMainView::~PuzzleMainView()
{
    delete ui;
    delete scene;
}

void PuzzleMainView::setResultText(std::string message)
{
    ui->labelMessage->setText(QString::fromStdString(message));
}

void PuzzleMainView::setResultTextQs(QString message)
{
    ui->labelMessage->setText(message);
}


void PuzzleMainView::createGame(int size)
{
    puzzle = new takuzu(size);
    scene = new PuzzleScene(this);
    scene->set_takuzu(puzzle);
    //scene->setSceneRect(0,0,400,400);
    ui->graphicsView->setScene(scene);
}

void PuzzleMainView::clearGame()
{
    delete scene;
    delete puzzle;
}

void PuzzleMainView::on_buttonSolve_clicked()
{
    setResultText("Solving game...");
    scene->clear();

    if(puzzle->solveRandom())
        setResultText("The board was solved .");
    else
        setResultText("The board could not be solved.");

    scene->plotBoard();
}

/*void PuzzleMainView::on_buttonLight_clicked()
{
    if(ui->buttonLight->text().toStdString() == "Light Off")
    {
        ui->buttonLight->setText(QString::fromStdString("Light On"));
        scene->resetColorToBlack();
    }
    else
    {
        ui->buttonLight->setText(QString::fromStdString("Light Off"));
        scene->resetColorToWhite();
    }
    scene->plotBoard();
}*/

void PuzzleMainView::on_buttonCheck_clicked()
{
    setResultText(puzzle->checkVictory());
}

int PuzzleMainView::getDifficultyPercentage()
{
    int diff = 0;

    if(ui->comboBoxLevel->currentText() == "Hard")
        diff = 35;
    else if(ui->comboBoxLevel->currentText() == "Medium")
        diff = 45;
    else if(ui->comboBoxLevel->currentText() == "Easy")
        diff = 65;

    return diff;
}

void PuzzleMainView::on_buttonGenerator_clicked()
{
    int size = ui->textSize->text().toInt();

    if((size % 2) != 0 || size == 0)
    {
        setResultText("The size must be a positive even number.");
        return;
    }

    clearGame();
    createGame(size);

    setResultText("Solving game...");
    scene->clear();

    if(puzzle->createNewGame(getDifficultyPercentage()))
    {
        setResultText("The game was created.");
    } else {
        setResultText("The board could not be created.");
    }

    //puzzle->obfuscatePuzzle(10);
    scene->plotBoard();
}

void PuzzleMainView::on_buttonHints_clicked()
{
    puzzle->solveHint();
    scene->clear();
    scene->plotBoard();

    setResultText("You got a hint!");
}

void PuzzleMainView::on_buttonSave_clicked()
{
    /*QPrinter printer;
    if (QPrintDialog(&printer).exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        painter.setRenderHint(QPainter::Antialiasing);
        scene->render(&painter);*/
    QMessageBox msgBox;
    msgBox.setText("The game has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
      case QMessageBox::Save:


          break;
      case QMessageBox::Discard:
          // Don't Save was clicked
          break;
      case QMessageBox::Cancel:
          // Cancel was clicked
          break;
      default:
          // should never be reached
          break;
    }
   if (ret == QMessageBox::Save ) {
       QPrinter printer;
       if (QPrintDialog(&printer).exec() == QDialog::Accepted) {
           QPainter painter(&printer);
           painter.setRenderHint(QPainter::Antialiasing);
           scene->render(&painter);
   }

}
}

/*void PuzzleMainView :: on_buttonScore_clicked()
{

    if(puzzle->solveRandom())
    {
        scene->clear();
        scene->score(50);
        scene->plotBoard();



    }


}*/


