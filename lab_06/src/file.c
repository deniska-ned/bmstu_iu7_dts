#include "../inc/file.h"
#include "../inc/error_codes.h"

int scan_elem_from_source(FILE *src, elem_t *dst)
{
    if (fscanf(src, "%ld", dst) != 1)
        return READ_ERROR;
    
    return EXIT_SUCCESS;
}

void print_elem_to_source(FILE *dst, elem_t src)
{
    fprintf(dst, "%ld\n", src);
}

int file_print(FILE *dst, char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ERROR;
    
    elem_t el;
    while (!scan_elem_from_source(f, &el))
    {
        fprintf(dst, "%ld\n", el);
    }
    
    fclose(f);
    
    return EXIT_SUCCESS;
}

int file_add(char *file_name, elem_t elem)
{
    FILE *f = fopen(file_name, "a+");
    if (!f)
        return OPEN_ERROR;

    elem_t el;
    while (!scan_elem_from_source(f, &el))
        if (el == elem)
            break;
    
    if (feof(f))
        print_elem_to_source(f, elem);

    fclose(f);
    
    return EXIT_SUCCESS;
}

int file_search(char *file_name, elem_t elem, size_t *comparisons, int *find)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ERROR;

    *comparisons = 0;
    *find = 0;
    elem_t el;
    while (!scan_elem_from_source(f, &el) && !(*find))
    {
        *comparisons += 1;
        if (el == elem)
            *find = 1;
    }

    fclose(f);

    return EXIT_SUCCESS;
}

int file_del(char *file_name, elem_t key)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
      return OPEN_ERROR;
  
    FILE *temp = fopen("temp.txt", "w");
    if (!temp)
    {
        fclose(f);
        return OPEN_ERROR;
    }
  
    elem_t buf;
    while (fscanf(f, "%ld", &buf) == 1)
    {
        if (buf != key)
            fprintf(temp, "%ld\n", buf);
    }
    
    fclose(f);
    fclose(temp);
  
    remove(file_name);
    rename("temp.txt", file_name);

    return EXIT_SUCCESS;
}

void file_make_empty(char *filename)
{
    FILE *f = fopen(filename, "w");
    
    assert(NULL != f);

    fclose(f);
}
