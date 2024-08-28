#include <stdio.h>
int main(int argc, char *argv[]) {
	int count = 0;
	int ct =0;

    char *filename = argv[1];

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error while opening the file\n");
        return 1;
    }

    printf("The comments in the file are:\n");
    char ch, ch1;

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '/') {
            ch1 = fgetc(fp);  // Read the next character after '/'

            if (ch1 == '/') {
                // Single-line comment detected
                count++;
                printf("%d. ", count);

                while ((ch1 = fgetc(fp)) != EOF && ch1 != '\n') {
                    putchar(ch1);  // Print the comment character by character
                }

                printf("\n");

            } else if (ch1 == '*') {
                // Multi-line comment detected
                count++; ct++;
                printf("%d. ", count);

                while ((ch = fgetc(fp)) != EOF) {
                    if (ch == '*') {
                        ch1 = fgetc(fp);
                        if (ch1 == '/') {
                            break;  // End of multi-line comment
                        }
                    }
		    else if (ch == '\n')
                        fseek(fp,2,SEEK_CUR);
                    else if (ch == ' ' || ch != '*') {
                        putchar(ch); 
                    }
                }

                printf("\n");

            } else continue;
        }
    }

    fclose(fp);
    return 0;
}
