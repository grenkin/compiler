
void swapint(int *a, int *b) {
	int tmp;
        tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition(int a[], int l, int r) {
	int x;
	int i, j;
        x = a[l];
        i = l-1; j = r+1;
	while (1) {
		do j--; while (a[j] > x);
		do i++; while (a[i] < x);
		if (i < j)
			swapint(&a[i], &a[j]);
		else
			return j;
	}
}

void quicksort(int a[], int l, int r) {
	int q;
	if (l < r) {
		q = partition(a, l, r);
		quicksort(a, l, q);
		quicksort(a, q+1, r);
	}
}

void main(void) {
        int x[10];
	int n;
	int i;

        n = 10;
	for (i = 0; i < n; i++)
		x[i] = 10-i;

	quicksort(x, 0, n-1);

	for (i = 0; i < n; i++) {
		print_int(x[i]);
                print_string(" ");
        }
}
