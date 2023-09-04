#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main()
{
    int panelData[4][100]; // Assuming a maximum of 100 recommendations per panel
    int panelSizes[4];

    for (int panel = 0; panel < 4; panel++)
    {
        char filename[20];
        snprintf(filename, sizeof(filename), "panel%d.txt", panel + 1);

        FILE *file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("Error opening %s\n", filename);
            return 1; // Exit with an error code
        }

        int count = 0;
        while (fscanf(file, "%d", &panelData[panel][count]) == 1)
            count++;

        panelSizes[panel] = count;
        fclose(file);

        mergeSort(panelData[panel], 0, panelSizes[panel] - 1);
    }

    int selectedStudents[100]; // Assuming a maximum of 100 students selected
    int selectedCount = 0;

    for (int i = 0; i < panelSizes[0]; i++)
    {
        int rollno = panelData[0][i];
        int count = 1;

        for (int panel = 1; panel < 4; panel++)
        {
            int *pos = bsearch(&rollno, panelData[panel], panelSizes[panel], sizeof(int), compare);
            if (pos != NULL)
                count++;
        }

        if (count >= 3)
        {
            selectedStudents[selectedCount] = rollno;
            selectedCount++;
        }
    }

    printf("Selected Students: ");
    for (int i = 0; i < selectedCount; i++)
        printf("%d ", selectedStudents[i]);
    printf("\n");

    return 0;
}
