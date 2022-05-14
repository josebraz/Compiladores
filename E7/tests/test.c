
int main ()
{
    int a;
    int b;
    int c;
    int d;
    a = 10;
    b = 20;
    c = 30;

    a = (b+c) * (b+c) - (b+c);
    d = b + c;
    b = 10;
    a = b + c;
    d = b + c;

    return 40;
}
