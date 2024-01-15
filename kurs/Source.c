#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define B 8
#define A 10
void full_elements(int arpol[A][A], int ur);
int put_elements(int arpol[A][A], int ur);
int cals_elements(int arpol[A][A], int ur);
void Task1();
void Task4(int ur);
int main() {
	setlocale(LC_ALL, "RUS");
	int num, ur = 0;
	int arpol[A][A];
	printf("Приветствуем вас в игре-головоломке 'Лоскутки', желаем успешного прохождения!\n");
	do {
		printf("Игровое меню:\n1 - Правила игры\n2 - Уровень сложности\n3 - Начать игру\n4 - Загрузить последнее сохранение\n5 - Выйти\n");
		scanf("%d", &num);
		switch (num)
		{
		case 1:
			Task1();
			break;
		case 2:
			puts("Выберите уровень сложности:");
			printf("1 - лёгкий\n2 - нормально\n3 - сложный\n");
			scanf("%d", &ur);
			if (ur == 1) {
				ur = 4;
			}
			if (ur == 2) {
				ur = 6;
			}
			if (ur == 3) {
				ur = 8;
			}
			break;
		case 3:
			full_elements(arpol, ur);
			put_elements(arpol, ur);
			cals_elements(arpol, ur);
			break;
		case 4:
			Task4(ur);
			break;
		case 5:
			return 0;
		default:
			printf("Неверный ввод");
		}
	} while (num != 4);
	return 0;
}
void Task1() {
	puts("Суть игры заключается в том, чтобы в четырёх клетках игрового поля стояли цифры от 1 до 4, они не должны повторяться, порядок не имеет значения.\n");
	puts("* Для лёгкого уровня сложности необходимо, чтобы в каждом столбце выполнялись правила игры;\n* Для нормального уровня сложности необходимо, чтобы в первых 4 столбах по строкам, далее в 5 и 6 столбцах по столбцам, и в правом нижнем углу останется квадрат, везде здесь должны выполняться правила игры;\n* Для сложного уровня необходимо, чтобы первые четыре столбца и вторые четыре стобца подходили под правила игры.\n");
	puts("Для вас представлен пример, когда игра считается завершённой (представлен сложный уровень игры):");
	char arpolbut[B][B] = {
		{'2', '1', '4', '3', '2', '1', '3', '4'},
		{'4', '2', '1', '3', '3', '2', '1', '4'},
		{'3', '4', '1', '2', '1', '4', '2', '3'},
		{'1', '3', '2', '4', '3', '1', '4', '2'},
		{'2', '1', '3', '4', '1', '3', '2', '4'},
		{'4', '3', '1', '2', '1', '4', '3', '2'},
		{'1', '2', '4', '3', '4', '2', '1', '3'},
		{'3', '4', '2', '1', '2', '3', '4', '1'},
	};
	for (int i = 0; i < 8; i++) {
		printf("%4d", i + 1);
	}
	printf("\n");
	for (int i = 0; i < 8; i++) {
		printf("%d", i + 1);
		for (int j = 0; j < 8; j++) {
			printf("|%2c|", arpolbut[i][j]);
		}
		printf("\n");
	}
}
void full_elements(int arpol[A][A], int ur) {
	for (int i = 0; i < ur; i++) {
		for (int j = 0; j < ur; j++) {
			arpol[i][j] = rand() % 4 + 1;
		}
	}
}
int put_elements(int arpol[A][A], int ur) {
	for (int i = 0; i < ur; i++) {
		printf("%4d", i + 1);
	}
	printf("\n");
	for (int i = 0; i < ur; i++) {
		printf("%d", i + 1);
		for (int j = 0; j < ur; j++) {
			printf("|%2d|", arpol[i][j]);
		}
		printf("\n\n");
		printf("- - - - - - - - - -\n");
	}
}
int cals_elements(int arpol[A][A], int ur) {
	int r, p, o, c = 0;
	char fname[100] = "result.txt";
	FILE* out;
	puts("Исправьте числа в каждой ячейке согласно правилам\n");
	for (int i = 0; i < ur; i++) {
		for (int j = 0; j < ur; j++) {
			printf("Введите координаты ячейки (строка, столбец) и число, на которое оно будет исправлено (для выхода введите 0 0 0, для сохранения введите 1 0 1): ");
			scanf("%d %d %d", &r, &p, &o);
			if (r == 0 && p == 0 && o == 0) {
				return 0;
			}
			arpol[r - 1][p - 1] = o;
			if (r == 1 && p == 0 && o == 1) {
				FILE* out = fopen("result.txt", "w");
				if (out == NULL) {
					printf("Ошибка открытия файла\n");
					return;
				}
				for (int i = 0; i < ur; i++) {
					for (int j = 0; j < ur; j++) {
						fprintf(out, "%2d", arpol[i][j]);
					}
					fprintf(out, "\n");
				}
				fclose(out);
			}
			puts("Измененное игровое поле:");
			for (int i = 0; i < ur; i++) {
				printf("%4d", i + 1);
			}
			printf("\n");
			for (int i = 0; i < ur; i++) {
				printf("%d", i + 1);
				for (int j = 0; j < ur; j++) {
					printf("|%2d|", arpol[i][j]);
				}
				printf("\n\n");
				printf("- - - - - - - - - -\n");
			}
			if (ur == 4) {
				int valid = 1;
				for (int i = 0; i < ur; i++) {
					int count[4] = { 0, 0, 0, 0 };
					for (int j = 0; j < ur; j++) {
						int num = arpol[j][i];
						if (num < 1 || num > 4 || count[num - 1] > 0) {
							valid = 0;
							break;
						}
						count[num - 1]++;
					}
				}
				if (valid) {
					printf("Победа! Отличный результат\n");
					return;
				}
			}
			if (ur == 6) {
				int valid = 1;
				for (int i = 0; i < ur; i++) {
					int count[4] = { 0, 0, 0, 0 };
					for (int j = 0; j < ur; j++) {
						int num = arpol[i][j];
						if (num < 1 || num > 4 || count[num - 1] > 0) {
							valid = 0;
							break;
						}
						count[num - 1]++;
					}
				}
				if (valid) {
					printf("Победа! Отличный результат\n");
					return;
				}
			}
			if (ur == 8) {
				int valid = 1;
				for (int i = 0; i < ur; i++) {
					int count[4] = { 0, 0, 0, 0 };
					for (int j = 0; j < ur; j++) {
						int num = arpol[i][j];
						if (num < 1 || num > 4 || count[num - 1] > 0) {
							valid = 0;
							break;
						}
						count[num - 1]++;
					}
				}
				if (valid) {
					printf("Победа! Отличный результат\n");
					return;
				}
			}
		}
	}
}
void Task4(int ur) {
	int arpol[A][A];
	FILE* in = fopen("result.txt", "r");
	if (in == NULL) {
		printf("Ошибка открытия файла\n");
		return;
	}
	for (int i = 0; i < ur; i++) {
		for (int j = 0; j < ur; j++) {
			if (fscanf(in, "%2d", &arpol[i][j]) != 1) {
				printf("Ошибка чтения из файла\n");
				fclose(in);
				return;
			}
		}
	}
	fclose(in);
	put_elements(arpol, ur);
	cals_elements(arpol, ur);
}