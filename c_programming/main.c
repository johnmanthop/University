/**
    02/2020
    This is the final commit to my first semester programming course.
    It is mainly a text parser, supporting 6 commands
    ap: <text> Appends a paragraph to the inputted text
    fw, fs, fp: <text> Finds the <text> in the words, sentences, paragraphs (accordingly) given by the user and outputs them
    owl, owf: output every word inputted based on length and frequency (accordingly)
**/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10000
#define WORDSIZE 1024

#define df(n) printf("HERE:%d\n", n)
//Pro level debugging flags

typedef struct sentence
{
    char **words;

    int wordcount;
} sentence;

typedef struct paragraph
{
    sentence *sentences;
    int sentencecount;
} paragraph;
/**
    The text structure should be as follows:
    paragraphs:(accessed as struct pointers)
        [0]:
        |   sentences:
        |       [0]: { word1, word2, ..., wordN }//Where all these words are the first sentence, first paragraph
        |       [1]: { word1, word2, ..., wordN }//And all these are the second sentence, first paragraph
        |       ...
        [1]:
        |   sentences:
        |       [0]: { word1, word2, ..., wordN }//Where all these words are the first sentence, second paragraph
        |       [1]: { word1, word2, ..., wordN }//And all these are the second sentence, second paragraph
        |       ...
        |..
                
**/



//FUNCTION DECLERATIONS
paragraph *ap(char *buffer);

void parse(paragraph *p,  char *buffer);//Only called internally

void fw(paragraph **pl, int size, char *local_buffer);//int size always indicates the number of paragraphs already read

void fs(paragraph **pl, int size, char *local_buffer);

void fp(paragraph **pl, int size, char *local_buffer);

void owf(paragraph **pl, int size);

void owl(paragraph **pl, int size);

int main()
{
    char run = 1;
    char *command = malloc(SIZE*sizeof(char));
    strcpy(command, "");
    int paragraph_counter = 0;//Counts how many paragraphs have been inputted

    paragraph **pl = malloc(sizeof(paragraph*)*SIZE);//Allocate enough memory for 10000*paragraphs
    for (int i = 0; i < SIZE; i++) pl[i] = malloc(sizeof(paragraph));//Init each one

    while (run)
    {
        fgets(command, SIZE, stdin);
        if (command[strlen(command) - 1] == '\n') command[strlen(command) - 1] = '\0';//Strip trailing \n

        if (command[0] == 'a' && command[1] == 'p' && command[2] == ':')
        {
            command += 3;//Memory level magic
            //strips the string of the 'ap:' part
            pl[paragraph_counter++] = ap(command);//I add a paragraph and fill the current paragraph in the array with the parse information
            //Add one to the paragraph counter and fill the struct with the info
            //Now i have a pointer full of the information needed
        }
        else if (command[0] == 'f' && command[1] == 'w' && command[2] == ':')
        {
            command += 3;
            fw(pl, paragraph_counter, command);
        }
        else if (command[0] == 'f' && command[1] == 's' && command[2] == ':')
        {
            command += 3;
            fs(pl, paragraph_counter, command);
        }
        else if (command[0] == 'f' && command[1] == 'p' && command[2] == ':')
        {
            command += 3;
            fp(pl, paragraph_counter, command);
        }
        else if (command[0] == 'o' && command[1] == 'w' && command[2] == 'f')
        {
            owf(pl, paragraph_counter);
        }
        else if (command[0] == 'o' && command[1] == 'w' && command[2] == 'l')
        {
            owl(pl, paragraph_counter);
        }
        else if (strcmp("qt", command) == 0)
        {
            run = 0;
        }
        strcpy(command, "");
    }

    return 0;
}

paragraph *ap(char *buffer)
{

    paragraph *cpar = malloc(sizeof(paragraph));

    parse(cpar, buffer);//Here is all the work
    return cpar;
}

