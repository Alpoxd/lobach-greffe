#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <math.h>

#include "framing.h"
#include "count.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    int k, i, jmax = 0;
    double e = pow(10, -60);
    printf("Введите количество коэффициентов: ");
    scanf("%d", &k);
    double* array = (double*)malloc((k * 2) * sizeof(double));
    double* arrn = (double*)malloc(k * sizeof(double));
    double* arrdec = (double*)malloc((k * 2) * sizeof(double));
    memset(arrdec, (float) 0, (k * 2) * sizeof(double));
    printf("Введите коэффициенты: ");
    for (i = 0; i < k; i++) scanf("%lf", (array + i)), *(arrn + i) = *(array + i);
    int j = 0, flag = 0;
    while (flag == 0)
    {
        for (i = 0; i < k; i++)
        {
            double sum = pow(*(array + k * j + i), 2);
            double pow = 0;
            double sumdec = 2 * *(arrdec + k * j + i);
            while (fabs(sum) >= 1000000)
            {
                sum /= 10;
                sumdec += 1;
            }
            int add = 1;
            int sign = -1;
            while ((i + add) < k && (i - add) > -1)
            {
                pow = sum;
                double sumloc = 2 * sign * *(array + k * j + (i + add)) * *(array + k * j + (i - add));
                double sumdecloc = *(arrdec + k * j + (i + add)) + *(arrdec + k * j + (i - add));
                while (fabs(sumloc) >= 1000000)
                {
                    sumloc /= 10;
                    sumdecloc += 1;
                }
                while (sumdec > sumdecloc)
                {
                    sum *= 10;
                    sumdec -= 1;
                }
                while (sumdec < sumdecloc)
                {
                    sumloc *= 10;
                    sumdecloc -= 1;
                }
                sum += sumloc;
                while (fabs(sum) >= 1000000)
                {
                    sum /= 10;
                    sumdec += 1;
                }
                sign *= -1;
                add += 1;
            }
            if (fabs(1 - pow / sum) < e) flag = 1;
            *(array + k * (j + 1) + i) = sum;
            *(arrdec + k * (j + 1) + i) = sumdec;
            //printf("%.0lf * 10^%0.0lf\t", *(array + k * (j + 1) + i), *(arrdec + k * (j + 1) + i));
        }
        for (i = 0; i < k; i++)
        {
            *(array + k * j + i) = *(array + k * (j + 1) + i);
            *(arrdec + k * j + i) = *(arrdec + k * (j + 1) + i);
        }
        jmax += 1;
        if (jmax > 20) flag = 1;
        printf("\n");
    }
    printf("Ответ:\n");
    for (i = 1; i < k; i++)
    {
        double x = 0, sump = 0, summ = 0;
        if (*(array + i) / *(array + i - 1) >= 0)
        {
            double y = log10(*(array + i) / *(array + i - 1));
            if (*(arrdec + i - 1) != 0) y += (*(arrdec + i) - *(arrdec + i - 1));
            else y += (*(arrdec + i));
            x = pow(10, y / pow(2, jmax));
            for (j = 0; j < k; j++) sump += pow(x, k - j - 1) * *(arrn + j);
            for (j = 0; j < k; j++) summ += pow(-x, k - j - 1) * *(arrn + j);
            if (fabs(sump) < 0.01) printf("X = %.5f\n", x);
            else if (fabs(summ) < 0.01) printf("X = %.5f\n", -x);
            else printf("Иррациональный корень\n");
        }
        else printf("Нет решения\n");
    }
    return 0;
}