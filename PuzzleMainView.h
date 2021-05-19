#ifndef PUZZLEMAINVIEW_H
#define PUZZLEMAINVIEW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include "takuzu.h"
#include "PuzzleScene.h"
#include "PuzzleSceneItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PuzzleMainView; }
QT_END_NAMESPACE

class PuzzleMainView : public QMainWindow
{
    Q_OBJECT

public:
    PuzzleMainView(QWidget *parent = 0);
    ~PuzzleMainView();

private slots:
    void on_buttonSolve_clicked();

    //void on_buttonLight_clicked();

    void on_buttonCheck_clicked();

    void on_buttonGenerator_clicked();

    void on_buttonHints_clicked();

    //void on_buttonScore_clicked();

    void on_buttonSave_clicked();


//
private:
    Ui::PuzzleMainView *ui;
    takuzu *puzzle = NULL;
    PuzzleScene *scene = NULL;
    void clearGame();
    void createGame(int size);
    void setResultText(std::string message);
    int getDifficultyPercentage();
    void setResultTextQs(QString message);
};
#endif // PUZZLEMAINVIEW_H
