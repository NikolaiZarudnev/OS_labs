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
Примеры запуска:\n ./lab1.sh -k <port>\n ./lab1.sh -t on/off <name>";;

-n)
    ip -o link show | awk '{print $2,$9}' ;;
-t)
    if [[ "$2" == "on" ]]; then
        shift
        shift
        for intrfc in $@
        do
            #Включение интерфейса
            sudo ip link set $intrfc up
            echo $intrfc "- switch on"
        done
    elif [[ "$2" == "off" ]]; then
        shift
        shift
        for intrfc in $@
        do
            #Отключение интерфейса
            sudo ip link set $intrfc down
            echo $intrfc "- switch off"
        done
    else
        echo "./lab1.sh -o on/off name"
    fi;;
-s)
    #добавление IP/Mask для сетевого интерфейса
    ip addr add $3/$4 dev $5
    echo "IP/Mask добавлен."

    #Добавление шлюза
    ip route add default via $6
    echo "Шлюз добавлен.";;
-k) ;;
-d) ;;
*) echo "$1 is not an option" ;;
esac
shift
done
echo