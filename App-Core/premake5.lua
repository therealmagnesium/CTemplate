local outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project("App-Core")
kind("StaticLib")
language("C")

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../build/" .. outputdir .. "/%{prj.name}")

files({
    "source/**.h",
    "source/**.c",
})

includedirs({
    "source",
    "../vendor/glad/include",
    "../vendor/cglm",
    "../vendor/nuklear/include",
})

libdirs({
    "../vendor/glad/lib",
    "../vendor/nuklear/lib",
})

links({
    "SDL2",
    "glad",
    "m",
    "nuklear",
})

filter("system:Unix")
system("linux")
cdialect("C17")
systemversion("latest")
defines({
    "PLATFORM_LINUX",
})

filter({ "configurations:Debug" })
defines("DEBUG")
symbols("on")

filter({ "configurations:Release" })
defines("RELEASE")
optimize("on")

filter({ "configurations:Dist" })
defines("DIST")
optimize("on")
