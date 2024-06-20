#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Enter the number of array elements\n");
    int N;
    scanf("%d", &N);
    int arr [N];
    printf("Enter elements\n");
    for (int i =0; i<N; i++){
        scanf("%d", &arr[i]);
    }
    printf("\n");
    for (int i =N-1; i>=0; i--){
        printf("%d ", arr[i]);
    }
    printf("\n");
}