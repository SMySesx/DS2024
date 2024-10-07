#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib> // 包含rand()和srand()
#include <ctime>   // 包含time()
using namespace std;

// 定义复数类(Complex)
class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // 成员函数打印复数
    void print() const {
        cout << "(" << real << ", " << imag << "i)" << endl;
    }

    //计算复数的模(modulus)
    double modulus() const {
        return sqrt(real * real + imag * imag);
    }
};

// 起泡排序
void bubbleSort(vector<Complex>& vec) {
    bool swapped = true;
    int n = vec.size();
    while (swapped) {
        swapped = false;
        for (int i = 1; i < n; i++) {
            if (vec[i - 1] > vec[i]) {
                swap(vec[i - 1], vec[i]);
                swapped = true;
            }
        }
        n--;
    }
}

// 归并排序
void merge(vector<Complex>& vec, int left, int middle, int right) {
    vector<Complex> temp(right - left + 1);
    int i = left, j = middle + 1, k = 0;
    while (i <= middle && j <= right) {
        if (vec[i] < vec[j]) {
            temp[k++] = vec[i++];
        } else {
            temp[k++] = vec[j++];
        }
    }
    while (i <= middle) {
        temp[k++] = vec[i++];
    }
    while (j <= right) {
        temp[k++] = vec[j++];
    }
    for (i = left, k = 0; i <= right; ++i, ++k) {
        vec[i] = temp[k];
    }
}

void mergeSort(vector<Complex>& vec, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(vec, left, middle);
        mergeSort(vec, middle + 1, right);
        merge(vec, left, middle, right);
    }
}

// 区间查找
vector<Complex> rangeSearch(const vector<Complex>& vec, double m1, double m2) {
    vector<Complex> result;
    for (const auto& c : vec) {
        if (c.modulus() >= m1 && c.modulus() < m2) {
            result.push_back(c);
        }
    }
    return result;
}

int main() {
    // 使用当前时间作为随机数生成器的种子
    srand(static_cast<unsigned int>(time(0)));

    // 创建一个包含复数的向量
    vector<Complex> complexVector;
        // 生成长整型范围内的随机实数和虚数
    for(int i=0;i<10;++i){
        double realPart = rand();
        double imagPart = rand();
        complexVector.emplace_back(realPart, imagPart);
    }
    // 使用成员函数打印向量
    cout << "Vector:" << endl;
    for (const auto& c : complexVector) {
        c.print();
    }

    //置乱
    template typename <T> void permute(Vector<T>&V){
        for(int i=V.size();i>0;i--)
            swap(V[i-1],V[rand()%i]);
    }
    //查找
    template typename<T>
    Rank Vector<T>::find(T const& e,Rank lo,Rank hi)const{
        while((lo<hi--)&&(e!=_elem[hi]));
        return hi;
    }
    //插入
    template typename<T>
    Rank Vector<T>::insert(Rank r,T const& e){
        expand();
        for(int i=_size;i>r;i--)_elem[i]=_elem[i-1];
        _elem[r]=e;_size++;
        return r;
    }
    //删除
    template <typename T> int Vector<T>::remove(Rank lo,Rank hi){
        if(lo==hi) return 0;
        while(hi<_size) _elem[lo++]=elem[hi++];
        _size=lo;
        shrink();
        return hi-lo;
    }
    //唯一化
    template typename<T> int Vector<T>::deduplicate(){
        int oldsize = _size;
        Rank i=1;
        while(i<_size)
            (find(_elem[i],0,i)<0)?
            i++:remove(i);
        return oldsize-_size;
    }

    // 排序并计时
    vector<Complex> sortedVector = complexVector;
    clock_t start, end;
    double time_used;

    // 起泡排序
    start = clock();
    bubbleSort(sortedVector);
    end = clock();
    time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "起泡排序用时: " << time_used << endl;

    // 归并排序
    start = clock();
    mergeSort(complexVector, 0, sortedVector.size() - 1);
    end = clock();
    time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "归并排序用时: " << time_used << endl;

    // 区间查找
    vector<Complex> rangeResult = rangeSearch(complexVector, 5.0, 10.0);
    cout << "区间查找结果:" << endl;
    for (const auto& c : rangeResult) {
        cout << c.real << " + " << c.imag << "i" << endl;
    }
    return 0;
}