#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

/** Constants **/
const char DETECT_BASE_URL[300] = "";
const char TRANSLATE_BASE_URL[300] = "";
const char RAPID_API_KEY[300] = "";
const char RAPID_API_HOST[300] = "";

/** Prototypes **/
CURLcode sendRequest(char url[300], char fields[300]);
void detect(char text[600]);
void translate(char text[600], char targetLang[2]);

int main(void)
{
    int option;

    printf("Welcome to the CLI Translation Service.\n");
    printf("Please select an option to begin: \n\n\n");
    printf("1. To detect language of a given text");
    printf("2. To translate a given text to another language");
    printf("3. To terminate service");
    scanf("%d", &option);

    do
    {
        if (option == 1) {
            char text[100];

            printf("Please enter the text to be translated: ");
            scanf("%s", text);

            detect(text);
        } else if (option == 2) {
            char text[100];
            char targetLang[100];

            printf("Please enter the text to be translated: ");
            scanf("%s", text);

            printf("Please enter the target language: ");
            scanf("%s", targetLang);

            translate(text, targetLang);
        } else {
            printf("Invalid option. Please try again.\n");
        }
    } while (option != 3);

    printf("Terminating service...\n");

    return 0;
}

CURLcode sendRequest(char url[300], char fields[300])
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    if (curl)
    {
        struct curl_slist *chunk = NULL;

        chunk = curl_slist_append(chunk, "Accept: application/json");
        chunk = curl_slist_append(chunk, "Content-Type: application/x-www-form-urlencoded");
        chunk = curl_slist_append(chunk, strcat("x-rapidapi-host: ", RAPID_API_HOST));
        chunk = curl_slist_append(chunk, strcat("x-rapidapi-key: ", RAPID_API_KEY));

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields); // "{\"text\":\"test\"}"

        res = curl_easy_perform(curl);

        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);

        /* free the custom headers */
        curl_slist_free_all(chunk);
    }

    fprintf(stderr, "curl failed");

    return res;
}

void detect(char text[600])
{
    char fields[700];
    
    sprintf(fields, "{\"text\":\"%s\"}", text);

    CURLcode res = sendRequest(DETECT_BASE_URL, fields);

    if (res == CURLE_OK) {
        printf("Successfully detected language of the text.\n");
    } else {
        printf("Failed to detect language of the text.\n");
    }
}

void translate(char text[600], char targetLang[2])
{
    char fields[700];
    
    sprintf(fields, "{\"text\":\"%s\",\"target\":\"%s\"}", text, targetLang);

    CURLcode res = sendRequest(TRANSLATE_BASE_URL, fields);

    if (res == CURLE_OK) {
        printf("Successfully translated the text.\n");
    } else {
        printf("Failed to translate the text.\n");
    }
}
