#include <ncurses.h>

int main()
{
	initscr();															  // ncurses 초기화
	mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED | BUTTON3_CLICKED, NULL); // 왼쪽, 중간, 오른쪽 버튼 클릭 이벤트 활성화
	keypad(stdscr, TRUE);												  // 키패드 입력 활성화
	noecho();															  // 입력한 내용을 화면에 표시하지 않음

	MEVENT event;
	while (true)
	{
		int ch = getch(); // 입력 대기
		if (ch == KEY_MOUSE)
		{
			if (getmouse(&event) == OK)
			{ // 마우스 이벤트 가져오기
				if (event.bstate & BUTTON1_CLICKED)
				{
					printw("Left button clicked at (%d, %d)\n", event.x, event.y);
				}
				if (event.bstate & BUTTON2_CLICKED)
				{
					printw("Middle button clicked at (%d, %d)\n", event.x, event.y);
				}
				if (event.bstate & BUTTON3_CLICKED)
				{
					printw("Right button clicked at (%d, %d)\n", event.x, event.y);
				}
				refresh(); // 화면 업데이트
			}
		}
	}

	endwin(); // ncurses 종료
	return 0;
}
