#include "splashkit.h"

#define NUM_VALS 100

//creating the bar array
void draw_values(const int values[], int size) 
{
    int x = 0;
    int y;
    int rect_height;
    int rect_width = screen_width() / size;

    for (int i = 0; i < size; i++)
    {
        rect_height = values[i];
        y = screen_height() - rect_height;

        fill_rectangle(COLOR_RED, x, y, rect_width, rect_height);
        draw_rectangle(COLOR_WHITE, x, y, rect_width, rect_height);
        
        x += rect_width;
    }
}

//visually representing what the sorts are doing
void draw_sort(int values[], int size)
{
    clear_screen(COLOR_WHITE);
    draw_values(values, size);
    refresh_screen(60);
}

//procedure for swapping values
void swap( int &value1, int &value2)
{
    int temp = value1;
    value1 = value2;
    value2 = temp;
}

//function for finding the pivot and swaping it either left or right depending in its size
int dividing(int values[], int start, int end)
{
    int divide = values[start];

    
    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if(values[i] <= divide)
        {
            count++;
        }
    }

    //providing divide index its correct position
    int divide_index = start + count;
    swap(values[divide_index], values[start]);

    //defining
    int i = start; 
    int j = end;

    //sorting the left and right parts of the divide index
    while (i < divide_index && j > divide_index)
    {
        while (values[i] <= divide)
        {
            i++;
        }

        while (values[j] > divide)
        {
            j--;
        }

        //swapping thr values if it is less then  i then it swaps, or if its greater than j then it swaps
        if( i < divide_index && j > divide_index)
        {
            swap(values[i++], values[j--]);
        }
    }
    return divide_index;
}

//sorting values by swapping the ones that are bigger
void bubble_sort(int values[], int size)
{
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size - 1; i++)
        {
            if (values[i] > values[ i + 1 ])
            {
                swap(values[i], values[ i + 1 ]);
                draw_sort(values, size);
            }
        }
    }
}

//procedure for the quick sort function, sorts each bar in groups
void quick_sort(int values[], int start, int end, int size)
{
    //base
    if (start >= end)
    {
        return;
    }

    //dividing the array into parts
    int d = dividing(values, start, end);

    draw_sort(values, size);

    //sorting the left part
    quick_sort(values, start, d - 1, size);

    //sorting the right part
    quick_sort(values, d + 1, end, size);
}

//filling the array with random bars
void random_fill_array(int values[], int size)
{
    for (int i = 0; i < size; i++) 
    {
        values[i] = rnd(screen_height()) + 1;
    }
}

//key functions, R, S and D keys
void handle_input(int values[], int size)
{
    if (key_typed(R_KEY))
    {
        random_fill_array(values, size);
    }

    else if (key_typed(S_KEY))
    {
        bubble_sort(values, size);
    }
    else if (key_typed(D_KEY))
    {
        quick_sort(values, 0, size - 1, size);
    }
    
}


int main()
{
    int values[NUM_VALS];

    open_window("Sort Visualiser", 800, 600);
    
    //making the array
    random_fill_array(values, NUM_VALS);

    while ( not quit_requested() )
    {
        process_events();
        handle_input(values, NUM_VALS);
        
        draw_sort(values, NUM_VALS);
    }

    return 0;
}