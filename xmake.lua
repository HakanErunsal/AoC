add_rules("mode.debug", "mode.release")

set_languages("c++20")

set_version("1.0.0")

target("AoC")
    set_kind("binary")
    add_files("src/*.cpp")
    add_deps("Trebuchet")


target("Trebuchet")
set_kind("static")
add_files("src/Trebuchet/*.cpp")
after_build(function(target)
    os.cp("Content/*.txt", path.join(target:targetdir(), "Content"))
end)

target("CubeConundrum")
set_kind("static")
add_files("src/CubeConundrum/*.cpp")
after_build(function(target)
    os.cp("Content/*.txt", path.join(target:targetdir(), "Content"))
end)

target("GearRatios")
set_kind("static")
add_files("src/GearRatios/*.cpp")
after_build(function(target)
    os.cp("Content/*.txt", path.join(target:targetdir(), "Content"))
end)