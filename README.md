﻿# slot_machine
simple slot machine

Проект состоит из 11 модулей с заголовочными файлами.
1)  slot_machine.cpp
        Файл для главной точки входа (функции main)
        запускает конструктор LMain
        обрабатывает нажатие на кнопку, вращение барабанов и перерисовку
2)  LMain.cpp
        Модуль для создания основных объектов:
        приложение, раскладка, вращение, перерисовка и таймер
3)  LApplication.cpp - приложение
        Инициализирует SDL2, SDL2_image и SDL2_ttf
4)  LLayout.cpp - раскладка
        Инициализирует фон, массив барабанов, текст FPS и кнопку
        Некоторые размеры объектов рассчитываются в заголовочном файле
5)  LRotation.cpp - вращение
        Поворачивает все барабаны, в конце замедляет вращение
6)  LRender.cpp - перерисовка
        Перерисовывает фон, массив барабанов, текст FPS и кнопку
7)  LTimer.cpp - таймер
        Считает миллисекунды, рассчитывает число кадров в секунду
        и переводит в строку для отображения
8)  LBackground.cpp - фон
9)  LDrum.cpp - массив барабанов
        Каждый барабан содержит 12 символов, из которых три повторяются
        когда вращение доходит до края барабана, он скачком переключается
        так что видимые символы остаются теми-же
10) LFPSText.cpp - текст FPS
11) LButton.cpp - кнопка
        Содержит несколько спрайтов, которые переключаются
        и создают эффект мигания
