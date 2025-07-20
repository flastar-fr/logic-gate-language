add_rules("mode.debug", "mode.release")
set_languages("c++17")

add_requires("gtest 1.16", {configs = {main = false}, system = false})

target("circuit-descriptor-language")
    set_kind("binary")
    add_files("src/*.cpp")

target("tests")
    set_kind("binary")
    add_files("tests/**.cpp")
    add_includedirs("tests")
    add_packages("gtest")
