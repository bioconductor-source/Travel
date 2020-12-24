#include "Travel.h"
#include "class_Filesystem_file_data.h"
#include "filesystem_manager.h"
size_t read_int_sequence_region(const Travel_altrep_info *altrep_info, void *buffer, size_t offset, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        ((int *)buffer)[i] = offset + i;
    }
    return length;
}
size_t read_int_sequence_block(const Travel_altrep_info *altrep_info, void *buffer,
                                          size_t offset, size_t length, size_t stride)
{
    for (size_t i = 0; i < length; i++)
    {
        ((int *)buffer)[i] = offset + i * stride;
    }
    return length;
}

Filesystem_file_data &make_int_sequence_file(int type, Subset_index index)
{
    Travel_altrep_info altrep_info;
    altrep_info.type = INTSXP;
    altrep_info.length = 1024 * 1024 * 1024;
    altrep_info.operations.get_region = read_int_sequence_region;
    altrep_info.operations.read_blocks = read_int_sequence_block;
    Filesystem_file_identifier file_info = add_filesystem_file(type, index, altrep_info);
    Filesystem_file_data &file_data = get_filesystem_file_data(file_info.file_inode);
    return file_data;
}


SEXP make_int_sequence_altrep(double n)
{
    Travel_altrep_info altrep_info;
    altrep_info.length = n;
    altrep_info.type = INTSXP;
    altrep_info.operations.get_region = read_int_sequence_region;
    altrep_info.operations.read_blocks = read_int_sequence_block;
    SEXP x = Travel_make_altrep(altrep_info);
    return x;
}
