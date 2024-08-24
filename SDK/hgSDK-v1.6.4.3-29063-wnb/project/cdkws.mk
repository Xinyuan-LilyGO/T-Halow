.PHONY: clean All Project_Title Project_Build Project_PostBuild

All: Project_Title Project_Build Project_PostBuild

Project_Title:
	@echo "----------Building project:[ txw4002a - BuildSet ]----------"

Project_Build:
	@make -r -f txw4002a.mk -j 12 -C  ./ 

Project_PostBuild:
	@echo Executing Post Build commands ...
	@export CDKPath="D:/app1/C-Sky/CDK" CDK_VERSION="V2.24.0" ProjectName="txw4002a" ProjectPath="D:/dgx/code/T-Halow/SDK/hgSDK-v1.6.4.3-29063-wnb/project/" && cmd /c BuildBIN.bat
	@echo Done


clean:
	@echo "----------Cleaning project:[ txw4002a - BuildSet ]----------"

