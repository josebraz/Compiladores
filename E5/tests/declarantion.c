

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

// int factorial(int n) {
//    if(n == 0) {
//       return 1;
//    } else {
//       return n * factorial(n-1);
//    };
// }

int fibonacci(int n) {
    if (n == 1) {
        return 0;
    } else {
        if (n == 2) {
            return 1;
        } else {
            return fibonacci(n-1) + fibonacci(n-2);
        };
    };
}

int main() { 
    int x;
    x = fibonacci(6); 
}