# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "autocomplete.h"

int termcmp(const void *a, const void *b){
    const struct term *term_a = (const struct term *)a;
    const struct term *term_b = (const struct term *)b;
    return strcmp(term_a->term, term_b->term);
}

int termcmpv2(const void *a, const void *b){
    const struct term *term_a = (const struct term *)a;
    const struct term *term_b = (const struct term *)b;
    return term_b->weight - term_a->weight;
}

void read_in_terms(term **terms, int *pnterms, char *filename){
    FILE *fp = fopen(filename, "r");
    char line[200];

    *pnterms = atoi(fgets(line, sizeof(line), fp)); // Read the number of terms in the text file
    *terms = (term *)malloc((*pnterms)*sizeof(term)); // Malloc enough space for the array of terms
    
    if(*terms == NULL){
        perror("Memory cannot be allocated");
        exit(1);
    }

    int i = 0;
    while(fgets(line, 200, fp) != NULL){
        (*terms)[i].weight = atoi(strtok(line, "\t")); // Take out string before tab
        strcpy((*terms)[i].term, strtok(NULL, "\n")); // Start from tab, take out string before end of line
        i++;
    }
    qsort(*terms, *pnterms, sizeof(term), termcmp); // Sort the terms array
    fclose(fp);
}


int lowest_match(term *terms, int nterms, char *substr){
    int ind = -1; // Target index
    int low = 0; // Lower bound
    int high = nterms-1; // Upper bound
    int mid = (high+low)/2;
    while(low <= high){
        if(strncmp(substr, terms[mid].term, strlen(substr)) == 0){
            if(mid - 1 >= 0 && strncmp(substr, terms[mid-1].term, strlen(substr)) == 0){
                high = mid - 1;
            }
            else{
                return mid;
            }
        }
        else if(strncmp(substr, terms[mid].term, strlen(substr)) > 0){
            low = mid+1;
        }
        else{
            high = mid-1;
        }
        mid = (high+low)/2;
    }
    return ind;
}


int highest_match(term *terms, int nterms, char *substr){
    int ind = -1;
    int low = 0;
    int high = nterms-1;
    int mid = (high+low)/2;
    while(low <= high){
        if(strncmp(substr, terms[mid].term, strlen(substr)) == 0){
            if(mid + 1 < nterms && strncmp(substr, terms[mid+1].term, strlen(substr)) == 0){
                low = mid + 1;
            }
            else{
                return mid;
            }
        }
        else if(strncmp(substr, terms[mid].term, strlen(substr)) > 0){
            low = mid+1;
        }
        else{
            high = mid-1;
        }
        mid = (high+low)/2;
    }
    return ind;
}

void autocomplete(term **answer, int *n_answer, term *terms, int nterms, char *substr){
    if(lowest_match(terms, nterms, substr) == -1){
        return;
    }
    else if(lowest_match(terms, nterms, substr) == highest_match(terms, nterms, substr)){
        int ind = lowest_match(terms, nterms, substr);
        *n_answer = 1;
        *answer = (term *)malloc(sizeof(term));
        strcpy((*answer)[0].term, terms[ind].term);
        (*answer)[0].weight = terms[ind].weight;
    }
    else{
        int low = lowest_match(terms, nterms, substr);
        int high = highest_match(terms, nterms, substr);
        *n_answer = high-low+1;
        *answer = (term *)malloc((*n_answer) * sizeof(term));
        for(int i = low; i <= high; i++){
            strcpy((*answer)[i - low].term, terms[i].term);
            (*answer)[i - low].weight = terms[i].weight;
        }
        qsort(*answer, *n_answer, sizeof(term), termcmpv2);
    }
}