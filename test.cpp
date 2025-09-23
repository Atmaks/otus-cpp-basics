// Type your code here, or load an example.
struct myStruct {
    int a{};
    int b{};
    void foobar() {
        this->a = 2;
        b = 3;
    }
};

int main() {
    myStruct bbbbb{};
    bbbbb.foobar();
}
