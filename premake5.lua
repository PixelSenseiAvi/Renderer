solution "Renderer"
	
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "GameEngine/extlib/GLFW/include"
IncludeDir["Glad"] = "GameEngine/extlib/Glad/include"
IncludeDir["glm"] = "GameEngine/extlib/glm"
IncludeDir["ImGui"] = "GameEngine/extlib/imgui"
IncludeDir["assimp"] = "GameEngine/extlib/assimp/include"
IncludeDir["stb_image"] = "GameEngine/extlib/stb_image"

group "Dependencies"
	include "GameEngine/extlib/GLFW"
	include "GameEngine/extlib/Glad"
	include "GameEngine/extlib/imgui"
	include "GameEngine/extlib/assimp"
group ""


project "GameEngine"
	location "GameEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "enpch.h"
	pchsource "GameEngine/src/enpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/extlib/stb_image/stb_image.h",
		"%{prj.name}/extlib/stb_image/stb_image.cpp",
		"%{prj.name}/extlib/glm/glm/**.hpp",
		"%{prj.name}/extlib/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/extlib/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"assimp",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"EN_PLATFORM_WINDOWS", 
			"EN_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/")		
		}
	
	filter "configurations:Debug"
		defines "EN_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "EN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "EN_DIST"
		optimize "On"


project "Sandbox"

	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"GameEngine/extlib/spdlog/include",
		"%{IncludeDir.glm}",
		"GameEngine/src"
	}

	links
	{
		"GameEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"EN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EN_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "EN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "EN_DIST"
		optimize "On"