#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

// Структура для деталей (вложенная)
struct details67 {
    int salary;        // зарплата
    int experience;    // стаж (лет)
};

// Основная структура
struct structure {
    int number;           // номер по порядку
    char name[50];        // название профессии
    int code;             // код профессии
    struct details specs; // характеристики профессии
};

// Функция для очистки буфера ввода
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Функция для ввода данных
void inputData(struct structure arr[], int n) {
    printf("Введите информацию о %d профессиях:\n", n);
    for (int i = 0; i < n; i++) {
        printf("\nПрофессия #%d:\n", i + 1);
        arr[i].number = i + 1;

        // Очистка буфера только перед вводом названия (кроме первой итерации)
        if (i > 0) {
            clearInputBuffer();
        }

        printf("  Название: ");
        fgets(arr[i].name, sizeof(arr[i].name), stdin);
        arr[i].name[strcspn(arr[i].name, "\n")] = 0; // удаление символа новой строки

        printf("  Код профессии (число): ");
        scanf_s("%d", &arr[i].code);

        printf("  Зарплата: ");
        scanf_s("%d", &arr[i].specs.salary);

        printf("  Стаж (лет): ");
        scanf_s("%d", &arr[i].specs.experience);

        // Если это не последняя запись, оставляем очистку буфера на следующей итерации
        if (i == n - 1) {
            clearInputBuffer();
        }
    }
}

// Функция для вывода данных в виде таблицы
void outputData(struct structure arr[], int n) {
    // Верхняя граница таблицы
    printf("\n ================================================================================\n");

    // Заголовок таблицы
    printf("| %-4s   %-20s   %-15s |                                |\n",
        "№", "Название", "Код");

    // Разделитель заголовка
    printf("|=============================|=================|                                |\n");

    // Подзаголовок для характеристик
    printf("|                             |                 | %-14s | %-13s |\n",
        "Зарплата", "Стаж");

    // Горизонтальная линия перед данными
    printf("|======|======================|=================|================================|\n");

    // Вывод данных
    for (int i = 0; i < n; i++) {
        printf("| %-4d | %-20s | %-15d | %-14d | %-13d |\n",
            arr[i].number,
            arr[i].name,
            arr[i].code,
            arr[i].specs.salary,
            arr[i].specs.experience);

        // Разделитель между строками (кроме последней)
        if (i < n - 1) {
            printf("|------|----------------------|-----------------|--------------------------------|\n");
        }
    }

    // Нижняя граница таблицы
    printf(" ================================================================================\n");
}

// Функция для перестановки верхней и нижней строк
void permutation(struct structure arr[], int n) {
    if (n > 1) {
        struct structure temp = arr[0];
        arr[0] = arr[n - 1];
        arr[n - 1] = temp;

        // Обновляем номера после перестановки
        arr[0].number = 1;
        arr[n - 1].number = n;
    }
}

int main(void) {
    // Настройка кодировки для корректного отображения русского текста
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    const int N = 3;  // количество записей
    struct structure professions[N];

    // 1. Ввод данных
    printf("=============== ВВОД ДАННЫХ О ПРОФЕССИЯХ ===============\n");
    inputData(professions, N);

    // 2. Вывод исходных данных
    printf("\n\n================== ИСХОДНЫЕ ДАННЫЕ ===================\n");
    outputData(professions, N);

    // 3. Перестановка верхней и нижней строк
    permutation(professions, N);

    // 4. Вывод результата преобразования
    printf("\n\n================ ПОСЛЕ ПЕРЕСТАНОВКИ ================\n");
    outputData(professions, N);

    printf("\nНажмите Enter для выхода...");
    getchar();

    return 0;
}