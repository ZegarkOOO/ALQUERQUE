#include "Bot.h"

/*KONSTRUKTOR Z ANALIZ¥ PLANSZY*/
void Bot::analyze_board_modified(int board[5][5])
{
	//przeszukiwanie tablicy i sprawdzanie ruchów dla pionków bota
	//nadawanie danym ruchom wartoœci
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (board[i][j] >= 12 && board[i][j] <= 23) {

				//w góre
				if (i > 0) {
					if (board[i - 1][j] == -1) {
						set_max(
							board[i][j],
							Vector2i(i - 1, j),
							value_of_move(board, i, j, -1, 0)
						);
					}
					else if (board[i - 1][j] != -1 && board[i - 1][j] >= 0 && board[i - 1][j] <= 11)
					{
						if (i > 1) {
							if (board[i - 2][j] == -1) {
								set_max(board[i][j], Vector2i(i - 2, j), 10);
							}
						}
					}
				}
				//w dó³
				if (i < 4) {
					if (board[i + 1][j] == -1) {
						set_max(board[i][j], Vector2i(i + 1, j), value_of_move(board, i, j, 1, 0));
					}
					else if (board[i + 1][j] != -1 && board[i + 1][j] >= 0 && board[i + 1][j] <= 11) {
						if (i < 3) {
							if (board[i + 2][j] == -1) {
								set_max(board[i][j], Vector2i(i + 2, j), 10);
							}
						}
					}
				}
				// w lewo
				if (j > 0) {
					if (board[i][j - 1] == -1) {
						set_max(board[i][j], Vector2i(i, j - 1), value_of_move(board, i, j, 0, -1));
					}
					else if (board[i][j - 1] != -1 && board[i][j - 1] >= 0 && board[i][j - 1] <= 11) {
						if (j > 1) {
							if (board[i][j - 2] == -1) {
								set_max(board[i][j], Vector2i(i, j - 2), 10);
							}
						}
					}
				}
				//w prawo
				if (j < 4) {
					if (board[i][j + 1] == -1) {
						set_max(board[i][j], Vector2i(i, j + 1), value_of_move(board, i, j, 0, 1));
					}
					else if (board[i][j + 1] != -1 && board[i][j + 1] >= 0 && board[i][j + 1] <= 11) {
						if (j < 3) {
							if (board[i][j + 2] == -1) {
								set_max(board[i][j], Vector2i(i, j + 2), 10);
							}
						}
					}
				}
				//po skosach
				if ((i + j) % 2 == 0) {

					//lewa gora
					if (i > 0 && j > 0) {
						if (board[i - 1][j - 1] == -1) {
							set_max(board[i][j], Vector2i(i - 1, j - 1), value_of_move(board, i, j, -1, -1));
						}
						else if (board[i - 1][j - 1] != -1 && board[i - 1][j - 1] >= 0 && board[i - 1][j - 1] <= 11) {
							if (i > 1 && j > 1) {
								if (board[i - 2][j - 2] == -1)
									set_max(board[i][j], Vector2i(i - 2, j - 2), 10);
							}
						}
					}
					//prawa dó³
					if (i < 4 && j < 4) {
						if (board[i + 1][j + 1] == -1) {
							set_max(board[i][j], Vector2i(i + 1, j + 1), value_of_move(board, i, j, 1, 1));
						}
						else if (board[i + 1][j + 1] != -1 && board[i + 1][j + 1] >= 0 && board[i + 1][j + 1] <= 11) {
							if (i < 3 && j < 3) {
								if (board[i + 2][j + 2] == -1)
									set_max(board[i][j], Vector2i(i + 2, j + 2), 10);
							}
						}
					}
					//lewy dó³
					if (i < 4 && j > 0) {
						if (board[i + 1][j - 1] == -1) {
							set_max(board[i][j], Vector2i(i + 1, j - 1), value_of_move(board, i, j, 1, -1));
						}
						else if (board[i + 1][j - 1] != -1 && board[i + 1][j - 1] >= 0 && board[i + 1][j - 1] <= 11) {
							if (i < 3 && j > 1) {
								if (board[i + 2][j - 2] == -1)
									set_max(board[i][j], Vector2i(i + 2, j - 2), 10);
							}
						}

					}
					//prawa góra
					if (i > 0 && j < 4) {
						if (board[i - 1][j + 1] == -1) {
							set_max(board[i][j], Vector2i(i - 1, j + 1), value_of_move(board, i, j, -1, 1));
						}
						else if (board[i - 1][j + 1] != -1 && board[i - 1][j + 1] >= 0 && board[i - 1][j + 1] <= 11) {
							if (i > 1 && j < 3) {
								if (board[i - 2][j + 2] == -1)
									set_max(board[i][j], Vector2i(i - 2, j + 2), 10);
							}
						}
					}
				}
			}
		}
	}
}

