##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=SDT
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :="C:/Users/FRDEMOLINSM/OneDrive - Tetra Pak/Dev/SDT"
ProjectPath            :="C:/Users/FRDEMOLINSM/OneDrive - Tetra Pak/Dev/SDT"
IntermediateDirectory  :=build-$(WorkspaceConfiguration)
OutDir                 :=$(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=FRDEMOLINSM
Date                   :=15/10/2022
CodeLitePath           :="C:/Program Files/CodeLite"
MakeDirCommand         :=mkdir
LinkerName             :=C:/TDM-GCC-64/bin/g++.exe
SharedObjectLinkerName :=C:/TDM-GCC-64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=C:/Users/FRDEMOLINSM/OneDrive - Tetra Pak/Dev/SDT/build-$(WorkspaceConfiguration)/bin
OutputFile             :=build-$(WorkspaceConfiguration)\bin\$(ProjectName).exe
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=C:/TDM-GCC-64/bin/windres.exe
LinkOptions            := -Dmain=SDL_main -DSDL_MAIN_HANDLED -O0
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../SDL2-2.0.22/x86_64-w64-mingw32/include/SDL2 $(IncludeSwitch)../SDL2_ttf-2.20.0/x86_64-w64-mingw32/include/SDL2 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)SDL2 $(LibrarySwitch)SDL2main $(LibrarySwitch)SDL2_ttf 
ArLibs                 :=  "SDL2" "SDL2main" "SDL2_ttf" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../SDL2-2.0.22/x86_64-w64-mingw32/lib $(LibraryPathSwitch)../SDL2_ttf-2.20.0/x86_64-w64-mingw32/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := C:/TDM-GCC-64/bin/ar.exe rcu
CXX      := C:/TDM-GCC-64/bin/g++.exe
CC       := C:/TDM-GCC-64/bin/gcc.exe
CXXFLAGS :=   $(Preprocessors)
CFLAGS   := -Wall -Wextra -std=gnu11 -Wshadow -g $(Preprocessors)
ASFLAGS  := 
AS       := C:/TDM-GCC-64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/StateWelcome.c$(ObjectSuffix) $(IntermediateDirectory)/StateDisplayTrend.c$(ObjectSuffix) $(IntermediateDirectory)/Quit.c$(ObjectSuffix) $(IntermediateDirectory)/Error.c$(ObjectSuffix) $(IntermediateDirectory)/State.c$(ObjectSuffix) $(IntermediateDirectory)/Graphlib.c$(ObjectSuffix) $(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/Button.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	cp ../SDL2-2.0.22/x86_64-w64-mingw32/bin/SDL2.dll ./build-Debug/bin/
	cp ../SDL2_ttf-2.20.0/x86_64-w64-mingw32/bin/SDL2_ttf.dll ./build-Debug/bin/
	@echo Done

MakeIntermediateDirs:
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"
	@if not exist "$(OutputDirectory)" $(MakeDirCommand) "$(OutputDirectory)"

$(IntermediateDirectory)/.d:
	@if not exist "$(IntermediateDirectory)" $(MakeDirCommand) "$(IntermediateDirectory)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/StateWelcome.c$(ObjectSuffix): StateWelcome.c $(IntermediateDirectory)/StateWelcome.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/FRDEMOLINSM/OneDrive - Tetra Pak/Dev/SDT/StateWelcome.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StateWelcome.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StateWelcome.c$(DependSuffix): StateWelcome.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StateWelcome.c$(ObjectSuffix) -MF$(IntermediateDirectory)/StateWelcome.c$(DependSuffix) -MM StateWelcome.c

$(IntermediateDirectory)/StateWelcome.c$(PreprocessSuffix): StateWelcome.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StateWelcome.c$(PreprocessSuffix) StateWelcome.c

$(IntermediateDirectory)/StateDisplayTrend.c$(ObjectSuffix): StateDisplayTrend.c $(IntermediateDirectory)/StateDisplayTrend.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/FRDEMOLINSM/OneDrive - Tetra Pak/Dev/SDT/StateDisplayTrend.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StateDisplayTrend.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StateDisplayTrend.c$(DependSuffix): StateDisplayTrend.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StateDisplayTrend.c$(ObjectSuffix) -MF$(IntermediateDirectory)/StateDisplayTrend.c$(DependSuffix) -MM StateDisplayTrend.c

$(IntermediateDirectory)/StateDisplayTrend.c$(PreprocessSuffix): StateDisplayTrend.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StateDisplayTrend.c$(PreprocessSuffix) StateDisplayTrend.c

$(IntermediateDirectory)/Quit.c$(ObjectSuffix): Quit.c $(IntermediateDirectory)/Quit.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/FRDEMOLINSM/OneDrive - Tetra Pak/Dev/SDT/Quit.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Quit.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Quit.c$(DependSuffix): Quit.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Quit.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Quit.c$(DependSuffix) -MM Quit.c

$(IntermediateDirectory)/Quit.c$(PreprocessSuffix): Quit.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Quit.c$(PreprocessSuffix) Quit.c

$(IntermediateDirectory)/Error.c$(ObjectSuffix): Error.c $(IntermediateDirectory)/Error.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/FRDEMOLINSM/OneDrive - Tetra Pak/Dev/SDT/Error.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Error.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Error.c$(DependSuffix): Error.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Error.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Error.c$(DependSuffix) -MM Error.c

$(IntermediateDirectory)/Error.c$(PreprocessSuffix): Error.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Error.c$(PreprocessSuffix) Error.c

$(IntermediateDirectory)/State.c$(ObjectSuffix): State.c $(IntermediateDirectory)/State.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/FRDEMOLINSM/OneDrive - Tetra Pak/Dev/SDT/State.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/State.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/State.c$(DependSuffix): State.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/State.c$(ObjectSuffix) -MF$(IntermediateDirectory)/State.c$(DependSuffix) -MM State.c

$(IntermediateDirectory)/State.c$(PreprocessSuffix): State.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/State.c$(PreprocessSuffix) State.c

$(IntermediateDirectory)/Graphlib.c$(ObjectSuffix): Graphlib.c $(IntermediateDirectory)/Graphlib.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/FRDEMOLINSM/OneDrive - Tetra Pak/Dev/SDT/Graphlib.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Graphlib.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Graphlib.c$(DependSuffix): Graphlib.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Graphlib.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Graphlib.c$(DependSuffix) -MM Graphlib.c

$(IntermediateDirectory)/Graphlib.c$(PreprocessSuffix): Graphlib.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Graphlib.c$(PreprocessSuffix) Graphlib.c

$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/FRDEMOLINSM/OneDrive - Tetra Pak/Dev/SDT/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c

$(IntermediateDirectory)/Button.c$(ObjectSuffix): Button.c $(IntermediateDirectory)/Button.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/Users/FRDEMOLINSM/OneDrive - Tetra Pak/Dev/SDT/Button.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Button.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Button.c$(DependSuffix): Button.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Button.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Button.c$(DependSuffix) -MM Button.c

$(IntermediateDirectory)/Button.c$(PreprocessSuffix): Button.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Button.c$(PreprocessSuffix) Button.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


