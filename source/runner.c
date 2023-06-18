#include "runner.h"

int curbg;
CharacterList *characters, *currentCharacter, *newCharacters;
char text[400];
char *novel;
bool textLock = false, textDone = false;
size_t novelsize;
int i = 0;
char* curText;
float progress = 0;
int characterSize = 0;

int parseText(char* novel, int pos) {
    free(curText);
    char* token;
    token = strstr(novel+pos, "\\t");
    char text[token-novel+pos+1];
    strncpy(text, novel+pos, token-novel+pos);
    text[token-novel+pos] = '\0';
    curText = malloc(strlen(text)+1);
    memset(curText, 0x00, strlen(text)+1);
    sprintf(curText, "%s", text);
    return token-novel+pos;
}

int doBackgroundStuff(char* novel, int pos) {
    char* token;
    token = strtok(novel+pos, " ");
    token = strtok(NULL, " ");
    curbg = atoi(token);
    token = strstr(novel+pos, "\n")+1;
    return token-novel+pos;
}

int popCharacters(char* novel, int pos, bool continues) {
    characterSize = 0;
    CharacterList *next_node = characters;
    CharacterList *freeing_node;
    while (1) {
        if (next_node->next == NULL) {
            free(next_node);
            break;
        }
        freeing_node = next_node;
        next_node = next_node->next;
        free(freeing_node);

    }
    if (continues) {
    char* token;
    token = strstr(novel+pos, "\n")+1;
    return token-novel+pos;
    }
    return 0;
}

int doCharacterStuff(char* novel, int pos) {
    characterSize++;
    CharacterList* chead = currentCharacter;
    chead = (CharacterList*)malloc(sizeof(CharacterList));
    char* token;
    token = strtok(novel+pos+2, " ");
    chead->characternum = atoi(token);
    token = strtok(NULL, " ");
    chead->x = atoi(token);
    token = strtok(NULL, " ");
    chead->scale = atoi(token);
    token = strstr(novel+pos, "\n")+1;
    currentCharacter = chead;
    return token-novel+pos;
    
}

void prepareNovel() {
    FILE *file = fopen("romfs:/gfx/novel.txt", "r");

    fseek(file, 0, SEEK_END);
    u32 size = ftell(file);
    fseek(file, 0, SEEK_SET);
    novel = malloc(size);
    fread(novel, size, 1, file);
    fclose(file);

    novel[size] = '\0';
    novelsize = strlen(novel)+1;
}

void exitNovel() {
    popCharacters("", 0, false);
    free(novel);

}

void DoStuff(u32 keys) {
    if (textLock == false) {
        for (;i<novelsize;i++) {
            if (novel[i] == 'c') {
                i += doCharacterStuff(novel, i);
            }
            if (novel[i] == 'b') {
                i+= doBackgroundStuff(novel, i);
            }
            if (novel[i] == 'p') {
                i += popCharacters(novel, i, true);
            }
            if (novel[i] == 't') {
                textLock = true;
                progress = -1.0f;
                i += parseText(novel, i);
                break;
            }
        }
    } else if (textDone == false) {
        drawTextBox(curText, progress);
        progress += 0.5f;
        if (progress > strlen(curText)) {
            textDone = true;
        }
    } else if (textDone && textLock) {
        if (keys & KEY_A) {
            textDone = false;
            textLock = false;
        }
    }
    drawScene(curbg, characters, characterSize);
}