void parse(paragraph *p, char *buffer)
{
    int n = strlen(buffer);
    int i, sc, wc, cc;
    /**
        sc: sentence counter
        wc: word counter
        cc: character counter
    **/

    char local_buffer[128] = { 0 };//Always holds one string per time

    p->sentencecount = 1;

    p->sentences = malloc(sizeof(sentence));
    p->sentences[0].wordcount = 0;
    p->sentences[0].words = malloc(sizeof(char*));
    p->sentences[0].words[0] = malloc(WORDSIZE*sizeof(char));
    //Initialize the first element of every pointer in the paragraph struct

    for (i = 0, sc = 0, wc = 0, cc = 0; i < n; i++)
    {
        if ((buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z'))
        {
            local_buffer[cc++] = buffer[i];//If the char is a normal character then add it to the local buffer
        }
        else if ((buffer[i-1] >= 'a' && buffer[i-1] <= 'z') || (buffer[i-1] >= 'A' && buffer[i-1] <= 'Z'))
        {//If the current char is a space or other not normal character and the character before is a normal
            local_buffer[cc] = '\0';//End the current word with \0
            strcpy(p->sentences[sc].words[wc], local_buffer);//Copy it to the words array
            p->sentences[sc].words = realloc(p->sentences[sc].words, (wc + 2)*sizeof(char*));//Free empty memory
            p->sentences[sc].words[wc + 1] = calloc(WORDSIZE,sizeof(char));//Ready up the next word cell
            strcpy(local_buffer, "");//Empty the buffer
            cc = 0;
            wc++;
            p->sentences[sc].wordcount++;

            if (buffer[i] == '.' || buffer[i] == '?' || buffer[i] == '!')
            {//If there is a new sentence coming
                p->sentences = realloc(p->sentences, (sc + 2)*sizeof(sentence));//Create a new cell for the new sentence
                p->sentences[sc + 1].words = malloc(sizeof(char*));//Initialize the first element of every pointer in the struct, like above(line 121)
                p->sentences[sc + 1].words[0] = malloc(WORDSIZE*sizeof(char));
                p->sentences[sc + 1].wordcount = 0;
                sc++;
                wc = 0;
                p->sentencecount++;//Add one to the counter
            }
        }
    }
}

void fw(paragraph **pl, int size, char *local_buffer)
{
    int pc, sc, wc, i;
    /**
        pc:paragraph counter
        sc:sentence counter
        wc:word counter
    **/
    char **printed_words = calloc(SIZE,sizeof(char*));//Array of already printed words (so they won't be printed again)
    int printed_words_c = 0;//Corresponding counter

    for (i = 0; i < SIZE; i++) printed_words[i] = calloc(WORDSIZE,sizeof(char));

    for (pc = 0; pc < size; pc++)
    {
        for (sc = 0; sc < pl[pc]->sentencecount; sc++)
        {
            for (wc = 0; wc < pl[pc]->sentences[sc].wordcount; wc++)
            {//3 loop structure to iterate through every word entered
                if (strstr(pl[pc]->sentences[sc].words[wc], local_buffer))
                {//If the local_buffer(string entered by user) is inside the current word
                    char found = 0;
                    for (i = 0; i < printed_words_c; i++)
                    {
                        if (strcmp(printed_words[i], pl[pc]->sentences[sc].words[wc]) == 0)
                        {
                            found = 1;//If it is already printed then do nothing
                        }
                    }
                    if (!found)
                    {//If it is not already printed, then print it and and it the printed words array
                        printf("%s\n", pl[pc]->sentences[sc].words[wc]);
                        strcpy(printed_words[printed_words_c], pl[pc]->sentences[sc].words[wc]);
                        printed_words_c++;
                    }
                }
            }
        }
    }
    for (i = 0; i < SIZE; i++) free(printed_words[i]);
    free(printed_words);
}

void fs(paragraph **pl, int size, char *local_buffer)//Same with fw
{
    int pc, sc, wc;
    for (pc = 0; pc < size; pc++)
    {
        for (sc = 0; sc < pl[pc]->sentencecount; sc++)
        {
            char found = 0;
            for (wc = 0; wc < pl[pc]->sentences[sc].wordcount; wc++)
            {
                if (strstr(pl[pc]->sentences[sc].words[wc], local_buffer)) found = 1;
            }
            if (found)
            {
                for (wc = 0; wc < pl[pc]->sentences[sc].wordcount; wc++)
                {
                    if (wc == pl[pc]->sentences[sc].wordcount - 1)
                        printf("%s\n", pl[pc]->sentences[sc].words[wc]);
                    else
                        printf("%s ", pl[pc]->sentences[sc].words[wc]);
                }
            }
        }
    }
}

void fp(paragraph **pl, int size, char *local_buffer)//Same with fs & fw
{
    int pc, sc, wc;
    char found;
    for (pc = 0; pc < size; pc++)
    {
        found = 0;
        for (sc = 0; sc < pl[pc]->sentencecount; sc++)
        {
            for (wc = 0; wc < pl[pc]->sentences[sc].wordcount; wc++)
            {
                if (strstr(pl[pc]->sentences[sc].words[wc], local_buffer)) found = 1;
            }
        }
        if (found)
        {
            for (sc = 0; sc < pl[pc]->sentencecount; sc++)
            {
                for (wc = 0; wc < pl[pc]->sentences[sc].wordcount; wc++)
                {
                    if (wc == pl[pc]->sentences[sc].wordcount - 1)
                        printf("%s\n", pl[pc]->sentences[sc].words[wc]);
                    else
                        printf("%s ", pl[pc]->sentences[sc].words[wc]);
                }
            }
        }
    }
}

char contains(char **array, char *wrd)//Internally used. Checks if an array contains a word
{
    char isin = 0;
    for (int i = 0; i < SIZE && !isin; i++)
    {
        if (strcmp(array[i], wrd) == 0)
            isin = 1;
    }
    return isin;
}

void owf(paragraph **pl, int size)
{
    char **logged_words = calloc(SIZE,sizeof(char*));//Again, a printed words array
    char **words = calloc(SIZE,sizeof(char*));//Array with all the words entered (only one time each)
    for (int i = 0; i < SIZE; i++)
    {
        logged_words[i] = calloc(WORDSIZE,sizeof(char));
        words[i] = calloc(WORDSIZE,sizeof(char));
    }

    int log_counter = 0;
    int word_counter = 0;
    int pc, sc, wc;


    int *word_times_counter = calloc(SIZE,sizeof(int));//Contains for every word, how many times it is found

    for (int i = 0; i < SIZE; i++)
    {
        word_times_counter[i] = 0;
    }

    for (pc = 0; pc < size; pc++)
    {
        for (sc = 0; sc < pl[pc]->sentencecount; sc++)
        {
            for (wc = 0; wc < pl[pc]->sentences[sc].wordcount; wc++)
            {
                char *current_word = calloc(WORDSIZE,sizeof(char));
                strcpy(current_word, pl[pc]->sentences[sc].words[wc]);

                if (!contains(logged_words, current_word))//Code that fills the word array with the words entered (one time each)
                {
                    strcpy(logged_words[log_counter++], current_word);
                    strcpy(words[word_counter++], current_word);
                }

                free(current_word);
            }
        }
    }

    for (int i = 0; i < word_counter; i++)
    {
        for (pc = 0; pc < size; pc++)
        {
            for (sc = 0; sc < pl[pc]->sentencecount; sc++)
            {
                for (wc = 0; wc < pl[pc]->sentences[sc].wordcount; wc++)
                {
                    if (strcmp(words[i], pl[pc]->sentences[sc].words[wc]) == 0)
                    {
                        word_times_counter[i]++;//Count how many times one word is entered
                    }
                }
            }
        }
    }



    for (int i = 0; i < word_counter - 1; i++)
    {
        for (int j = 0; j < word_counter - i - 1; j++)
        {
            if (word_times_counter[j] < word_times_counter[j+1])//Sorting according to times entered
            {
                int temp = word_times_counter[j];
                word_times_counter[j] = word_times_counter[j+1];
                word_times_counter[j+1] = temp;
                char *ctemp = calloc(WORDSIZE,sizeof(char));
                strcpy(ctemp, words[j]);
                strcpy(words[j], words[j+1]);
                strcpy(words[j+1], ctemp);
                free (ctemp);
            }
            else if (word_times_counter[j] == word_times_counter[j+1])//Else, short according to alhpabetical order
            {
                if (strcmp(words[j], words[j+1]) > 0)
                {
                    char *temp = calloc(WORDSIZE, sizeof(char));
                    strcpy(temp, words[j]);
                    strcpy(words[j], words[j+1]);
                    strcpy(words[j+1], temp);
                    free(temp);
                }
            }
        }
    }


    for (int i = 0; i < word_counter; i++)
        printf("%s [%d]\n", words[i], word_times_counter[i]);


    free(word_times_counter);
    for (int i = 0; i < SIZE; i++)
    {
        free(logged_words[i]);
        free(words[i]);
    }
    free(logged_words);
    free(words);
}


void owl(paragraph **pl, int size)//Same with owf
{
    char **logged_words = calloc(SIZE,sizeof(char*));
    char **words = calloc(SIZE,sizeof(char*));
    for (int i = 0; i < SIZE; i++)
    {
        logged_words[i] = calloc(WORDSIZE,sizeof(char));
        words[i] = calloc(WORDSIZE,sizeof(char));
    }

    int log_counter = 0;
    int word_counter = 0;
    int pc, sc, wc;


    int *word_times_counter = calloc(SIZE,sizeof(int));

    for (int i = 0; i < SIZE; i++) word_times_counter[i] = 0;

    for (pc = 0; pc < size; pc++)
    {
        for (sc = 0; sc < pl[pc]->sentencecount; sc++)
        {
            for (wc = 0; wc < pl[pc]->sentences[sc].wordcount; wc++)
            {
                char *current_word = calloc(WORDSIZE,sizeof(char));
                strcpy(current_word, pl[pc]->sentences[sc].words[wc]);

                if (!contains(logged_words, current_word))
                {
                    strcpy(logged_words[log_counter++], current_word);
                    strcpy(words[word_counter++], current_word);
                }

                free(current_word);
            }
        }
    }


    for (int i = 0; i < word_counter; i++)
    {
        word_times_counter[i] = strlen(words[i]);
    }


    for (int i = 0; i < word_counter; i++)
    {
        for (int j = 0; j < word_counter - i - 1; j++)
        {
            if (word_times_counter[j] > word_times_counter[j+1])
            {
                int temp = word_times_counter[j];
                word_times_counter[j] = word_times_counter[j+1];
                word_times_counter[j+1] = temp;
                char *ctemp = calloc(WORDSIZE,sizeof(char));
                strcpy(ctemp, words[j]);
                strcpy(words[j], words[j+1]);
                strcpy(words[j+1], ctemp);
                free (ctemp);
            }
            else if (word_times_counter[j] == word_times_counter[j+1])
            {
                if (strcmp(words[j], words[j+1]) > 0)
                {
                    char *temp = calloc(WORDSIZE, sizeof(char));
                    strcpy(temp, words[j]);
                    strcpy(words[j], words[j+1]);
                    strcpy(words[j+1], temp);
                    free(temp);
                }
            }
        }
    }

    for (int i = 0; i < word_counter; i++)
        printf("%s [%d]\n", words[i], word_times_counter[i]);


    free(word_times_counter);
    for (int i = 0; i < SIZE; i++)
    {
        free(logged_words[i]);
        free(words[i]);
    }
    free(logged_words);
    free(words);
}
