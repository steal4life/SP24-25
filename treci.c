//dodane jos funkcije za oslobađanje memorije te brojanje elemenata u listi

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct osoba {
    char ime[50];
    char prezime[50];
    int godina_rodjenja;
    struct osoba* next;
} Osoba;

Osoba* nova_osoba(const char* ime, const char* prezime, int godina_rodjenja) {
    Osoba* nova = (Osoba*)malloc(sizeof(Osoba));
    if (!nova) {
        printf("Greska u alociranju memorije.\n");
        return NULL;
    }
    strcpy(nova->ime, ime);
    strcpy(nova->prezime, prezime);
    nova->godina_rodjenja = godina_rodjenja;
    nova->next = NULL;
    return nova;
}

void dodaj_na_pocetak(Osoba** head, const char* ime, const char* prezime, int godina_rodjenja) {
    Osoba* nova = nova_osoba(ime, prezime, godina_rodjenja);
    nova->next = *head;
    *head = nova;
}

void dodaj_na_kraj(Osoba** head, const char* ime, const char* prezime, int godina_rodjenja) {
    Osoba* nova = nova_osoba(ime, prezime, godina_rodjenja);
    if (*head == NULL) {
        *head = nova;
        return;
    }
    Osoba* trenutna = *head;
    while (trenutna->next != NULL) {
        trenutna = trenutna->next;
    }
    trenutna->next = nova;
}

void ispisi_listu(Osoba* head) {
    Osoba* trenutna = head;
    while (trenutna != NULL) {
        printf("Ime: %s, Prezime: %s, Godina rodenja: %d\n", trenutna->ime, trenutna->prezime, trenutna->godina_rodjenja);
        trenutna = trenutna->next;
    }
}

void dodaj_iza(Osoba* head, const char* prezime, const char* ime_nove, const char* prezime_nove, int godina_rodenja_nove) {
    Osoba* trenutna = head;
    while (trenutna != NULL && strcmp(trenutna->prezime, prezime) != 0) {
        trenutna = trenutna->next;
    }

    if (trenutna == NULL) {
        printf("Osoba sa prezimenom '%s' nije pronađena.\n", prezime);
        return;
    }

    Osoba* nova = nova_osoba(ime_nove, prezime_nove, godina_rodenja_nove);
    nova->next = trenutna->next;
    trenutna->next = nova;
}

void dodaj_ispred(Osoba** head, const char* prezime, const char* ime_nove, const char* prezime_nove, int godina_rodenja_nove) {
    Osoba* nova = nova_osoba(ime_nove, prezime_nove, godina_rodenja_nove);

    if (*head == NULL || strcmp((*head)->prezime, prezime) == 0) {
        nova->next = *head;
        *head = nova;
        return;
    }

    Osoba* trenutna = *head;
    while (trenutna->next != NULL && strcmp(trenutna->next->prezime, prezime) != 0) {
        trenutna = trenutna->next;
    }

    if (trenutna->next == NULL) {
        printf("Osoba sa prezimenom '%s' nije pronađena.\n", prezime);
        free(nova);
        return;
    }

    nova->next = trenutna->next;
    trenutna->next = nova;
}

void sortiraj_po_prezimenu(Osoba** head) {
    Osoba* sorted = NULL;

    Osoba* trenutna = *head;
    while (trenutna != NULL) {
        Osoba* next = trenutna->next;
        Osoba** mjesto = &sorted;

        while (*mjesto != NULL && strcmp((*mjesto)->prezime, trenutna->prezime) < 0) {
            mjesto = &(*mjesto)->next;
        }

        trenutna->next = *mjesto;
        *mjesto = trenutna;
        trenutna = next;
    }

    *head = sorted;
}

void upisi_u_datoteku(Osoba* head, const char* naziv_datoteke) {
    FILE* file = fopen("treci.txt", "w");
    if (!file) {
        printf("Greska pri otvaranju datoteke.\n");
        return;
    }

    Osoba* trenutna = head;
    while (trenutna != NULL) {
        fprintf(file, "%s %s %d\n", trenutna->ime, trenutna->prezime, trenutna->godina_rodjenja);
        trenutna = trenutna->next;
    }

    fclose(file);
    printf("Lista je upisana u datoteku '%s'.\n", naziv_datoteke);
}

void ucitaj_iz_datoteke(Osoba** head, const char* naziv_datoteke) {
    FILE* file = fopen("treci.txt", "r");
    if (!file) {
        printf("Greska pri otvaranju datoteke.\n");
        return;
    }

    char ime[50], prezime[50];
    int godina_rodjenja;

    while (fscanf(file, "%s %s %d", ime, prezime, &godina_rodjenja) == 3) {
        dodaj_na_kraj(head, ime, prezime, godina_rodjenja);
    }

    fclose(file);
    printf("Lista je ucitana iz datoteke '%s'.\n", naziv_datoteke);
}

void obrisi_listu(Osoba** head) {
    Osoba* trenutna = *head;
    while (trenutna != NULL) {
        Osoba* za_brisanje = trenutna;
        trenutna = trenutna->next;
        free(za_brisanje);
    }
    *head = NULL;
    printf("Lista je obrisana.\n");
}

int broj_elemenata(Osoba* head) {
    int brojac = 0;
    Osoba* trenutna = head;
    while (trenutna != NULL) {
        brojac++;
        trenutna = trenutna->next;
    }
    return brojac;
}

int main() {
    Osoba* lista = NULL;

    dodaj_na_pocetak(&lista, "Ana", "Anic", 1990);
    dodaj_na_kraj(&lista, "Marko", "Maric", 1985);
    dodaj_na_pocetak(&lista, "Ivan", "Ivic", 1992);

    printf("Ispis liste:\n");
    ispisi_listu(lista);

    dodaj_iza(lista, "Anic", "Luka", "Lukic", 1993);
    dodaj_ispred(&lista, "Maric", "Petar", "Petrovic", 1988);

    printf("\nLista nakon dodavanja:\n");
    ispisi_listu(lista);

    sortiraj_po_prezimenu(&lista);
    printf("\nLista nakon sortiranja:\n");
    ispisi_listu(lista);

    upisi_u_datoteku(lista, "treci.txt");
    obrisi_listu(&lista);
    ucitaj_iz_datoteke(&lista, "treci.txt");

    printf("\nLista nakon ucitavanja iz datoteke:\n");
    ispisi_listu(lista);

    printf("\nBroj elemenata u listi: %d\n", broj_elemenata(lista));

    obrisi_listu(&lista);
    return 0;
}
