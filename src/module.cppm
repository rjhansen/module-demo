module;

import std;

export module ModuleTest;

std::string ebenezar() {
    return "Ebenezar McCoy";
}

export void greet() {
    std::println("Hello, Wizard {}!", ebenezar());
}
