#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QWidget>


class CustomTextEdit : public QTextEdit
{
    // Добавляем макрос для корректной
    // работы метасистемы Qt
    Q_OBJECT

public:
    explicit CustomTextEdit(const QString &placeholder, QWidget *parent = nullptr)
        : QTextEdit(parent), placeholderText(placeholder)
    {
        // устанавливаем начальный текст
        setText(placeholderText);
        // стилизация начального текста
        setStyleSheet("color: grey;");
    }

protected:
    void focusInEvent(QFocusEvent *event) override
    {
        if (toPlainText() == placeholderText) {
            // очищаем текст при фокусе
            clear();
            // устанавливаем обычный цвет текста
            setStyleSheet("color: black;");
        }

        QTextEdit::focusInEvent(event);
    }

    void focusOutEvent(QFocusEvent *event) override
    {
        if (toPlainText().isEmpty()) {
            // восстанавливаем текст, если поле пустое
            setText(placeholderText);
            // стилизация текста как подсказки
            setStyleSheet("color: grey;");
        }

        QTextEdit::focusOutEvent(event);
    }

private:
    QString placeholderText;
};


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Пример Qt6");

    // создаем два компонента CustomTextEdit с подсказками
    CustomTextEdit *textEdit1 = new CustomTextEdit("Введите вопрос...", &window);
    CustomTextEdit *textEdit2 = new CustomTextEdit("Введите ответ на вопрос...", &window);

    // создаем три кнопки
    QPushButton *button1 = new QPushButton("button 1", &window);
    QPushButton *button2 = new QPushButton("button 2", &window);
    QPushButton *button3 = new QPushButton("Close", &window);

    // устанавливаем фокус на button3
    button3->setFocus();

    // завершение приложения при нажатии на button3
    QObject::connect(button3, &QPushButton::clicked, &app, &QCoreApplication::quit);

    // компоновщик для кнопок
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    // добавляем растяжку для смещения кнопок вправо
    buttonLayout->addStretch();
    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);
    buttonLayout->addWidget(button3);

    // основной компоновщик для формы
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(textEdit1);
    mainLayout->addWidget(textEdit2);
    mainLayout->addLayout(buttonLayout);

    // устанавливаем компоновщик для окна
    window.setLayout(mainLayout);
    window.resize(400, 300);
    window.show();


    return app.exec();
}

#include "main.moc" // необходим для работы с Q_OBJECT в CMake или qmake
