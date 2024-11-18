// gcc -o panel1.c -Wall -o panel1 -lpanel -lncurses
#include <ncurses.h>
#include <panel.h>
#include <unistd.h>

int main() {
    initscr();
    cbreak();
    noecho();

    // 패널 시스템 초기화
    PANEL *panel1, *panel2;
    WINDOW *win1, *win2;

    // 두 개의 윈도우를 생성
    win1 = newwin(10, 30, 5, 5);
    win2 = newwin(10, 30, 10, 10);

    box(win1, 0, 0);
    box(win2, 0, 0);

    // 두 개의 패널을 생성
    panel1 = new_panel(win1);
    panel2 = new_panel(win2);

    // 첫 번째 패널을 가장 위로 올림
    top_panel(panel1);
    update_panels();  // 패널의 논리적 상태를 업데이트하며, 커널과 직접 상호작용하지 않습니다.
    doupdate();  // 변경된 내용을 커널을 통해 터미널로 출력하며, 터미널 드라이버와의 상호작용이 포함됩니다.

    // 5초 동안 대기
    sleep(5);

    // 두 번째 패널을 가장 위로 올림
    top_panel(panel2);
    update_panels();
    doupdate();

    // 종료 처리
    sleep(5);
    endwin();
    return 0;
}
