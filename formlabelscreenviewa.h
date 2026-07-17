#ifndef FORMLABELSCREENVIEWA_H
#define FORMLABELSCREENVIEWA_H

#include <QWidget>
#include <QTabWidget>
#include <QTabBar>
#include <QIcon>

namespace Ui { class FormLabelScreenViewA; }

typedef struct {
    QTabWidget *tabWidget;
    QWidget *newTab;
    QWidget *plusTab;
    QWidget *widget;
    int plusIndex;
} TabStruct;

class FormLabelScreenViewA : public QWidget {
    Q_OBJECT
public:
    explicit FormLabelScreenViewA(QWidget *parent = nullptr);
    ~FormLabelScreenViewA();

private slots:
    void handleClickedTab(int index);
    void handleTabCloseRequested(int index);

private:
    Ui::FormLabelScreenViewA *ui;
    TabStruct *tabs;
};

#endif // FORMLABELSCREENVIEWA_H
