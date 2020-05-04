/**
 * @file updateIARconfig.c
 * @author Carl Mattatall (carl.mattatall@rimot.io)
 * @brief This C file will be run as part of the build script and will 
 * automatically update the configuration passed into 
 * workspace.settings.iarvsc.configuration from the configuration provided by
 * the ewp file in iar-vsc.json
 * @version 0.1
 * @date 2020-05-01
 * 
 * @copyright Copyright (c) 2020 Rimot.io Incorporated
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>


int main(void)
{
    /* File pointer to hold reference of input file */
    FILE *fSettings = NULL;
    FILE *fTemp = NULL;
    FILE *fIAR = NULL;
    const char settingsFile[] = ".vscode/settings.json";
    const char iarFile[] = ".vscode/iar-vsc.json";
    const char keyToFindinIARfile[] = "configuration";
    const char keyToFindinSettingsFile[] = "iarvsc.configuration";
    char valueOfKeyFromIARfile[100] = {0};
    char buffer[1000];




    /*  Open all required files */
    fSettings  = fopen(settingsFile, "r");
    fTemp = fopen("replace.tmp", "w");
    fIAR = fopen(iarFile, "r"); /* Open for reading only */

    /* fopen() return NULL if unable to open file in given mode. */
    if (fSettings == NULL || fTemp == NULL || fIAR == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open a file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }

    printf("reading lines from %s....\n", iarFile);
    unsigned line = 0;  /* line counter in file */
    while(NULL != fgets(buffer, sizeof(buffer), fIAR))
    {   
        printf("%d : %s", line++, buffer);
        char *ptr = strstr(buffer, keyToFindinIARfile);
        if(NULL != ptr) /* if the key is on the current line */
        {

            printf("\n\n\nfound %s in line : %d of %s\n", 
            keyToFindinIARfile,
            line,
            iarFile);

            /* Advance to end of word */
            while('\"' != *ptr)
            {
                printf("read character : >%c<\n", *ptr);
                ptr++;
            }

            /* Skip whitespace */
            do
            {
                printf("read character : >%c<\n", *ptr);
                ptr++;
            }   while(isspace(*ptr));
            

            /* Key : val delimiter */
            if(':' == *ptr)
            {
                printf("FOUND COLON\n");
                ptr++;
            }
            else
            {
                printf("ERROR : JSON FORMAT in %s\n", iarFile);
                fclose(fSettings);
                fclose(fTemp);
                fclose(fIAR);
                exit(EXIT_FAILURE);
            }   

            /* Skip whitespace */
            do
            {
                printf("read character : >%c<\n", *ptr);
                ptr++;
            }   while(isspace(*ptr));

            /* Start of value for the key */
            if('\"' == *ptr)
            {
                ptr++;
                int i = 0;
                if(0 == ptr[i])
                {
                    printf("ERROR : EMPTY VALUE FOR KEY %s\n", 
                    keyToFindinIARfile);
                }
                else
                {
                    while(ptr[i] != '\"')
                    {


                        /* value can't fit into value holder */
                        if(i > sizeof(valueOfKeyFromIARfile))
                        {
                            printf("ERROR : VALUE BUFFER SIZE\n");
                            fclose(fSettings);
                            fclose(fTemp);
                            fclose(fIAR);
                            exit(EXIT_FAILURE);
                        }
                        
                        /* 
                         * value can't fit into line buffer 
                         * (this should never happen) 
                         */
                        else if(i > (sizeof(buffer) - (ptr - buffer)))
                        {
                            printf("ERROR : LINE BUFFER SIZE\n");
                            fclose(fSettings);
                            fclose(fTemp);
                            fclose(fIAR);
                            exit(EXIT_FAILURE);
                        }
                        else
                        {   
                            /* Copy byte */
                            valueOfKeyFromIARfile[i] = ptr[i];
                            i++;
                            printf("copied >%c<\n", valueOfKeyFromIARfile[i]);
                        }
                    }
                    i++;
                    valueOfKeyFromIARfile[i] = '\0'; /* Nul terminate */
                    printf("KEY VALUE == %s\n", valueOfKeyFromIARfile);
                }
            }
            else
            {
                printf("ERROR : JSON FORMAT in %s\n", iarFile);
                fclose(fSettings);
                fclose(fTemp);
                fclose(fIAR);
                exit(EXIT_FAILURE);
            }
            break;  
        }
    }

    memset(buffer, 0, sizeof(buffer));
    while(NULL != fgets(buffer, sizeof(buffer), fSettings))
    {
        char *ptr = strstr(buffer, keyToFindinSettingsFile);
        if(NULL != ptr)
        {
            /* FOUND THE KEY IN SETTINGS FILE */
            printf("found >\"%s\"< in %s\n", keyToFindinSettingsFile, settingsFile);

            printf("buffer = %s\n", buffer);
            
            char *t = buffer;
            while(t != (ptr - 1))
            {
                fputc(*t, fTemp);
                printf("wrote >%c<\n", *t);
                t++;
            }

            /* CONFIRM KEY STARTS WITH QUOTE */
            if('\"' != *t)
            {   
                printf("t = >%c<\n", *t);
                printf("DID NOT FIND EXPECTED QUOTE AT START OF KEY\n");
                printf("ERROR : JSON FORMAT in %s\n", settingsFile);
            }

            char *max_t = ptr + strlen(keyToFindinSettingsFile);
            for(; t < max_t; t++)
            {
                fputc(*t, fTemp);
                printf("wrote >%c<\n", *t);
            }
            
            /* CONFIRM KEY ENDS WITH QUOTE */
            if('\"' != *t)
            {   
                printf("t = >%c<\n", *t);
                printf("DID NOT FIND EXPECTED QUOTE AT END OF KEY\n");
                printf("ERROR : JSON FORMAT in %s\n", settingsFile);
            }
            else
            {
                fputc(*t, fTemp);
            }

            /* Skip whitespace */
            t++;
            while(isspace(*t))
            {
                fputc(*t, fTemp);
                printf("wrote >%c<\n", *t);
                t++;
            }

            if(':' != *t)
            {   
                printf("DID NOT FIND EXPECTED COLON. *t = >%c<\n", *t);
                printf("ERROR : JSON FORMAT in %s\n", settingsFile);
                fclose(fSettings);
                fclose(fTemp);
                fclose(fIAR);
                exit(EXIT_FAILURE);
            }
            else
            {
                fputc(*t, fTemp);
                printf("wrote >%c<\n", *t);
            }

            /* Skip whitespace */
            t++;
            while(isspace(*t))
            {
                fputc(*t, fTemp);
                printf("wrote >%c<\n", *t);
                t++;
            }

            /* Find start of quoted key value */
            if('\"' != *t)
            {   
                printf("DID NOT FIND EXPECTED QUOTE\n");
                printf("ERROR : JSON FORMAT in %s\n", settingsFile);
                fclose(fSettings);
                fclose(fTemp);
                fclose(fIAR);
                exit(EXIT_FAILURE);
            }
            else
            {   
                /* We copy the new value for IAR.config into the file */
                printf("FOUND START OF VALUE\n");
                fputc(*t, fTemp);
                printf("wrote >%c<\n", *t);
                t++;


                printf("Remaining line buffer == >%s<\n", t);
                
                /* 
                 * I don't trust stdlib / string / file 
                 * functions not to append a nul char on my 
                 * bytestring so I'm manually placing the bytes
                 * into the file
                 */
                unsigned i;
                const unsigned max = strlen(valueOfKeyFromIARfile);
                for(i = 0; i < max; i++)
                {   
                    fputc(valueOfKeyFromIARfile[i], fTemp);
                    printf("wrote >%c<\n", valueOfKeyFromIARfile[i]);
                }

                fputc('\"', fTemp);
                printf("wrote >%c<\n", '\"');

                
            }

            while('\0' != *t)
            {
                fputc(*t, fTemp);
                printf("wrote >%c<\n", *t);
                t++;
            }
        }
        else
        {   
            /* 
             * line doesn't contain the key, write entire line
             * to output file 
             */
            fputs(buffer, fTemp);
            printf("wrote line %s\n", buffer);
        }


        break;
    }

    /* Close all files to release resource */
    fclose(fSettings);
    fclose(fTemp);
    fclose(fIAR);


    #if 0
    /* Delete original source file */
    remove(settingsFile);

    /* Rename temp file as original file */
    rename("replace.tmp", settingsFile);

    #endif

    return 0;
}
