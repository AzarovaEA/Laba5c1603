#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// вывод массива a размера size
void outputArray_(const int *a, size_t size) {
    for (size_t i = 0; i < size; i++)
        printf("%d ", a[i]);
}

// обмен значений двух переменных по адресам a и b
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Выполняет сортировку массива a размером size обменом (пузырьковую сортировку)
void bubbleSort(int *a, size_t size) {
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = size - 1; j > i; j--)
            if (a[j - 1] > a[j])
                swap(&a[j - 1], &a[j]);
}

/* Возвращает количества сравнений, производимых
сортировкой обменом в массиве a размера size */
long long getBubbleSortNComp(int *a, size_t size) {
    long long nComps = 0;
    for (size_t i = 0; ++nComps && i < size - 1; i++)
        for (size_t j = size - 1; ++nComps && j > i; j--)
            if (++nComps && a[j - 1] > a[j])
                swap(&a[j - 1], &a[j]);

    return nComps;
}

// ВЫполняет сортировку массива a размером size выбором
void selectionSort(int *a, size_t size) {
    for (int i = 0; i < size - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < size; j++)
            if (a[j] < a[minPos])
                minPos = j;
        swap(&a[i], &a[minPos]);
    }
}

/* Возвращает количества сравнений, производимых
сортировкой выбором в массиве a размера size */
long long getSelectionSortNComp(int *a, size_t n) {
    long long nComps = 0;
    for (int i = 0; ++nComps && i < n; i++) {
        int min = a[i];
        int minIndex = i;
        for (int j = i + 1; ++nComps && j < n; j++)
            if (++nComps && a[j] < min) {
                min = a[j];
                minIndex = j;
            }
        if (++nComps && i != minIndex)
            swap(&a[i], &a[minIndex]);
    }

    return nComps;
}

