#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define epoca 50000
#define K 0.05f

float EntNt(float x0, float x1, float target);

float InitNt(float x0, float x1);


float sigmoide(float);

void pesos_initNt();

float Pesos_AND[2];   // w1, w2
float bias_AND = 0.5f;

float Pesos_OR[2];    // w3, w4
float bias_OR = 0.5f;

float Pesos_XOR[2];   // w6, w7
float bias_XOR = 0.5f;

float Error;          // Error de la neurona de salida (XOR)

// Sigmoide logistica correcta: 1 / (1 + e^(-s))
float sigmoide(float s) {
    return 1.0f / (1.0f + expf(-s));
}

void pesos_initNt(void) {
    for (int i = 0; i < 2; i++) {
        Pesos_AND[i] = (float)rand() / RAND_MAX;
        Pesos_OR[i]  = (float)rand() / RAND_MAX;
        Pesos_XOR[i] = (float)rand() / RAND_MAX;
    }
}

float EntNt(float x0, float x1, float target_xor) {
    // 1. Definir targets para las neuronas ocultas AND y OR
    float target_and = (x0 == 1.0f && x1 == 1.0f) ? 1.0f : 0.0f;
    float target_or  = (x0 == 1.0f || x1 == 1.0f) ? 1.0f : 0.0f;

    // --- NEURONA 1: AND (Salida x6) ---
    float net_and = Pesos_AND[0] * x0 + Pesos_AND[1] * x1 - bias_AND;
    float x6 = sigmoide(net_and);
    float err_and = target_and - x6;
    bias_AND -= K * err_and;
    Pesos_AND[0] += K * err_and * x0;
    Pesos_AND[1] += K * err_and * x1;

    // --- NEURONA 2: OR (Salida x7) ---
    float net_or = Pesos_OR[0] * x0 + Pesos_OR[1] * x1 - bias_OR;
    float x7 = sigmoide(net_or);
    float err_or = target_or - x7;
    bias_OR -= K * err_or;
    Pesos_OR[0] += K * err_or * x0;
    Pesos_OR[1] += K * err_or * x1;

    // --- NEURONA 3: XOR (Entradas x6 y x7) ---
    float net_xor = Pesos_XOR[0] * x6 + Pesos_XOR[1] * x7 - bias_XOR;
    float out_xor = sigmoide(net_xor);
    Error = target_xor - out_xor;
    bias_XOR -= K * Error;
    Pesos_XOR[0] += K * Error * x6;
    Pesos_XOR[1] += K * Error * x7;

    return out_xor;
}


float InitNt(float x0, float x1) {
    float x6 = sigmoide(Pesos_AND[0] * x0 + Pesos_AND[1] * x1 - bias_AND);
    float x7 = sigmoide(Pesos_OR[0] * x0 + Pesos_OR[1] * x1 - bias_OR);
    float out_xor = sigmoide(Pesos_XOR[0] * x6 + Pesos_XOR[1] * x7 - bias_XOR);
    return out_xor;
}

int main() {
    int i = 0;
    float apr;
    pesos_initNt();

    printf("Iniciando entrenamiento del Perceptron Multicapa para XOR...\n");

    while (i < epoca) {

        apr = EntNt(1, 1, 0);
        apr = EntNt(1, 0, 1);
        apr = EntNt(0, 1, 1);
        apr = EntNt(0, 0, 0);

        if (i % 5000 == 0 || i == epoca - 1) {
            printf("------------------------\n");
            printf("Salida Entrenamiento Epoca %d \n", i);
            printf("1,1 = %f (esperado: 0)\n", InitNt(1, 1));
            printf("1,0 = %f (esperado: 1)\n", InitNt(1, 0));
            printf("0,1 = %f (esperado: 1)\n", InitNt(0, 1));
            printf("0,0 = %f (esperado: 0)\n", InitNt(0, 0));
            printf("\nPesos Neurona AND (w1, w2, bias):\n");
            printf("w1 = %f, w2 = %f, bias = %f\n", Pesos_AND[0], Pesos_AND[1], bias_AND);
            printf("Pesos Neurona OR (w3, w4, bias):\n");
            printf("w3 = %f, w4 = %f, bias = %f\n", Pesos_OR[0], Pesos_OR[1], bias_OR);
            printf("Pesos Neurona XOR (w6, w7, bias):\n");
            printf("w6 = %f, w7 = %f, bias = %f\n", Pesos_XOR[0], Pesos_XOR[1], bias_XOR);
            printf("Ultimo Error: %f\n", Error);
            printf("------------------------\n");
        }
        i++;
    }

    printf("\n================ RESULTADOS FINALES ================\n");
    printf("XOR(1, 1) = %f -> Clasificado: %d\n", InitNt(1, 1), InitNt(1, 1) >= 0.5 ? 1 : 0);
    printf("XOR(1, 0) = %f -> Clasificado: %d\n", InitNt(1, 0), InitNt(1, 0) >= 0.5 ? 1 : 0);
    printf("XOR(0, 1) = %f -> Clasificado: %d\n", InitNt(0, 1), InitNt(0, 1) >= 0.5 ? 1 : 0);
    printf("XOR(0, 0) = %f -> Clasificado: %d\n", InitNt(0, 0), InitNt(0, 0) >= 0.5 ? 1 : 0);
    printf("====================================================\n");

    return 0;
}
