#!/bin/bash

while [ -n "$1" ]
do
case "$1" in
-h | --help) printf "Авторы: Владислав Каширин, Далия Бесаева, Никоалай Заруднев\n
Все доступные аргументы:
-n: Вывод всех сетевых интерфейсов;
-t: Включение/отключение заданных интерфейсов (в т.ч. сразу нескольких);
-s: Установка IP/Mask/Gateway для определенного интерфейса;
-k: Убийство процесса по занимаемому порту;
-d: Отображение сетевой статистики;
Краткое описание проекта: Управление сетевыми настройками системы\n
Примеры запуска:\n ./lab1.sh -q <port>" ;;

-n) ;;
-t) ;;
-s) ;;
-k) 
    kill -9 $(lsof -t -i:$2);;
-d) 
    cat /proc/net/dev;;
*) echo "$1 is not an option" ;;
esac
shift
done
echo