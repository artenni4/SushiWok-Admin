#pragma once

#include <Python.h>
#include <QDialog>
namespace Ui { class AddActiveOrderDialog; };

class AddActiveOrderDialog : public QDialog
{
	Q_OBJECT
public:
	AddActiveOrderDialog(PyObject *pAddOrderFunction, QWidget *parent = Q_NULLPTR);
	~AddActiveOrderDialog();

private:
	Ui::AddActiveOrderDialog *ui;
	PyObject* pFunction;
};
