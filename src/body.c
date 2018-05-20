#include "body.h"

typedef struct {
    int *same;
    wchar_t *buffer;
} words;

int num = 0;

int scan_words(words **arr_w);
int correct_words(words **arr_w);
int calc_words(words **arr_sravn, words **arr_correct);
int bun_words(words **arr_sravn, words **arr_correct, words **arr_done);
void alignment_words(words **arr_done, int max);
void printf_in_file(words **arr_done, int max);
void free_struct(words **struct_v);
words* create_mass(words *struct_v);

words* create_mass(words *struct_v) {
    struct_v = (words*) malloc(sizeof(words));
    struct_v->buffer = (wchar_t*) malloc(sizeof(wchar_t) * 10000);
    struct_v->same = (int*) malloc(sizeof(int));
    if (struct_v == NULL || struct_v->buffer == NULL) {
        return NULL;
    }
    return struct_v;
}

void free_struct(words **struct_v) {
    for (int i = 0; i < num; i++) {
        free(struct_v[i]->same);
        free(struct_v[i]->buffer);
        free(struct_v[i]);
    }
}

int scan_words(words **arr_w) {
    int i = 0;
    while (fwscanf(data, L"%ls", arr_w[i]->buffer) != EOF) {
        i++;
    }
    if (correct_words(arr_w) == -1) {
        return -1;
    }
    return 0;
}

int correct_words(words **arr_w) {
    words *(arr_correct[num]);
    words *(arr_sravn[num]);
    for (int i = 0; i < num; i++) {
        if ((arr_correct[i] = create_mass(arr_correct[i])) == NULL) {
            return -1;
        }
        if ((arr_sravn[i] = create_mass(arr_sravn[i])) == NULL) {
            return -1;
        }
    }
    for (int i = 0; i < num; i++) {
        for (int j = 0, k = 0; j < num; j++) {
            if (!iswpunct(arr_w[i]->buffer[j])) {
                arr_correct[i]->buffer[k] = towlower(arr_w[i]->buffer[j]);
                k++;
            }
        }
        wcscpy(arr_sravn[i]->buffer, arr_correct[i]->buffer);
    }  

    if (calc_words(arr_sravn, arr_correct) == -1) {
        return -1;
    }

    free_struct(arr_correct);
    free_struct(arr_sravn);

    return 0;
}

int calc_words(words **arr_sravn, words **arr_correct) {
    words *(arr_done[num]);
    for (int i = 0; i < num; i++) {
        if ((arr_done[i] = create_mass(arr_done[i])) == NULL) {
            return -1;
        }
    }
    int same;
    for (int i = 0; i < num; i++) {
        same = 1;
        for (int j = 0; j < num; j++) {
            if (wcscmp(arr_sravn[i]->buffer, arr_correct[j]->buffer) == 0) {
                same++;
            }
            swprintf(arr_done[i]->buffer, 10000, L"%ld - %ls", same, arr_correct[i]->buffer);
        }
    }

    if (bun_words(arr_sravn, arr_correct, arr_done) == -1) {
        return -1;
    }

    free_struct(arr_done);

    return 0;
}

int bun_words(words **arr_sravn, words **arr_correct, words **arr_done) {
    words *(bun[num]);
    for (int i = 0; i < num; i++) {
        if ((bun[i] = create_mass(bun[i])) == NULL) {
            return -1;
        }
    }

    int max = 0, knok;
    for (int i = 0; i < num; i++) {
        knok = 0;
        for (int k = 0; k < num; k++) {
            if (wcscmp(bun[k]->buffer, arr_correct[i]->buffer) == 0) {
                knok++;
            }
        }
        arr_done[max]->same[0] = 0;
        for (int j = 0; j < num; j++) {
            if (wcscmp(arr_sravn[i]->buffer, arr_correct[j]->buffer) == 0) {
                arr_done[max]->same[0]++;
            }
        }
        if (knok == 0 && arr_done[max]->same[0] > 1) {
            swprintf(arr_done[max]->buffer, 1000, L"%ld - %ls", arr_done[max]->same[0], arr_correct[i]->buffer);
            wcscpy(bun[max]->buffer, arr_correct[i]->buffer);
            max++;
        }
    }

    free_struct(bun);

    alignment_words(arr_done, max);

    return 0;
}

void alignment_words(words **arr_done, int max) {
    for (int i = 0; i < max; i++) {
        for (int j = 0; j < max; j++) {
            if (arr_done[i]->same[0] > arr_done[j]->same[0]) {
                words *temp = arr_done[i];
                arr_done[i] = arr_done[j];
                arr_done[j] = temp;
            }
        }
    }
    printf_in_file(arr_done, max);
}

void printf_in_file(words **arr_done, int max) {
    if (max == 0) {
        fwprintf(analize, L"The same words not found!\n");
    }
    for (int i = 0; i < max; i++) {
        fwprintf(analize, L"%ls\n", arr_done[i]->buffer);
    }
}
int analize_func() {
    wchar_t *fal = malloc(1000);
    if (fal == NULL) {
        return -1;
    }

    while (fwscanf(data, L"%ls" , fal) != EOF) {
        num++;
    }
    free(fal);
    fclose(data);

    words *(arr_w[num]);
    for (int i = 0; i < num; i++) {
        if ((arr_w[i] = create_mass(arr_w[i])) == NULL) {
            return -1;
        }
    }
    data = fopen(namedata, "r");
    if (data == NULL) {
        return -1;
    }  
    if (scan_words(arr_w)  == -1) {
        return -1;
    }
    free_struct(arr_w);
    return 0;
}