// Выполняет сортировку массива a размером size вставками
void insertionSort(int *a, const size_t size) {
    for (size_t i = 1; i < size; i++) {
        int t = a[i];
        size_t j = i;
        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
}

/* Возвращает количества сравнений, производимых
сортировкой вставками в массиве a размера size */
long long getInsertionSortNComp(int *a, size_t size) {
    long long nComps = 0;
    for (size_t i = 1; ++nComps && i < size; i++) {
        int t = a[i];
        size_t j = i;
        while (++nComps && j > 0 && ++nComps && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
    return nComps;
}

// Выполняет сортировку массива a размером size расческой
void combSort(int *a, const size_t size) {
    size_t step = size;
    int swapped = 1;
    while (step > 1 || swapped) {
        if (step > 1)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; j < size; ++i, ++j)
            if (a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
    }
}

/* Возвращает количества сравнений, производимых
сортировкой расческой в массиве a размера size */
long long getCombSortNComp(int *a, size_t size) {
    long long nComps = 0;
    size_t step = size;
    int swapped = 1;
    while (++nComps && step > 1 || ++nComps && swapped) {
        if (++nComps && step > 1)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; ++nComps && j < size; ++i, ++j)
            if (++nComps && a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
    }
    return nComps;
}

// Выполняет сортировку  Шелла массива a размером size
void ShellSort(int *a, size_t size) {
    int t;
    for (size_t step = size / 2; step > 0; step /= 2)
        for (size_t i = step; i < size; i++) {
            t = a[i];
            size_t j;
            for (j = i; j >= step; j -= step) {
                if (t < a[j - step])
                    a[j] = a[j - step];
                else
                    break;
            }
            a[j] = t;
        }
}

/* Возвращает количества сравнений, производимых
сортировкой Шелла в массиве a размера size */
long long getShellSortNComp(int *a, size_t size) {
    long long nComps = 0;
    int t;
    for (size_t step = size / 2; ++nComps && step > 0; step /= 2)
        for (size_t i = step; ++nComps && i < size; i++) {
            t = a[i];
            size_t j;
            for (j = i; ++nComps && j >= step; j -= step) {
                if (++nComps && t < a[j - step])
                    a[j] = a[j - step];
                else
                    break;
            }
            a[j] = t;
        }
    return nComps;
}

int digit(int n, int k, int N, int M) {
    return (n >> (N * k) & (M - 1));
}

// Функция выполняет сортировку массива начиная с left до right по N
void _radixSort(int *left, int *right, int N) {
    int k = (32 + N - 1) / N;
    int M = 1 << N;
    int sz = right - left;
    int *b = (int *) malloc(sizeof(int) * sz);
    int *c = (int *) malloc(sizeof(int) * M);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < M; j++)
            c[j] = 0;

        for (int *j = left; j < right; j++)
            c[digit(*j, i, N, M)]++;

        for (int j = 1; j < M; j++)
            c[j] += c[j - 1];

        for (int *j = right - 1; j >= left; j--)
            b[--c[digit(*j, i, N, M)]] = *j;

        int cur = 0;
        for (int *j = left; j < right; j++)
            *j = b[cur++];
    }
    free(b);
    free(c);
}

// Выполняет цифровую сортировку массива a размером size
void radix_Sort(int *a, size_t n) {
    _radixSort(a, a + n, 8);
}

/* Возвращает количества сравнений, производимых цифровой
сортировкой в массиве a размера size */
long long _radixSortNComp(int *left, int *right, int N) {
    long long nComps = 0;
    int k = (32 + N - 1) / N;
    int M = 1 << N;
    int sz = right - left;
    int *b = (int *) malloc(sizeof(int) * sz);
    int *c = (int *) malloc(sizeof(int) * M);
    for (int i = 0; ++nComps && i < k; i++) {
        for (int j = 0; j < M; j++)
            c[j] = 0;

        for (int *j = left;  ++nComps && j < right; j++)
            c[digit(*j, i, N, M)]++;

        for (int j = 1;  ++nComps && j < M; j++)
            c[j] += c[j - 1];

        for (int *j = right - 1;  ++nComps && j >= left; j--)
            b[--c[digit(*j, i, N, M)]] = *j;

        int cur = 0;
        for (int *j = left;  ++nComps && j < right; j++)
            *j = b[cur++];
    }
    free(b);
    free(c);

    return nComps;
}

// Выполняет цифровую сортировку массива a размером size
long long getRadixSortNComp(int *a, size_t n) {
    return _radixSortNComp(a, a + n, 8);
}

#define ARRAY_SIZE(a) sizeof (a) / sizeof(a[0])

#define TIME_TEST(testCode, time) { \
    clock_t start_time = clock(); \
    testCode \
      clock_t end_time = clock();\
    clock_t sort_time = end_time - start_time; \
    time = (double) sort_time / CLOCKS_PER_SEC; \
}

// функция сортировки
typedef struct SortFunc {
    void (*sort )(int *a, size_t n); // указатель на функцию
    // сортировки
    char name[64]; // имя сортировки,
    // используемое при выводе
} SortFunc;

// функция генерации
typedef struct GeneratingFunc {
    void (*generate )(int *a, size_t n); // указатель на функцию
    // генерации последоват.
    char name[64]; // имя генератора,
    // используемое при выводе
} GeneratingFunc;

// функция сортировки
typedef struct nCompSort {
    long long (*nComp )(int *a, size_t n); // указатель на функцию
    // сортировки
    char name[64]; // имя сортировки,
    // используемое при выводе
} nCompSort;

// Функция, возвращающая истину, если массив a размером size отсортирован
bool isOrdered(const int *a, size_t size) {
    for (int i = 0; i < size - 1; i++)
        if (a[i] > a[i + 1])
            return false;
    return true;
}

