#include <stdio.h>
#include <string.h>

#define N_ESTADOS 26
#define MAX_NOME 50

typedef struct {
    char nome[MAX_NOME];
    int numVeiculos;
    int numAcidentes;
} Estado;

void lerDados(Estado estados[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Estado %d:\n", i+1);
        printf("Nome: ");
        fgets(estados[i].nome, MAX_NOME, stdin);
        estados[i].nome[strcspn(estados[i].nome, "\n")] = '\0';
        printf("Número de veículos (2007): ");
        scanf("%d", &estados[i].numVeiculos);
        printf("Número de acidentes (2007): ");
        scanf("%d", &estados[i].numAcidentes);
        getchar();  
    }
}

void acharMaiorMenor(const Estado estados[], int n, int *idxMaior, int *idxMenor) {
    *idxMaior = 0;
    *idxMenor = 0;
    for (int i = 1; i < n; i++) {
        if (estados[i].numAcidentes > estados[*idxMaior].numAcidentes) {
            *idxMaior = i;
        }
        if (estados[i].numAcidentes < estados[*idxMenor].numAcidentes) {
            *idxMenor = i;
        }
    }
}

double percentual(const Estado estados[], int idx) {
    return 100.0 * estados[idx].numAcidentes / estados[idx].numVeiculos;
}

double mediaAcidentes(const Estado estados[], int n) {
    int soma = 0;
    for (int i = 0; i < n; i++) {
        soma += estados[i].numAcidentes;
    }
    return (double) soma / n;
}

void exibirAcimaMedia(const Estado estados[], int n, double media) {
    printf("\nEstados com número de acidentes acima da média (%.2f):\n", media);
    for (int i = 0; i < n; i++) {
        if (estados[i].numAcidentes > media) {
            printf("%s – %d acidentes\n", estados[i].nome, estados[i].numAcidentes);
        }
    }
}

int main(void) {
    Estado estados[N_ESTADOS];
    int idxMaior, idxMenor;
    double med;

    lerDados(estados, N_ESTADOS);

    acharMaiorMenor(estados, N_ESTADOS, &idxMaior, &idxMenor);
    printf("\nMaior número de acidentes: %s – %d\n", estados[idxMaior].nome, estados[idxMaior].numAcidentes);
    printf("Menor número de acidentes: %s – %d\n", estados[idxMenor].nome, estados[idxMenor].numAcidentes);

    printf("\nPercentual de veículos envolvidos em acidentes por estado:\n");
    for (int i = 0; i < N_ESTADOS; i++) {
        printf("%s: %.2f%%\n", estados[i].nome, percentual(estados, i));
    }

    med = mediaAcidentes(estados, N_ESTADOS);
    printf("\nMédia de acidentes no país: %.2f\n", med);

    exibirAcimaMedia(estados, N_ESTADOS, med);

    return 0;
}

