

int main(){
    int N = 100;
    int i, j;
    double a[N], b[N];
    double x, f, sum;

    //a[i-1] ist eine Read-after-Write-Abhängigkeit, 
    //da mehrere Threads gleichzeitig a[i] schreiben und a[i-1] lesen. Dies führt zu Race Conditions.
    a[0] = 0;
    #pragma omp parallel for
    for (i=1; i<N; i++) {
        a[i] = 2.0*i*(i-1);
    b[i] = a[i] - a[i-1];
    }
    //fix:
    a[0] = 0;
    #pragma omp parallel for
    for(i=1; i<N; i++) {
        a[i] = 2.0*i*(i-1);
    }
    #pragma omp parallel for
    for(i=1; i<N; i++) {
        b[i] = a[i] - a[i-1];
    }
    //
    //nowait macht das die Threads nicht aufeinander warten, das kann zu Race Condition führen
    a[0] = 0;
    #pragma omp parallel
    {
        #pragma omp for //nowait //fix nowait entfernen
        for (i=1; i<N; i++) {
            a[i] = 3.0*i*(i+1);
        }
        #pragma omp for
        for (i=1; i<N; i++) {
            b[i] = a[i] - a[i-1];
        }
    }
    //
    #pragma omp parallel for default(none) private(x) shared(a,b,N) /*fix*/
    for (i=0; i<N; i++) {
        x = sqrt(b[i]) - 1;
        a[i] = x*x + 2*x + 1;
    }
    //
    //f ist vor der Parallelregion definiert, also nicht initalisiert in den Threads
    //x wird außerhalb der Schleife verwendet, ist aber nur in einem Thread definiert (undefiniertes Verhalten)
    f = 2; //wenn variable vor omp parallel deklariert wrid wird firstprivate benötigt
    #pragma omp parallel for firstprivate(f) lastprivate(x)
    for (i=0; i<N; i++) {
        x = f * b[i];
        a[i] = x - 7;
    }
    a[0] = x; 
    //
    sum = 0; 
    #pragma omp parallel for
    for (i=0; i<N; i++) {
        sum = sum + b[i];
    }
    //
    #pragma omp parallel
    #pragma omp for
    for (i=0; i<N; i++) {
        #pragma omp for
        for (j=0; j<N; j++) {
            a[i][j] = b[i][j];
        }
    }
}