add_rules("mode.debug", "mode.release")
set_languages("c++17")

add_requires("gtest 1.16", {configs = {main = false}, system = false})

add_includedirs("src", {public = true})

target("logic-gate-lib")
    set_kind("static")
    add_files("src/**.cpp")
    remove_files("src/main.cpp")

target("logic-gate-language")
    set_kind("binary")
    add_files("src/main.cpp")
    add_deps("logic-gate-lib")

target("tests")
    set_kind("binary")
    add_files("tests/**.cpp")
    add_includedirs("tests")
    add_packages("gtest")
    add_deps("logic-gate-lib")
