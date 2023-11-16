#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

//CMAX = max number of commands -> max # row_swap (20) + max # col_swap(20)
#define CMAX 40

//if target is in array 'arr', then return 1, otherwise 0
int is_in(int target, int *arr, int n){
    for(int i=0; i<n; i++){
        if(arr[i]==target){
            return 1;
        }
    }
    return 0;
}

//swap arr[i] and arr[j]
void swap_arr(int* arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// if target is in array 'arr', then return the index, other wise -1
int find_idx(int target, int *arr, int n){
    for(int i=0; i<n; i++){
        if(arr[i] == target){
            return i;
        }
    }
    return -1;
}

int main()
{
    //commands[?][0]=0 -> row_swap
    //commands[?][0]=1 -> col_swap
    //commands[?][1] -> first argument
    //commands[?][2] -> second argument
    int commands[CMAX][3];
    int com_idx = 0; // index of commands[][]

    int n;

    //scanning 'n'
    scanf("%d", &n);

    //memmory allocating of a[][], b[][]
    int **a = (int**)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++){
        a[i] = (int*)malloc(n*sizeof(int));
    }
    int **b = (int**)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++){
        b[i] = (int*)malloc(n*sizeof(int));
    }

    //scanning a[][]
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d", &a[i][j]);
        }
    }
    //scanning b[][]
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d", &b[i][j]);
        }
    }

    //certain row(or column) of a[][]
    int* small_a = (int*)malloc(n*sizeof(int));
    //certain row(or column) of b[][]
    int* small_b = (int*)malloc(n*sizeof(int));
    //if one element in one row(or column) is already handled(this means the element should be fixed in that position),
    //that element should be in 'checked[]' array
    int* checked = (int*)malloc(n*sizeof(int));


    int ch_idx; //index of checked array
    int t_idx; // target index of small_a[]
    int s_idx; // swap_index
    //for all target_index, we need to find s_index to make small_a == small_b ,using swap(small_a, t_idx, s_idx)


    /*--------------------1. find all of row_swap operations--------------------*/
    ch_idx = 0;
    t_idx = 0;
    s_idx = 0;

    //copy first column of 'a' to small_a
    for(int i=0; i<n; i++){
        small_a[i] = a[i][0];
    }

    //copy corresponding changed column of 'b' to small_b
    for(int i=0; i<n; i++){
        if(is_in(b[0][i], small_a, n)){
            for(int j=0; j<n; j++){
                small_b[j] = b[j][i];
            }
            break;
        }
    }

    while(ch_idx < n){
        //if the value t_idx is pointing was already handled before(this means the value is moved to match with 'small_b')
        //then t_idx points to the next value
        if(is_in(small_a[t_idx], checked, ch_idx)){
            t_idx++;
        }
        //if the value is not handled before, but there is no need for changing positions to match with small_b
        //then just check that value and skip to next iteration
        else if(small_a[t_idx] == small_b[t_idx]){
            checked[ch_idx++] = small_a[t_idx];
        }
        //if the value is not handled before and we need to change positions to match with small_b
        //then add row_swap commands and adjust small_a
        else{
            checked[ch_idx++] = small_a[t_idx];

            s_idx = find_idx(small_a[t_idx], small_b, n);

            //add command
            commands[com_idx][0] = 0; //row_swap
            commands[com_idx][1] = t_idx+1;
            commands[com_idx][2] = s_idx+1;
            com_idx++;

            //adjust small_a
            swap_arr(small_a, t_idx, s_idx);
        }
    }


    /*--------------------2. find all of col_swap operations--------------------*/
    ch_idx = 0;
    t_idx = 0;
    s_idx = 0;

    //copy first row of 'a' to small_a
    for(int i=0; i<n; i++){
        small_a[i] = a[0][i];
    }

    //copy corresponding changed row of 'b' to small_b
    for(int i=0; i<n; i++){
        if(is_in(b[i][0], small_a, n)){
            for(int j=0; j<n; j++){
                small_b[j] = b[i][j];
            }
            break;
        }
    }

    while(ch_idx < n){
        //if the value t_idx is pointing was already handled before(this means the value is moved to match with 'small_b')
        //then t_idx points to the next value
        if(is_in(small_a[t_idx], checked, ch_idx)){
            t_idx++;
        }
        //if the value is not handled before, but there is no need for changing positions to match with small_b
        //then just check that value and skip to next iteration
        else if(small_a[t_idx] == small_b[t_idx]){
            checked[ch_idx++] = small_a[t_idx];
        }
        //if the value is not handled before and we need to change positions to match with small_b
        //then add col_swap commands and adjust small_a
        else{
            checked[ch_idx++] = small_a[t_idx];

            s_idx = find_idx(small_a[t_idx], small_b, n);

            //add command
            commands[com_idx][0] = 1; //col_swap
            commands[com_idx][1] = t_idx+1;
            commands[com_idx][2] = s_idx+1;
            com_idx++;

            //adjust small_a
            swap_arr(small_a, t_idx, s_idx);
        }
    }

    /*--------------------3. print commands and terminate--------------------*/

    for(int i=0; i<com_idx; i++){
        if(commands[i][0] == 0){
            printf("row_swap %d %d\n", commands[i][1], commands[i][2]);
        }else if(commands[i][0] == 1){
            printf("col_swap %d %d\n", commands[i][1], commands[i][2]);
        }
    }

    printf("exit\n");

    for(int i=0; i<n; i++){
        free(a[i]);
    }
    free(a);
    for(int i=0; i<n; i++){
        free(b[i]);
    }
    free(b);
    free(small_a);
    free(small_b);
    free(checked);

    return 0;
}

