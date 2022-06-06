//
// Created by stefa on 4/18/2022.
//

#include "main.h"

namespace Console {
    void gotoxy(short row, short col) {
        COORD coords = {col, row};
        SetConsoleCursorPosition(
                GetStdHandle(STD_OUTPUT_HANDLE),
                coords
        );
    }

    void setCursorVisibility(bool isVisible) {
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = isVisible;
        SetConsoleCursorInfo(
                GetStdHandle(STD_OUTPUT_HANDLE),
                &info
        );
    }

//    void toggleCursorVisibility() {
//
//        HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//
//        CONSOLE_CURSOR_INFO cursorInfo;
//
//
//        GetConsoleCursorInfo()
//        bool isVisible = GetConsoleCursorInfo(, );
//
//        CONSOLE_CURSOR_INFO info;
//        info.dwSize = 100;
//        info.bVisible = isVisible;
//        SetConsoleCursorInfo(
//                GetStdHandle(STD_OUTPUT_HANDLE),
//                &info
//        );
//    }

    void main() {
        getchar();
        gotoxy(1, 3);

//        getchar();
//        toggleCursorVisibility();

//        getchst();
//        toggleCursorVisibility();

        getchar();
        setCursorVisibility(true);
        getchar();
        setCursorVisibility(false);
    }
}
