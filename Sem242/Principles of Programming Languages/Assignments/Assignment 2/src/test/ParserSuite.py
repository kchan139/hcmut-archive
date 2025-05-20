import unittest
from TestUtils import TestParser


class ParserSuite(unittest.TestCase):

    def test_001(self):
        """Literal: constant int declaration"""
        self.assertTrue(
            TestParser.checkParser("const Votien = 1;", "successful", 101)
        )

    def test_002(self):
        """Literal: constant boolean declaration"""
        self.assertTrue(
            TestParser.checkParser("const Votien = true;", "successful", 102)
        )

    def test_003(self):
        """Literal: array literal in constant declaration"""
        self.assertTrue(
            TestParser.checkParser('const Votien = [5][0]string{1, "string"};', "successful", 103)
        )

    def test_004(self):
        """Error: illegal float literal in array type"""
        self.assertTrue(
            TestParser.checkParser("const Votien = [1.]ID{1, 3};", "Error on line 1 col 16: 1.", 104)
        )

    def test_005(self):
        """Literal: struct literal constant declaration"""
        self.assertTrue(
            TestParser.checkParser('const Votien = Person{name: "Alice", age: 30};', "successful", 105)
        )

    def test_006(self):
        """Expression: mix of logical, arithmetic and unary operators"""
        self.assertTrue(
            TestParser.checkParser("const Votien = 1 || 2 && c + 3 / 2 - -1;", "successful", 106)
        )

    def test_007(self):
        """Expression: array accesses and field accesses"""
        self.assertTrue(
            TestParser.checkParser("const Votien = 1[2] + foo()[2] + ID[2].b.b;", "successful", 107)
        )

    def test_008(self):
        """Expression: function call with field access in expression"""
        self.assertTrue(
            TestParser.checkParser("const Votien = ca.foo(132) + b.c[2];", "successful", 108)
        )

    def test_009(self):
        """Expression: chained field access with function call"""
        self.assertTrue(
            TestParser.checkParser("const Votien = a.a.foo();", "successful", 109)
        )

    def test_010(self):
        """Declaration: multiple variable declarations"""
        input_str = """
            var x int = foo() + 3 / 4;
            var y = "Hello" / 4;   
            var z str;
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 110)
        )

    def test_011(self):
        """Declaration: constant expression with function call"""
        self.assertTrue(
            TestParser.checkParser("const VoTien = a.b() + 2;", "successful", 111)
        )

    def test_012(self):
        """Declaration: multiple function declarations with different return types"""
        input_str = """
            func VoTien(x int, y int) int {return;}
            func VoTien1() [2][3] ID {return;};
            func VoTien2() {return;}
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 112)
        )

    def test_013(self):
        """Declaration: multiple method declarations"""
        input_str = """
            func (c Calculator) VoTien(x int) int {return;};
            func (c Calculator) VoTien() ID {return;};
            func (c Calculator) VoTien(x int, y [2]VoTien) {return;};
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 113)
        )

    def test_014(self):
        """Declaration: struct type declaration"""
        input_str = """
            type VoTien struct {
                VoTien string;
                VoTien [1][3]VoTien;
            }
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 114)
        )

    def test_015(self):
        """Error: struct declaration with empty body"""
        input_str = """
            type VoTien struct {}
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "Error on line 2 col 32: }", 115)
        )

    def test_016(self):
        """Error: interface declaration with extra closing brace"""
        input_str = """
            type Calculator interface {
                Add(x, y int) int;
                Subtract(a, b float, c int) [3]ID;
                Reset()
                SayHello(name string);
            }
            type VoTien interface {}
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "Error on line 8 col 35: }", 116)
        )

    def test_017(self):
        """Declaration: function with inner declarations"""
        input_str = """
            func VoTien() {
                var x int = foo() + 3 / 4;
                var y = "Hello" / 4;
                var z str;
                const VoTien = a.b() + 2;
            }
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 117)
        )

    def test_018(self):
        """Statement: assignment using short declaration and field indexing"""
        input_str = """
            func VoTien() {
                x := foo() + 3 / 4;
                x.c[2][4] := 1 + 2;
            }
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 118)
        )

    def test_019(self):
        """Statement: if-else-if statement with nested declarations"""
        input_str = """
            func VoTien() {
                if (x > 10) {return;}
                if (x > 10) {
                  return;
                } else if (x == 10) {
                    var z str;
                } else {
                    var z ID;
                }
            }
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 119)
        )

    def test_020(self):
        """Statement: various forms of for loops"""
        input_str = """
            func VoTien() {
                for i < 10 {return;}
                for i := 0; i < 10; i += 1 {return;}
                for index, value := range array {return;}
            }
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 120)
        )

    def test_021(self):
        """Statement: break, continue, return and call statements"""
        input_str = """
            func VoTien() {
                for i < 10 {break;}
                break;
                continue;
                return 1;
                return;
                foo(2 + x, 14 / y); m.goo();
            }
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 121)
        )

    def test_022(self):
        """Literal: binary integer literal"""
        self.assertTrue(
            TestParser.checkParser("const a = 0b11;", "successful", 122)
        )

    def test_023(self):
        """Error: invalid array literal element type"""
        self.assertTrue(
            TestParser.checkParser("var z VOTIEN = [true]int{1};", "Error on line 1 col 16: true", 123)
        )

    def test_024(self):
        """Expression: identifier followed by empty block (interpreted as a struct literal)"""
        self.assertTrue(
            TestParser.checkParser("var z VOTIEN = ID {};", "successful", 124)
        )

    def test_025(self):
        """Expression: nested struct literal in variable initialization"""
        self.assertTrue(
            TestParser.checkParser("var z VOTIEN = ID {a: 2, b: 2 + 2 + ID {a: 1}};", "successful", 125)
        )

    def test_026(self):
        """Expression: multiple logical operators"""
        self.assertTrue(
            TestParser.checkParser("var z VOTIEN = 1 && 2 && 3 || 1 || 1;", "successful", 126)
        )

    def test_027(self):
        """Expression: mixed relational operators with array and struct literals"""
        self.assertTrue(
            TestParser.checkParser("var z VOTIEN = a >= 2 <= \"string\" > a[2][3] < ID{A: 2} >= [2]S{2};", "successful", 127)
        )

    def test_028(self):
        """Expression: chained field accesses"""
        self.assertTrue(
            TestParser.checkParser("var z VOTIEN = a.b.a.c.e.g;", "successful", 128)
        )

    def test_029(self):
        """Expression: nested array indexing with expression"""
        self.assertTrue(
            TestParser.checkParser("var z VOTIEN = a[2][3][a + 2];", "successful", 129)
        )

    def test_030(self):
        """Expression: function call on an array element in a chained expression"""
        self.assertTrue(
            TestParser.checkParser("var z VOTIEN = a.a.a[2].foo(1);", "successful", 130)
        )

    def test_031(self):
        """Expression: chained function and array call"""
        self.assertTrue(
            TestParser.checkParser("var z VOTIEN = foo().a[2].goo();", "successful", 131)
        )

    def test_032(self):
        """Expression: use of multiple unary operators"""
        self.assertTrue(
            TestParser.checkParser("const k = -a + -!-!c - ---[2]int{2};", "successful", 132)
        )

    def test_033(self):
        """Declaration: array variable without initializer"""
        self.assertTrue(
            TestParser.checkParser("var c [2][3]ID;", "successful", 133)
        )

    def test_034(self):
        """Error: constant declaration with missing initializer"""
        self.assertTrue(
            TestParser.checkParser("const a =;", "Error on line 1 col 9: ;", 134)
        )

    def test_035(self):
        """Declaration: function with array parameter and array return type"""
        self.assertTrue(
            TestParser.checkParser("func Add(x int, y [2]int) [2]id {return ;};", "successful", 135)
        )

    def test_036(self):
        """Declaration: function with no parameter and no return type"""
        self.assertTrue(
            TestParser.checkParser("func Add() {return ;};", "successful", 136)
        )

    def test_037(self):
        """Declaration: struct type with multiple fields"""
        input_str = """
            type Calculator struct {
                value int;
                a [2]int; a [2]ID;
                c Calculator
            }
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 137)
        )

    def test_038(self):
        """Error: struct field declared with assignment (not allowed)"""
        input_str = """
            type Calculator struct {
                a int = 2;
            }
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "Error on line 3 col 22: =", 138)
        )

    def test_039(self):
        """Declaration: interface type with multiple methods"""
        input_str = """
            type Calculator interface {
                Add(x, y [2]ID) [2]int;
                Subtract(a, b float, c, e int);
                Reset();
                SayHello(name string)
            }
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 139)
        )

    def test_040(self):
        """Error: interface type declaration with missing semicolon or newline token"""
        self.assertTrue(
            TestParser.checkParser("type Calculator interface {Reset()}", "Error on line 1 col 34: }", 140)
        )

    def test_041(self):
        """Declaration: interface type with two method declarations on one line"""
        input_str = """
            type Calculator interface { 
                Add(x int,c,d ID); Add() 
            }
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 141)
        )

    def test_042(self):
        """Declaration: function with parameters and return type"""
        self.assertTrue(
            TestParser.checkParser("func Add(x int, y int) int {return ;};", "successful", 142)
        )

    def test_043(self):
        """Error: method declaration with invalid receiver type"""
        self.assertTrue(
            TestParser.checkParser("""
                func (c Calculator) Add(x int) int {
                    return ;
                }
                """, "successful", 143)
        )

    def test_044(self):
        """Error: empty program (or missing content)"""
        self.assertTrue(
            TestParser.checkParser("", "Error on line 1 col 0: <EOF>", 144)
        )

    def test_045(self):
        """Statement: function with a simple variable declaration inside a block"""
        input_str = """
            func Add() {
                var a int;
            };
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 145)
        )

    def test_046(self):
        """Statement: function with variable initialized using array access"""
        input_str = """
            func Add() {
                var a = a[2].b;
            };
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 146)
        )

    def test_047(self):
        """Statement: function with several compound assignment statements"""
        input_str = """
            func Add() {
                a += 2;
                a -= a[2].b();
                a /= 2;
                a *= 2;
                a %= 2;
            };
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 147)
        )

    def test_048(self):
        """Statement: function with complex chained field and array accesses in assignment"""
        input_str = """
            func Add() {
                a.c[2].e[3].k += 2;
            };
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 148)
        )

    def test_049(self):
        """Error: function attempting to assign to a function call result"""
        input_str = """
            func Add() {
                a.foo() += 2;
            };
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "Error on line 3 col 24: +=", 149)
        )

    def test_050(self):
        """Statement: function with complex expression inside an array index and assignment"""
        input_str = """
            func Add() {
                a[2+3&&2] += foo().b[2];
            };
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 150)
        )

    def test_051(self):
        """Statement: function with if-else statement including declarations and returns"""
        input_str = """
            func Add() {
                if (x.foo().b[2]) {
                    a := 2;
                } else if (a && b) {
                    return;
                } else {
                    a := 2;
                }
            };
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 151)
        )

    def test_052(self):
        """Statement: function with for loop using an expression as header"""
        input_str = """
            func Add() {
                for true + 2 + foo().b {return; }
            };
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 152)
        )

    def test_053(self):
        """Statement: function with standard for loop header"""
        input_str = """
            func Add() {
                for i := 0; i < 10; i += 1 { return; }
            };
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 153)
        )

    def test_054(self):
        """Statement: function with for loop using range clause"""
        input_str = """
            func Add() {
                for index, value := range 23 { return; }
            };
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 154)
        )

    def test_055(self):
        """Statement: function with multiple break and continue statements"""
        input_str = """
            func Add() {
                break;
                continue;
                break; continue; break;
            };
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 155)
        )

    def test_056(self):
        """Statement: function with several return statements"""
        input_str = """
            func Add() {
                return;
                return 2 + a[2].b();
                return; return a;
            };
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 156)
        )

    def test_057(self):
        """Statement: function with two function calls having struct literals as arguments"""
        input_str = """
            func Add() {
                a.foo(2 + 3, a {a:2});
                foo(2 + 3, a {a:2});
            };
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 157)
        )

    def test_058(self):
        """Statement: for loop with variable declaration in initializer"""
        input_str = """
            func Add() {
                for var b [2]ID = 1 + 2 / 4; foo().a.b(); i := 1 {
                    return;
                }
            };
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 158)
        )

    def test_059(self):
        """Literal: complex array literal with multidimensional type"""
        self.assertTrue(
            TestParser.checkParser("const a = [ID][2][VT]int{{{1}}};", "successful", 159)
        )

    def test_060(self):
        """Error: variable declaration missing initializer"""
        self.assertTrue(
            TestParser.checkParser("var a;", "Error on line 1 col 5: ;", 160)
        )

    def test_061(self):
        """Error: variable declaration with illegal literal form"""
        self.assertTrue(
            TestParser.checkParser("var a = {1, 2};", "Error on line 1 col 8: {", 161)
        )

    def test_062(self):
        """Literal: constant float literal"""
        self.assertTrue(
            TestParser.checkParser("const pi = 3.1415;", "successful", 162)
        )

    def test_063(self):
        """Literal: constant wtf"""
        self.assertTrue(
            TestParser.checkParser("const a = [1]ID{Votien{}};", "successful", 163)
        )

    def test_064(self):
        """Error: illegal escape sequence in string literal"""
        self.assertTrue(
            TestParser.checkParser("const s = \"Hello\\q\";", "\"Hello\\q", 164)
        )

    def test_065(self):
        """Error: unclosed string literal"""
        self.assertTrue(
            TestParser.checkParser("const s = \"Hello", "\"Hello", 165)
        )

    def test_066(self):
        """Literal: valid string literal with escape sequence"""
        self.assertTrue(
            TestParser.checkParser("const s = \"Hello\\nWorld\";", "successful", 166)
        )

    def test_067(self):
        """Declaration: array literal declaration"""
        self.assertTrue(
            TestParser.checkParser("var arr = [3]int{1,2,3};", "successful", 167)
        )

    def test_068(self):
        """Declaration: array variable declaration with initializer"""
        self.assertTrue(
            TestParser.checkParser("var arr [2]int = [2]int{1, 2};", "successful", 168)
        )

    def test_069(self):
        """Literal: struct literal variable declaration"""
        self.assertTrue(
            TestParser.checkParser("var person = Person{name: \"John\", age: 25};", "successful", 169)
        )

    def test_070(self):
        """Literal: nested struct literal variable declaration"""
        self.assertTrue(
            TestParser.checkParser("var rec = Rectangle{topLeft: Point{x:0, y:0}, bottomRight: Point{x:10, y:10}};", "successful", 170)
        )

    def test_071(self):
        """Declaration: function that multiplies two integers"""
        self.assertTrue(
            TestParser.checkParser("func Multiply(a int, b int) int { return a * b; };", "successful", 171)
        )

    def test_072(self):
        """Declaration: function with string parameter and no return type"""
        self.assertTrue(
            TestParser.checkParser("func Print(a string) { return; };", "successful", 172)
        )

    def test_073(self):
        """Expression: function call inside an arithmetic expression"""
        self.assertTrue(
            TestParser.checkParser("var result = Multiply(3, 14) + 2;", "successful", 173)
        )

    def test_074(self):
        """Expression: array access on a previously declared array"""
        self.assertTrue(
            TestParser.checkParser("var element = arr[1];", "successful", 174)
        )

    def test_075(self):
        """Expression: field access on a struct variable"""
        self.assertTrue(
            TestParser.checkParser("var name = person.name;", "successful", 175)
        )

    def test_076(self):
        """Expression: complex arithmetic expression with parentheses"""
        self.assertTrue(
            TestParser.checkParser("var comp = (a + b) * (c - d) / e;", "successful", 176)
        )

    def test_077(self):
        """Expression: method call on an object"""
        self.assertTrue(
            TestParser.checkParser("var ret = obj.method(1,2);", "successful", 177)
        )

    def test_078(self):
        """Expression: chained method calls"""
        self.assertTrue(
            TestParser.checkParser("var ret = obj.getA().getB().do();", "successful", 178)
        )

    def test_079(self):
        """Statement: compound assignment with arithmetic operators"""
        self.assertTrue(
            TestParser.checkParser("a += b * c - d / e;", "successful", 179)
        )

    def test_080(self):
        """Literal: constant boolean expression with logical operators"""
        self.assertTrue(
            TestParser.checkParser("const flag = false && true || false;", "successful", 180)
        )

    def test_081(self):
        """Expression: chained relational operators"""
        self.assertTrue(
            TestParser.checkParser("var rel = a == b != c < d <= e > f >= g;", "successful", 181)
        )

    def test_082(self):
        """Expression: logical operators with grouping"""
        self.assertTrue(
            TestParser.checkParser("var logic = (a && b) || (!c);", "successful", 182)
        )

    def test_083(self):
        """Expression: use of unary minus operator"""
        self.assertTrue(
            TestParser.checkParser("var neg = -a + (-b);", "successful", 183)
        )

    def test_084(self):
        """Expression: multiple nested parentheses"""
        self.assertTrue(
            TestParser.checkParser("var paren = (((a)));", "successful", 184)
        )

    def test_085(self):
        """Statement: if statement without else clause"""
        self.assertTrue(
            TestParser.checkParser("func Check() { if (a > 0) { return; } };", "successful", 185)
        )

    def test_086(self):
        """Statement: for loop with minimal header"""
        self.assertTrue(
            TestParser.checkParser("func Loop() { for i < 10 { return; } };", "successful", 186)
        )

    def test_087(self):
        """Statement: for loop with complete header"""
        self.assertTrue(
            TestParser.checkParser("func Loop() { for i := 0; i < 5; i += 1 { return; } };", "successful", 187)
        )

    def test_088(self):
        """Statement: for loop using range clause with two identifiers"""
        self.assertTrue(
            TestParser.checkParser("""
                func Iterate() { 
                    for key, value := range array {
                        return;
                    } 
                }
                """, "successful", 188)
        )

    def test_089(self):
        """Declaration: function with return statement returning an integer literal"""
        self.assertTrue(
            TestParser.checkParser("func GetValue() int { return 42; };", "successful", 189)
        )

    def test_090(self):
        """Statement: for loop with if-else inside, using break and continue"""
        self.assertTrue(
            TestParser.checkParser("""
                func Process() { 
                    for i := 0; i < 10; i += 1 { 
                        if (i == 5) { 
                            break; 
                        } else { 
                            continue; 
                        } 
                    } 
                };""", "successful", 190)
        )

    def test_091(self):
        """Expression: nested function calls as part of an expression"""
        self.assertTrue(
            TestParser.checkParser("var nested = foo(bar(1, 2), baz(3));", "successful", 191)
        )

    def test_092(self):
        """Statement: assignment to an array element"""
        self.assertTrue(
            TestParser.checkParser("arr[0] := 100;", "successful", 192)
        )

    def test_093(self):
        """Statement: assignment to a struct field"""
        self.assertTrue(
            TestParser.checkParser("person.age := person.age + 1;", "successful", 193)
        )

    def test_094(self):
        """Declaration: multiple sequential variable declarations"""
        input_str = """
            var a int = 1;
            var b int = 2;
            var c int = a + b;
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 194)
        )

    def test_095(self):
        """Literal: constant string declaration"""
        self.assertTrue(
            TestParser.checkParser("const greeting = \"Hello, World!\";", "successful", 195)
        )

    def test_096(self):
        """Declaration: struct type with two fields"""
        input_str = """
            type Point struct {
                x int;
                y int;
            }
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 196)
        )

    def test_097(self):
        """Declaration: interface type with one method"""
        input_str = """
            type Drawable interface {
                Draw();
            }
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 197)
        )

    def test_098(self):
        """Declaration: interface type with method returning a float"""
        input_str = """
            type Shape interface {
                Area() float;
            }
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 198)
        )

    def test_099(self):
        """Declaration: method declaration with a receiver on a struct type"""
        input_str = """
            func (p Point) Distance(q Point) float { return 0.0; }
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 199)
        )

    def test_100(self):
        """Declaration: function calling a function and a method"""
        input_str = """
            func votien() {
                foo(1, 2);
                a[2].foo(1,3);
            }
        """
        self.assertTrue(
            TestParser.checkParser(input_str, "successful", 200)
        )