#include <stdio.h>

#define MAXSIZE 100000
long long ans = 0;
int temp[MAXSIZE];

void reversePairs(int *arr, int begin, int end) {
    int mid=(begin+end)/2;
    int i=begin,j=mid+1,k=0;
    if (begin!=end)
    {
    	reversePairs(arr,begin,mid);
		reversePairs(arr,mid+1,end);
    	while (i<=mid&&j<=end){
        if (arr[i]<=arr[j]) temp[k++]=arr[i++];
        else{
            temp[k++]=arr[j++];
            ans+=mid-i+1;
        }
    }
    while (i<=mid) temp[k++]=arr[i++];
    while (j<=end) temp[k++]=arr[j++];
    for (i=0,j=begin;j<=end;i++,j++) arr[j]=temp[i];
	}
}

int main() {
    int n;
    int arr[MAXSIZE];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    reversePairs(arr, 0, n - 1);
    printf("%lld\n", ans);
    return 0;
}