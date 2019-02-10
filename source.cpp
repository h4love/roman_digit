/* Задача на римские числа */
// Перевод римских в арабские и наоборот

#include <stdio.h>

//put after scanf
void clean_stdin()
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

//0 - none, 1,2,3,4 - rank
int roman_rank(char symbol)
{
    int rank;
    switch (symbol) {
    case 'M':
        rank = 4;
        break;
    case 'D':
        rank = 3;
        break;
    case 'C':
        rank = 3;
        break;
    case 'L':
        rank = 2;
        break;
    case 'X':
        rank = 2;
        break;
    case 'V':
        rank = 1;
        break;
    case 'I':
        rank = 1;
        break;
    default:
        rank = 0;
        break;
    }

    return rank;
}

int roman_cost(char symbol)
{
    int cost = 0;
    switch (symbol) {
    case 'M':
    case 'C':
    case 'X':
    case 'I':
        cost = 1;
        break;
    case 'D':
    case 'L':
    case 'V':
        cost = 5;
        break;
    }

    return cost;
}

int pow10(int grade)
{
    int sum = 1;
    for (int i = 1; i < grade; i++) {
        sum *= 10;
    }

    return sum;
}

//0 - good, 1 - error
int arabic(char* input, int* output)
{
    int roman_rank(char);
    int roman_cost(char);
    int pow10(int);

    int steps = 0;
    x int sum = 0, temp = 0;
    int i = -1, err = -1;

    do {
        i++;
        if (err != -1) {
            //Summation
            if (roman_rank(input[i]) > err) {
                temp *= -1;
            }
            else {
                sum += temp;
                temp = 0;
            }
            //Repeat check
            if (input[i] != input[i - 1]) {
                steps = 0;
            }
            //Other laps
            err = roman_rank(input[i]);
        }
        else {
            //First lap
            err = roman_rank(input[i]);
        }
        //Leave after summation
        if (input[i] == 0) {
            break;
        }
        //Intermediate summation
        if (err != 0) {
            temp += roman_cost(input[i]) * pow10(roman_rank(input[i]));
            steps++;
        }
        else {
            return 1;
        }

        //When D,L,V more than one
        if ((roman_cost(input[i]) == 5) && (steps > 1)) {
            return 2;
        }
        //When M,C,X,I more than three
        if ((roman_cost(input[i]) == 1) && (steps > 3)) {
            return 3;
        }

        /* DEBUG */
        //printf("(%d) SUM: %d, TEMP: %d, RANK: %d, COST: %d\n", i, sum, temp, roman_rank(input[i]), roman_cost(input[i]));
        /* DEBUG */
    } while (input[i] != 0);

    *output = sum;

    return 0;
}

//0 - good, 1 - error
int roman(int input, char* output)
{
    char A = ' ', B = ' ', C = ' ';
    char roman_sym[8] = "IVXLCDM";

    if ((input > 3999) || (input < 1)) {
        return 1;
    }

    int step = 10000;
    int digit, pos = 0;
    for (int i = 4; i > 0; i--) {
        step /= 10;
        digit = (input / step) % 10;

        if (i < 4) {
            A = roman_sym[2 * i];
            B = roman_sym[2 * i - 1];
        }
        C = roman_sym[2 * i - 2];

        switch (digit) {
        case 1:
            output[pos++] = C;
            break;
        case 2:
            output[pos++] = C;
            output[pos++] = C;
            break;
        case 3:
            output[pos++] = C;
            output[pos++] = C;
            output[pos++] = C;
            break;
        case 4:
            output[pos++] = C;
            output[pos++] = B;
            break;
        case 5:
            output[pos++] = B;
            break;
        case 6:
            output[pos++] = B;
            output[pos++] = C;
            break;
        case 7:
            output[pos++] = B;
            output[pos++] = C;
            output[pos++] = C;
            break;
        case 8:
            output[pos++] = B;
            output[pos++] = C;
            output[pos++] = C;
            output[pos++] = C;
            break;
        case 9:
            output[pos++] = C;
            output[pos++] = A;
            break;
        }
    }
    output[pos] = '\0';

    return 0;
}

int main()
{
    int roman(int, char*);
    int arabic(char*, int*);

    /* -- special variables -- */
    //
    /* temp */ char err = -1;
    //
    /* ----- don't touch ----- */

    int type = -1;
    char* output_r = new char[16];

    //Converter type
    while (err < 1 || type < 0 || type > 1) {
        if (err == -1) {
            printf("[>] Converter type [ 0 - to roman, 1 - to arabic ]: ");
        }
        else {
            printf("[>] Wrong input! Try again: ");
        }
        err = scanf("%d", &type);
        clean_stdin();
    }
    err = -1;

    switch (type) {
    //Arabic to roman
    case 0:
        int input_a;
        while (err < 1) {
            if (err == -1) {
                printf("[>] Enter arabic number [ 1 - 3999 ]: ");
            }
            else {
                printf("[>] Wrong input! Try again: ");
            }
            err = scanf("%d", &input_a);
            clean_stdin();
        }

        err = roman(input_a, output_r);

        if (err == 0) {
            printf("[<] Roman: %s", output_r);
        }
        else {
            printf("[!] Convertation error, check available range");
        }

        break;

    //Roman to arabic
    case 1:
        char input_r[16];
        while (err < 1) {
            if (err == -1) {
                printf("[>] Enter roman number [ I - MMMCMXCI ]: ");
            }
            else {
                printf("[>] Wrong input! Try again: ");
            }
            err = scanf("%s", input_r);
            clean_stdin();
        }

        int output_a = 0;

        err = arabic(input_r, &output_a);
        if (err == 0) {
            printf("[<] Arabic: %d", output_a);
        }
        else {
            printf("[!] Convertation error, check syntax", err);
        }

        break;
    }

    return 0;
}