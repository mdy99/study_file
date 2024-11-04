#include <ncurses.h>

void display_buttons(WINDOW *win, const char *buttons[], int count, int highlight)
{
	for (int i = 0; i < count; i++)
	{
		if (i == highlight)
		{
			wattron(win, A_REVERSE); // 선택된 버튼 강조
			mvwprintw(win, i + 1, 1, "%s", buttons[i]);
			wattroff(win, A_REVERSE); // 강조 해제
		}
		else
		{
			mvwprintw(win, i + 1, 1, "%s", buttons[i]);
		}
	}
}

int main()
{
	initscr();						   // ncurses 초기화
	cbreak();						   // 캐릭터 모드로 전환
	noecho();						   // 입력한 내용을 화면에 표시하지 않음
	keypad(stdscr, TRUE);			   // 키패드 입력 활성화
	mousemask(ALL_MOUSE_EVENTS, NULL); // 모든 마우스 이벤트 활성화

	const char *buttons[] = {
		"Button 1",
		"Button 2",
		"Button 3",
		"Button 4",
		"Button 5"};
	int button_count = sizeof(buttons) / sizeof(buttons[0]);
	int highlight = 0; // 현재 강조된 버튼 인덱스

	// 창 크기 및 위치 정의
	int width = 30;
	int height = button_count + 2; // 버튼 수 + 테두리

	// 왼쪽 창 생성
	WINDOW *left_win = newwin(height, width, 0, 0);
	box(left_win, 0, 0); // 테두리 추가
	mvwprintw(left_win, 0, 1, " Left Window ");
	display_buttons(left_win, buttons, button_count, highlight);
	refresh();
	wrefresh(left_win); // 왼쪽 창 업데이트

	// 오른쪽 창 생성
	WINDOW *right_win = newwin(height, width, 0, width + 1);
	box(right_win, 0, 0); // 테두리 추가
	mvwprintw(right_win, 0, 1, " Right Window ");
	display_buttons(right_win, buttons, button_count, highlight);
	refresh();
	wrefresh(right_win); // 오른쪽 창 업데이트

	// 메시지를 표시할 새로운 창 생성
	WINDOW *msg_win = newwin(3, width * 2 + 1, height + 1, 0);		  // 창의 위치와 크기 설정
	box(msg_win, 0, 0);												  // 테두리 추가
	mvwprintw(msg_win, 1, 1, " Click a button to see the message. "); // 초기 메시지
	refresh();
	wrefresh(msg_win); // 메시지 창 업데이트

	MEVENT event;
	while (true)
	{
		int ch = getch(); // 입력 대기
		if (ch == KEY_MOUSE)
		{
			if (getmouse(&event) == OK)
			{ // 마우스 이벤트 가져오기
				if (event.bstate & BUTTON1_CLICKED)
				{ // 왼쪽 버튼 클릭
					// 클릭된 위치에서 버튼을 찾음
					WINDOW *clicked_win = (event.x < width) ? left_win : right_win; // 클릭한 창 확인

					for (int i = 0; i < button_count; i++)
					{
						if (event.y == i + 1 && (clicked_win == left_win || clicked_win == right_win))
						{ // 클릭한 Y 좌표가 버튼의 Y 좌표와 일치하면
							mvwprintw(msg_win, 1, 1, "You clicked: %s", buttons[i]);
							refresh();
							wrefresh(msg_win); // 메시지 업데이트
							break;
						}

					https: // github.com/shiftkey/desktop
					}
				}
			}
		}
	}

	delwin(left_win);  // 왼쪽 창 삭제
	delwin(right_win); // 오른쪽 창 삭제
	delwin(msg_win);   // 메시지 창 삭제
	endwin();		   // ncurses 종료
	return 0;
}
