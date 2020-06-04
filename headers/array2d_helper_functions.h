#ifndef ARRAY2D_HELPER_FUNCTIONS_H
#define ARRAY2D_HELPER_FUNCTIONS_H
#include "assert.h"

// ============================ Declarations =============================
template <typename T>
void fill_single_row(T** t_array, int row, int* collum_indices, T value);

template <typename T>
void fill_cell(T** t_array, int row, int collum, T value);

template <typename T>
void fill_single_collum(T** t_array, int* row_indices, int collum, T value);

template <typename T>
void fill_block(T** t_array, int* rows, int* collums, T value);

template <typename T>
void initialize_array(T** t_array, int max_rows, int max_cols, T value);

template <typename T>
void allocate_array(T** &t_array, int rows, int cols);




// ============================ Definitions =============================

template <typename T>
void fill_single_row(T** t_array, int row, int* collum_indices, int& col_height, T value)
{
    for(int i = 0; i < col_height; i++)
        t_array[row][collum_indices[i]] = value;
}

template <typename T>
void fill_cell(T** t_array, int row, int collum, T value)
{
    t_array[row][collum] = value;
}

template <typename T>
void fill_single_collum(T** t_array, int* row_indices, int row_length, int collum, T value)
{
    for(int i = 0; i < row_length; i++)
        t_array[row_indices[i]][collum] = value;
}

template <typename T>
void fill_block(T** t_array, int* rows, int row_length, int* collums, int col_height, T value)
{
    for(int i = 0; i < row_length; i++)
    {
        for(int j = 0; j < col_height; j++)
        {
            t_array[rows[i]][collums[j]] = value;
        }
    }
}

template <typename T>
void allocate_array(T** &t_array, int rows, int cols)
{
    t_array = new T*[rows];
    for(int i = 0; i < rows; i++)
        t_array[i] = new T[cols];
}

template <typename T>
void initialize_array(T** t_array, int max_rows, int max_cols, T value)
{
    assert (t_array);

    for(int r = 0; r < max_rows; r++)
        for(int c = 0; c < max_cols; c++)
            t_array[r][c] = value;
}


#endif // ARRAY2D_HELPER_FUNCTIONS_H
