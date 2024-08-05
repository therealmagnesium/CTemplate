local outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project("Application")
kind("ConsoleApp")
language("C")

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../build/" .. outputdir .. "/%{prj.name}")

files({
	"source/**.h",
	"source/**.c",
})

includedirs({
	"../App-Core/source",
	"../vendor/glad/include",
	"../vendor/cglm/",
	"../vendor/nuklear/include",
	"../vendor/stb_image/include",
})

libdirs({
	"../vendor/glad/lib",
	"../vendor/nuklear/lib",
	"../vendor/stb_image/lib",
})

links({
	"App-Core",
	"SDL2",
	"glad",
	"m",
	"nuklear",
	"stb_image",
})

postbuildcommands({
	"cp -r assets/ %{cfg.buildtarget.directory}",
})

filter("system:Unix")
system("linux")
cdialect("C17")
systemversion("latest")
defines({
	"PLATFORM_LINUX",
})

filter("configurations:Debug")
defines("DEBUG")
symbols("on")

filter("configurations:Release")
defines("RELEASE")
optimize("on")

filter("configurations:Dist")
defines("DIST")
optimize("on")
kind("WindowedApp")
