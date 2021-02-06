#include "notepad.h"
#include "ui_notepad.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextCursor>
#include <QColorDialog>
#include <QFile>
#include <QFontDialog>
#include <QFont>

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);

}

Notepad::~Notepad()
{
    delete ui;
}

//Function - New Document

void Notepad::on_actionNew_triggered()
{
   currentFile.clear();
   ui->textEdit->setText(QString());
}

//Function - Open

void Notepad::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open File");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning ","Unable to Open the File");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();

}

//Function - Save

void Notepad::on_actionSave_File_triggered()
{
    QFile file(currentFile);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QString filename = QFileDialog::getSaveFileName(this,"Save File");
        QFile file(filename);
        currentFile = filename;
        if(!file.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::warning(this," ","Failed to Save");
            return;
        }
        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.close();
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

//Function - Save as

void Notepad::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,"Save File");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this," ","File not Saved");
        return;
    }
    currentFile=filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();

}

//Function - save as PDF

void Notepad::on_actionSave_as_PDF_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
    "untitled",tr("PDF Document (*.pdf)"));
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);
    ui->textEdit->print(&printer);

}

//Function - Print

void Notepad::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog dialog(&printer,this);
    if (dialog.exec() == QDialog::Rejected)
    {
      QMessageBox::information(this,"Reminder","You Didn't Select a Printer");
        return;
    }
    ui->textEdit->print(&printer);

}

//Function - Redo

void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

//Function - Undo

void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

//Function - Cut

void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

//Function - Paste

void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

//Function - About

void Notepad::on_actionAbout_Us_triggered()
{
    QString about;
    about = "Minimalistic Notepad\nCopyright © 2020 by Kaveesha Pathirana";
    QMessageBox::about(this,"About",about);

}

//Function - Quit Application

void Notepad::on_actionExit_triggered()
{
    QApplication::quit();
}


//Function - Set sont size (Sizes : min 12 , max 72)

void Notepad::on_fontSizeBox_valueChanged(int val)
{
    int fsize = val;
    QTextCursor cursor = ui->textEdit->textCursor();
        if (cursor.isNull())
            return;

        if (!cursor.hasSelection())
            cursor.select(QTextCursor::WordUnderCursor);

        if (cursor.charFormat().property(QTextFormat::FontPointSize).toInt() == fsize)
            return;

        QTextCharFormat format;
        format.setFontPointSize(fsize);
        if (!cursor.hasSelection())
            cursor.select(QTextCursor::WordUnderCursor);
        cursor.mergeCharFormat(format);
        ui->textEdit->mergeCurrentCharFormat(format);

}


//Function - change font button

void Notepad::on_fontBtn_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok)
    {
        ui->textEdit->setFont(font);
    }else return;
}

//Function - change font Action in menubar

void Notepad::on_actionConfigure_Fonts_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok)
    {
        ui->textEdit->setFont(font);
    }else return;
}

//function - Bold Letters

void Notepad::on_boldBtn_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if(!cursor.charFormat().font().bold())
    {
        ui->textEdit->setFontWeight(QFont::Bold);
    }
    else
    {
        ui->textEdit->setFontWeight(QFont::Normal);
    }

}

// function - Italic Letters

void Notepad::on_italicBtn_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if(!cursor.charFormat().font().italic())
    {
        ui->textEdit->setFontItalic(QFont::StyleItalic);
    }
    else
    {
        ui->textEdit->setFontItalic(QFont::StyleNormal);
    }

}

//function - Underline Letters

void Notepad::on_underlineBtn_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if(!cursor.charFormat().font().underline())
    {
        ui->textEdit->setFontUnderline(Qt::SolidLine);
    }
    else
    {
        ui->textEdit->setFontUnderline(QFont::StyleNormal);
    }

}

//function - change fonts to Uppercase Letters

void Notepad::on_upperBtn_clicked()
{
    QTextCharFormat format;
    format.setFontCapitalization(QFont::AllUppercase);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.mergeCharFormat(format);

}

//function - change fonts to Lowercase Letters

void Notepad::on_lowerBtn_clicked()
{
    QTextCharFormat format;
    format.setFontCapitalization(QFont::AllLowercase);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.mergeCharFormat(format);
}

//function - Left-Align

void Notepad::on_leftAlignBtn_clicked()
{
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignLeft);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.mergeBlockFormat(format);
}

//function - Center-Align

void Notepad::on_centerBtn_clicked()
{
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignCenter);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.mergeBlockFormat(format);
}

//function - Justify-Align

void Notepad::on_justifyBtn_clicked()
{
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignJustify);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.mergeBlockFormat(format);

}

//function - Right-Align

void Notepad::on_rightAlignBtn_clicked()
{
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignRight);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.mergeBlockFormat(format);

}

//function - for change font colors Action in the menu bar

void Notepad::on_actionFont_Color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Select Color");
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }

}

//function - for highlight fonts and sentences

void Notepad::on_highlightBtn_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white,this,"Select Color");
    if(color.isValid())
    {
        ui->textEdit->setTextBackgroundColor(color);
    }

}


//function - for change font colors

void Notepad::on_comboBox_activated(const QString &col)
{
    QBrush color;
    if (col== "Red")
    {
        color = Qt::red;
    }
    else if(col== "Blue")
    {
        color = Qt::blue;
    }
    else if(col== "Gray")
    {
        color = Qt::gray;
    }
    else if(col== "Green")
    {
        color = Qt::green;
    }
    else if(col== "Yellow")
    {
        color = Qt::yellow;
    }
    else if(col== "Cyan")
    {
        color = Qt::cyan;
    }
    else if(col== "Magenta")
    {
        color = Qt::magenta;
    }
    else
    {
        color = Qt::black;
    }
    QTextCharFormat format;
    format.setForeground(color);
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.mergeCharFormat(format);
}

