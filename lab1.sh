#!/bin/bash

case "$1" in
-h | --help) printf "Авторы: Владислав Каширин, Далия Бесаева, Никоалай Заруднев\n
Все доступные аргументы:
-n: Вывод всех сетевых интерфейсов;
-t: Включение/отключение заданных интерфейсов (в т.ч. сразу нескольких);
-s: Установка IP/Mask/Gateway для определенного интерфейса;
-k: Убийство процесса по занимаемому порту;
-d: Отображение сетевой статистики;\n
Краткое описание проекта: Управление сетевыми настройками системы\n
Примеры запуска:\n ./lab1.sh -o on/off <name>\n ./lab1.sh -k <port>";;

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
        echo "./lab1.sh -t on/off <name>"
    fi;;
-s)
    #добавление IP/Mask для сетевого интерфейса
    ip addr add $3/$4 dev $5
    echo "IP/Mask добавлен."

    #Добавление шлюза
    ip route add default via $6
    echo "Шлюз добавлен.";;
-k) 
    kill -9 $(lsof -t -i:$2);;
-d) 
    cat /proc/net/dev;;
*) echo "'$1' is not an option" ;;
esac

echo
