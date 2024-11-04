#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

uint8_t hex_to_byte(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('a' <= c && c <= 'f') return c - 'a' + 10;
    if ('A' <= c && c <= 'F') return c - 'A' + 10;
} 

void url_decode(char *src, char *dest) {
    // iterate through the src string until you hit a \0
    char *p_src = src;
    char *p_dest = dest;

    while (*p_src) { // for (int i = 0; p_src[i] != 0; i++)
        if (*p_src == '%') {

            // ex: %20, %25 etc
            uint8_t f = hex_to_byte(*(p_src + 1));
            uint8_t s = hex_to_byte(*(p_src + 2));

            uint8_t final = (f*16) + s;
            *p_dest = (unsigned char) final;

            // increment p_src
            p_src += 2;


        } else {
            // not percent-encoded
            *p_dest = *p_src;

        }
        p_src++;
        p_dest++;
    }
    *p_dest = '\0';
}

int main() {
    char simple[] = "abc";
    char percent_encoding[] = "5\%25\%20of\%20200";
    char emoji[] = "\%F0\%9F\%98\%82\%20jdshglksfdh";

    char dest[strlen(simple)];
    url_decode(simple, dest);
    printf("Encoded variant: %s        Decoded variant: %s\n", simple, dest);

    char dest2[strlen(percent_encoding)];
    url_decode(percent_encoding, dest2);
    printf("Encoded variant: %s        Decoded variant: %s\n", percent_encoding, dest2);


    char dest3[strlen(emoji)];
    url_decode(emoji, dest3);
    printf("Encoded variant: %s        Decoded variant: %s\n", emoji, dest3);

    
}