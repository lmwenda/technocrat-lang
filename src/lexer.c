#include <stdlib.h> 
#include <string.h> 
#include "include/lexer.h" 
#include <ctype.h>
#include <stdio.h>

// starting the lexer at index

lexer_T* init_lexer(char* scode) 
{
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->scode = scode;
    lexer->i=0;
    lexer->c = scode[lexer->i];

    return lexer;
}


// iterate  threw each charater in a content

void lexer_advance(lexer_T* lexer)
{
    if(lexer->c != '\0' && lexer->i < strlen(lexer->scode))
    {
        lexer->i += 1;
        lexer->c = lexer->scode[lexer->i];
    }
}

// lexer to skip spaces or new lines

void lexer_skip_whitespace(lexer_T* lexer)
{
    while(lexer->c == ' ' || lexer->c == 10) // 10 is the code for new line
    {
        lexer_advance(lexer);
    }
}


token_T* lexer_get_next_token(lexer_T* lexer)
{
    while(lexer->c != '\0' && lexer->i < strlen(lexer->scode))
    {

        if(lexer->c == ' ' || lexer->c == 10) // 10 is the code for new line
        {
            lexer_skip_whitespace(lexer);
        }

        if(isalnum(lexer->c))
        {
            return lexer_collect_id(lexer);
        }

        if(lexer->c == '=')
        {
            return lexer_collect_string(lexer);
        }
    
        switch(lexer->c)
        {
            case '=':
                return lexer_advance_with_tokens(lexer, init_token(TOKEN_EQUALS, get_current_char_as_string(lexer)));
                break;

            case ';':
                return lexer_advance_with_tokens(lexer, init_token(TOKEN_SEMI, get_current_char_as_string(lexer)));
                break;

            case '(':
                return lexer_advance_with_tokens(lexer, init_token(TOKEN_LPAREN, get_current_char_as_string(lexer)));
                break;

            case ')':
                return lexer_advance_with_tokens(lexer, init_token(TOKEN_RPAREN, get_current_char_as_string(lexer)));
                break;
        }
    }

    return(void*)0;
}


token_T* lexer_advance_with_tokens(lexer_T* lexer, token_T* token)
{
    lexer_advance(lexer);

    return token;
}

token_T* lexer_collect_id(lexer_T* lexer)
{
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while(isalnum(lexer->c))
    {
        char* s = get_current_char_as_string(lexer);
        value = realloc(value, (strlen(s) + strlen(value) + 1) * sizeof(char));
        strcat(value, s);
    
        lexer_advance(lexer);

    }

    lexer_advance(lexer);

    return init_token(TOKEN_ID, value);
}

token_T* lexer_collect_string(lexer_T* lexer)
{

    lexer_advance(lexer);

    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while(lexer->c != '"')
    {
        char* s = get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }

    lexer_advance(lexer);

    return init_token(TOKEN_STRING, value);
}

char* get_current_char_as_string(lexer_T* lexer)
{
    char* str = calloc(2, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';

    return str;
}
