//ЛКГ: states[x + 1] = (states[x] * multiplier + increment) % modulus

#include <stdio.h>

int states[5] = {};                                             //массив для хранения чисел

void myrand(void);                                              //генератор
unsigned int gcd(unsigned int n1, unsigned int n2);             //поиск НОД
int modinv(int a, int m);                                       //инверсный mod
int find_modulus(int states[]);                                 //поиск модуля
int find_multiplier(int modulus, int states[]);                 //поиск множителя  
int find_increment(int modulus, int multiplier, int states[]);  //поиск инкремента


int main(int argc, const char* argv[]) { //в мейне генерируем 5 чисел, далее вычисляем 6
    myrand();
    int modulus = find_modulus(states);
    int multiplier = find_multiplier(modulus, states);
    int increment = find_increment(modulus, multiplier, states);
    states[5] = (states[4] * multiplier + increment) % modulus;
    printf("%i\n", states[5]);

    return 0;
}

void myrand(void) { 
    int modulus = 10;
    int multiplier = 8;
    int increment = 7;
    states[0] = 7;
    for (int i = 0; i < 5; i++) {
        states[i + 1] = (states[i] * multiplier + increment) % modulus;
    }
    printf("%i original\n", states[5]); //выводим правильное 6 число, оно никак не учавствует в вычислениях,
    states[5] = 0;                      //но для честности обнулим его
}

unsigned int gcd(unsigned int n1, unsigned int n2) {
    return (n2 == 0) ? n1 : gcd(n2, n1 % n2);
}

int modinv(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 0;
}

int find_increment(int modulus, int multiplier, int states[]) {
    int increment = (states[1] - states[0] * multiplier) % modulus;
    return (states[1] - states[0] * multiplier) % modulus;
}

int find_multiplier(int modulus, int states[]) {
    int multiplier = (states[2] - states[1]) * modinv(states[1] - states[0], modulus) % modulus;
    return multiplier;
}

int find_modulus(int states[]) { 
    int t[4] = {};
    for (int i = 0; i < 4; i++) {
        t[i] = states[i + 1] - states[i];
    }
    int zero1 = t[2] * t[0] - t[1] * t[1];
    int zero2 = t[3] * t[1] - t[2] * t[2];
    int modulus = gcd(zero1, zero2);
    return modulus;
}
/*Тут немного математики:
* Если у нас есть несколько случайных кратных n, с большой вероятностью их НОД будет равно n;
* далее, если х % n = 0, то x = k * n,
* следовательно нужно найти НОД из определенных значений, и мы можем восстановить n.
* Перейдем к следуующему преобразованию:
* t0 = s1 - s0
* t1 = s2 - s1 = (s1*m + c) - (s0*m + c) = m*(s1 - s0) = m*t0 (mod n)
* t2 = s3 - s2 = (s2*m + c) - (s1*m + c) = m*(s2 - s1) = m*t1 (mod n)
* t3 = s4 - s3 = (s3*m + c) - (s2*m + c) = m*(s3 - s2) = m*t2 (mod n)
* Далее:
* t2*t0 - t1*t1 = (m*m*t0 * t0) - (m*t0 * m*t0) = 0 (mod n)
* t3*t1 - t2*t2 = (m*m*t0 * t0) - (m*t0 * m*t0) = 0 (mod n)
* Получаем два выражения конгруэнтных 0.
* Для получения модуля найдем их НОД.
*/