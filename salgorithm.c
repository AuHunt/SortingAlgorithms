#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define OK 1
#define NOK 0
#define NELM 100
#define N 1048576

void selection_sort();

void merge_sort();
void msort_recursive();

void int_radix_sort();
void self_check();

int rand(void);
void srand();
int rand_r();
void init_lst();
void print_lst();

int n, lst[N], buf[N];

int main(int argc,char **argv) {

    long double del_sec,del_msec;
    struct timeval tv_s,tv_e;

    if (argc>1) n = atoi(argv[1]);
    else n = NELM;
    printf("n=%d\n",n);
    init_lst(lst,n);
    clock_t t;

    // UNCOMMENT TO PRINT LIST BEFORE SORT
    //print_lst(lst,n);

    t = clock();

    // UNCOMMENT THE SORT YOU WANT TO TEST
    
    //selection_sort(lst,n);
    //merge_sort(lst,n);
    //int_radix_sort(lst,buf,n);
    
    t = clock() - t;
    float time = ((float)t)/CLOCKS_PER_SEC;
    printf("Execution time: %f\n", time);

    // UNCOMMENT TO PRINT LIST AFTER SORT
    //printf("\n");
    
    //print_lst(lst,n);
    self_check(lst,n);
    return 0;
}

void selection_sort(int lst[],int n){
    int min, tpos, temp;
    for (int i = 0; i < n; i++){
        min = lst[i];
        tpos = i;
        // printf("New Min is %d\n", min);
        for (int x = i; x < n; x++ ) {
            if (min > lst[x]) {
                // printf("Min changed from %d to %d\n", min, lst[x]);
                min = lst[x];
                tpos = x;
            }
        }
        // printf("Min set to %d\n", min);
        temp = lst[i];
        lst[i] = min;
        lst[tpos] = temp;
    }
}

void merge_sort(int lst[], int n){
    msort_recursive(lst, 0, n-1);
}

void msort_recursive(int lst[], int left, int right){
    int nsplit;
    //printf("pootis0 %d\n", nsplit);
    if (left < right) {
        nsplit = (left + right) / 2;
        //printf("pootis1 %d\n", nsplit);

        msort_recursive(lst, left, nsplit);
        //printf("pootis2 %d\n", nsplit);

        msort_recursive(lst, nsplit + 1, right);
        //printf("pootis3 %d\n", nsplit);

        //printf("pootis %d %d\n", nsplit, left);

        int llen = nsplit - left + 1;   // Length-bounds for use in arrays for left
        int rlen = right - nsplit;      // Length-bounds for use in arrays for right
        int lsplit[llen];
        int rsplit[rlen];

        int lpos;
        int rpos;
        for (lpos = 0; lpos < llen; lpos++) {
            lsplit[lpos] = lst[left + lpos];    // Takes item from passed down lst and puts it in corresponding spot in new array (left)
        }
        for (rpos = 0; rpos < rlen; rpos++) {
            rsplit[rpos] = lst[nsplit + 1 + rpos];    // Takes item from passed down lst and puts it in corresponding spot in new array (right)
        }

        int pos = left; // set position of index to start of the lst you passed down
        lpos = 0;
        rpos = 0; // reset since using the same pos index messes something
        while (lpos < llen && rpos < rlen) {
            int lvalue = lsplit[lpos];
            int rvalue = rsplit[rpos];
            if (lvalue <= rvalue) {
                lst[pos] = lvalue;
                lpos++; pos++;
                continue;
            }
            lst[pos] = rvalue;
            rpos++;
            pos++;
        }

        // sometimes some numbers are left behind if you dont catch up to the length-bound, this is done on both left and right
        while (lpos != llen) {
            lst[pos] = lsplit[lpos];
            lpos++; pos++;
        }
        while (rpos != rlen) {
            lst[pos] = rsplit[rpos];
            rpos++; pos++;
        }
    }
} 

void int_radix_sort(int lst[], int buf[], int n){
    int flag,*src,*dst;
    int bSize = 256; 	// Bucket size fixed to 256
    int mask = bSize - 1;
    int pbits = 8;
    int i;

    int cnt[bSize];
    int map[bSize];
    for (i = 0; i < (4*pbits); i += pbits) {
        // cnt:
        for (int x = 0; x < bSize; x++) { cnt[x] = 0; }
        for (int y = 0; y < n; y++) {
            cnt[(lst[y] >> i) & mask]++;
            buf[y] = lst[y];
        }
        // map:
        map[0] = 0;
        for (int z = 1; z < bSize; z++){ //
            map[z] = cnt[z-1] + map[z-1];
        }
        // move:
        for(int v = 0; v < n; v++){
            lst[ map[ (buf[v] >> i)&mask ] ] = buf[v];
            map[ (buf[v] >> i) & mask]++;
        }
    }
}

void print_lst(int *l,int n){
    int i;
    for (i=0; i<n; i++) {
        printf("%d ",l[i]);
    }
    printf("\n");
}

void init_lst(int *l,int n){
    int i;
    srand(1234);
    for (i=0; i<n; i++) {
        l[i] = rand();
	//printf("%i\n", l[i]);
    }
}

void self_check(int *lst,int n) {
    int i,j,flag=OK,*lstp;
    
    lstp = lst;
    for (i=0;i<n-1;i++) {
      if (lstp[i] > lstp[i+1]) { flag = NOK; break; }
    }
    if (flag == OK) printf("sorted\n");
    else printf("NOT sorted at %d\n",i);
}
