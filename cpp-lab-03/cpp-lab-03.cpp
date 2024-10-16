#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;
using namespace std::chrono;

int Pourage(int gramm[], const int n)
{
    long long plate1 = 0, plate2 = 0;

    for (int i = 0; i != n; i++)
    {
        if (abs((plate1 + gramm[i]) - plate2) < abs(plate1 - (plate2 + gramm[i])))
        {
            plate1 += gramm[i];
        }

        else
        {
            plate2 += gramm[i];
        }
    }

    return abs(plate1-plate2);
}

void Merge(int gramm[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = gramm[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = gramm[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            gramm[k] = L[i];
            i++;
        }
        else {
            gramm[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        gramm[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        gramm[k] = R[j];
        j++;
        k++;
    }

    delete [] L;
    delete [] R;
}

void MergeSort(int gramm[], int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    MergeSort(gramm, left, mid);
    MergeSort(gramm, mid + 1, right);
    Merge(gramm, left, mid, right);
}

void Test(char *read, char *outp)
{
    ifstream f_read(read);
    ifstream output(outp);

    int answer;
    output >> answer;
    output.close();

    int n;
    f_read >> n;
    auto start = high_resolution_clock::now();
    int gramm[n];

    for (int i = 0; i != n; i++)
    {
        f_read >> gramm[i];
    }

    f_read.close();

    MergeSort(gramm, 0, n - 1);

    int a = Pourage(gramm, n);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    if (duration.count()/1000000 < 1 && a == answer)
    {
        cout << a << " | Execution time " << duration.count() << " microseconds" << endl;
    }

    else
    {
        cout << "Error" << endl;
    }
}

int main()
{
    Test("C:/cpp-lab-03/input/input1.txt", "C:/cpp-lab-03/output/output1.txt");
    Test("C:/cpp-lab-03/input/input2.txt", "C:/cpp-lab-03/output/output2.txt");
    Test("C:/cpp-lab-03/input/input3.txt", "C:/cpp-lab-03/output/output3.txt");
    Test("C:/cpp-lab-03/input/input4.txt", "C:/cpp-lab-03/output/output4.txt");
    Test("C:/cpp-lab-03/input/input5.txt", "C:/cpp-lab-03/output/output5.txt");
}