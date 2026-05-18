// min.h
#ifndef MIN_H
#define MIN_H

// 模板函数的声明和定义都放在头文件中
template <typename T>
T min(T a, T b) {
    return (a < b) ? a : b;
}

#endif // MIN_H