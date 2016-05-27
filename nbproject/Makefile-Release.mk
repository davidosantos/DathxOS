#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/DathxLib/Drivers.o \
	${OBJECTDIR}/system/Cmos.o \
	${OBJECTDIR}/system/DathxMain.o \
	${OBJECTDIR}/system/Interrupts.o \
	${OBJECTDIR}/system/RunTime/ElfLoader.o \
	${OBJECTDIR}/system/RunTime/IRQHandler.o \
	${OBJECTDIR}/system/RunTime/SysCallHandler.o \
	${OBJECTDIR}/system/Start.o \
	${OBJECTDIR}/system/Tasks/Tasks.o \
	${OBJECTDIR}/system/autoCheck.o \
	${OBJECTDIR}/system/drivers/APIC.o \
	${OBJECTDIR}/system/drivers/Chip8259.o \
	${OBJECTDIR}/system/drivers/DriverLoader.o \
	${OBJECTDIR}/system/drivers/HardDriveDriver.o \
	${OBJECTDIR}/system/drivers/HardwareIO.o \
	${OBJECTDIR}/system/fs/FAT32.o \
	${OBJECTDIR}/system/fs/File.o \
	${OBJECTDIR}/system/fs/MBR.o \
	${OBJECTDIR}/system/memory/Memory.o \
	${OBJECTDIR}/system/memory/Paging.o \
	${OBJECTDIR}/system/memory/pageManagment.o \
	${OBJECTDIR}/system/monitor/Console.o \
	${OBJECTDIR}/system/processor.o \
	${OBJECTDIR}/util/util.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dathx_os

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dathx_os: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dathx_os ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/DathxLib/Drivers.o: DathxLib/Drivers.cpp 
	${MKDIR} -p ${OBJECTDIR}/DathxLib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DathxLib/Drivers.o DathxLib/Drivers.cpp

${OBJECTDIR}/system/Cmos.o: system/Cmos.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/Cmos.o system/Cmos.cpp

${OBJECTDIR}/system/DathxMain.o: system/DathxMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/DathxMain.o system/DathxMain.cpp

${OBJECTDIR}/system/Interrupts.o: system/Interrupts.asm 
	${MKDIR} -p ${OBJECTDIR}/system
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/system/Interrupts.o system/Interrupts.asm

${OBJECTDIR}/system/RunTime/ElfLoader.o: system/RunTime/ElfLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/RunTime
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/RunTime/ElfLoader.o system/RunTime/ElfLoader.cpp

${OBJECTDIR}/system/RunTime/IRQHandler.o: system/RunTime/IRQHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/RunTime
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/RunTime/IRQHandler.o system/RunTime/IRQHandler.cpp

${OBJECTDIR}/system/RunTime/SysCallHandler.o: system/RunTime/SysCallHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/RunTime
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/RunTime/SysCallHandler.o system/RunTime/SysCallHandler.cpp

${OBJECTDIR}/system/Start.o: system/Start.asm 
	${MKDIR} -p ${OBJECTDIR}/system
	$(AS) $(ASFLAGS) -o ${OBJECTDIR}/system/Start.o system/Start.asm

${OBJECTDIR}/system/Tasks/Tasks.o: system/Tasks/Tasks.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/Tasks
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/Tasks/Tasks.o system/Tasks/Tasks.cpp

${OBJECTDIR}/system/autoCheck.o: system/autoCheck.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/autoCheck.o system/autoCheck.cpp

${OBJECTDIR}/system/drivers/APIC.o: system/drivers/APIC.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/drivers
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/drivers/APIC.o system/drivers/APIC.cpp

${OBJECTDIR}/system/drivers/Chip8259.o: system/drivers/Chip8259.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/drivers
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/drivers/Chip8259.o system/drivers/Chip8259.cpp

${OBJECTDIR}/system/drivers/DriverLoader.o: system/drivers/DriverLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/drivers
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/drivers/DriverLoader.o system/drivers/DriverLoader.cpp

${OBJECTDIR}/system/drivers/HardDriveDriver.o: system/drivers/HardDriveDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/drivers
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/drivers/HardDriveDriver.o system/drivers/HardDriveDriver.cpp

${OBJECTDIR}/system/drivers/HardwareIO.o: system/drivers/HardwareIO.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/drivers
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/drivers/HardwareIO.o system/drivers/HardwareIO.cpp

${OBJECTDIR}/system/fs/FAT32.o: system/fs/FAT32.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/fs
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/fs/FAT32.o system/fs/FAT32.cpp

${OBJECTDIR}/system/fs/File.o: system/fs/File.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/fs
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/fs/File.o system/fs/File.cpp

${OBJECTDIR}/system/fs/MBR.o: system/fs/MBR.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/fs
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/fs/MBR.o system/fs/MBR.cpp

${OBJECTDIR}/system/memory/Memory.o: system/memory/Memory.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/memory
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/memory/Memory.o system/memory/Memory.cpp

${OBJECTDIR}/system/memory/Paging.o: system/memory/Paging.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/memory
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/memory/Paging.o system/memory/Paging.cpp

${OBJECTDIR}/system/memory/pageManagment.o: system/memory/pageManagment.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/memory
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/memory/pageManagment.o system/memory/pageManagment.cpp

${OBJECTDIR}/system/monitor/Console.o: system/monitor/Console.cpp 
	${MKDIR} -p ${OBJECTDIR}/system/monitor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/monitor/Console.o system/monitor/Console.cpp

${OBJECTDIR}/system/processor.o: system/processor.cpp 
	${MKDIR} -p ${OBJECTDIR}/system
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/system/processor.o system/processor.cpp

${OBJECTDIR}/util/util.o: util/util.cpp 
	${MKDIR} -p ${OBJECTDIR}/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/util/util.o util/util.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dathx_os

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
