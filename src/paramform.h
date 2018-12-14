#ifndef PARAMFORM_H
#define PARAMFORM_H

#include <QDialog>
#include "SolarSystem.h"
#include "AstronmicalObject.h"

namespace Ui {
class ParamForm;
}

class ParamForm : public QDialog
{
    Q_OBJECT

public:
    explicit ParamForm(QWidget *parent = nullptr, AstronmicalObject *astronmicalObject = nullptr);
    ~ParamForm();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ParamForm *ui;
    AstronmicalObject *astronmicalObject;
};

#endif // PARAMFORM_H