int Bot::value_of_move(int tm_board[5][5], int p_pos_x, int p_pos_y, int mov_x, int mov_y)
{
	int value = -1;
	if(mov_x == -1 && mov_y == 0){
		//góra
		value = -1;
		if (p_pos_x == 1) {
			if (p_pos_y == 4 || p_pos_y == 0) {
				value = 5;
			}
			else if (p_pos_y >= 1 && p_pos_y <= 3) {
				if (tm_board[p_pos_x - 1][p_pos_y - 1] == -1 || (tm_board[p_pos_x - 1][p_pos_y - 1] >= 12 && tm_board[p_pos_x - 1][p_pos_y - 1] <= 23)) {
					if (tm_board[p_pos_x - 1][p_pos_y + 1] == -1 || (tm_board[p_pos_x - 1][p_pos_y + 1] >= 12 && tm_board[p_pos_x - 1][p_pos_y + 1] <= 23)) {
						value = 6;
					}
				}
			}
		}
		else if (tm_board[p_pos_x + 2][p_pos_y] == -1 || (tm_board[p_pos_x + 2][p_pos_y] >= 12 && tm_board[p_pos_x + 2][p_pos_y] <= 23)) {
			value = 3;
			if (p_pos_y >= 1 && p_pos_y <= 3) {
				if (tm_board[p_pos_x - 1][p_pos_y - 1] == -1 || (tm_board[p_pos_x - 1][p_pos_y - 1] >= 12 && tm_board[p_pos_x - 1][p_pos_y - 1] <= 23)) {
					if (tm_board[p_pos_x - 1][p_pos_y + 1] == -1 || (tm_board[p_pos_x - 1][p_pos_y + 1] >= 12 && tm_board[p_pos_x - 1][p_pos_y + 1] <= 23)) {
						value = 6;
					} 
				}
			}
		}
	}
	else if(mov_x == 0 && mov_y == -1){
		//lewo
		value = -1;
		if (p_pos_y >= 2 && (p_pos_x != 0 && p_pos_x != 4)) {
			if (tm_board[p_pos_x][p_pos_y - 2] >= 12 && tm_board[p_pos_x][p_pos_y - 2] <= 23 || tm_board[p_pos_x][p_pos_y - 2] == -1) {
				value = 3;
			}
		}
		if ((p_pos_x == 0 || p_pos_x == 4) && (p_pos_y >= 2)) {
			if (tm_board[p_pos_x][p_pos_y - 2] >= 12 && tm_board[p_pos_x][p_pos_y - 2] <= 23 || tm_board[p_pos_x][p_pos_y - 2] == -1) {
				value = 5;
			}
		}
		else if (p_pos_y >= 2 && p_pos_x >= 1 && p_pos_x <= 3) {
			if (
				(tm_board[p_pos_x + 1][p_pos_y - 1] >= 12 && tm_board[p_pos_x + 1][p_pos_y - 1] <= 23 || tm_board[p_pos_x + 1][p_pos_y - 1] == -1) &&
				(tm_board[p_pos_x + 1][p_pos_y - 2] >= 12 && tm_board[p_pos_x + 1][p_pos_y - 2] <= 23 || tm_board[p_pos_x + 1][p_pos_y - 2] == -1) &&
				(tm_board[p_pos_x][p_pos_y - 2] >= 12 && tm_board[p_pos_x][p_pos_y - 2] <= 23 || tm_board[p_pos_x][p_pos_y - 2] == -1) &&
				(tm_board[p_pos_x - 1][p_pos_y - 2] >= 12 && tm_board[p_pos_x - 1][p_pos_y - 2] <= 23 || tm_board[p_pos_x - 1][p_pos_y - 2] == -1) &&
				(tm_board[p_pos_x - 1][p_pos_y - 1] >= 12 && tm_board[p_pos_x - 1][p_pos_y - 1] <= 23 || tm_board[p_pos_x - 1][p_pos_y - 1] == -1)
				) {
				value = 8;
			}
		}
	}
	else if(mov_x == 1 && mov_y == 0){
		//dó³
		value = -1;
		if (p_pos_y == 0 || p_pos_y == 4) {
			if (p_pos_x <= 2) {
				if (tm_board[p_pos_x + 2][p_pos_y] >= 12 && tm_board[p_pos_x + 2][p_pos_y] <= 23 || tm_board[p_pos_x + 2][p_pos_y] == -1) {
					value = 9;
				}
			}
			else if (p_pos_x == 3) {
				value = 4;
				if (p_pos_y == 0) {
					if (tm_board[p_pos_x + 1][p_pos_y + 1] >= 12 && tm_board[p_pos_x][p_pos_y + 1] >= 12) {
						value = 8;
					}
				}
				else {
					if (tm_board[p_pos_x + 1][p_pos_y - 1] >= 12 && tm_board[p_pos_x][p_pos_y - 1] >= 12) {
						value = 8;
					}
				}
			}
		}
		else if (p_pos_y >= 1 && p_pos_y <= 3) {
			if (p_pos_x <= 2) {
				if ((tm_board[p_pos_x + 1][p_pos_y - 1] >= 12 || tm_board[p_pos_x + 1][p_pos_y - 1] == -1) &&
					((tm_board[p_pos_x + 1][p_pos_y + 1] >= 12 || tm_board[p_pos_x + 1][p_pos_y + 1] == -1)) &&
					((tm_board[p_pos_x][p_pos_y + 1] >= 12 || tm_board[p_pos_x][p_pos_y + 1] == -1)) &&
					((tm_board[p_pos_x][p_pos_y - 1] >= 12 || tm_board[p_pos_x][p_pos_y - 1] == -1)) &&
					((tm_board[p_pos_x + 2][p_pos_y - 1] >= 12 || tm_board[p_pos_x + 2][p_pos_y - 1] == -1)) &&
					((tm_board[p_pos_x + 2][p_pos_y + 1] >= 12 || tm_board[p_pos_x + 2][p_pos_y + 1] == -1)) &&
					((tm_board[p_pos_x + 2][p_pos_y] >= 12 || tm_board[p_pos_x + 2][p_pos_y] == -1))) {
					value = 8;
				}				

			}
			else if (p_pos_x == 3) {
				if ((tm_board[p_pos_x + 1][p_pos_y - 1] >= 12 || tm_board[p_pos_x + 1][p_pos_y - 1] == -1) &&
					((tm_board[p_pos_x + 1][p_pos_y + 1] >= 12 || tm_board[p_pos_x + 1][p_pos_y + 1] == -1)) &&
					((tm_board[p_pos_x][p_pos_y + 1] >= 12 || tm_board[p_pos_x][p_pos_y + 1] == -1)) &&
					((tm_board[p_pos_x][p_pos_y - 1] >= 12 || tm_board[p_pos_x][p_pos_y - 1] == -1))) {
					value = 7;
				}
			}
		}
	}
	else if(mov_x == 0 && mov_y == 1){
		//prawo
		value = -1;
		if (p_pos_x == 0 || p_pos_x == 4) {
			if (p_pos_y == 3) {
				value = 4;
			}
			else {
				if (p_pos_x == 0) {
					if (tm_board[p_pos_x][p_pos_y + 2] >= 12 || tm_board[p_pos_x][p_pos_y + 2] == -1 && tm_board[p_pos_x + 1][p_pos_y + 1] <= 11 || tm_board[p_pos_x - 1][p_pos_y + 1] == -1) {
						value = 4;
					}
				}
				else {
					if (tm_board[p_pos_x - 1][p_pos_y + 1] <= 11 && tm_board[p_pos_x][p_pos_y + 2] >= 12 || tm_board[p_pos_x][p_pos_y + 2] == -1) {
						value = 5;
					}
				}
			}
		}
		else {
			if (p_pos_y == 3) {
				if (p_pos_x == 0 || p_pos_x == 4) {
					value = 5;
				}
				else {
					if ((tm_board[p_pos_x + 1][p_pos_y + 1] <= 11 && tm_board[p_pos_x - 1][p_pos_y + 1] == -1) ||
						(tm_board[p_pos_x + 1][p_pos_y + 1] == -1 && tm_board[p_pos_x - 1][p_pos_y + 1] <= 11)) {
						value = -1;
					}
					else {
						value = 5;
					}
				}
			}
			else {
				if (tm_board[p_pos_x][p_pos_y + 2] >= 12 || tm_board[p_pos_x][p_pos_y + 2] == -1) {
					value = 2;
					if ((tm_board[p_pos_x + 1][p_pos_y + 1] >= 12 || tm_board[p_pos_x + 1][p_pos_y + 1] < 12) &&
						(tm_board[p_pos_x - 1][p_pos_y + 1] >= 12 || tm_board[p_pos_x - 1][p_pos_y + 1] < 12))
					{
						value = 7;
					}
					else if (tm_board[p_pos_x + 1][p_pos_y + 1] >= 12 || tm_board[p_pos_x + 1][p_pos_y + 1] == -1) {
						value = 3;
						if (tm_board[p_pos_x + 1][p_pos_y] >= 12 || tm_board[p_pos_x + 1][p_pos_y] == -1) {
							value = 6;
						}
						else if (tm_board[p_pos_x - 1][p_pos_y] >= 12 || tm_board[p_pos_x - 1][p_pos_y] == -1) {
							value = 6;
						}
					}
					else if (tm_board[p_pos_x - 1][p_pos_y + 1] >= 12 || tm_board[p_pos_x - 1][p_pos_y + 1] == -1) {
						value = 3;
						if (tm_board[p_pos_x + 1][p_pos_y] >= 12 || tm_board[p_pos_x + 1][p_pos_y] == -1) {
							value = 6;
						}
						else if (tm_board[p_pos_x - 1][p_pos_y] >= 12 || tm_board[p_pos_x - 1][p_pos_y] == -1) {
							value = 6;
						}
					}
				}
			}
		}
	}
	else if(mov_x == -1 && mov_y == -1){
		//góra lewo
		value = -1;
		if (p_pos_x <= 3 && p_pos_y <= 3) {
			if ((tm_board[p_pos_x - 1][p_pos_y] != -1 && tm_board[p_pos_x + 1][p_pos_y] != -1) &&
				(tm_board[p_pos_x][p_pos_y - 1] != -1 && tm_board[p_pos_x][p_pos_y + 1] != -1)) {
				value = -1;
			}
		}
		if (p_pos_x >= 2 && p_pos_y >= 2) {
			if ((tm_board[p_pos_x - 2][p_pos_y - 1] >= 12 || tm_board[p_pos_x - 2][p_pos_y - 1] == -1) &&
				(tm_board[p_pos_x][p_pos_y - 1] >= 12 || tm_board[p_pos_x][p_pos_y - 1] == -1) &&
				(tm_board[p_pos_x - 1][p_pos_y] >= 12 || tm_board[p_pos_x - 1][p_pos_y] == -1) &&
				(tm_board[p_pos_x - 1][p_pos_y - 2] >= 12 || tm_board[p_pos_x - 1][p_pos_y - 2] == -1) &&
				(tm_board[p_pos_x][p_pos_y - 2] >= 12 || tm_board[p_pos_x][p_pos_y - 2] == -1) &&
				(tm_board[p_pos_x - 2][p_pos_y] >= 12 || tm_board[p_pos_x - 2][p_pos_y] == -1) &&
				(tm_board[p_pos_x - 2][p_pos_y - 2] >= 12 || tm_board[p_pos_x - 2][p_pos_y - 2] == -1)) {
				value = 7;
			}
			if ((tm_board[p_pos_x - 2][p_pos_y - 2] <= 11 && tm_board[p_pos_x - 2][p_pos_y - 2] == -1) ||
				(tm_board[p_pos_x - 2][p_pos_y - 1] <= 11 && tm_board[p_pos_x - 2][p_pos_y - 1] == -1) ||
				(tm_board[p_pos_x - 2][p_pos_y] <= 11 && tm_board[p_pos_x - 2][p_pos_y] == -1) ||
				(tm_board[p_pos_x - 1][p_pos_y] <= 11 && tm_board[p_pos_x - 1][p_pos_y] == -1) ||
				(tm_board[p_pos_x][p_pos_y - 1] <= 11 && tm_board[p_pos_x][p_pos_y - 1] == -1) ||
				(tm_board[p_pos_x][p_pos_y - 2] <= 11 && tm_board[p_pos_x][p_pos_y - 2] == -1) ||
				(tm_board[p_pos_x - 1][p_pos_y - 2] <= 11 && tm_board[p_pos_x - 1][p_pos_y - 2] == -1)
				) {
				value = -1;
			}
		}
		else if (p_pos_x >= 1 && p_pos_y >= 1) {
			if (p_pos_x == 1 && p_pos_y == 1) {
				if ((tm_board[p_pos_x - 1][p_pos_y] >= 12 || tm_board[p_pos_x - 1][p_pos_y] == -1) &&
					(tm_board[p_pos_x][p_pos_y - 1] >= 12 || tm_board[p_pos_x][p_pos_y - 1] == -1)) {
					value = 7;
				}
			}
			else if (p_pos_x == 1){
				if ((tm_board[p_pos_x - 2][p_pos_y - 1] >= 12 || tm_board[p_pos_x - 2][p_pos_y - 1] == -1) &&
					(tm_board[p_pos_x][p_pos_y - 1] >= 12 || tm_board[p_pos_x][p_pos_y - 1] == -1)) {
					value = 7;
				}
			}
		}
	}
	else if(mov_x == 1 && mov_y == 1){
		//dó³ prawo
		value = -1;

		if (p_pos_x <= 2 && p_pos_y <= 2) {
			if ((tm_board[p_pos_x + 1][p_pos_y] <= 11 && tm_board[p_pos_x + 1][p_pos_y] == -1) ||
				(tm_board[p_pos_x + 2][p_pos_y] <= 11 && tm_board[p_pos_x + 2][p_pos_y] == -1) ||
				(tm_board[p_pos_x + 2][p_pos_y + 1] <= 11 && tm_board[p_pos_x + 2][p_pos_y + 1] == -1) ||
				(tm_board[p_pos_x + 2][p_pos_y + 2] <= 11 && tm_board[p_pos_x + 2][p_pos_y + 2] == -1) ||
				(tm_board[p_pos_x + 1][p_pos_y + 2] <= 11 && tm_board[p_pos_x + 1][p_pos_y + 2] == -1) ||
				(tm_board[p_pos_x][p_pos_y + 2] <= 11 && tm_board[p_pos_x][p_pos_y + 2] == -1) ||
				(tm_board[p_pos_x][p_pos_y + 1] <= 11 && tm_board[p_pos_x][p_pos_y + 1] == -1)) {
				value = -1;
			}
			else if ((tm_board[p_pos_x + 1][p_pos_y] <= 11 && tm_board[p_pos_x + 1][p_pos_y] >= 12) ||
				(tm_board[p_pos_x + 2][p_pos_y] <= 11 && tm_board[p_pos_x + 2][p_pos_y] >= 12) ||
				(tm_board[p_pos_x + 2][p_pos_y + 1] <= 11 && tm_board[p_pos_x + 2][p_pos_y + 1] >= 12) ||
				(tm_board[p_pos_x + 2][p_pos_y + 2] <= 11 && tm_board[p_pos_x + 2][p_pos_y + 2] >= 12) ||
				(tm_board[p_pos_x + 1][p_pos_y + 2] <= 11 && tm_board[p_pos_x + 1][p_pos_y + 2] >= 12) ||
				(tm_board[p_pos_x][p_pos_y + 2] <= 11 && tm_board[p_pos_x][p_pos_y + 2] >= 12) ||
				(tm_board[p_pos_x][p_pos_y + 1] <= 11 && tm_board[p_pos_x][p_pos_y + 1] >= 12)) {
				value = 7;
			}
			else if ((tm_board[p_pos_x + 1][p_pos_y] == -1 && tm_board[p_pos_x + 1][p_pos_y] >= 12) ||
				(tm_board[p_pos_x + 2][p_pos_y] == -1 && tm_board[p_pos_x + 2][p_pos_y] >= 12) ||
				(tm_board[p_pos_x + 2][p_pos_y + 1] == -1 && tm_board[p_pos_x + 2][p_pos_y + 1] >= 12) ||
				(tm_board[p_pos_x + 2][p_pos_y + 2] == -1 && tm_board[p_pos_x + 2][p_pos_y + 2] >= 12) ||
				(tm_board[p_pos_x + 1][p_pos_y + 2] == -1 && tm_board[p_pos_x + 1][p_pos_y + 2] >= 12) ||
				(tm_board[p_pos_x][p_pos_y + 2] == -1 && tm_board[p_pos_x][p_pos_y + 2] >= 12) ||
				(tm_board[p_pos_x][p_pos_y + 1] == -1 && tm_board[p_pos_x][p_pos_y + 1] >= 12)) {
					value = 5;
			}
		}
		else if (p_pos_x <= 3 && p_pos_y <= 3) {
			if (p_pos_x == 3 && p_pos_y == 3) {
				if (tm_board[p_pos_x + 1][p_pos_y] != -1 && tm_board[p_pos_x][p_pos_y + 1] != -1) {
					value = 8;
				}
			}
			else if (p_pos_x == 3) {
				if ((tm_board[p_pos_x + 1][p_pos_y] <= 11 && tm_board[p_pos_x + 1][p_pos_y + 2] != -1) ||
					(tm_board[p_pos_x + 1][p_pos_y] != -1 && tm_board[p_pos_x + 1][p_pos_y + 2] <= 11)) {
					value = -1;
				}
				else if ((tm_board[p_pos_x + 1][p_pos_y] >= 12 || tm_board[p_pos_x + 1][p_pos_y + 2] >= 12) ||
					tm_board[p_pos_x][p_pos_y + 2] <= 11){
					value = 7;
				}
				else if ((tm_board[p_pos_x][p_pos_y + 1] <= 11) && tm_board[p_pos_x - 1][p_pos_y + 1] == -1) {
					value = 9;
				}
			}
			else if (p_pos_y == 3) {
				if ((tm_board[p_pos_x][p_pos_y + 1] <= 11 && tm_board[p_pos_x + 2][p_pos_y + 1] == -1) ||
					(tm_board[p_pos_x][p_pos_y + 1] != -1 && tm_board[p_pos_x + 2][p_pos_y + 1] <= 11)) {
					value = -1;
				}
				else if (tm_board[p_pos_x + 1][p_pos_y] <= 11 || tm_board[p_pos_x + 2][p_pos_y] <= 11) {
					value = 8;
				}
			}
		}
	} 
	else if(mov_x == -1 && mov_y == 1){
		//góra prawo
		value = -1;
		if (p_pos_x >= 2 && p_pos_y <= 2) {
			if ((tm_board[p_pos_x - 1][p_pos_y] <= 11 && tm_board[p_pos_x - 1][p_pos_y] == -1) ||
				(tm_board[p_pos_x - 2][p_pos_y] <= 11 && tm_board[p_pos_x - 2][p_pos_y] == -1) ||
				(tm_board[p_pos_x - 2][p_pos_y + 1] <= 11 && tm_board[p_pos_x - 2][p_pos_y + 1] == -1) ||
				(tm_board[p_pos_x - 2][p_pos_y + 2] <= 11 && tm_board[p_pos_x - 2][p_pos_y + 2] == -1) ||
				(tm_board[p_pos_x - 1][p_pos_y + 2] <= 11 && tm_board[p_pos_x - 1][p_pos_y + 2] == -1) ||
				(tm_board[p_pos_x][p_pos_y + 2] <= 11 && tm_board[p_pos_x][p_pos_y + 2] == -1) ||
				(tm_board[p_pos_x][p_pos_y + 1] <= 11 && tm_board[p_pos_x][p_pos_y + 1] == -1)) {
				value = -1;
			}
			else if ((tm_board[p_pos_x - 1][p_pos_y] <= 11 && tm_board[p_pos_x - 1][p_pos_y] >= 12) ||
				(tm_board[p_pos_x - 2][p_pos_y] <= 11 && tm_board[p_pos_x - 2][p_pos_y] >= 12) ||
				(tm_board[p_pos_x - 2][p_pos_y + 1] <= 11 && tm_board[p_pos_x - 2][p_pos_y + 1] >= 12) ||
				(tm_board[p_pos_x - 2][p_pos_y + 2] <= 11 && tm_board[p_pos_x - 2][p_pos_y + 2] >= 12) ||
				(tm_board[p_pos_x - 1][p_pos_y + 2] <= 11 && tm_board[p_pos_x - 1][p_pos_y + 2] >= 12) ||
				(tm_board[p_pos_x][p_pos_y + 2] <= 11 && tm_board[p_pos_x][p_pos_y + 2] >= 12) ||
				(tm_board[p_pos_x][p_pos_y + 1] <= 11 && tm_board[p_pos_x][p_pos_y + 1] >= 12)) {
				value = 7;
			}
			else if ((tm_board[p_pos_x - 1][p_pos_y] == -1 && tm_board[p_pos_x - 1][p_pos_y] >= 12) ||
				(tm_board[p_pos_x - 2][p_pos_y] == -1 && tm_board[p_pos_x - 2][p_pos_y] >= 12) ||
				(tm_board[p_pos_x - 2][p_pos_y + 1] == -1 && tm_board[p_pos_x - 2][p_pos_y + 1] >= 12) ||
				(tm_board[p_pos_x - 2][p_pos_y + 2] == -1 && tm_board[p_pos_x - 2][p_pos_y + 2] >= 12) ||
				(tm_board[p_pos_x - 1][p_pos_y + 2] == -1 && tm_board[p_pos_x - 1][p_pos_y + 2] >= 12) ||
				(tm_board[p_pos_x][p_pos_y + 2] == -1 && tm_board[p_pos_x][p_pos_y + 2] >= 12) ||
				(tm_board[p_pos_x][p_pos_y + 1] == -1 && tm_board[p_pos_x][p_pos_y + 1] >= 12)) {
				value = 5;
			}
		}
		else if (p_pos_x >= 1 && p_pos_y <= 3) {
			if (p_pos_x == 1 && p_pos_y == 3) {
				if ((tm_board[p_pos_x - 1][p_pos_y] <= 11 && tm_board[p_pos_x - 1][p_pos_y - 1] == -1) || 
					(tm_board[p_pos_x][p_pos_y + 1] <= 11 && tm_board[p_pos_x + 1][p_pos_y + 1] == -1)){
					value = 9;
				}
				else if ((tm_board[p_pos_x - 1][p_pos_y] >= 12 || tm_board[p_pos_x][p_pos_y + 1] >= 12)) {
					value = 6;
				}
			}
			else if (p_pos_x == 1) {
				if ((tm_board[p_pos_x - 1][p_pos_y] <= 11 && tm_board[p_pos_x - 1][p_pos_y - 1] == -1) ||
					(tm_board[p_pos_x - 1][p_pos_y + 2] <= 11 && tm_board[p_pos_x - 1][p_pos_y + 2] == -1)) {
					value = 9;
				}
				else if ((tm_board[p_pos_x - 1][p_pos_y] >= 12) ||
					(tm_board[p_pos_x - 1][p_pos_y + 2] >= 12)) {
					value = 6;
				}
				if ((tm_board[p_pos_x + 1][p_pos_y] <= 11 && tm_board[p_pos_x + 2][p_pos_y] == -1)) {
					value = 9;
				}
			}
			else if (p_pos_y == 3) {
				if ((tm_board[p_pos_x][p_pos_y + 1] <= 11 && tm_board[p_pos_x][p_pos_y + 2] == -1) ||
					(tm_board[p_pos_x - 2][p_pos_y + 1] <= 11 && tm_board[p_pos_x - 3][p_pos_y + 1] == -1)) {
					value = 9;
				}
				else if ((tm_board[p_pos_x - 2][p_pos_y + 1] >= 12) ||
					(tm_board[p_pos_x][p_pos_y + 1] >= 12)) {
					value = 6;
				}
				else if ((tm_board[p_pos_x - 1][p_pos_y] <= 11 && tm_board[p_pos_x - 1][p_pos_y - 2] == -1)) {
					value = 9;
				}
			}
		}
	}
	else if(mov_x == 1 && mov_y == -1){
		//dó³ lewo
		value = -1;
		if (p_pos_x + mov_x == 4) {
			if (tm_board[p_pos_x + 1][p_pos_y] >= 12 && tm_board[p_pos_x + mov_x][p_pos_y] <= 23){
				value = 6;		
			}
			if (p_pos_y > 1) {
				if (tm_board[p_pos_x + 1][p_pos_y - 2] >= 12 && tm_board[p_pos_x + 1][p_pos_y - 2] <= 23) {
					value = 6;
				}
			}
		}
		else if (p_pos_y >= 2 && p_pos_x <= 3) {
			if ((tm_board[p_pos_x + 1][p_pos_y] >= 12 && tm_board[p_pos_x + mov_x][p_pos_y] <= 23) &&
				(tm_board[p_pos_x + 2][p_pos_y - 2] >= 12 && tm_board[p_pos_x + 2][p_pos_y - 2] <= 23)) {
				value = 7;
			}
		}
		else if (p_pos_x <= 2) {
			if ((tm_board[p_pos_x - 2][p_pos_y - 1] >= 12 && tm_board[p_pos_x - 2][p_pos_y - 1] <= 23 || tm_board[p_pos_x - 2][p_pos_y - 1] == -1) &&
				(tm_board[p_pos_x][p_pos_y - 1] >= 12 && tm_board[p_pos_x][p_pos_y - 1] <= 23 || tm_board[p_pos_x][p_pos_y - 1] == -1)) {
				value = 5;
			}
		}
	}
	return value;
}

/*USTAWIENIE RUCHU DLA MAKSYMALNEJ WARTOŒCI*/
void Bot::set_max(int sel, Vector2i mov, int rank)
{
	if (sel == this->tm_selected && mov == this->tm_move) {
		
	}
	else {
		if (this->maxEval <= rank) {
			this->selected = sel;
			this->move = mov;
			this->maxEval = rank;
		}
	}
}

/*ZWRACA VEKTOR RUCHU*/
Vector2i Bot::get_move()
{
	return this->move;
}

/*ZWRACA NUMER WYBRANEGO PIONKA*/
int Bot::get_selected()
{
	return this->selected;
}

/*RESETUJE ZMIENNE WYBIERANE DO WARTOŒCI POCZ¥TKOWYCH*/
void Bot::reset()
{
	tm_move = move;
	tm_move *= -1;
	tm_selected = selected;
	this->move = {};
	this->selected = -1;
	maxEval = -1;
}
