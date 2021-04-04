/* File : example.h */

enum color { RED, BLUE, GREEN };

class Foo {
 public:
  Foo() { }
  enum speed { IMPULSE, WARP, LUDICROUS };
  void enum_test(speed s);
};

void enum_test(color c, Foo::speed s);

enum ImportFlags {
    FLAG_0 = 1,
    FLAG_1 = 2,
    FLAG_2 = 4
};

int load_image(char const* filename, ImportFlags s);

