.PHONY: clean All Project_Title Project_Build Project_PostBuild

All: Project_Title Project_Build Project_PostBuild

Project_Title:
	@echo "----------Building project:[ txw4002a - BuildSet ]----------"

Project_Build:
	@make -r -f txw4002a.mk -j 16 -C  ./ 

Project_PostBuild:
	@echo Executing Post Build commands ...
	@export CDKPath="C:/Users/29076/AppData/Roaming/C-Sky/CDK" CDK_VERSION="V2.8.8" ProjectPath="C:/nonos/hgSDK-v1.6.4.3-29063-wnb/project/" && cmd /c BuildBIN.bat
	@echo Done


clean:
	@echo "----------Cleaning project:[ txw4002a - BuildSet ]----------"

