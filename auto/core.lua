--------------------------------------------------------------
-- Define core static lib for producers and consumers to use.
project("AssetPipelineCore")
	kind("SharedLib")
	language("C++")
	Platform_SetCppDialect()

	location(path.join(RootPath, "build"))

	filter { "configurations:Debug" }
		objdir(path.join(RootPath, "build/obj/Debug"))
		targetdir(path.join(RootPath, "build/bin/Debug"))
	filter { "configurations:Release" }
		objdir(path.join(RootPath, "build/obj/Release"))
		targetdir(path.join(RootPath, "build/bin/Release"))
	filter {}

	defines {
		"CORE_BUILD_SHARED"
	}

	if ChoosePlatform == "Android" then
		defines {
			"CD_PLATFORM_ANDROID"
		}
		
		linkoptions("-lm")
	else
		defines {
			"CD_PLATFORM_WINDOWS"
		}		
	end

	files {
		path.join(RootPath, "public/**.*"),
		path.join(RootPath, "private/**.*"),
	}
	
	removefiles {
		path.join(RootPath, "public/Producers/*/**.*"),
		path.join(RootPath, "public/Consumers/*/**.*"),
		path.join(RootPath, "private/Producers/*/**.*"),
		path.join(RootPath, "private/Consumers/*/**.*"),
	}

	vpaths {
		["Public/*"] = { 
			path.join(RootPath, "public/**.*"),
		},
		["Private/*"] = {
			path.join(RootPath, "private/**.*"),
		}
	}
	
	includedirs {
		path.join(RootPath, "public"),
	}