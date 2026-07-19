#ifndef FORMLABELSCREENVIEWA_H
#define FORMLABELSCREENVIEWA_H

#include <QWidget>
#include <QTabWidget>
#include <QTabBar>
#include <QIcon>
#include <QMenu>
#include <QAction>

namespace Ui { class FormLabelScreenViewA; }

class StackedWidgetTabOptions;  // 전방 선언

typedef struct {
    QTabWidget* tabWidget;
    QWidget* newTab;
    QWidget* plusTab;
    QWidget* widget;
    QMenu* contextMenu;
    QAction* actionOptions;
    QAction* actionClose;
    int* plusIndex;
} TabStruct;

typedef struct {
    int index;
    int count;
    int plusIdx;
    bool exists;
} BaseTypes;

class FormLabelScreenViewA : public QWidget {
    Q_OBJECT
public:
    explicit FormLabelScreenViewA(QWidget* parent = nullptr);
    ~FormLabelScreenViewA();

private slots:
    void handleClickedTab(int index);
    void handleTabCloseRequested(int index);
    void showContextMenu(const QPoint& pos);
    void handleOptions();
    void handleClose();

private:
    struct Impl;   // PIMPL 구조체 선언
    Impl* d;       // 구현 포인터
};

#endif
