#include "view.h"

namespace s21 {

View::View(Controller* c, QWidget* parent)
    : controller(c)
    , QMainWindow(parent)
    , ui(new s21::View)
{
    ui->setupUi(this);
    setlocale(LC_NUMERIC, "C");

    // Создаем три экземпляра калькуляторов
    smartView = new SmartView(controller);
    creditView = new CreditView(controller);
    depositView = new DepositView(controller);

    // Создаем вкладки для каждого калькулятора
    QTabWidget* tabs = new QTabWidget(this);
    tabs->addTab(smartView, tr("Smart"));
    tabs->addTab(creditView, tr("Credit"));
    tabs->addTab(depositView, tr("Deposit"));

    // Устанавливаем вкладки в центр главного окна
    setCentralWidget(tabs);

    // Устанавливаем текущую вкладку на Smart калькулятор
    tabs->setCurrentIndex(0);
}

View::~View()
{
    delete smartView;
    delete creditView;
    delete depositView;
    delete ui;
}

}  // namespace s21
