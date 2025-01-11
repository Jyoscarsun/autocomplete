# include <stdio.h>
# include <string.h>
# include <stdlib.h>

int main(){
    // char *test = "     1234 Melbourne";
    // int ind = 0;
    // while(test[ind] == ' '){
    //     ind++;
    // }
    // int ind2 = ind;
    // while(test[ind2] != ' '){
    //     ind2++;
    // }
    // char *num = (char *)malloc((ind2-ind+1)*sizeof(char));
    // char *city = (char *)malloc((strlen(test)-ind2)*sizeof(char));
    // strncpy(num, test+ind, ind2-ind);
    // strncpy(city, test+ind2+1, strlen(test)-ind2);
    // printf("num: %s\n", num);
    // printf("city: %s\n", city);

    char strings[5][10];
    strcpy(strings[0], "First string");
    strcpy(strings[1], "Second string");
    strcpy(strings[2], "Third string");
    strcpy(strings[3], "Fourth string");
    strcpy(strings[4], "Fifth string");
    qsort(strings, 5, sizeof(char *), strcmp);
    printf("\nAfter sorting the list is: \n");
    for(int n = 0 ; n < 5; n++ ) {   
      printf("%s\n", strings[n]);
    }

    char *num = "1234";
    int a = atoi(num);
    print("%d\n", a);
}