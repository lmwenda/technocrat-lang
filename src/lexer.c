#include <stdlib.h>
#include <string.h>
#include "include/lexer.h"

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
    while(lexer->c != '\0' && lexer->c < strlen(lexer->scode))
    {
        if(lexer->c == ' ' || lexer->c == 10) // 10 is the code for new line
        {
            lexer_skip_whitespace(lexer);
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
                return lexer_advance_with_tokens(lexer, init_token(TOKEN_RPAREN get_current_char_as_string(lexer)));
                break;


        }
    }
}


token_T* lexer_advance_with_tokens(lexer_T* lexer, token_T* token)
{
    lexer_advance(lexer);

    return token;
}

token_T* lexer_collect_string(lexer_T* lexer)
{

}

char* get_current_char_as_string(lexer_T* lexer)
{

}
