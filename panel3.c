// // gcc -o panel3.c -Wall -o panel3 -lpanel -lncurses
#include <ncurses.h>
#include <panel.h>
#include <unistd.h>
#define NUM 3

int main() {
    initscr();
    cbreak();
    noecho();

    // 패널 시스템 초기화
    PANEL *panels[NUM];
    WINDOW *windows[NUM];

    // 두 개의 패널을 생성
    for (int i = 0; i < NUM; i++) {
        windows[i] = newwin(10, 30, 5 + (5 * i), 5 + (5 * i));  // 1. 윈도우를 생성한다.
        box(windows[i], 0, 0);  // 2. 보기 쉽게 박스를 씌워준다
        panels[i] = new_panel(windows[i]);  // 3. 윈도우를 패널 위에 올린다.
    }

    int ch;
    while ((ch = getch()) != 'q') {
        if (ch == '0') {  // 0을 누르면, 0번 패널이 최상단으로 올라옴
            top_panel(panels[0]);
        } else if (ch == '1') {  // 1을 누르면, 1번 패널이 최상단으로 올라옴
            top_panel(panels[1]);
        } else if (ch == '2') {  // 2을 누르면, 2번 패널이 최상단으로 올라옴
            top_panel(panels[2]);
        }
        update_panels();
        doupdate();
    }
    // 종료 처리
    sleep(5);
    endwin();
    return 0;
}
