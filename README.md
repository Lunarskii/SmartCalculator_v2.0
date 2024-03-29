# SmartCalculator v2.0

## Возможности

- Графический интерфейс
- Вычисление произвольных скобочных арифметических выражений в инфиксной нотации, содержание которых может иметь целые, вещественные и в экспоненциальной форме записи числа
- Вычисление произвольных скобочных арифметических выражений в инфиксной нотации с подстановкой значения переменной _x_ в виде числа
- Построение графика функции, заданной с помощью выражения в инфиксной нотации с переменной _x_  (с координатными осями, отметкой используемого масштаба и сеткой с адаптивным шагом)
- Кредитный калькулятор
- Депозитный калькулятор

## Перед установкой

Перед началом установки убедитесь, что у вас установлены следующие пакеты:

- 'GCC'
- 'MAKE'
- 'CMAKE'
- 'QT5' и выше
- 'OpenGL API'

## Установка

- Из папки репозитория выполните следующую команду (приложение будет находиться в репозитории)

```sh
make install
```

## Запуск

- Из папки репозитория выполните следующую команду

```sh
make launch
```

## Архивация файлов

- Из папки репозитория выполните следующую команду (архив будет находиться в репозитории)

```sh
make dist
```

## Удаление

- Из папки репозитория выполните следующую команду

```sh
make uninstall
```