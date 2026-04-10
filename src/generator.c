/**
 * @file generator.c
 * @brief
 */

#include "generator.h"
#include "base.h"

static const char* teamNames[] = {
    "T1",
    "Damwon Gaming",
    "Gen.G",
    "Hanwha Life Esports",
    "Fnatic",
    "G2 Esports",
    "MAD Lions",
    "Rogue",
    "Cloud9",
    "Immortals",
    "FlyQuest",
    "100 Thieves",
    "Sentinels"
};

char* generate_random_name(){
    const char letters[] = "abcdefghijklmnopqrstuvwxyz";
    int n = (int)strlen(letters);

    char* name = malloc((size_t)NAMES_LENGHT + 1);
    if (name == NULL) {
        return NULL; // aca deberia manejarse con alguna funcion de error, pero por ahora solo devuelvo NULL
    }

    for (int i = 0; i < NAMES_LENGHT; i++) {
        name[i] = letters[rand() % n];
    }

    name[NAMES_LENGHT] = '\0';
    return name;

}

char* generate_random_team(){

    int n = (int)(sizeof(teamNames) / sizeof(teamNames[0]));
    const char* selected = teamNames[rand() % n];

    char* team = malloc(strlen(selected) + 1);
    if (team == NULL) {
        return NULL;
    }

    strcpy(team, selected);
    return team;

}

// quizas se podrian abstraer mas las funciones y ponerlas como herramientas generales -.-
float generate_random_score(){
    float randomScore = ((float)rand() / RAND_MAX) * (MAX_SCORE - MIN_SCORE) + MIN_SCORE;
    return randomScore;
}

int generate_random_competitions(){
    int randomCompetitions = (rand() % (MAX_COMPETITIONS - MIN_COMPETITIONS + 1)) + MIN_COMPETITIONS;
    return randomCompetitions;
}
