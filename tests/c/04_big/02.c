int m;
float X;

float abs(float x) {
	if (x >= 0)
		return x;
	else
		return -x;
	return x >= 0 ? x : -x;
}

void main(void) {
	float x[6], y[6];
	int n;
	float res, p;
	int i, j, k;

	n = 5;
	x[0] = 0; y[0] = 0;
	x[1] = 1; y[1] = 10;
	x[2] = 2; y[2] = 5;
	x[3] = 3; y[3] = -2;
	x[4] = 4; y[4] = -6.5;
	x[5] = 5; y[5] = 7;
	X = 3.5;

	res = 0;
	for (k = 0; k < n+1; k++) {
		p = y[k];
		for (j = 0; j < n+1; j++) {
			if (j != k)
				p *= (X-x[j])/(x[k]-x[j]);
		}
		res += p;
	}

	print_float(res);
}
