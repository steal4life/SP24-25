#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINIJA 100
#define MAX_BODOVI 50

struct Studenti {
    char ime[10];
    char prezime[10];
    int bodovi;
};

int broj_redaka(FILE* f);
void ispis_studenata(struct Studenti* studenti, int broj_studenata, int max_bodovi);
void sortiraj_studente(struct Studenti* studenti, int broj_studenata);
void trazi_studenta(struct Studenti* studenti, int broj_studenata);
void prosjecni_bodovi(struct Studenti* studenti, int broj_studenata);

int main() {
    FILE* f;
    int brojac = 0;
    int max_bodovi = MAX_BODOVI; 
    char linija[MAX_LINIJA];

    f = fopen("Prvi.txt", "r");
    if (f == NULL) {
        printf("Greska prilikom otvaranja txt datoteke.\n");
        return 1;
    }

    fscanf(f, "%d", &brojac);

    struct Studenti* studenti = (struct Studenti*)malloc(brojac * sizeof(struct Studenti));
    if (studenti == NULL) {
        printf("Alokacija memorije nije uspjela.\n");
        fclose(f);
        return 1;
    }

    for (int i = 0; i < brojac; i++) {
        fscanf(f, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
    }
    fclose(f);

    ispis_studenata(studenti, brojac, max_bodovi);
    prosjecni_bodovi(studenti, brojac);

    printf("\nStudenti sortirani po bodovima:\n");
    sortiraj_studente(studenti, brojac);
    ispis_studenata(studenti, brojac, max_bodovi);

    trazi_studenta(studenti, brojac);

    free(studenti);
    return 0;
}

void ispis_studenata(struct Studenti* studenti, int broj_studenata, int max_bodovi) {
    printf("\nIspis studenata i broja bodova:\n");
    for (int i = 0; i < broj_studenata; i++) {
        int relativni_br = (studenti[i].bodovi * 100) / max_bodovi;
        printf("%s %s ima %d bodova, relativno %d%%\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativni_br);
    }
}

void sortiraj_studente(struct Studenti* studenti, int broj_studenata) {
    struct Studenti temp;
    for (int i = 0; i < broj_studenata - 1; i++) {
        for (int j = i + 1; j < broj_studenata; j++) {
            if (studenti[i].bodovi < studenti[j].bodovi) {
                temp = studenti[i];
                studenti[i] = studenti[j];
                studenti[j] = temp;
            }
        }
    }
}

void trazi_studenta(struct Studenti* studenti, int broj_studenata) {
    char trazeno_ime[10];
    printf("\nUnesite ime studenta kojeg trazite: ");
    scanf("%s", trazeno_ime);

    for (int i = 0; i < broj_studenata; i++) {
            printf("Student %s %s ima %d bodova.\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi);
            return;
    }
    printf("Student s imenom %s nije pronaden.\n", trazeno_ime);
}

void prosjecni_bodovi(struct Studenti* studenti, int broj_studenata) {
    float suma_bodova = 0;
    for (int i = 0; i < broj_studenata; i++) {
        suma_bodova += studenti[i].bodovi;
    }
    float prosjek = suma_bodova / broj_studenata;
    printf("\nProsjecan broj bodova: %.2f\n", prosjek);
}
