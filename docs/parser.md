# [libparser-rt](../submodules/parser-rt)

The parsing library for `.rt` files. It is meant to be an abstraction layer for file parsing, and is used by providing object-parsers functions, created by combining smaller "primitive" parsers.

## Usage

```c
#include <rt/parser.h>

void    parse_file(const char* path)
{
    t_rt_parser parser;

    // pass `true` to enable the default primitive parsers
    rt_parser_init(&parser, true, NULL);
    add_type_parsers(&parser);

    // parse the file
    rt_parser_parse(&parser, path);

    t_list  *scene;
    scene = parser.result;

    // destroy the parser (this will *NOT* free the result list)
    rt_parser_destroy(&parser);
}
```

### Type Parsers

A type parser is a struct that allows for parsing an entire line (an object entry).
