// gcc -o panel2.c -Wall -o panel2 -lpanel -lncurses
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
        windows[i] = newwin(10, 30, 5 + (5 * i), 5 + (5 * i));
        box(windows[i], 0, 0);
        panels[i] = new_panel(windows[i]);
    }

    for (int i = 0; i < 12; i++) {
        top_panel(panels[(i % 3)]);
        update_panels();
        doupdate();
        sleep(1);
    }

    // 종료 처리
    sleep(5);
    endwin();
    return 0;
}
