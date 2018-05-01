#include "body.h"


wchar_t *analize_w = NULL;

typedef struct {
    int same;
    wchar_t buffer[1000];
} words;

void analize_func() {
    setlocale(LC_CTYPE, "");
    wchar_t *fal = malloc(1000);
    int num = 0;

    while (fwscanf(data, L"%ls" , fal) != EOF) { // подсчет количества слов для создания массива структур
        num++;
    }
    free(fal);
    fclose(data);

    data = fopen("./src/.data_text.txt", "r");
    words arr_w[num];
    int i = 0;
    while (fwscanf(data, L"%ls", arr_w[i].buffer) != EOF) { // заполнение
        i++;
    }
    words arr_correct[num];
    words arr_sravn[num];
    for (i = 0; i < num; i++) {  // убирает лишнее из строки
        for (int j = 0, k = 0; j < num; j++) {
            if (!iswpunct(arr_w[i].buffer[j])) {
                arr_correct[i].buffer[k] = towlower(arr_w[i].buffer[j]);
                k++;
            }
        }
        wcscpy(arr_sravn[i].buffer, arr_correct[i].buffer);
    }
    words arr_done[num];
    int same;
    for (i = 0; i < num; i++) {// подсчет
        same = 1;
        for (int j = 0; j < num; j++) {
            if (wcscmp(arr_sravn[i].buffer, arr_correct[j].buffer) == 0) {
                same++;
            }
            swprintf(arr_done[i].buffer, 1000, L"%ld - %ls", same, arr_correct[i].buffer);
        }
    }

    words bun[num];
    int max = 0, knok;
    for (i = 0; i < num; i++) { // подсчет
        knok = 0;
        for (int k = 0; k < num; k++) { // бан слов 
            if (wcscmp(bun[k].buffer, arr_correct[i].buffer) == 0) {
                knok++;
            }
        }
        arr_done[max].same = 0;
        for (int j = 0; j < num; j++) {
            if (wcscmp(arr_sravn[i].buffer, arr_correct[j].buffer) == 0) {
                arr_done[max].same++;
            }
        }
        if (knok == 0) {
            swprintf(arr_done[max].buffer, 1000, L"%ld - %ls", arr_done[max].same, arr_correct[i].buffer);
            wcscpy(bun[max].buffer, arr_correct[i].buffer);
            max++;
        }
    }
    for (i = 0; i < max; i++) {
        for (int j = 0; j < max; j++) {
            if (arr_done[i].same > arr_done[j].same) {
                words temp = arr_done[i];
                arr_done[i] = arr_done[j];
                arr_done[j] = temp;
            }
        }
    }
    for (i = 0; i < max; i++) {
        fwprintf(analize, L"%ls\n", arr_done[i].buffer);
    }
}