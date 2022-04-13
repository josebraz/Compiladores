

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

int foo(int y, int x) { 
    return y + x; 
}

int main() { 
    int x;
    x = foo(5, 10); 
}