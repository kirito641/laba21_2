#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

const int rows = 4;
const int cols = 4;

void view_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == nullptr) {
        cout << "Неможливо відкрити файл\n";
        return;
    }

    cout << "\nДані у файлі " << filename << endl;

    char s[100];
    while (fgets(s, 100, f)) {
        cout << s;
    }

    fclose(f);
}

void create_matrix(const char *filename, int matrix[rows][cols]) {
    FILE *f = fopen(filename, "r");
    if (f == nullptr) {
        cout << "Неможливо відкрити файл\n";
        return;
    }

    int i = 0, j;
    char s[100];
    while (fgets(s, 100, f)) {
        istringstream iss(s);
        j = 0;
        while (iss >> matrix[i][j]) {
            j++;
        }
        i++;
    }

    fclose(f);
}

void print_matrix(int matrix[rows][cols]) {
    cout << "\nДані матриці:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    FILE *f = fopen("F2.txt", "w");
    if (f == nullptr) {
        cout << "Не вдалося відкрити файл для запису\n";
        return;
    }

    fprintf(f, "Матриця:\n");
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            fprintf(f, "%d ", matrix[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

void count_negative_elements(int matrix[rows][cols]) {
    int negative_count = 0;
    for (int i = 0; i <= 3; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] < 0) {
                negative_count++;
            }
        }
    }
    FILE *f = fopen("F2.txt", "a");
    if (f == nullptr) {
        cout << "Не вдалося відкрити файл для запису\n";
        return;
    }
    fprintf(f, "\nКількість від'ємних елементів у перших трьох рядках=%d\n", negative_count);
    cout << "\nКількість від'ємних елементів у перших трьох рядках=" << negative_count << endl;
    fclose(f);
}

void product_of_positive_elements_with_zero(int matrix[rows][cols]) {
    FILE *f = fopen("F2.txt", "a");
    if (f == nullptr) {
        cout << "Не вдалося відкрити файл для запису\n";
        return;
    }

    fprintf(f, "\nДобуток додатніх елементів рядків, які містять хоча б один нульовий елемент: ");

    cout << "\nДобуток додатніх елементів рядків, які містять хоча б один нульовий елемент:";

    long int product = 1;

    for (int i = 0; i < rows; ++i) {
        bool contains_zero = false;

        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == 0) {
                contains_zero = true;
            }
            if (contains_zero) {
                for (int k = 0; k < cols; ++k) {
                    if (matrix[i][k] > 0) {
                        product *= matrix[i][k];
                    }
                }
                break;
            }
        }

    }
    fprintf(f, "%ld\n", product);
    fclose(f);
    cout << product << endl;
}

void max_elements_by_row(int matrix[rows][cols]) {
    FILE *f = fopen("F2.txt", "a");
    if (f == nullptr) {
        cout << "Не вдалося відкрити файл для запису\n";
        return;
    }

    fprintf(f, "\nНайбільші за модулем елементи рядків: ");

    cout << endl << "Найбільші за модулем елементи рядків:";
    int vector[rows];
    for (int i = 0; i < rows; ++i) {
        vector[i] = matrix[i][0];
        for (int j = 1; j < cols; ++j) {
            if (abs(matrix[i][j]) > abs(vector[i])) {
                vector[i] = matrix[i][j];
            }
        }
        fprintf(f, "%d ", vector[i]);
        cout << vector[i] << " ";
    }
    fprintf(f, "\n");
    fclose(f);
    cout << endl;
}

void create_dynamic_array(int matrix[rows][cols], int *&dynamic_array) {
    int size = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (abs(matrix[i][j] - 5) <= 10) {
                size++;
            }
        }
    }

    dynamic_array = new int [size];
    FILE *f = fopen("F2.txt", "a");
    if (f == nullptr) {
        cout << "Не вдалося відкрити файл F2 для запису\n";
        return;
    }
    fprintf(f, "\nЕлементи, які відрізняються від числа 5 не більше ніж на 10:");
    int temp=0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (abs(matrix[i][j] - 5) <= 10) {
                dynamic_array[temp] = matrix[i][j];
                temp++;
                fprintf(f, " %d\t", matrix[i][j]);
            }
        }
    }
    fprintf(f, "\n");
    fclose(f);

    cout << "\nЕлементи, які відрізняються від числа 5 не більше ніж на 10:";
    for (int i = 0; dynamic_array[i]<size; ++i) {
        cout << " " << dynamic_array[i];
    }
}

int main() {
    system("chcp 65001");

    const char *filename = "F1.txt";

    int matrix[rows][cols];

    view_file(filename);

    create_matrix(filename, matrix);

    print_matrix(matrix);

    count_negative_elements(matrix);

    product_of_positive_elements_with_zero(matrix);

    max_elements_by_row(matrix);

    int *dynamic_array;


    create_dynamic_array(matrix, dynamic_array);

    delete[] dynamic_array;

    return 0;
}