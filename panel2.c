// gcc -o panel2.c -Wall -o panel2 -lpanel -lncurses
#include <ncurses.h>
#include <panel.h>
#include <unistd.h>
#define NUM 3

int main() {
    initscr();
    cbreak();
    noecho();

    // 윈도우, 패널 배열 생성
    PANEL *panels[NUM];
    WINDOW *windows[NUM];

    
    for (int i = 0; i < NUM; i++) {
        windows[i] = newwin(10, 30, 5 + (5 * i), 5 + (5 * i)); // 윈도우 생성 후 WINDOW 포인터에 담아주기
        box(windows[i], 0, 0); // 보기 쉽게 박스 씌우기
        panels[i] = new_panel(windows[i]); // 윈도우를 패널 위에 올림
    }
    // 3개의 패널이 1초 간격으로 최상단으로 올라옴
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
