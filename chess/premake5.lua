workspace "chess"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "chess"
	location "chess"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin_obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h"
		"%{prj.name}/src/**.cpp"
	}

	include
	{
		"Dependencies/glfw/include",
		"Dependencies/glew/include",
		"Dependencies/glm/glm",
		"%{prj.name}/src/vendor"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			GLEW_STATIC;
		}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
	
	filter "system:not windows"
		defines
		{
			GLEW_STATIC;
		}