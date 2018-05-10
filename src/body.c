#include "body.h"

typedef struct {
    int same;
    wchar_t buffer[10000];
} words;

int num = 0;

void scan_words(words *arr_w);
void correct_words(words *arr_w);
void calc_words(words *arr_sravn, words *arr_correct);
void bun_words(words *arr_sravn, words *arr_correct, words *arr_done);
void alignment_words(words *arr_done, int max);
void printf_in_file(words *arr_done, int max);

void scan_words(words *arr_w) {
    int i = 0;
    while (fwscanf(data, L"%ls", arr_w[i].buffer) != EOF) {
        i++;
    }
    correct_words(arr_w);
}

void correct_words(words *arr_w) {
    words *arr_correct = (words*) malloc(sizeof(words) * num);
    words *arr_sravn = (words*) malloc(sizeof(words) * num);
    for (int i = 0; i < num; i++) {
        for (int j = 0, k = 0; j < num; j++) {
            if (!iswpunct(arr_w[i].buffer[j])) {
                arr_correct[i].buffer[k] = towlower(arr_w[i].buffer[j]);
                k++;
            }
        }
        wcscpy(arr_sravn[i].buffer, arr_correct[i].buffer);
    }
    free(arr_w);
    calc_words(arr_sravn, arr_correct);
}

void calc_words(words *arr_sravn, words *arr_correct) {
    words *arr_done = (words*) malloc(sizeof(words) * num); 
    int same;
    for (int i = 0; i < num; i++) {
        same = 1;
        for (int j = 0; j < num; j++) {
            if (wcscmp(arr_sravn[i].buffer, arr_correct[j].buffer) == 0) {
                same++;
            }
            swprintf(arr_done[i].buffer, 10000, L"%ld - %ls", same, arr_correct[i].buffer);
        }
    }
    bun_words(arr_sravn, arr_correct, arr_done);
}

void bun_words(words *arr_sravn, words *arr_correct, words *arr_done) {
    words *bun = (words*) malloc(sizeof(words) * num);
    int max = 0, knok;
    for (int i = 0; i < num; i++) {
        knok = 0;
        for (int k = 0; k < num; k++) {
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
        if (knok == 0 && arr_done[max].same > 1) {
            swprintf(arr_done[max].buffer, 1000, L"%ld - %ls", arr_done[max].same, arr_correct[i].buffer);
            wcscpy(bun[max].buffer, arr_correct[i].buffer);
            max++;
        }
    }
    free(arr_correct);
    free(bun);
    free(arr_sravn);
    alignment_words(arr_done, max);
}

void alignment_words(words *arr_done, int max) {
    for (int i = 0; i < max; i++) {
        for (int j = 0; j < max; j++) {
            if (arr_done[i].same > arr_done[j].same) {
                words temp = arr_done[i];
                arr_done[i] = arr_done[j];
                arr_done[j] = temp;
            }
        }
    }
    printf_in_file(arr_done, max);
}

void printf_in_file(words *arr_done, int max) {
    if (max == 0) {
        fwprintf(analize, L"The same words not found!\n");
    }
    for (int i = 0; i < max; i++) {
        fwprintf(analize, L"%ls\n", arr_done[i].buffer);
    }
    free(arr_done);
}

int analize_func() {
    wchar_t *fal = malloc(1000);

    while (fwscanf(data, L"%ls" , fal) != EOF) {
        num++;
    }
    free(fal);
    fclose(data);

    data = fopen("./src/.data_text.txt", "r");
    words *arr_w = (words*) malloc(sizeof(words) * num);
    if (arr_w == NULL) {
        return -1;
    }
    scan_words(arr_w);
    return 0;
}
