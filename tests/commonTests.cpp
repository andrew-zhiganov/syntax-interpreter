#define CATCH_CONFIG_MAIN

#include "catch.h"

#include "../main.tpp"
#include "../messages.tpp"


SCENARIO("Ошибка! Отсутствует var"){
    GIVEN("qwer, vare, qwqw :integer;"){
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/1.txt");
            THEN("Код ошибки 1 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 1);
                REQUIRE(Message(exitCode) == "var expected");
            }
        }
    }
}

SCENARIO("Ошибка! Ожидается идентификатор"){
    GIVEN("var qwer, vare,:integer;") {
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/2.txt");
            THEN("Код ошибки 2 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 2);
                REQUIRE(Message(exitCode) == "identifier expected");
            }
        }
    }
}

SCENARIO("Ошибка! Ожидается идентификатор (отсутствуют вообще)"){
    GIVEN("var :integer;") {
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/3.txt");
            THEN("Код ошибки 2 и функция Message выдает то же сообщение") {
                REQUIRE(exitCode == 2);
                REQUIRE(Message(exitCode) == "identifier expected");
            }
        }
    }
}

SCENARIO("Ошибка! Повторное объявление"){
    GIVEN("var qwert, asd, qwert :integer;") {
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/4.txt");
            THEN("Код ошибки 3 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 3);
                REQUIRE(Message(exitCode) == "duplicate declaration");
            }
        }
    }
}

SCENARIO("Ошибка! Превышение длины идентификатора"){
    GIVEN("var qwertyqwerty :integer;") {
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/5.txt");
            THEN("Код ошибки 4 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 4);
                REQUIRE(Message(exitCode) == "expected max length of identifier to be 11");
            }
        }
    }
}

SCENARIO("Ошибка! Неверное имя идентификатора"){
    GIVEN("var qwerty12 :integer;") {
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/6.txt");
            THEN("Код ошибки 5 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 5);
                REQUIRE(Message(exitCode) == "wrong identifier");
            }
        }
    }
}

SCENARIO("Ошибка! Использование служебных слов для имени идентификатора"){
    GIVEN("var begin :integer;") {
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/7.txt");
            THEN("Код ошибки 5 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 5);
                REQUIRE(Message(exitCode) == "wrong identifier");
            }
        }
    }
}

SCENARIO("Ошибка! Ожидается , или :"){
    GIVEN("var asda. qwer :integer;") {
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/8.txt");
            THEN("Код ошибки 6 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 6);
                REQUIRE(Message(exitCode) == ", or : expected");
            }
        }
    }
}

SCENARIO("Ошибка! Ожидается integer"){
    GIVEN("var a, qwer : integar;") {
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/9.txt");
            THEN("Код ошибки 7 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 7);
                REQUIRE(Message(exitCode) == "integer expected");
            }
        }
    }
}

SCENARIO("Ошибка! Ожидается ;"){
    GIVEN("var a, qwer : integer") {
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/10.txt");
            THEN("Код ошибки 8 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 8);
                REQUIRE(Message(exitCode) == "; expected");
            }
        }
    }
}

SCENARIO("Ошибка! Ожидается begin"){
    GIVEN("var a, qwer : integer;"
                  "began"){
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/11.txt");
            THEN("Код ошибки 9 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 9);
                REQUIRE(Message(exitCode) == "begin expected");
            }
        }
    }
}

SCENARIO("Ошибка! Неизвестный идентификатор"){
    GIVEN("var a : integer;"
                  "begin"
                  "b = 5;"){
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/12.txt");
            THEN("Код ошибки 10 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 10);
                REQUIRE(Message(exitCode) == "unknown identifier");
            }
        }
    }
}

SCENARIO("Ошибка! Ожидается ="){
    GIVEN("var a : integer;"
                  "begin"
                  "a + 5;"){
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/13.txt");
            THEN("Код ошибки 11 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 11);
                REQUIRE(Message(exitCode) == "= expected");
            }
        }
    }
}

