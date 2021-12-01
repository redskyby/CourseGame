#include "Functions.h"


bool DoubleHit(int HitArray[], int& c) {
    if (HitArray[c] == 1) {
        HitArray[c] = 0;
        return false;
    }
    else {
        return true;
    }
};
void ReadIngFromFile(int ReadFromFile[]) {
    ifstream read;
    read.open("DataPlayer.txt");

    if (!read.is_open()) {
        cout << "Problem load a file.";
    }
    else {
        int point = 0;
        while (!read.eof()) {
            read >> ReadFromFile[point];
            point++;
        }
        read.close();
    }
    //вызов сортировки
    SortOfVector(ReadFromFile, ReadFromFile[10]);

}
void WrittenInFile(int WrittenInFile[], int& LoadInFileScore) {

    //вставляю в конец , так как  сортровка идет по убыванию.
    WrittenInFile[10] = LoadInFileScore;

    SortOfVector(WrittenInFile, WrittenInFile[10]);
    ofstream written;
    written.open("DataPlayer.txt", ios_base::out | ios_base::trunc);
    if (!written.is_open()) {
        cout << "Fail data is down";
    }
    else {
        for (int i = 0; i < 11; i++) {
            written << WrittenInFile[i] << endl;
        }
        written.close();
    }
}
void SortOfVector(int sortArray[], int& thisScore) {
    int temp = 0;

    for (int i = 0; i < 11; i++) {
        for (int j = 0;j < 11 - i; j++) {
            if (sortArray[j] <= sortArray[j + 1]) {
                temp = sortArray[j];
                sortArray[j] = sortArray[j + 1];
                sortArray[j + 1] = temp;
            }
        }
    }
}