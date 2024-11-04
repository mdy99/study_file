#include <ncurses.h>

int main()
{
	initscr();
	keypad(stdscr, TRUE);
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	MEVENT event;

	printw("Double-click the left mouse button to test.\n");
	refresh();

	while (true)
	{
		int ch = getch();
		if (ch == KEY_MOUSE)
		{
			if (getmouse(&event) == OK)
			{
				if (event.bstate & BUTTON1_DOUBLE_CLICKED)
				{
					printw("Left button double-clicked at (%d, %d)\n", event.x, event.y);
					refresh();
				}
			}
		}
	}

	endwin();
	return 0;
}

/*
BUTTON1_CLICKED: 왼쪽 버튼 클릭
BUTTON1_DOUBLE_CLICKED: 왼쪽 버튼 더블 클릭
BUTTON1_TRIPLE_CLICKED: 왼쪽 버튼 트리플 클릭
BUTTON2_CLICKED: 중간 버튼 클릭
BUTTON2_DOUBLE_CLICKED: 중간 버튼 더블 클릭
BUTTON2_TRIPLE_CLICKED: 중간 버튼 트리플 클릭
BUTTON3_CLICKED: 오른쪽 버튼 클릭
BUTTON3_DOUBLE_CLICKED: 오른쪽 버튼 더블 클릭
BUTTON3_TRIPLE_CLICKED: 오른쪽 버튼 트리플 클릭
BUTTON4_CLICKED: 스크롤 휠 위로 클릭
BUTTON5_CLICKED: 스크롤 휠 아래로 클릭
REPORT_MOUSE_POSITION: 마우스 위치 보고
*/