void checkTime(void (*sortFunc )(int *, size_t),
               void (*generateFunc )(int *, size_t),
               size_t size, char *experimentName) {
    static size_t runCounter = 1;

    // генерация последовательности
    static int innerBuffer[200000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu| ", runCounter++);
    printf(" Name : %s\n", experimentName);

    // замер времени
    double time;
    TIME_TEST({
                  sortFunc(innerBuffer, size);
              }, time)

    // результаты замера
    printf(" Status: ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time : %.3f s.\n", time);

        // запись в файл
        char filename[256];
        sprintf(filename, "./data/time/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf(" FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf(" Wrong !\n");

        // вывод массива, который не смог быть отсортирован
        outputArray_(innerBuffer, size);

        exit(1);
    }
}

void numberOfComparisons(long long (*nComp)(int *a, size_t n),
                         void (*generateFunc)(int *, size_t),
                         size_t size, char *experimentName, char *name) {
    static size_t runCounter = 1;

    // генерация последовательности
    static int innerBuffer[200000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    // замер времени
    long long nComps = nComp(innerBuffer, size);

    // результаты замера
    printf("Status: ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Comps: %lld\n", nComps);

        // запись в файл
        char filename[256];
        sprintf(filename, "./data/nComps/%s.csv",experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %lld\n", size, nComps);
        fclose(f);
    } else {
        printf("Wrong!\n");

        // вывод массива, который не смог быть отсортирован
        outputArray_(innerBuffer, size);

        exit(1);
    }
}

int cmp_int(const void *a, const void *b) {
    return *(const int *) a - *(const int *) b;
}

int cmp_intReverse(const void *a, const void *b) {
    return *(const int *) b - *(const int *) a;
}

void generateRandomArray(int *a, size_t size) {
    srand(time(0));
    for (int i = 0; i < size; i++)
        a[i] = 20000 - rand() % 10000;
}

void generateOrderedArray(int *a, size_t size) {
    generateRandomArray(a, size);
    qsort(a, size, sizeof(int), cmp_int);
}

void generateOrderedBackwards(int *a, size_t size) {
    generateRandomArray(a, size);
    qsort(a, size, sizeof(int), cmp_intReverse);
}

void timeExperiment() {
    // описание функций сортировки
    SortFunc sorts[] = {
            {selectionSort, "selectionSort"},
            {insertionSort, "insertionSort"},
            {bubbleSort,    "bubbleSort"},
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

    // описание функций сортировки
    SortFunc sortsCombShellRadix[] = {
            {combSort,      "combSort"},
            {ShellSort,     "ShellSort"},
            {radix_Sort,    "radix_Sort"},
    };
    const unsigned FUNCS2_N = ARRAY_SIZE(sortsCombShellRadix);

    nCompSort nComp[] = {
            {getSelectionSortNComp, "getSelectionSortNComp"},
            {getInsertionSortNComp, "getInsertionSortNComp"},
            {getBubbleSortNComp,    "getBubbleSortNComp"},
            {getCombSortNComp,      "getCombSortNComp"},
            {getShellSortNComp,     "getShellSortNComp"},
            {getRadixSortNComp,     "getRadixSortNComp"},
    };

    const unsigned COMP_N = ARRAY_SIZE(nComp);

    // описание функций генерации
    GeneratingFunc generatingFuncs[] = {
            // генерируется случайный массив
            {generateRandomArray,      "random"},
            // генерируется массив 0, 1, 2, ..., n - 1
            {generateOrderedArray,     "ordered"},
            // генерируется массив n - 1, n - 2, ..., 0
            {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

    // запись статистики в файл
    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("Size : %d\n", size);
        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                // генерация имени файла
                static char filename[128];
                sprintf(filename, "%s_%s_time ",
                        sorts[i].name, generatingFuncs[j].name);
                checkTime(sorts[i].sort,
                          generatingFuncs[j].generate,
                          size, filename);
            }
        }
        printf("\n");
    }

    // запись статистики в файл
    for (size_t size = 100000; size <= 200000; size += 10000) {
        printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("Size : %d\n", size);
        for (int i = 0; i < FUNCS2_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                // генерация имени файла
                static char filename[128];
                sprintf(filename, "%s_%s_time",
                        sortsCombShellRadix[i].name, generatingFuncs[j].name);
                checkTime(sortsCombShellRadix[i].sort,
                          generatingFuncs[j].generate,
                          size, filename);
            }
        }
        printf("\n");
    }

    // запись статистики в файл
    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("Size : %d\n", size);
        for (int i = 0; i < COMP_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                // генерация имени файла
                static char filename[128];
                sprintf(filename, "%s_%s_time ",
                        nComp[i].name, generatingFuncs[j].name);
                numberOfComparisons(nComp[i].nComp,
                          generatingFuncs[j].generate,
                          size, filename, nComp[i].name);
            }
        }
        printf("\n");
    }
}

int main() {
    timeExperiment();

    return 0;
}


