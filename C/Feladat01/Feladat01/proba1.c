# include < stdio .h >
# include < stdlib .h >



void readvecs ( char *fn , int n , double *x , double *y , double *z)
 {
 FILE *f ;
 f = fopen ( fn , "r");
 for ( int i = 0; i < n; i ++) {
 fscanf (f ,"%lf %lf %lf", &x[i] , &y [i], &z[i ]);
 }
 fclose (f );
 return ;
 }

