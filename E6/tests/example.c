int int_global;
int segundo_global;

int fn() {
    return 10;
}

int foo() {
    int foo_variable;
    foo_variable = -1;
    return 20 + foo_variable;
}

int main() {
    int c;
    c = -10;
    int d;
    d = -20;
    return 100 + d + fn();
}

