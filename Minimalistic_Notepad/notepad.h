/* Used pragma once instead of

#ifndef NOTEPAD_H
#define NOTEPAD_H
#endif // NOTEPAD_H

to reduce the compile time
*/

#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:

    //Function Prototypes

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_File_triggered();

    void on_actionSave_as_triggered();

    void on_actionSave_as_PDF_triggered();

    void on_actionPrint_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionAbout_Us_triggered();

    void on_actionExit_triggered();

    void on_fontSizeBox_valueChanged(int val);

    void on_fontBtn_clicked();

    void on_actionConfigure_Fonts_triggered();

    void on_boldBtn_clicked();

    void on_italicBtn_clicked();

    void on_underlineBtn_clicked();

    void on_upperBtn_clicked();

    void on_lowerBtn_clicked();

    void on_leftAlignBtn_clicked();

    void on_centerBtn_clicked();

    void on_justifyBtn_clicked();

    void on_rightAlignBtn_clicked();

    void on_actionFont_Color_triggered();

    void on_highlightBtn_clicked();

    void on_comboBox_activated(const QString &col);



private:
    Ui::Notepad *ui;
    QString currentFile="";
};

