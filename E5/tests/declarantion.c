

// int foo(int y) { 
//     if (y == 5) {
//         return 5;
//     } else {
//         return foo(y + 1); 
//     };
// } 

// int main() { 
//     int x; 
//     x = foo(x); 
// }

int fibonacci(int n) {
    if (n == 1) {
        return 1;
    } else {
        return n + fibonacci(n-1);
    };
}

int main() { 
    int x;
    x = fibonacci(2); 
}