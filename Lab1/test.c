

fp = fopen("Q1_21052522.c", "r");
fscanf(fp, "%d", &n);
printf("\n n= %d", n);
int a[n];
for (i = 0; i < n; i++)
{
    fscanf(fp, "%d", &a[i]);
    printf("\n a[%d]= %d", i, a[i]);
}
fclose(fp);