SCENARIO("Ошибка! Ожидается ; в конце присваивания"){
    GIVEN("var a : integer;"
                  "begin"
                  "a = 5"){
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/14.txt");
            THEN("Код ошибки 8 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 8);
                REQUIRE(Message(exitCode) == "; expected");
            }
        }
    }
}

SCENARIO("Верный сценарий 1 (easy)"){
    GIVEN("var a : integer;"
                  "begin"
                  "a = 5;"
                  "end"){
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/15.txt");
            THEN("Код ошибки 0 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 0);
                REQUIRE(Message(exitCode) == "The program is correct");
            }
        }
    }
}

SCENARIO("Верный сценарий 2 (easy)"){
    GIVEN("var a, b : integer;"
                  "begin"
                  "a = 5;"
                  "b = 45;"
                  "a = b + b;"
                  "b = a / b;"
                  "end"){
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/16.txt");
            THEN("Код ошибки 0 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 0);
                REQUIRE(Message(exitCode) == "The program is correct");
            }
        }
    }
}

SCENARIO("Верный сценарий 3 (hard)"){
    GIVEN("var a, b, c : integer;"
                  "begin"
                  "a = (5 + 23) - b + (c + 12);"
                  "c = -(a / 3)"
                  "end"){
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/17.txt");
            THEN("Код ошибки 0 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 0);
                REQUIRE(Message(exitCode) == "The program is correct");
            }
        }
    }
}

SCENARIO("Ошибка! Скобки не закрыты (не открыты)"){
    GIVEN("var a : integer;"
                  "begin"
                  "a = (5 + 4 - a)+(78 / 12;"){
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/18.txt");
            THEN("Код ошибки 13 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 13);
                REQUIRE(Message(exitCode) == "missing ( or )");
            }
        }
    }
}

SCENARIO("Ошибка! Отсутствует end"){
    GIVEN("var a : integer;"
                  "begin"
                  "a = (5 + 4 - a)+(78 / 12);"){
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/19.txt");
            THEN("Код ошибки 14 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 14);
                REQUIRE(Message(exitCode) == "end expected");
            }
        }
    }
}

SCENARIO("Ошибка! Недопустимый символ"){
    GIVEN("var a : integer;"
                  "begin"
                  "a = (5 + 4 * a)+(78 / 12);"){
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/20.txt");
            THEN("Код ошибки 12 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 12);
                REQUIRE(Message(exitCode) == "illegal symbol");
            }
        }
    }
}

SCENARIO("Ошибка! Неверное выражение"){
    GIVEN("var a : integer;"
                  "begin"
                  "a = (5 + + 4 + a)+(78 / 12);"){
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/21.txt");
            THEN("Код ошибки 15 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 15);
                REQUIRE(Message(exitCode) == "illegal expression");
            }
        }
    }
}

SCENARIO("Верный сценарий 4 (infinity)"){
    GIVEN("var a, b, c, d, e : integer;"
                  "begin"
                  "a = ((-(((5 + 23) - b + (c + 12)) / d - 35)) - e + 23) + 13 - (a / 23 - (12 + b));"
                  "c = -(a / 3);"
                  "end"){
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/22.txt");
            THEN("Код ошибки 0 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 0);
                REQUIRE(Message(exitCode) == "The program is correct");
            }
        }
    }
}

SCENARIO("Верный сценарий 5 (infinity)"){
    GIVEN("var a, "
                  "b, c, "
                  "d, e : integer;"
                  "begin"
                  "a = (-(-(((a + 44) / b - (a + 29 / e)) / d - 53)) + b - 83) - a - (d + 21 / (e - 29)) - (c / 34);"
                  "c = (-(a / 3) + (27 / a)) / (12 + (b - 16 / (27 - 32)) - (e -(e)));"
                  "end"){
        WHEN("Проверям правильность программы вызовом функции Proceed") {
            int exitCode = Proceed("/home/andrew/workspace/syntax-interpreter/tests/23.txt");
            THEN("Код ошибки 0 и функция Message выдает сообщение") {
                REQUIRE(exitCode == 0);
                REQUIRE(Message(exitCode) == "The program is correct");
            }
        }
    }
}
