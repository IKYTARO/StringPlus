#include <stdarg.h>
#include <stdlib.h>

#include "my_string.h"
#include "utils.h"

struct sscanf_context {
    char const *string_char;
    char const *format_char;
    unsigned current_position;
    va_list *arg_pointer;
};
static struct sscanf_context *make_context(char const *str, char const *format, va_list *ap) {
    struct sscanf_context *context = (struct sscanf_context *)calloc(1, sizeof(struct sscanf_context));
    context->string_char = str;
    context->format_char = format;
    context->current_position = 0;
    context->arg_pointer = ap;

    return context;
}
static void free_context(struct sscanf_context *context) { free(context); }

static bool handle_literal_char(struct sscanf_context *context) { bool process_result = true; }

static void handle_conversion_specifier(struct sscanf_context *context) {}

static bool parse_format(struct sscanf_context *context) {
    bool parsing_status = true;

    while (*context->format_char != '\0') {
        if (!skip_spaces(context->string_char, context->format_char)) {
            parsing_status = false;
            break;
        }
        if (*context->format_char == '%') {
            handle_conversion_specifier(context);
        } else {
            handle_literal_char(context);
        }
    }

    return parsing_status;
}

int my_sscanf(char const *str, char const *format, ...) {
    va_list arg_pointer;
    va_start(arg_pointer, format);

    struct sscanf_context *context = make_context(str, format, &arg_pointer);

    parse_format(context);

    free_context(context);
    va_end(arg_pointer);
}