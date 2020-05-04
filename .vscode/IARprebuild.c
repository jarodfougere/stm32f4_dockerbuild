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
    const char settingsFile[] = "settings.json";
    const char iarFile[] = "iar-vsc.json";
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
        /* Unable to open file so exit */
        printf("\nUnable to open a file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }

    unsigned line = 0;  /* line counter in file */
    while(NULL != fgets(buffer, sizeof(buffer), fIAR))
    {   
        char *ptr = strstr(buffer, keyToFindinIARfile);
        if(NULL != ptr) /* if the key is on the current line */
        {

            /* Advance to end of word */
            while('\"' != *ptr)
            {
                ptr++;
            }

            /* Skip whitespace */
            do
            {
                ptr++;
            }   while(isspace(*ptr));
            

            /* Key : val delimiter */
            if(':' == *ptr)
            {
                //printf("FOUND COLON\n");
                ptr++;
            }
            else
            {
                fclose(fSettings);
                fclose(fTemp);
                fclose(fIAR);
                exit(EXIT_FAILURE);
            }   

            /* Skip whitespace */
            do
            {
                ptr++;
            }   while(isspace(*ptr));

            /* Start of value for the key */
            if('\"' == *ptr)
            {
                ptr++;
                unsigned i = 0;
                if(0 == ptr[i])
                {
                    fclose(fSettings);
                    fclose(fTemp);
                    fclose(fIAR);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    while(ptr[i] != '\"')
                    {


                        /* value can't fit into value holder */
                        if(i > sizeof(valueOfKeyFromIARfile))
                        {
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
                        }
                    }
                    i++;
                    valueOfKeyFromIARfile[i] = '\0'; /* Nul terminate */
                }
            }
            else
            {
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
            char *t = buffer;
            while(t != (ptr - 1))
            {
                fputc(*t, fTemp);
                t++;
            }

            /* CONFIRM KEY STARTS WITH QUOTE */
            if('\"' != *t)
            {   
                fclose(fSettings);
                fclose(fTemp);
                fclose(fIAR);
                exit(EXIT_FAILURE);
            }

            char *max_t = ptr + strlen(keyToFindinSettingsFile);
            for(; t < max_t; t++)
            {
                fputc(*t, fTemp);
            }
            
            /* CONFIRM KEY ENDS WITH QUOTE */
            if('\"' != *t)
            {   
                fclose(fSettings);
                fclose(fTemp);
                fclose(fIAR);
                exit(EXIT_FAILURE);
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
                t++;
            }

            if(':' != *t)
            {   
                fclose(fSettings);
                fclose(fTemp);
                fclose(fIAR);
                exit(EXIT_FAILURE);
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
                t++;
            }

            /* Find start of quoted key value */
            if('\"' != *t)
            {   
                fclose(fSettings);
                fclose(fTemp);
                fclose(fIAR);
                exit(EXIT_FAILURE);
            }

            else
            {   

                /* We copy the new value for IAR.config into the file */
                fputc(*t, fTemp);
                t++;



                char *fwdCheck;
                for(fwdCheck = t; *fwdCheck != '\"'; fwdCheck++)
                {
                    if(*fwdCheck == '\n' || *fwdCheck == '\0')
                    {
                        fclose(fSettings);
                        fclose(fTemp);
                        fclose(fIAR);
                        exit(EXIT_FAILURE);
                    }
                }

                unsigned oldValLen = (unsigned)(fwdCheck - t);
                unsigned newValLen = strlen(valueOfKeyFromIARfile);


                unsigned flag = 0;
                unsigned k;
                for(k = 0; k < newValLen; k++)
                {
                    fputc(valueOfKeyFromIARfile[k], fTemp);

                    if((t != fwdCheck) && (flag == 0))
                    {
                        t++;
                    }
                    else
                    {
                        flag = 1;
                    }
                }

                fputc('\"', fTemp);
                fputc(',', fTemp);
                

                if(!flag)
                {   
                    //printf("fastwordwarding to end of old line\n");
                    /* 
                     * we need  to fast forward to end of
                     * value in old line 
                     */
                    
                    /* find delimiting comma in old line */
                    char *fwdCheckCommaDelim = fwdCheck;
                    for(; *fwdCheckCommaDelim != '\0'; fwdCheckCommaDelim++)
                    {
                        if(*fwdCheckCommaDelim == ',')
                        {   
                            break;
                        }
                    }
                    
                    /* 
                     * We've alrady tacked on our delimiting comma in
                     * new file but we need to make sure that
                     * copying the rest of the file doesn't copy
                     * the old comma (there would be 2 commas copied)
                     * which is invalid JSON
                     */

                    /* 
                     * Write spaces to file until we've passed
                     * the delimiting comma in old file 
                     */
                    while(t < fwdCheck)
                    {   
                        fputc(' ', fTemp);
                        t++;
                    }
                }
            }

        }
        else
        {   
            /* 
             * line doesn't contain the key, write entire line
             * to output file 
             */
            fputs(buffer, fTemp);
        }
    }

    /* Close all files to release resource */
    fclose(fSettings);
    fclose(fTemp);
    fclose(fIAR);

    /* Delete original source file */
    remove(settingsFile);

    /* Rename temp file as original file */
    rename("replace.tmp", settingsFile);

    return 0;
}
